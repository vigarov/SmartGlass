package com.smartglass.smartglassapp

import android.Manifest
import android.annotation.SuppressLint
import android.app.Activity
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
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.Button
import androidx.annotation.Nullable
import androidx.annotation.RequiresApi
import androidx.core.app.ActivityCompat
import androidx.core.content.ContextCompat
import androidx.fragment.app.Fragment
import androidx.recyclerview.widget.LinearLayoutManager
import androidx.recyclerview.widget.RecyclerView
import androidx.recyclerview.widget.SimpleItemAnimator
import com.smartglass.smartglassapp.databinding.ActivityMainBinding
import kotlinx.android.synthetic.main.fragment_bluetooth.*
import java.util.*

@SuppressLint("MissingPermission")
@RequiresApi(Build.VERSION_CODES.S)
class BluetoothFragment : Fragment() {

    companion object {
        //Permission Codes
        const val BLUETOOTH_PERMISSION: Int = 100
        const val BLUETOOTH_ADMIN_PERMISSION: Int = 101
        const val BLUETOOTH_CONNECT_PERMISSION: Int = 102
        const val BLUETOOTH_SCAN_PERMISSION: Int = 103
        private const val FINE_LOCATION_PERMISSION: Int = 104
        private const val COARSE_LOCATION_PERMISSION: Int = 105

        //Bluetooth UUIDs
        //private const val SERVICE_UUID: String = "1e7b14e7-f5d9-4113-b249-d16b6ae7db7f"
        private const val BUFFER_ATTR_UUID: String = "8d5b53b8-fe04-4509-a689-82ab4c3d2507"
        private const val GATT_MAX_MTU_SIZE = 64
    }

    @Nullable
    override fun onCreateView(
        inflater: LayoutInflater,
        container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View? {
        binding = ActivityMainBinding.inflate(layoutInflater)
        isScanning = false

        val btPermissionsButton: Button? = view?.findViewById(R.id.bluetooth_permissions)
        val bleConnectButton: Button? = view?.findViewById(R.id.ble_connect)
        val locPermissionsButton: Button? = view?.findViewById(R.id.location_permissions)

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

        return inflater.inflate(R.layout.fragment_bluetooth, container, false)
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
    private var notifQueue: List<Notification> = listOf()

    private lateinit var binding: ActivityMainBinding

    val mainAct: MainActivity = MainActivity()
    val bluetoothAdapter = mainAct.bluetoothAdapter

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
                            activity as Activity,
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
            Log.d("BluetoothGattCallback", "I was here!")
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
                        }
                        btGatt.requestMtu(GATT_MAX_MTU_SIZE)
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
                printGattTable() // See implementation just above this section
                // Consider connection setup as complete here
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
                Log.d("BluetoothGattCallback", "Characteristic $uuid changed | value: ${value.toString()}")
            }
        }
    }

    private lateinit var btGatt: BluetoothGatt
    private lateinit var btServices: List<BluetoothGattService>

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
                        activity as Activity,
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
                connectGatt(activity, false, gattCallback)
            }
        }
    }

    //------------------------------------------------------------------------
    //Utility Functions Below

    private fun writeDescriptor(descriptor: BluetoothGattDescriptor, payload: ByteArray) {
        btGatt.let { gatt ->
            descriptor.value = payload
            gatt.writeDescriptor(descriptor)
        }
    }

    private fun BluetoothGattCharacteristic.isIndicatable(): Boolean =
        containsProperty(BluetoothGattCharacteristic.PROPERTY_INDICATE)

    private fun BluetoothGattCharacteristic.isNotifiable(): Boolean =
        containsProperty(BluetoothGattCharacteristic.PROPERTY_NOTIFY)

    private fun BluetoothGattCharacteristic.containsProperty(property: Int): Boolean =
        properties and property != 0

    private fun enableNotifications(characteristic: BluetoothGattCharacteristic) {
        val cccdUuid = UUID.fromString(BUFFER_ATTR_UUID)
        val payload = when {
            characteristic.isIndicatable() -> BluetoothGattDescriptor.ENABLE_INDICATION_VALUE
            characteristic.isNotifiable() -> BluetoothGattDescriptor.ENABLE_NOTIFICATION_VALUE
            else -> {
                Log.d("ConnectionManager", "${characteristic.uuid} doesn't support notifications/indications")
                return
            }
        }

        characteristic.getDescriptor(cccdUuid)?.let { cccDescriptor ->
            if (!btGatt.setCharacteristicNotification(characteristic, true)) {
                Log.d("ConnectionManager", "setCharacteristicNotification failed for ${characteristic.uuid}")
                return
            }
            writeDescriptor(cccDescriptor, payload)
        } ?: Log.d("ConnectionManager", "${characteristic.uuid} doesn't contain the CCC descriptor!")
    }

    private fun disableNotifications(characteristic: BluetoothGattCharacteristic) {
        if (!characteristic.isNotifiable() && !characteristic.isIndicatable()) {
            Log.d("ConnectionManager", "${characteristic.uuid} doesn't support indications/notifications")
            return
        }

        val cccdUuid = UUID.fromString(BUFFER_ATTR_UUID)
        characteristic.getDescriptor(cccdUuid)?.let { cccDescriptor ->
            if (!btGatt.setCharacteristicNotification(characteristic, false)) {
                Log.d("ConnectionManager", "setCharacteristicNotification failed for ${characteristic.uuid}")
                return
            }
            writeDescriptor(cccDescriptor, BluetoothGattDescriptor.DISABLE_NOTIFICATION_VALUE)
        } ?: Log.d("ConnectionManager", "${characteristic.uuid} doesn't contain the CCC descriptor!")
    }

    private fun checkPermission(permission: String, requestCode: Int){
        if(ContextCompat.checkSelfPermission(activity as Activity, permission)
            != PackageManager.PERMISSION_GRANTED)
        {
            ActivityCompat.requestPermissions(
                activity as Activity,
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
                activity as Activity,
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

    private fun printGattTable() {
        if (btServices.isEmpty()) {
            Log.d("printGattTable", "No service and characteristic available, call discoverServices() first?")
            return
        }
        btServices.forEach { service ->
            val characteristicsTable = service.characteristics.joinToString(
                separator = "\n|--",
                prefix = "|--"
            ) { it.uuid.toString() }
            Log.d("printGattTable", "\nService ${service.uuid}\nCharacteristics:\n$characteristicsTable"
            )
        }
    }

    @SuppressLint("NotifyDataSetChanged")
    @RequiresApi(Build.VERSION_CODES.S)
    private fun startBleScan(){
        if (ActivityCompat.checkSelfPermission(
                context as Context,
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
                context as Context,
                Manifest.permission.BLUETOOTH_SCAN
            ) != PackageManager.PERMISSION_GRANTED
        ) {
            checkPermission(Manifest.permission.BLUETOOTH_SCAN, BLUETOOTH_SCAN_PERMISSION)
        }
        bleScanner.stopScan(scanCallback)
        isScanning = false
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