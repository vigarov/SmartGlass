package com.smartglass.smartglassapp


import android.Manifest
import android.annotation.SuppressLint
import android.bluetooth.*
import android.bluetooth.le.ScanCallback
import android.bluetooth.le.ScanResult
import android.bluetooth.le.ScanSettings
import android.content.Context
import android.content.pm.PackageManager
import android.os.Build
import android.os.Bundle
import android.os.Handler
import android.os.Looper
import android.util.Log
import android.widget.Button
import androidx.annotation.RequiresApi
import androidx.core.app.ActivityCompat
import androidx.core.content.ContextCompat
import androidx.recyclerview.widget.LinearLayoutManager
import androidx.recyclerview.widget.RecyclerView
import androidx.recyclerview.widget.SimpleItemAnimator
import com.smartglass.smartglassapp.databinding.ActivityBluetoothBinding
import kotlinx.android.synthetic.main.activity_bluetooth.*
import java.util.*

@SuppressLint("MissingPermission")
@RequiresApi(Build.VERSION_CODES.S)

class BluetoothActivity : MainActivity() {
    //--------------------------------------------------------
    //Private Variables Below



    companion object {
        //Permission Codes
        const val BLUETOOTH_PERMISSION: Int = 100
        const val BLUETOOTH_ADMIN_PERMISSION: Int = 101
        const val BLUETOOTH_CONNECT_PERMISSION: Int = 102
        const val BLUETOOTH_SCAN_PERMISSION: Int = 103
        private const val FINE_LOCATION_PERMISSION: Int = 104
        private const val COARSE_LOCATION_PERMISSION: Int = 105

        //Bluetooth UUIDs
        private const val SERVICE_UUID: String = "1e7b14e7-f5d9-4113-b249-d16b6ae7db7f"
        private const val BUFFER_ATTR_UUID: String = "8d5b53b8-fe04-4509-a689-82ab4c3d2507"
        private const val GATT_MAX_MTU_SIZE = 64
    }

    //Remember to set the notification lists up properly
    //When a new notification arrives, it will go to the end of the list
    //When a notification is sent, it will be deleted from the list
    //It should basically function as a queue. Make it so that when notifQueue changes, their is
    //a callback triggered which sends the data of the notification to the smart glasses. A
    //Notification class has already been defined by me. It also includes a method called
    //packForDelivery, which converts the Notification object into a ByteArray (which you can use
    //as argument for the writeDescriptor method, calling which will send this data to the connected
    //BLE device (in our case, the smart glasses)

    private lateinit var binding: ActivityBluetoothBinding

    private val bluetoothAdapter: BluetoothAdapter by lazy {
        val bluetoothManager = getSystemService(Context.BLUETOOTH_SERVICE) as BluetoothManager
        bluetoothManager.adapter
    }

    private val bleScanner by lazy {
        bluetoothAdapter.bluetoothLeScanner
    }

    private val scanCallback = object : ScanCallback() {
        @RequiresApi(Build.VERSION_CODES.S)
        override fun onScanResult(callbackType: Int, result: ScanResult) {
            val indexQuery = scanResults.indexOfFirst {it.device.address == result.device.address}
            if (indexQuery >= 0) { // A scan result already exists with the same address
                scanResults[indexQuery] = result
                scanResultAdapter.notifyItemChanged(indexQuery)
            }
            else{
                with(result.device) {
                    if (ActivityCompat.checkSelfPermission(
                            this@BluetoothActivity,
                            Manifest.permission.BLUETOOTH_CONNECT
                        ) != PackageManager.PERMISSION_GRANTED
                    ) {
                        checkPermission(
                            Manifest.permission.BLUETOOTH,
                            BLUETOOTH_PERMISSION
                        )
                        checkPermission(
                            Manifest.permission.BLUETOOTH_ADMIN,
                            BLUETOOTH_ADMIN_PERMISSION
                        )
                        checkPermission(
                            Manifest.permission.BLUETOOTH_CONNECT,
                            BLUETOOTH_CONNECT_PERMISSION
                        )
                        return
                    }
                    Log.d("ScanCallback", "Found BLE device! Name:" +
                            "${result.device.name ?: "Unnamed"}, address: $address")
                    scanResults.add(result)
                    scanResultAdapter.notifyItemInserted(scanResults.size - 1)
                }
            }

        }

        override fun onScanFailed(errorCode: Int) {
            Log.d("ScanCallback", "onScanFailed: code $errorCode")
        }
    }

