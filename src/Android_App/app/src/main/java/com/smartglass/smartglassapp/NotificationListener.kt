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
                    return;
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
}