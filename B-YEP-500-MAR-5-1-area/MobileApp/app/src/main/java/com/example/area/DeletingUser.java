package com.example.area;

import android.content.SharedPreferences;
import android.os.Bundle;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.fragment.app.Fragment;
import androidx.fragment.app.FragmentManager;
import androidx.fragment.app.FragmentTransaction;
import androidx.navigation.fragment.NavHostFragment;

import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.EditText;

import com.google.android.material.snackbar.Snackbar;

import org.json.JSONException;
import org.json.JSONObject;

import java.io.IOException;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

import okhttp3.Call;
import okhttp3.Callback;
import okhttp3.FormBody;
import okhttp3.MediaType;
import okhttp3.MultipartBody;
import okhttp3.OkHttpClient;
import okhttp3.Request;
import okhttp3.RequestBody;
import okhttp3.Response;

/**
 * A simple {@link Fragment} subclass.
 * Use the {@link DeletingUser#newInstance} factory method to
 * create an instance of this fragment.
 */
public class DeletingUser extends Fragment {

    private EditText _mail;
    private String _mailText;
    SharedPreferences _pref;

    public DeletingUser() {
    }

    public static DeletingUser newInstance() {
        DeletingUser fragment = new DeletingUser();
        Bundle args = new Bundle();
        fragment.setArguments(args);
        return fragment;
    }

    private final View.OnClickListener mListener = new View.OnClickListener() {
        @Override
        public void onClick(View v) {
            switch (v.getId()) {
                case R.id.deluser:
                    deleteUser(v);
                    break;
                default:
                    break;
            }
        }
    };

    @Override
    public void onCreate(Bundle savedInstanceState) {

        super.onCreate(savedInstanceState);
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        // Inflate the layout for this fragment
        return inflater.inflate(R.layout.fragment_deleting_user, container, false);
    }

    @Override
    public void onViewCreated(@NonNull View view, @Nullable Bundle savedInstanceState) {
        super.onViewCreated(view, savedInstanceState);
        _mail = (EditText)view.findViewById(R.id.mail);
        view.findViewById(R.id.deluser).setOnClickListener(mListener);
    }

    private static boolean isEmailValid(String email) {
        String expression = "^[\\w\\.-]+@([\\w\\-]+\\.)+[A-Z]{2,4}$";
        Pattern pattern = Pattern.compile(expression, Pattern.CASE_INSENSITIVE);
        Matcher matcher = pattern.matcher(email);
        return matcher.matches();
    }

    protected void deleteUser(View v) {
        _mailText = _mail.getText().toString();
        _pref = getActivity().getApplicationContext().getSharedPreferences("PrefArea", 0);
        String currentMail = _pref.getString("mailKey", null);
        if (!currentMail.isEmpty() || !isEmailValid(currentMail)) {
            Snackbar.make(v, "Please enter a valid email", Snackbar.LENGTH_LONG).show();
            System.out.println("Please enter a valid email");

        }
        if (!currentMail.equals(_mailText)) {
            Snackbar.make(v, "Wrong account", Snackbar.LENGTH_LONG).show();
            System.out.println("Wrong account");
            System.out.println("Input: " + _mailText);
            System.out.println("Current mail: " + currentMail);

        } else
            _pref = getActivity().getApplicationContext().getSharedPreferences("PrefArea", 0);
        Links link = new Links();
        String url = link.getDeleteUser();
        MediaType mediaType = MediaType.parse("application/json");
        OkHttpClient httpClient = new OkHttpClient().newBuilder().build();
        String sendStr = "{\"email\": \"" + _mailText + "\"}";
        RequestBody body = RequestBody.create(mediaType, sendStr);

        Request request = new Request.Builder()
                .url(url)
                .method("DELETE", body)
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
                        result = JObject.getString("success");
                        switch (result) {
                            case "true":
                                edit.remove("mailKey");
                                edit.commit();
                                Nav nav = new Nav();
                                boolean passed = false;
                                if (!nav.CompareLab(NavHostFragment.findNavController(DeletingUser.this).getCurrentDestination().getLabel(), 21)) {
                                    NavHostFragment.findNavController(DeletingUser.this)
                                            .navigate(nav.SendId(NavHostFragment.findNavController(DeletingUser.this).getCurrentDestination().getLabel(), 2));
                                    passed = _pref.getBoolean("passed", false);
                                    edit.putBoolean("passed", true);
                                    edit.commit();
                                }
                                _pref = getActivity().getApplicationContext().getSharedPreferences("PrefArea", 0);
                                passed = _pref.getBoolean("passed", false);
                                NavHostFragment.findNavController(DeletingUser.this).navigate(R.id.action_deletingUser_to_FirstFragment);
                                FragmentManager fm = getFragmentManager();

                                if (fm != null && passed == true) {
                                    loginFragment fragment = new loginFragment();
                                    Bundle args = new Bundle();
                                    fragment.setArguments(args);
                                    FragmentTransaction ft = fm.beginTransaction();
                                    ft.replace(R.id.activity_main_frame_layout, fragment);
                                    ft.commit();
                                }
                                System.out.println("Account deleted. Switching to login menu..");
                                Snackbar.make(v, "Account deleted. Switching to login menu..", Snackbar.LENGTH_LONG).show();
                        }
                    } catch (JSONException e) {
                        Snackbar.make(v, "Error " + e, Snackbar.LENGTH_LONG).show();
                        System.out.println("Error " + e);
                        e.printStackTrace();
                    }
                }
            }
        });
    }
}