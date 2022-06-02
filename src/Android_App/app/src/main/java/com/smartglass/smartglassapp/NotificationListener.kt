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

    override fun onListenerConnected() {
        super.onListenerConnected()
    }

    @RequiresApi(Build.VERSION_CODES.S)
    override fun onNotificationPosted(sbn: StatusBarNotification?) {
        super.onNotificationPosted(sbn)

        if (sbn != null && BluetoothActivity.onServicesDiscoveredBool == true) {
            var app: APP = APP.OTHER
            var notif: Notification = Notification(app, "", "")
            when(sbn.packageName){
                "com.google.android.apps.maps" -> APP.MAPS
                "com.google.android.apps.messaging" -> APP.SMS
                "com.whatsapp" -> {
                    app = APP.WHATSAPP
                    notif = Notification(
                        app,
                        sbn.notification.extras.get("android.title") as String,
                        sbn.notification.extras.get("android.text") as String
                    )
                }
                "org.thoughtcrime.securesms" -> {
                    app = APP.SIGNAL
                    notif = Notification(
                        app,
                        sbn.notification.extras.get("android.title") as String,
                        sbn.notification.extras.get("android.text") as String
                    )
                }
                "com.snapchat.android" -> APP.SNAPCHAT
                "com.instagram.android" -> APP.INSTAGRAM
                "com.google.android.gm" -> APP.GMAIL
                "com.discord" -> APP.DISCORD
                "com.facebook.katana" -> APP.FACEBOOK
                "org.telegram.messenger" -> {
                    app = APP.TELEGRAM
                    notif = Notification(
                        app,
                        sbn.notification.extras.get("android.title") as String,
                        sbn.notification.extras.get("android.text") as String
                    )
                }
                "com.linkedin.android" -> APP.LINKEDIN
                else -> APP.OTHER
            }

            BluetoothActivity.queue.add(notif)
            sendMessage()
            Log.d("Info", sbn.toString())
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
            val notif: Notification = BluetoothActivity.queue.poll()
            if(BluetoothActivity.onServicesDiscoveredBool){
                writeCharacteristic(BluetoothActivity.btGatt.getService(
                    UUID.fromString(BluetoothActivity.NOTIFICATION_SERVICE_UUID)).getCharacteristic(UUID.fromString(BluetoothActivity.NOTIFICATION_BUFFER_ATTR_UUID))
                    , notif.packForDelivery())
                BluetoothActivity.messageSendBool = false
            }
        }
    }
}