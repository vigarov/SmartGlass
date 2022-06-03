package com.smartglass.smartglassapp


import android.Manifest
import android.annotation.SuppressLint
import android.bluetooth.*
import android.bluetooth.le.ScanCallback
import android.bluetooth.le.ScanResult
import android.bluetooth.le.ScanSettings
import android.content.Context
import android.content.Intent
import android.content.pm.PackageManager
import android.os.Build
import android.os.Bundle
import android.os.Handler
import android.os.Looper
import android.util.Log
import android.view.animation.AlphaAnimation
import android.view.animation.Animation
import android.widget.Button
import androidx.annotation.RequiresApi
import androidx.core.app.ActivityCompat
import androidx.core.content.ContextCompat
import androidx.recyclerview.widget.LinearLayoutManager
import androidx.recyclerview.widget.RecyclerView
import androidx.recyclerview.widget.SimpleItemAnimator
import com.smartglass.smartglassapp.databinding.ActivityBluetoothBinding
import kotlinx.android.synthetic.main.activity_bluetooth.*
import java.time.LocalDateTime
import java.util.*

@SuppressLint("MissingPermission")
@RequiresApi(Build.VERSION_CODES.S)

class BluetoothActivity : MainActivity() {
    //--------------------------------------------------------
    //Private Variables Below