    private val gattCallback = object : BluetoothGattCallback() {
        override fun onConnectionStateChange(gatt: BluetoothGatt, status: Int, newState: Int) {
            val deviceAddress = gatt.device.address
            stopBleScan()
            if (status == BluetoothGatt.GATT_SUCCESS) {
                when (newState) {
                    BluetoothProfile.STATE_CONNECTED -> {
                        Log.d(
                            "BluetoothGattCallback",
                            "Successfully connected to $deviceAddress"
                        )
                        btGatt = gatt
                        Handler(Looper.getMainLooper()).post {
                            btGatt.discoverServices()
                            btGatt.requestMtu(GATT_MAX_MTU_SIZE)
                        }

                    }
                    BluetoothProfile.STATE_DISCONNECTED -> {
                        Log.d(
                            "BluetoothGattCallback",
                            "Successfully disconnected from $deviceAddress"
                        )
                        gatt.close()
                    }
                    else -> {
                        Log.d("BluetoothGattCallback", "Something went wrong, not connected!")
                    }
                }
            } else {
                Log.d(
                    "BluetoothGattCallback",
                    "Error $status encountered for $deviceAddress! Disconnecting..."
                )
                gatt.close()
            }
        }

        override fun onServicesDiscovered(gatt: BluetoothGatt, status: Int) {
            with(gatt) {
                Log.d(
                    "BluetoothGattCallback",
                    "Discovered ${services.size} services for ${device.address}"
                )
                val service = btGatt.getService(
                    UUID.fromString(SERVICE_UUID)
                )
                val characteristic = service.getCharacteristic(
                    UUID.fromString(BUFFER_ATTR_UUID)
                )

                btGatt.setCharacteristicNotification(characteristic, true)

                val notification = Notification(
                    APP.SMS,
                    "System",
                    "Alert"
                )

                writeCharacteristic(characteristic, notification.packForDelivery())
            }
        }

        override fun onMtuChanged(gatt: BluetoothGatt, mtu: Int, status: Int) {
            Log.d(
                "MtuChanged",
                "ATT MTU changed to $mtu, success: ${status == BluetoothGatt.GATT_SUCCESS}"
            )
        }

        override fun onCharacteristicChanged(
            gatt: BluetoothGatt,
            characteristic: BluetoothGattCharacteristic
        ) {
            with(characteristic) {
                Log.d("BluetoothGattCallback", "Characteristic $uuid changed | value: $value")
                writeCharacteristic(
                    characteristic,
                    Notification(APP.SMS, "Joe", "Mama").packForDelivery()
                )
            }
        }
    }

    private lateinit var btGatt: BluetoothGatt

    private var isScanning: Boolean = false

