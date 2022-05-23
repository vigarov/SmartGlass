package com.smartglass.smartglassapp

import android.util.Log
import java.lang.IllegalArgumentException

class Notification(
    private val app: APP,
    private val title: String,
    private val additionalInfo: String
) {
    private val maxTitleLength: Int = 12
    private val maxAddInfoLength: Int = 48
    private val packageLength: Int = 64

    fun packForDelivery(): ByteArray{
        var bA: ByteArray = ByteArray(64)

        // LSB of ByteArray is going to be the app type (1 byte)
        bA[0] = app.ordinal.toByte()
        bA[1] = 0.toByte()

        // Bytes 2 to 14 (included) are the title
        // Byte 2 informs us whether the string fits in the given bytes
        // The byte number represents its position in a string + 2, eg:
        // "Title", would mean that bA[3] = 'T', bA[4] = 'i', etc
        // Byte 14 represents the ending character
        val titleChars = title.toCharArray()
        if(titleChars.size >= maxTitleLength){
            bA[2] = 0.toByte()
        }
        else{
            bA[2] = 1.toByte()
        }
        var i: Int = 3
        while(i < titleChars.size + 3 && i < maxTitleLength + 2){
            bA[i] = titleChars[i - 3].code.toByte()
            i++
        }
        while(i < maxTitleLength + 2){
            bA[i] = 0.toByte()
            i++
        }
        bA[maxTitleLength + 2] = 0.toByte()

        // Bytes 15 to 63 (included) are the additional info
        // Byte 15 informs us whether the string fits in the given bytes
        // Same conventions apply as for the title, but instead e.g.:
        // "Hello", would mean bA[16] = 'H', bA[17] = 'e', etc
        // Byte 63 represents the ending character
        if(titleChars.size >= maxTitleLength){
            bA[maxTitleLength + 3] = 0.toByte()
        }
        else{
            bA[maxTitleLength + 3] = 1.toByte()
        }
        i = maxTitleLength + 4
        val infoChars = additionalInfo.toCharArray()
        while(i < infoChars.size + maxTitleLength + 4 && i < maxAddInfoLength + maxTitleLength + 3){
            bA[i] = infoChars[i - (maxTitleLength + 4)].code.toByte()
            i++
        }
        while(i < maxAddInfoLength + maxTitleLength + 3){
            bA[i] = 0.toByte()
            i++
        }
        bA[63] = 0.toByte()

        return bA
    }
}

enum class APP{
    SYSTEM, SMS, WHATSAPP, SIGNAL,
    SNAPCHAT, INSTAGRAM, GMAIL, DISCORD,
    FACEBOOK, TELEGRAM, TEAMS, OTHER
}