package com.example.area;

import androidx.appcompat.app.AppCompatActivity;
import androidx.fragment.app.FragmentManager;
import androidx.fragment.app.FragmentTransaction;
import androidx.lifecycle.Observer;
import androidx.lifecycle.ViewModelProvider;
import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.annotation.StringRes;
import androidx.fragment.app.Fragment;
import androidx.navigation.fragment.NavHostFragment;

import android.accounts.AccountManager;
import android.content.Intent;
import android.content.SharedPreferences;
import android.net.Uri;
import android.os.Bundle;
import android.text.Editable;
import android.text.TextWatcher;
import android.util.Log;
import android.view.KeyEvent;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.view.inputmethod.EditorInfo;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ProgressBar;
import android.widget.TextView;
import android.widget.Toast;

import com.example.area.R;

import com.google.android.gms.auth.api.Auth;
import com.google.android.gms.auth.api.signin.GoogleSignIn;
import com.google.android.gms.auth.api.signin.GoogleSignInAccount;
import com.google.android.gms.auth.api.signin.GoogleSignInClient;
import com.google.android.gms.auth.api.signin.GoogleSignInOptions;
import com.google.android.gms.auth.api.signin.GoogleSignInResult;
import com.google.android.gms.common.api.ApiException;
import com.google.android.gms.common.api.GoogleApiClient;
import com.google.android.gms.common.api.OptionalPendingResult;
import com.google.android.gms.tasks.Task;
import com.google.android.material.snackbar.Snackbar;

import org.json.JSONException;
import org.json.JSONObject;
import org.w3c.dom.Text;

import java.io.IOException;
import java.net.HttpURLConnection;
import java.net.URL;
import java.net.URLConnection;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

import okhttp3.Call;
import okhttp3.Callback;
import okhttp3.MediaType;
import okhttp3.MultipartBody;
import okhttp3.OkHttpClient;
import okhttp3.Request;
import okhttp3.RequestBody;
import okhttp3.Response;

public class loginFragment extends Fragment {

    private Links _link = new Links();
    private EditText _username;
    private EditText _password;
    private String _userText;
    private String _usrPwd;
    private static final int RC_SIGN_IN = 1;
    SharedPreferences _pref;
    GoogleSignInClient mGoogleSignInClient;

    public static loginFragment newInstance() {
        loginFragment fragment = new loginFragment();
        Bundle args = new Bundle();
        fragment.setArguments(args);
        return fragment;
    }

    private static boolean isEmailValid(String email) {
        String expression = "^[\\w\\.-]+@([\\w\\-]+\\.)+[A-Z]{2,4}$";
        Pattern pattern = Pattern.compile(expression, Pattern.CASE_INSENSITIVE);
        Matcher matcher = pattern.matcher(email);
        return matcher.matches();
    }

    @Override
    public void onCreate(Bundle savedInstanceState) {

        super.onCreate(savedInstanceState);

        GoogleSignInOptions gso = new GoogleSignInOptions.Builder(GoogleSignInOptions.DEFAULT_SIGN_IN)
                .requestEmail()
                .build();
        mGoogleSignInClient = GoogleSignIn.getClient(loginFragment.this.getActivity(), gso);

    }

    @Nullable
    @Override
    public View onCreateView(@NonNull LayoutInflater inflater,
                             @Nullable ViewGroup container,
                             @Nullable Bundle savedInstanceState) {
        View view = inflater.inflate(R.layout.fragment_login, container, false);
        _username = view.findViewById(R.id.username);
        _password = view.findViewById(R.id.password);
        return view;
    }

    @Override
    public void onViewCreated(@NonNull View view, @Nullable Bundle savedInstanceState) {
        super.onViewCreated(view, savedInstanceState);
        view.findViewById(R.id.login).setOnClickListener(mListener);
        view.findViewById(R.id.link_signup).setOnClickListener(mListener);
        view.findViewById(R.id.googleButton).setOnClickListener(mListener);
    }

    @Override
    public void onResume() {
        ((AppCompatActivity)getActivity()).getSupportActionBar().hide();
        super.onResume();
    }
    @Override
    public void onStart() {
        super.onStart();
    }


    private final View.OnClickListener mListener = v -> {
        switch (v.getId()) {
            case R.id.login:
                loginMethod(v);
                break;
            case R.id.link_signup:
                registerMethod(v);
                break;
            case R.id.googleButton:
                try {
                    googleConnect(v);
                } catch (IOException e) {
                    e.printStackTrace();
                }
                break;
            default:
                break;
        }
    };

