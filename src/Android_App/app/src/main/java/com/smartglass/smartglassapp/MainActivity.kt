package com.smartglass.smartglassapp

import android.Manifest
import android.annotation.SuppressLint
import android.app.Activity
import android.bluetooth.BluetoothAdapter
import android.bluetooth.BluetoothManager
import android.content.Context
import android.content.Intent
import android.content.pm.PackageManager
import android.graphics.Camera
import android.os.Build
import android.os.Bundle
import android.util.Log
import com.google.android.material.snackbar.Snackbar
import androidx.appcompat.app.AppCompatActivity
import androidx.navigation.findNavController
import androidx.navigation.ui.AppBarConfiguration
import androidx.navigation.ui.navigateUp
import androidx.navigation.ui.setupActionBarWithNavController
import android.view.Menu
import android.view.MenuItem
import android.view.View
import android.widget.FrameLayout
import android.widget.Toast
import androidx.activity.result.contract.ActivityResultContracts
import androidx.annotation.RequiresApi
import androidx.appcompat.app.ActionBarDrawerToggle
import androidx.appcompat.widget.Toolbar
import androidx.core.app.ActivityCompat
import androidx.core.content.ContextCompat
import androidx.core.view.GravityCompat
import androidx.drawerlayout.widget.DrawerLayout
import androidx.fragment.app.FragmentManager
import com.google.android.gms.dynamic.SupportFragmentWrapper
import com.google.android.gms.maps.CameraUpdateFactory
import com.google.android.gms.maps.GoogleMap
import com.google.android.gms.maps.OnMapReadyCallback
import com.google.android.gms.maps.SupportMapFragment
import com.google.android.gms.maps.model.LatLng
import com.google.android.gms.maps.model.MarkerOptions
import com.google.android.material.navigation.NavigationView
import com.smartglass.smartglassapp.databinding.ActivityMainBinding


//Making sure Bluetooth is on
private const val ENABLE_BLUETOOTH_REQUEST_CODE = 1



open class MainActivity : AppCompatActivity(), NavigationView.OnNavigationItemSelectedListener {

    companion object {
        private const val BLUETOOTH_PERMISSION: Int = 100
        private const val BLUETOOTH_ADMIN_PERMISSION: Int = 101
        private const val BLUETOOTH_CONNECT_PERMISSION: Int = 102
        private const val BLUETOOTH_SCAN_PERMISSION: Int = 103
        private const val FINE_LOCATION_PERMISSION: Int = 104
        private const val COARSE_LOCATION_PERMISSION: Int = 105
    }

    lateinit var mapFragment: SupportMapFragment
    lateinit var googleMap: GoogleMap
    private var permissions = arrayOf(Manifest.permission.ACCESS_FINE_LOCATION)

    private lateinit var drawer: DrawerLayout;

    override fun setContentView(view: View?) {
        drawer = findViewById(R.id.drawer_layout)
        val container: FrameLayout = drawer.findViewById(R.id.activityContainer)
        container.addView(view)
        super.setContentView(drawer)


    }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        drawer = findViewById(R.id.drawer_layout)
        val toolbar: Toolbar = findViewById<Toolbar>(R.id.toolbar)
        setSupportActionBar(toolbar)



        var toggle: ActionBarDrawerToggle = ActionBarDrawerToggle(this, drawer, toolbar,
            R.string.naviagtion_drawer_open, R.string.naviagtion_drawer_close)
        drawer.addDrawerListener(toggle)
        toggle.syncState()

        val navigationView: NavigationView = findViewById(R.id.nav_view)
        navigationView.setNavigationItemSelectedListener(this)


        /*
        mapFragment = supportFragmentManager.findFragmentById(R.id.map) as SupportMapFragment
        mapFragment.getMapAsync(OnMapReadyCallback {
            googleMap = it
            googleMap.isMyLocationEnabled = true

            var location = LatLng(0.03, 77.60)
            googleMap.addMarker(MarkerOptions().position(location).title("My Location"))
            googleMap.animateCamera(CameraUpdateFactory.newLatLngZoom(location, 10f))


        })
         */
    }

    override fun onBackPressed() {
        if(drawer.isDrawerOpen(GravityCompat.START)){
            drawer.closeDrawer(GravityCompat.START)
        } else {
            super.onBackPressed()
        }
    }

    @RequiresApi(Build.VERSION_CODES.S)
    override fun onNavigationItemSelected(item: MenuItem): Boolean {
        drawer.closeDrawer(GravityCompat.START)
        if(item.itemId == R.id.nav_message){
            supportFragmentManager.beginTransaction().replace(R.id.activityContainer,
                MessageFragment()).commit()
        }else if(item.itemId == R.id.nav_bluetooth){
            checkPermission(Manifest.permission.BLUETOOTH, BLUETOOTH_PERMISSION)
            checkPermission(Manifest.permission.BLUETOOTH_ADMIN, BLUETOOTH_ADMIN_PERMISSION)
            checkPermission(Manifest.permission.BLUETOOTH_CONNECT, BLUETOOTH_CONNECT_PERMISSION)
            checkPermission(Manifest.permission.BLUETOOTH_SCAN, BLUETOOTH_SCAN_PERMISSION)
            drawer.closeDrawer(GravityCompat.START)
            startActivity(Intent(this, BluetoothActivity::class.java))
            overridePendingTransition(0, 0)

        }else if(item.itemId == R.id.nav_map){
            checkPermission(Manifest.permission.ACCESS_FINE_LOCATION, FINE_LOCATION_PERMISSION)
            checkPermission(Manifest.permission.ACCESS_COARSE_LOCATION, COARSE_LOCATION_PERMISSION)
            supportFragmentManager.beginTransaction().replace(R.id.activityContainer,
                MapsFragment()).commit()
        }else if(item.itemId == R.id.nav_share){
            Toast.makeText(this, "Share", Toast.LENGTH_SHORT).show()
        }


        return true
    }

    protected fun allocateActivityTitle(titleString: String){
        supportActionBar?.setTitle(titleString)
    }

    private fun checkPermission(permission: String, requestCode: Int){
        if(ContextCompat.checkSelfPermission(this@MainActivity, permission)
            != PackageManager.PERMISSION_GRANTED)
        {
            ActivityCompat.requestPermissions(this@MainActivity, arrayOf(permission), requestCode)
        }
        else{
            Log.d("checkPermission", "$permission granted!")
        }
    }

    @SuppressLint("LongLogTag")
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