    private val scanSettings by lazy {
        ScanSettings.Builder()
            .setScanMode(ScanSettings.SCAN_MODE_LOW_LATENCY).build()
    }
    private val scanResults = mutableListOf<ScanResult>()
    private val scanResultAdapter: ScanResultAdapter by lazy {
        ScanResultAdapter(scanResults) { result ->
            // User tapped on a scan result
            if (isScanning) {
                stopBleScan()
            }
            with(result.device) {
                Log.d("ScanResultAdapter", "Connecting to $address")
                if (ActivityCompat.checkSelfPermission(
                        this@BluetoothActivity,
                        Manifest.permission.BLUETOOTH_CONNECT
                    ) != PackageManager.PERMISSION_GRANTED
                ) {
                    checkPermission(
                        Manifest.permission.BLUETOOTH,
                        BLUETOOTH_PERMISSION
                    )
                    checkPermission(
                        Manifest.permission.BLUETOOTH_ADMIN,
                        BLUETOOTH_ADMIN_PERMISSION
                    )
                    checkPermission(
                        Manifest.permission.BLUETOOTH_CONNECT,
                        BLUETOOTH_CONNECT_PERMISSION
                    )
                    checkPermission(
                        Manifest.permission.BLUETOOTH_SCAN,
                        BLUETOOTH_SCAN_PERMISSION
                    )
                    return@ScanResultAdapter
                }
                connectGatt(this@BluetoothActivity, false, gattCallback)
                disconnect.setOnClickListener{closeConnection()}
            }
        }
    }

    //------------------------------------------------------------------------
    //Utility Functions Below

    private fun writeCharacteristic(characteristic: BluetoothGattCharacteristic, payload: ByteArray){
        btGatt.let { gatt ->
            characteristic.value = payload
            gatt.writeCharacteristic(characteristic)
        }
    }

    private fun closeConnection(){
        btGatt.close()
    }

    private fun checkPermission(permission: String, requestCode: Int){
        if(ContextCompat.checkSelfPermission(this@BluetoothActivity, permission)
            != PackageManager.PERMISSION_GRANTED)
        {
            ActivityCompat.requestPermissions(
                this@BluetoothActivity,
                arrayOf(permission),
                requestCode
            )
        }
        else{
            Log.d("checkPermission", "$permission granted!")
        }
    }

    private fun setupRecyclerView() {
        scan_results_recycler_view.apply {
            adapter = scanResultAdapter
            layoutManager = LinearLayoutManager(
                this@BluetoothActivity,
                RecyclerView.VERTICAL,
                false
            )
            isNestedScrollingEnabled = false
        }

        val animator = scan_results_recycler_view.itemAnimator
        if (animator is SimpleItemAnimator) {
            animator.supportsChangeAnimations = false
        }
    }

    @SuppressLint("NotifyDataSetChanged")
    @RequiresApi(Build.VERSION_CODES.S)
    private fun startBleScan(){
        if (ActivityCompat.checkSelfPermission(
                this,
                Manifest.permission.BLUETOOTH_SCAN
            ) != PackageManager.PERMISSION_GRANTED
        ) {
            checkPermission(Manifest.permission.BLUETOOTH, BLUETOOTH_PERMISSION)
            checkPermission(Manifest.permission.BLUETOOTH_ADMIN, BLUETOOTH_ADMIN_PERMISSION)
            checkPermission(Manifest.permission.BLUETOOTH_CONNECT, BLUETOOTH_CONNECT_PERMISSION)
            checkPermission(Manifest.permission.BLUETOOTH_SCAN, BLUETOOTH_SCAN_PERMISSION)
            return
        }
        scanResults.clear()
        scanResultAdapter.notifyDataSetChanged()
        bleScanner.startScan(null, scanSettings, scanCallback)
        isScanning = true
    }

    @RequiresApi(Build.VERSION_CODES.S)
    private fun stopBleScan() {
        if (ActivityCompat.checkSelfPermission(
                this,
                Manifest.permission.BLUETOOTH_SCAN
            ) != PackageManager.PERMISSION_GRANTED
        ) {
            checkPermission(Manifest.permission.BLUETOOTH_SCAN, BLUETOOTH_SCAN_PERMISSION)
        }
        bleScanner.stopScan(scanCallback)
        isScanning = false
    }

    //----------------------------------------------------
    //Android Stuff Below

    @RequiresApi(Build.VERSION_CODES.S)
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        binding = ActivityBluetoothBinding.inflate(layoutInflater)
        allocateActivityTitle("Bluetooth")
        setContentView(binding.root)

        isScanning = false