    private void loginMethod(View v) {
        _userText = _username.getText().toString();
        _usrPwd = _password.getText().toString();
        if (_userText.isEmpty() || _usrPwd.isEmpty()) {
            Snackbar.make(v, "Username or password is empty, Please enter something.", Snackbar.LENGTH_LONG).show();
            System.out.println("Username or password is empty, Please enter something.");
        }
        else if (isEmailValid(_userText) == false) {
            Snackbar.make(v, "Please enter a valid email.", Snackbar.LENGTH_LONG).show();
            System.out.println("Please enter a valid email.");
        } else {
            connectToDB(v, _userText, _usrPwd);
        }
    }

    protected void connectToDB(View v, @NonNull String mail, @NonNull String pwd) {
        _pref = getActivity().getApplicationContext().getSharedPreferences("PrefArea", 0);
        String url = _link.getLoginUser();
        OkHttpClient httpClient = new OkHttpClient.Builder().build();
        MediaType mediaType = MediaType.parse("application/json");
        String sendStr = "{\r\n    \"email\": \""+ mail + "\",\r\n    \"password\": \"" + pwd + "\"\r\n}";
        RequestBody body = RequestBody.create(mediaType, sendStr);
        Request request = new Request.Builder()
                .url(url)
                .method("POST", body)
                .build();
        httpClient.newCall(request).enqueue(new Callback() {
            @Override
            public void onFailure(okhttp3.Call call, IOException e) {
                System.out.println("Connection to API Failed: " + e);
            }

            @Override
            public void onResponse(Call call, Response response) throws IOException {
                if (response.isSuccessful()) {
                    String resp = response.body().string();
                    String result = "";
                    try {

                        JSONObject JObject = new JSONObject(resp);
                        SharedPreferences.Editor edit = _pref.edit();
                        if (_pref.contains("mailKey")) {
                            edit.clear();
                            edit.commit();
                        }
                        result = JObject.getString("success");
                        Nav nav = new Nav();
                        switch (result) {
                            case "true":
                                edit.putString("mailKey", mail);
                                boolean good = _pref.getBoolean("passed", false);
                                boolean once = _pref.getBoolean("once", false);
                                if (!once && good) {
                                    edit.putBoolean("passed", false);
                                    edit.putBoolean("once", true);
                                    edit.commit();
                                }
                                if (good) {
                                    edit.putBoolean("passed", false);
                                    edit.putBoolean("once", false);
                                }
                                edit.commit();
                                boolean passed = false;
                                if (!nav.CompareLab(NavHostFragment.findNavController(loginFragment.this).getCurrentDestination().getLabel(), 0)) {
                                    System.out.println(NavHostFragment.findNavController(loginFragment.this).getCurrentDestination().getLabel());
                                    NavHostFragment.findNavController(loginFragment.this)
                                            .navigate(nav.SendId(NavHostFragment.findNavController(loginFragment.this).getCurrentDestination().getLabel(), 0));
                                    passed = _pref.getBoolean("passed", false);
                                    edit = _pref.edit();
                                    edit.putBoolean("passed", true);
                                    edit.commit();
                                }
                                NavHostFragment.findNavController(loginFragment.this).navigate(R.id.action_FirstFragment_to_SecondFragment);
                                FragmentManager fm = getFragmentManager();
                                _pref = getActivity().getApplicationContext().getSharedPreferences("PrefArea", 0);
                                passed = _pref.getBoolean("passed", false);
                                if (fm != null && passed == true) {
                                    SecondFragment fragment = new SecondFragment();
                                    Bundle args = new Bundle();
                                    fragment.setArguments(args);
                                    FragmentTransaction ft = fm.beginTransaction();
                                    ft.replace(R.id.activity_main_frame_layout, fragment);
                                    ft.commit();
                                }
                                System.out.println("Connected, Switching to main menu..");
                                Snackbar.make(v, "Connected, Switching to main menu..", Snackbar.LENGTH_LONG).show();
                                break;
                            case "false":
                                System.out.println("Error while connecting to server");
                                Snackbar.make(v, "Error while connecting to server", Snackbar.LENGTH_LONG).show();
                                break;
                            default:
                                System.out.println("Unexpected error");
                                Snackbar.make(v, "Unexpected error", Snackbar.LENGTH_LONG).show();
                                break;
                        }
                    } catch (JSONException e) {
                        e.printStackTrace();
                    }
                }
            }
        });
    }

