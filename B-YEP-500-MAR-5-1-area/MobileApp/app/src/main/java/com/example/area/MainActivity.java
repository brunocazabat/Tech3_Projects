package com.example.area;

import android.content.SharedPreferences;
import android.os.Bundle;
import androidx.annotation.NonNull;
import androidx.appcompat.app.ActionBarDrawerToggle;
import androidx.appcompat.app.AppCompatActivity;
import androidx.appcompat.widget.Toolbar;
import androidx.core.view.GravityCompat;
import androidx.drawerlayout.widget.DrawerLayout;
import androidx.fragment.app.Fragment;
import androidx.navigation.fragment.NavHostFragment;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.TextView;

import com.google.android.material.navigation.NavigationView;
import com.google.android.material.snackbar.Snackbar;

import org.json.JSONException;
import org.json.JSONObject;
import okhttp3.Call;
import okhttp3.Callback;
import okhttp3.FormBody;
import okhttp3.MediaType;
import okhttp3.MultipartBody;
import okhttp3.OkHttpClient;
import okhttp3.Request;
import okhttp3.RequestBody;
import okhttp3.Response;
import java.io.IOException;

public class MainActivity extends AppCompatActivity implements NavigationView.OnNavigationItemSelectedListener {

    SharedPreferences _pref;

    /* **** LISTE FRAGMENT **** */
    // MENU OPTIONS
    private Fragment fragmentMainMenu;
    private Fragment fragmentDelete;
    private Fragment fragmentLogout;

    // API //
    private Fragment fragmentEpitech;
    private Fragment fragmentImgur;

    // FRAGMENT MENU API

    /* **** LISTE DATAS **** */
    // MENU OPTIONS
    private static final int FRAG_MAIN_MENU = 0;
    private static final int FRAG_LOGOUT = 1;
    private static final int FRAG_DEL = 2;

    // API //
    private static final int FRAG_API_EPITECH = 3;
    private static final int FRAG_API_IMGUR = 4;

    private Toolbar toolbar;
    private DrawerLayout drawerLayout;
    private NavigationView navigationView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        this.configureToolBar();
        this.configureDrawerLayout();
        this.configureNavigationView();
        getWindow().setStatusBarColor(getColor(R.color.grey1));
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu_main, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();

        /*
        //noinspection SimplifiableIfStatement
        if (id == R.id.action_settings) {
            return true;
        }
*/
        return super.onOptionsItemSelected(item);
    }

    @Override
    public void onBackPressed() {
        // 5 - Handle back click to close menu
        if (this.drawerLayout.isDrawerOpen(GravityCompat.START)) {
            this.drawerLayout.closeDrawer(GravityCompat.START);
        } else {
            super.onBackPressed();
        }
    }

    @Override
    public boolean onNavigationItemSelected(@NonNull MenuItem item) {
        int id = item.getItemId();

        switch (id) {
            case R.id.MainMenuDrawer:
                this.showFragment(FRAG_MAIN_MENU);
                break;
            case R.id.logoutDrawer:
                this.showFragment(FRAG_LOGOUT);
                break;
            case R.id.deleteDrawer:
                this.showFragment(FRAG_DEL);
                break;
            case R.id.epitechDrawer:
                this.showFragment(FRAG_API_EPITECH);
                break;
            case R.id.imgurDrawer:
                this.showFragment(FRAG_API_IMGUR);
                break;
            default:
                break;
        }
        this.drawerLayout.closeDrawer(GravityCompat.START);
        return true;
    }

    private void showFragment(int fragmentIdentifier) {
        switch (fragmentIdentifier) {
            case FRAG_MAIN_MENU:
                this.showMainMenuFragment();
                break;
            case FRAG_LOGOUT:
                this.showLogoutFrag();
                break;
            case FRAG_DEL:
                this.showDeleteFragment();
                break;
            case FRAG_API_EPITECH:
                this.showEpitechFragment();
                break;
            case FRAG_API_IMGUR:
                this.showImgurFragment();
                break;
            default:
                break;
        }
    }


    // Permet de retourner au menu principal
    private void showMainMenuFragment(){
        if (this.fragmentMainMenu == null) this.fragmentMainMenu = SecondFragment.newInstance();
        this.startTransactionFragment(this.fragmentMainMenu);
    }

    // Permet de se déconnecter
    private void showLogoutFrag(){
        if (this.fragmentLogout == null) this.fragmentLogout = loginFragment.newInstance();
        this.startTransactionFragment(this.fragmentLogout);
    }

    // Permet de supprimer son compte
    private void showDeleteFragment(){
        if (this.fragmentDelete == null) this.fragmentDelete = DeletingUser.newInstance();
        this.startTransactionFragment(this.fragmentDelete);
    }

    // Affiche le fragment EPITECH
    private void showEpitechFragment(){
        if (this.fragmentEpitech == null) this.fragmentEpitech = ConnectToEpitech.newInstance();
        this.startTransactionFragment(this.fragmentEpitech);
    }

    private void showImgurFragment(){
        if (this.fragmentImgur == null) this.fragmentImgur = ConnectToImgur.newInstance();
        this.startTransactionFragment(this.fragmentImgur);
    }


    private void configureToolBar(){
        this.toolbar = (Toolbar)findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);
    }

    private void startTransactionFragment(Fragment fragment){
        if (!fragment.isVisible()){
            getSupportFragmentManager().beginTransaction()
                    .replace(R.id.activity_main_frame_layout, fragment).commit();
        }
    }

    // 2 - Configure Drawer Layout
    private void configureDrawerLayout(){
        this.drawerLayout = (DrawerLayout) findViewById(R.id.activity_main_drawer_layout);
        ActionBarDrawerToggle toggle = new ActionBarDrawerToggle(this, drawerLayout, toolbar, R.string.navigation_drawer_open, R.string.navigation_drawer_close);
        drawerLayout.addDrawerListener(toggle);
        toggle.syncState();
    }

    // 3 - Configure NavigationView
    private void configureNavigationView(){
        this.navigationView = (NavigationView) findViewById(R.id.activity_main_nav_view);
        navigationView.setNavigationItemSelectedListener(this);
    }
}