package com.smartglass.smartglassapp

import android.annotation.SuppressLint
import android.bluetooth.BluetoothGattCharacteristic
import android.os.Build
import android.service.notification.NotificationListenerService
import android.service.notification.StatusBarNotification
import android.util.Log
import androidx.annotation.RequiresApi
import java.util.*

class NotificationListener: NotificationListenerService() {
    private lateinit var lastNotification: StatusBarNotification;
    override fun onListenerConnected() {
        super.onListenerConnected()
    }

    @RequiresApi(Build.VERSION_CODES.S)
    override fun onNotificationPosted(sbn: StatusBarNotification?) {
        super.onNotificationPosted(sbn)

        if (sbn != null && sbn.notification.extras.containsKey("android.subText")) {
            var app: APP = APP.OTHER
            var notif: Notification = Notification(app, "", "")
            when(sbn.packageName){
                "com.android.systemui" -> APP.SYSTEM
                "com.google.android.apps.maps" -> {
                    if(BluetoothActivity.navStarted) {
                        var bA = ByteArray(8)
                        val strTokSub: StringTokenizer = StringTokenizer(
                            sbn.notification.extras.get("android.subText").toString(), " · "
                        )
                        strTokSub.nextToken()
                        val strTokTitle: StringTokenizer = StringTokenizer(
                            sbn.notification.extras.get("android.title").toString(),
                            " "
                        )
                        val direction =
                            sbn.notification.extras.get("android.title").toString().substring(5)
                        val distance = strTokSub.nextToken()
                        val eta = strTokSub.nextToken()

                        var directionByte: Byte = 10
                        if (direction == "left") {
                            directionByte = DIRECTION.LEFT.ordinal.toByte()
                        } else if (direction == "right") {
                            directionByte = DIRECTION.RIGHT.ordinal.toByte()
                        } else {
                            directionByte = DIRECTION.FORWARD.ordinal.toByte()
                        }

                        val tokenizeDistance = StringTokenizer(distance, " ")
                        var distanceInt: UInt
                        val dist: String = tokenizeDistance.nextToken()
                        val unit: String = tokenizeDistance.nextToken()

                        if (unit == "km") {
                            distanceInt = (dist.toDouble() * 1000).toUInt()
                        } else {
                            distanceInt = dist.toUInt()
                        }

                        val etaTokenizer = StringTokenizer(eta, ":")
                        val hour: Byte = etaTokenizer.nextToken().toByte()
                        val minute: Byte = etaTokenizer.nextToken().toByte()

                        if(hour == 0.toByte() && minute == 0.toByte()){
                            BluetoothActivity.mapQueue.add(
                                byteArrayOf(
                                    0.toByte(),
                                    0.toByte(),
                                    0.toByte(),
                                    0.toByte(),
                                    0.toByte(),
                                    0.toByte(),
                                    0.toByte(),
                                    0.toByte()
                                )
                            )
                            Log.d("Maps integration", "arrived at destination!")
                            BluetoothActivity.navStarted = false
                        }
                        else{
                            BluetoothActivity.mapQueue.add(
                                byteArrayOf(
                                    1.toByte(),
                                    directionByte,
                                    distanceInt.toByte(),
                                    distanceInt.shr(8).toByte(),
                                    distanceInt.shr(16).toByte(),
                                    distanceInt.shr(24).toByte(),
                                    hour,
                                    minute
                                )
                            )
                            Log.d("Maps integration", "maps is sending!")
                        }
                        sendMapData()
                        return
                    }
                    else{
                        BluetoothActivity.navStarted = true
                        BluetoothActivity.mapQueue.add(
                            byteArrayOf(
                                1.toByte(),
                                0.toByte(),
                                0.toByte(),
                                0.toByte(),
                                0.toByte(),
                                0.toByte(),
                                0.toByte(),
                                0.toByte()
                            )
                        )
                        Log.d("Maps integration", "maps is starting!")
                        sendMapData()
                        return
                    }
                }
                "com.google.android.apps.messaging" -> {
                    app = APP.SMS
                    notif = Notification(
                        app,
                        sbn.notification.extras.get("android.title").toString(),
                        sbn.notification.extras.get("android.text").toString()
                    )
                }
                "com.whatsapp" -> {
                    if(!sbn.notification.extras.containsKey("android.textLines")) {
                        app = APP.WHATSAPP
                        notif = Notification(
                            app,
                            sbn.notification.extras.get("android.title").toString(),
                            sbn.notification.extras.get("android.text").toString()
                        )
                    }
                    else{
                        return;
                    }
                }
                "org.thoughtcrime.securesms" -> {
                    if(sbn.notification.extras.containsKey("android.text") &&
                        !sbn.notification.extras.get("android.text").toString().contains("Most recent from")){
                        app = APP.SIGNAL
                        notif = Notification(
                            app,
                            sbn.notification.extras.get("android.title").toString(),
                            sbn.notification.extras.get("android.text").toString()
                        )
                    }
                    else{
                        return;
                    }
                }
                "com.snapchat.android" -> APP.SNAPCHAT
                "com.instagram.android" -> {
                    return
                    /*if(!sbn.notification.extras.containsKey("android.text") ||
                            !sbn.notification.extras.get("android.text").toString().contains(":")){
                        return
                    }
                    app = APP.INSTAGRAM
                    var st = StringTokenizer(sbn.notification.extras.get("android.text").toString(), ":")
                    st.nextToken()
                    var title = sbn.notification.extras.get("android.title").toString().substring(0, 6)
                    if(title.length > 5){
                        title = title.substring(0, 5)
                    }
                    notif = Notification(
                        app,
                        title,
                        ""
                    )*/
                }
                "com.google.android.gm" -> APP.GMAIL
                "com.discord" -> APP.DISCORD
                "com.facebook.katana" -> {
                    app = APP.FACEBOOK
                    notif = Notification(
                        app,
                        sbn.notification.extras.get("android.title").toString(),
                        sbn.notification.extras.get("android.text").toString()
                    )
                }
                "org.telegram.messenger" -> {
                    val text: String = sbn.notification.extras.get("android.text").toString()
                    if(text.contains(" new messages from ") && text.contains("chats")){
                        return
                    }
                    app = APP.TELEGRAM
                    notif = Notification(
                        app,
                        sbn.notification.extras.get("android.title").toString(),
                        text
                    )
                }
                "com.linkedin.android" -> APP.LINKEDIN
                else -> APP.OTHER
            }

            BluetoothActivity.queue.add(notif)
            sendMessage()
            Log.d("Info", sbn.toString() )
            Log.d("Info", BluetoothActivity.onServicesDiscoveredBool.toString() )
        }
    }

