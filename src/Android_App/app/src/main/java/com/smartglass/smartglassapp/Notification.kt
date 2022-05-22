package com.smartglass.smartglassapp

import java.lang.IllegalArgumentException

class Notification(
    private val app: APP,
    private val title: String,
    private val additionalInfo: String
) {
    private val maxTitleLength: Int = 12
    private val maxAddInfoLength: Int = 48
    private val packageLength: Int = 64

    private fun checkValidity(): Boolean{
        return title.length <= maxTitleLength && additionalInfo.length <= maxAddInfoLength
    }

    fun packForDelivery(): ByteArray{
        var bA: ByteArray = ByteArray(64)

        if(!checkValidity()){
            throw IllegalArgumentException("title or additional info too long!")
        }

        // LSB of ByteArray is going to be the app type (1 byte)
        bA[0] = app.ordinal.toByte()

        // Bytes 1 to 13 (included) are the title
        // The byte number represents its position in a string, eg:
        // "Title", would mean that bA[1] = 'T', bA[2] = 'i', etc
        // Byte 13 represents the length of the string
        // (For me the '\0' string isn't supported in Kotlin :/
        val titleChars = title.toCharArray()
        var i: Int = 1
        for(char in titleChars){
            bA[i] = titleChars[i-1].code.toByte()
            i++
        }
        bA[i + maxTitleLength] = titleChars.size.toByte()

        // Bytes 14 to 63 (included) are the additional info
        // Same conventions apply as for the title, but instead e.g.:
        // "Hello", would mean bA[14] = 'H', bA[15] = 'e', etc
        // MSB Byte represents the length of the string
        i = 14
        val infoChars = additionalInfo.toCharArray()
        for(char in infoChars){
            bA[i] = infoChars[i-14].code.toByte()
            i++
        }
        bA[i + maxAddInfoLength] = infoChars.size.toByte()

        return bA
    }
}

enum class APP{
    SYSTEM, SMS, WHATSAPP, SIGNAL,
    SNAPCHAT, INSTAGRAM, GMAIL, DISCORD,
    FACEBOOK, TELEGRAM, TEAMS, OTHER
}