    companion object {
        val queue: Queue<Notification> = LinkedList()
        lateinit var btGatt: BluetoothGatt
        var onServicesDiscoveredBool: Boolean = false
        var messageSendBool: Boolean = true

        val mapQueue: Queue<ByteArray> = LinkedList()
        var mapsSendBool: Boolean = true
        var navStarted: Boolean = false
        //Permission Codes
        const val BLUETOOTH_PERMISSION: Int = 100
        const val BLUETOOTH_ADMIN_PERMISSION: Int = 101
        const val BLUETOOTH_CONNECT_PERMISSION: Int = 102
        const val BLUETOOTH_SCAN_PERMISSION: Int = 103
        private const val FINE_LOCATION_PERMISSION: Int = 104
        private const val COARSE_LOCATION_PERMISSION: Int = 105

        //Bluetooth UUIDs
        const val NOTIFICATION_SERVICE_UUID: String = "1e7b14e7-f5d9-4113-b249-d16b6ae7db7f"
        const val GRANNY_SERVICE_UUID: String = ""
        const val NOTIFICATION_BUFFER_ATTR_UUID: String = "8d5b53b8-fe04-4509-a689-82ab4c3d2507"
        const val GRANNY_FALLING_UUID: String = "4d8aea79-7207-4f92-a629-60e0fdb2f242"
        const val MAPS_UUID: String = "df1fbdbe-c41b-45fb-9c99-cb5ba89cfac1"
        const val GATT_MAX_MTU_SIZE = 64
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
                onServicesDiscoveredBool = true
                Log.d(
                    "BluetoothGattCallback",
                    "Discovered ${services.size} services for ${device.address}"
                )
                val service = btGatt.getService(
                    UUID.fromString(NOTIFICATION_SERVICE_UUID)
                )
                val grannyService = btGatt.getService(
                    UUID.fromString(GRANNY_SERVICE_UUID)
                )

                val charNotification = service.getCharacteristic(
                    UUID.fromString(NOTIFICATION_BUFFER_ATTR_UUID)
                )
                btGatt.setCharacteristicNotification(charNotification, true)

                val charGranny = grannyService.getCharacteristic(
                    UUID.fromString(GRANNY_FALLING_UUID)
                )
                btGatt.setCharacteristicNotification(charGranny, true)

                val charMaps = service.getCharacteristic(
                    UUID.fromString(MAPS_UUID)
                )
                btGatt.setCharacteristicNotification(charMaps, true)
            }
        }

        override fun onMtuChanged(gatt: BluetoothGatt, mtu: Int, status: Int) {
            Log.d(
                "MtuChanged",
                "ATT MTU changed to $mtu, success: ${status == BluetoothGatt.GATT_SUCCESS}"
            )
        }

        @SuppressLint("SetTextI18n")
        override fun onCharacteristicChanged(
            gatt: BluetoothGatt,
            characteristic: BluetoothGattCharacteristic
        ) {
            with(characteristic) {
                Log.d("BluetoothGattCallback", "Characteristic $uuid changed | value: $value")

                if(characteristic.uuid.toString() == NOTIFICATION_BUFFER_ATTR_UUID){
                    messageSendBool = true
                    sendMessage()
                }
                else if(characteristic.uuid.toString() == GRANNY_FALLING_UUID) {
                    Log.d("BluetootGallCallback", "GRANNY FELL ALERT!!!!!!!!")
                    textView.text = "GRANNY FELL"
                    textView.textSize = 50f
                    val anim = AlphaAnimation(0f, 1f)
                    anim.duration = 500
                    anim.startOffset = 50
                    anim.repeatMode = Animation.REVERSE
                    anim.repeatCount = 20
                    textView.startAnimation(anim)

                    val date = LocalDateTime.now()
                    val tm_sec: Int = date.second
                    val tm_min: Int = date.minute
                    val tm_hour: Int = date.hour
                    val tm_mday: Int = date.dayOfMonth
                    val tm_mon: Int = date.monthValue
                    val tm_year: Int = date.year
                    val tm_wday: Int = date.dayOfWeek.ordinal
                    val tm_yday: Int = date.dayOfYear

                    var packet = ByteArray(32)
                    packet = intToByteArray(tm_sec).copyInto(packet, 0, 0, 4)
                    packet = intToByteArray(tm_min).copyInto(packet, 4, 0, 4)
                    packet = intToByteArray(tm_hour).copyInto(packet, 8, 0, 4)
                    packet = intToByteArray(tm_mday).copyInto(packet, 12, 0, 4)
                    packet = intToByteArray(tm_mon).copyInto(packet, 16, 0, 4)
                    packet = intToByteArray(tm_year).copyInto(packet, 20, 0, 4)
                    packet = intToByteArray(tm_wday).copyInto(packet, 24, 0, 4)
                    packet = intToByteArray(tm_yday).copyInto(packet, 28, 0, 4)
                    writeCharacteristic(
                        btGatt.getService(UUID.fromString(GRANNY_SERVICE_UUID))
                            .getCharacteristic(UUID.fromString(GRANNY_FALLING_UUID)),
                        packet
                    )
                }
                else if(characteristic.uuid.toString() == GRANNY_FALLING_UUID) {
                    mapsSendBool = true
                    sendMapData()
                }
            }
        }
    }

    fun intToByteArray(int: Int): ByteArray = byteArrayOf(
        int.toByte(),
        int.shr(8).toByte(),
        int.shr(16).toByte(),
        int.shr(24).toByte()
    )

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

    fun writeCharacteristic(characteristic: BluetoothGattCharacteristic, payload: ByteArray){
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
        val intent = Intent("android.settings.ACTION_NOTIFICATION_LISTENER_SETTINGS")
        startActivity(intent)
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

    fun sendMessage(){
        if(messageSendBool && !queue.isEmpty()){
            val notif: Notification = queue.poll() as Notification
            if (onServicesDiscoveredBool) {
                writeCharacteristic(
                    btGatt.getService(
                        UUID.fromString(NOTIFICATION_SERVICE_UUID)
                    )
                        .getCharacteristic(UUID.fromString(NOTIFICATION_BUFFER_ATTR_UUID)),
                    notif.packForDelivery()
                )
                messageSendBool = false
            }
        }
    }

    @RequiresApi(Build.VERSION_CODES.S)
    fun sendMapData(){
        if(mapsSendBool && !mapQueue.isEmpty()){
            Log.d("Info", "inside maps send and queue is not empty, and messageSend Bool is true" )
            val payload: ByteArray? = mapQueue.poll()
            if(onServicesDiscoveredBool){
                Log.d("Info", "========maps should have sent=======" )
                writeCharacteristic(
                    btGatt.getService(
                        UUID.fromString(
                            NOTIFICATION_SERVICE_UUID
                        )
                    ).getCharacteristic(
                        UUID.fromString(NOTIFICATION_BUFFER_ATTR_UUID)),
                    payload as ByteArray)
                mapsSendBool = false
            }
        }
    }
}