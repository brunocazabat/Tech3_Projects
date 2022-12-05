package com.example.area;

import android.content.Intent;
import android.content.SharedPreferences;
import android.net.Uri;
import android.os.Bundle;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.fragment.app.Fragment;
import androidx.navigation.fragment.NavHostFragment;

import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.EditText;
import android.widget.TextView;

import com.google.android.material.snackbar.Snackbar;

import org.json.JSONException;
import org.json.JSONObject;

import java.io.IOException;

import okhttp3.Call;
import okhttp3.Callback;
import okhttp3.MediaType;
import okhttp3.MultipartBody;
import okhttp3.OkHttpClient;
import okhttp3.Request;
import okhttp3.RequestBody;
import okhttp3.Response;

/**
 * A simple {@link Fragment} subclass.
 * Use the {@link ConnectToImgur#newInstance} factory method to
 * create an instance of this fragment.
 */
public class ConnectToImgur extends Fragment {
    SharedPreferences _pref;
    private EditText _pinCodeEdit;
    private String _pinCode = "";
    public ConnectToImgur() {
    }

    public static ConnectToImgur newInstance() {
        ConnectToImgur fragment = new ConnectToImgur();
        Bundle args = new Bundle();
        fragment.setArguments(args);
        return fragment;
    }

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        return inflater.inflate(R.layout.fragment_connect_to_imgur, container, false);
    }

    @Override
    public void onViewCreated(@NonNull View view, @Nullable Bundle savedInstanceState) {
        super.onViewCreated(view, savedInstanceState);
        _pinCodeEdit = view.findViewById(R.id.editPin);
        view.findViewById(R.id.getPin).setOnClickListener(mListener);
        view.findViewById(R.id.buttonConnect).setOnClickListener(mListener);
    }

    private final View.OnClickListener mListener = v -> {
        switch (v.getId()) {
            case R.id.getPin:
                Intent viewIntent = new Intent("android.intent.action.VIEW", Uri.parse("https://api.imgur.com/oauth2/authorize?client_id=581ee108516390a&response_type=pin"));
                startActivity(viewIntent);
                break;
            case R.id.buttonConnect:
                _pinCode = _pinCodeEdit.getText().toString();
                connectToImgur(v, _pinCode);
                break;
            default:
                break;
        }
    };

    private void connectToImgur(View view, String pinCode) {
        if (!pinCode.isEmpty()) {
            _pref = getActivity().getApplicationContext().getSharedPreferences("PrefArea", 0);
            Links link = new Links();
            String url = link.getImgurAccessToken() + "?pin=" + pinCode;
            OkHttpClient client = new OkHttpClient().newBuilder().build();
            MediaType mediaType = MediaType.parse("text/plain");
            RequestBody body = RequestBody.create(mediaType, "");
            Request request = new Request.Builder()
                    .url(url)
                    .method("POST", body)
                    .build();

            client.newCall(request).enqueue(new Callback() {
                @Override
                public void onFailure(Call call, IOException e) {
                    Snackbar.make(view, "Connection to API failed", Snackbar.LENGTH_LONG).show();
                    e.printStackTrace();
                }

                @Override
                public void onResponse(Call call, Response response) throws IOException {
                    if (response.isSuccessful()) {
                        String resp = response.body().string();
                        String username = "";
                        String accessToken = "";
                        String refreshToken = "";
                        try {
                            JSONObject JObject = new JSONObject(resp);
                            SharedPreferences.Editor edit = _pref.edit();
                            username = JObject.getString("account_username");
                            refreshToken = JObject.getString("refresh_token");
                            accessToken = JObject.getString("access_token");
                            edit.putString("AccessTokenKey", accessToken);
                            edit.putString("RefreshTokenKey", refreshToken);
                            edit.putString("ImgurUsernameKey", username);
                            edit.commit();
                            System.out.println("You are connected to the Imgur API with the account " + username);
                            Snackbar.make(view, "You are connected to the Imgur API with the account " + username, Snackbar.LENGTH_LONG).show();
                        } catch (JSONException e) {
                            System.out.println("Error while connecting to Imgur API");
                            Snackbar.make(view, "Error while connecting to Imgur API", Snackbar.LENGTH_LONG).show();
                            e.printStackTrace();
                        }
                    } else {
                        System.out.println("Unexpected error");
                        Snackbar.make(view, "Unexpected error", Snackbar.LENGTH_LONG).show();
                    }
                }
            });
        } else {
            System.out.println("Please provide a valid PIN Code.");
            Snackbar.make(view, "Please provide a valid PIN Code.", Snackbar.LENGTH_LONG).show();
        }
    }
}