        val btPermissionsButton: Button? = findViewById(R.id.bluetooth_permissions)
        val bleConnectButton: Button? = findViewById(R.id.ble_connect)
        val locPermissionsButton: Button? = findViewById(R.id.location_permissions)

        btPermissionsButton?.setOnClickListener{
            checkPermission(Manifest.permission.BLUETOOTH, BLUETOOTH_PERMISSION)
            checkPermission(Manifest.permission.BLUETOOTH_ADMIN, BLUETOOTH_ADMIN_PERMISSION)
            checkPermission(Manifest.permission.BLUETOOTH_CONNECT, BLUETOOTH_CONNECT_PERMISSION)
            checkPermission(Manifest.permission.BLUETOOTH_SCAN, BLUETOOTH_SCAN_PERMISSION)
        }

        bleConnectButton?.setOnClickListener{
            Log.d("bleConnectButton", "Are we scanning? $isScanning")
            if(isScanning){
                Log.d("bleConnectButton", "Stopping Scan!")
                stopBleScan()
            }
            else{
                Log.d("bleConnectButton", "Starting Scan!")
                startBleScan()
            }
        }

        locPermissionsButton?.setOnClickListener{
            checkPermission(Manifest.permission.ACCESS_FINE_LOCATION, FINE_LOCATION_PERMISSION)
            checkPermission(Manifest.permission.ACCESS_COARSE_LOCATION, COARSE_LOCATION_PERMISSION)
        }

        setupRecyclerView()
    }

    override fun onRequestPermissionsResult(
        requestCode: Int,
        permissions: Array<out String>,
        grantResults: IntArray
    ) {
        super.onRequestPermissionsResult(requestCode, permissions, grantResults)
        if(requestCode == BLUETOOTH_PERMISSION){
            if(grantResults.isEmpty() || grantResults[0] != PackageManager.PERMISSION_GRANTED){
                Log.d("onRequestPermissionResult", "Bluetooth denied!")
            }
            else{
                Log.d("onRequestPermissionResult", "Bluetooth granted!")
            }
        }
        else if(requestCode == BLUETOOTH_ADMIN_PERMISSION){
            if(grantResults.isEmpty() || grantResults[0] != PackageManager.PERMISSION_GRANTED){
                Log.d("onRequestPermissionResult", "Bluetooth admin denied!")
            }
            else{
                Log.d("onRequestPermissionResult", "Bluetooth admin granted!")
            }
        }
        else if(requestCode == BLUETOOTH_CONNECT_PERMISSION){
            if(grantResults.isEmpty() || grantResults[0] != PackageManager.PERMISSION_GRANTED){
                Log.d("onRequestPermissionResult", "Bluetooth connect denied!")
            }
            else{
                Log.d("onRequestPermissionResult", "Bluetooth connect granted!")
            }
        }
        else if(requestCode == BLUETOOTH_SCAN_PERMISSION){
            if(grantResults.isEmpty() || grantResults[0] != PackageManager.PERMISSION_GRANTED){
                Log.d("onRequestPermissionResult", "Bluetooth scanning denied!")
            }
            else{
                Log.d("onRequestPermissionResult", "Bluetooth scanning granted!")
            }
        }
        else if(requestCode == FINE_LOCATION_PERMISSION){
            if(grantResults.isEmpty() || grantResults[0] != PackageManager.PERMISSION_GRANTED){
                Log.d("onRequestPermissionResult", "Location fine denied!")
            }
            else{
                Log.d("onRequestPermissionResult", "Location fine granted!")
            }
        }
        else if(requestCode == COARSE_LOCATION_PERMISSION){
            if(grantResults.isEmpty() || grantResults[0] != PackageManager.PERMISSION_GRANTED){
                Log.d("onRequestPermissionResult", "Location coarse denied!")
            }
            else{
                Log.d("onRequestPermissionResult", "Location coarse granted!")
            }
        }
    }
}