    @RequiresApi(Build.VERSION_CODES.S)
    @SuppressLint("MissingPermission")
    fun writeCharacteristic(characteristic: BluetoothGattCharacteristic, payload: ByteArray){
        BluetoothActivity.btGatt.let { gatt ->
            characteristic.value = payload
            gatt.writeCharacteristic(characteristic)
        }
    }

    @RequiresApi(Build.VERSION_CODES.S)
    fun sendMessage(){
        if(BluetoothActivity.messageSendBool && !BluetoothActivity.queue.isEmpty()){
            Log.d("Info", "inside message send and queue is not empty, and messageSend Bool is true" )
            val notif: Notification = BluetoothActivity.queue.poll()
            if(BluetoothActivity.onServicesDiscoveredBool){
                Log.d("Info", "========should have sent=======" )
                writeCharacteristic(BluetoothActivity.btGatt.getService(
                    UUID.fromString(BluetoothActivity.NOTIFICATION_SERVICE_UUID)).getCharacteristic(UUID.fromString(BluetoothActivity.NOTIFICATION_BUFFER_ATTR_UUID))
                    , notif.packForDelivery())
                BluetoothActivity.messageSendBool = false
            }
        }
    }

    @RequiresApi(Build.VERSION_CODES.S)
    fun sendMapData(){
        if(BluetoothActivity.mapsSendBool && !BluetoothActivity.mapQueue.isEmpty()){
            Log.d("Info", "inside maps send and queue is not empty, and messageSend Bool is true" )
            val payload: ByteArray? = BluetoothActivity.mapQueue.poll()
            if(BluetoothActivity.onServicesDiscoveredBool){
                Log.d("Info", "========maps should have sent=======" )
                writeCharacteristic(
                    BluetoothActivity.btGatt.getService(
                        UUID.fromString(
                            BluetoothActivity.NOTIFICATION_SERVICE_UUID
                        )
                    ).getCharacteristic(
                        UUID.fromString(BluetoothActivity.NOTIFICATION_BUFFER_ATTR_UUID)),
                    payload as ByteArray)
                BluetoothActivity.mapsSendBool = false
            }
        }
    }
}

enum class DIRECTION{
    FORWARD, LEFT, RIGHT
}