    public void updateUI(GoogleSignInAccount account){
        _pref = getActivity().getApplicationContext().getSharedPreferences("PrefArea", 0);
        SharedPreferences.Editor edit = _pref.edit();

        if(account != null){
            if (_pref.contains("mailKey")) {
                edit.clear();
                edit.commit();
            }
            String mail = account.getEmail();
            String firstName = account.getGivenName();
            String name = account.getFamilyName();
            edit.putString("isGoogle?", "yes");
            edit.putString("mailKey", mail);
            edit.putString("nameKey", name);
            edit.putString("firstnameKey", firstName);
            edit.commit();
            boolean good = _pref.getBoolean("passed", false);
            boolean once = _pref.getBoolean("once", false);
            if (!once && good) {
                edit.putBoolean("passed", false);
                edit.putBoolean("once", true);
                edit.commit();
            }
            if (good) {
                edit.putBoolean("passed", false);
                edit.putBoolean("once", false);
                edit.commit();
            }
            Nav nav = new Nav();
            boolean passed = false;
            if (!nav.CompareLab(NavHostFragment.findNavController(loginFragment.this).getCurrentDestination().getLabel(), 0)) {
                NavHostFragment.findNavController(loginFragment.this)
                        .navigate(nav.SendId(NavHostFragment.findNavController(loginFragment.this).getCurrentDestination().getLabel(), 0));
                passed = _pref.getBoolean("passed", false);
                edit = _pref.edit();
                edit.putBoolean("passed", true);
                edit.commit();
            }
            _pref = getActivity().getApplicationContext().getSharedPreferences("PrefArea", 0);
            passed = _pref.getBoolean("passed", false);
            NavHostFragment.findNavController(loginFragment.this).navigate(R.id.action_FirstFragment_to_SecondFragment);
            FragmentManager fm = getFragmentManager();

            if (fm != null && passed == true) {
                SecondFragment fragment = new SecondFragment();
                Bundle args = new Bundle();
                fragment.setArguments(args);
                FragmentTransaction ft = fm.beginTransaction();
                ft.replace(R.id.activity_main_frame_layout, fragment);
                ft.commit();
            }
        }else {
            System.out.println("Error while connecting to server");
        }
    }

    private void googleConnect(View v) throws IOException {
        _pref = getActivity().getApplicationContext().getSharedPreferences("PrefArea", 0);
        Intent signInIntent = mGoogleSignInClient.getSignInIntent();
        startActivityForResult(signInIntent, RC_SIGN_IN);
    }

    @Override
    public void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
        if (requestCode == RC_SIGN_IN) {
            Task<GoogleSignInAccount> task = GoogleSignIn.getSignedInAccountFromIntent(data);
            System.out.println("task: " + task);
            handleSignInResult(task);
        }
    }

    private void handleSignInResult(Task<GoogleSignInAccount> completedTask) {
        try {
            GoogleSignInAccount account = completedTask.getResult(ApiException.class);
            updateUI(account);
        } catch (ApiException e) {
            System.out.println("Error: " + e);
            updateUI(null);
        }
    }

    private void registerMethod(View v) {
        _pref = getActivity().getApplicationContext().getSharedPreferences("PrefArea", 0);
        SharedPreferences.Editor edit = _pref.edit();
        boolean good = _pref.getBoolean("passed", false);
        boolean once = _pref.getBoolean("once", false);
        if (!once && good) {
            edit.putBoolean("passed", false);
            edit.putBoolean("once", true);
            edit.commit();
        }
        if (good) {
            edit.putBoolean("passed", false);
            edit.putBoolean("once", false);
        }
        edit.commit();
        Nav nav = new Nav();
        boolean passed = false;
        if (!nav.CompareLab(NavHostFragment.findNavController(loginFragment.this).getCurrentDestination().getLabel(), 0)) {
            NavHostFragment.findNavController(loginFragment.this)
                    .navigate(nav.SendId(NavHostFragment.findNavController(loginFragment.this).getCurrentDestination().getLabel(), 0));
            passed = _pref.getBoolean("passed", false);
            edit = _pref.edit();
            edit.putBoolean("passed", true);
            edit.commit();
        }
        _pref = getActivity().getApplicationContext().getSharedPreferences("PrefArea", 0);
        passed = _pref.getBoolean("passed", false);
        NavHostFragment.findNavController(loginFragment.this).navigate(R.id.action_FirstFragment_to_registerFragment);
        FragmentManager fm = getFragmentManager();

        if (fm != null && passed == true) {
            RegisterFragment fragment = new RegisterFragment();
            Bundle args = new Bundle();
            fragment.setArguments(args);
            FragmentTransaction ft = fm.beginTransaction();
            ft.replace(R.id.activity_main_frame_layout, fragment);
            ft.commit();
        }
    }
}