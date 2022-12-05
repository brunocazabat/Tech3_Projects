package com.example.area;

import android.content.Intent;
import android.content.SharedPreferences;
import android.net.Uri;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.EditText;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.fragment.app.Fragment;

import com.google.android.material.snackbar.Snackbar;

import org.json.JSONException;
import org.json.JSONObject;

import java.io.IOException;

import okhttp3.Call;
import okhttp3.Callback;
import okhttp3.OkHttpClient;
import okhttp3.Request;
import okhttp3.Response;

public class ConnectToEpitech extends Fragment {

    SharedPreferences _pref;
    private EditText _autologEdit;
    private String _autolog;

    public ConnectToEpitech() {
    }
    public static ConnectToEpitech newInstance() {
        ConnectToEpitech fragment = new ConnectToEpitech();
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
        return inflater.inflate(R.layout.fragment_connect_to_epitech, container, false);
    }

    @Override
    public void onViewCreated(@NonNull View view, @Nullable Bundle savedInstanceState) {
        super.onViewCreated(view, savedInstanceState);
        _autologEdit = view.findViewById(R.id.editTextAuthlog);
        view.findViewById(R.id.getAutolog).setOnClickListener(mListener);
        view.findViewById(R.id.buttonConnectApiEpitech).setOnClickListener(mListener);
    }

    private final View.OnClickListener mListener = v -> {
        switch (v.getId()) {
            case R.id.getAutolog:
                Intent viewIntent = new Intent("android.intent.action.VIEW", Uri.parse("https://intra.epitech.eu/admin/autolog?format=json"));
                startActivity(viewIntent);
                break;
            case R.id.buttonConnectApiEpitech:
                _autolog = _autologEdit.getText().toString();
                connectToEpitech(v, _autolog);
                break;
            default:
                break;
        }
    };

    private void connectToEpitech(View view, String autolog) {
        if (!autolog.isEmpty()) {
            _pref = getActivity().getApplicationContext().getSharedPreferences("PrefArea", 0);
            Links link = new Links();
            String url = link.epitechLogin() + autolog;
            OkHttpClient client = new OkHttpClient().newBuilder().build();
            Request request = new Request.Builder()
                    .url(url)
                    .method("GET", null)
                    .build();
            client.newCall(request).enqueue(new Callback() {
                @Override
                public void onFailure(Call call, IOException e) {
                    Snackbar.make(view, "Connection to Epitech API failed", Snackbar.LENGTH_LONG).show();
                    e.printStackTrace();
                }

                @Override
                public void onResponse(Call call, Response response) throws IOException {
                    if (response.isSuccessful()) {
                        String resp = response.body().string();
                        String success = "";
                        String autolog = "";
                        try {
                            JSONObject JObject = new JSONObject(resp);
                            SharedPreferences.Editor edit = _pref.edit();
                            success = JObject.getString("success");
                            autolog = JObject.getString("autolog");
                            switch (success) {
                                case "true":
                                    edit.putString("EpitechSuccessKey", success);
                                    edit.putString("EpitechAutologKey", autolog);
                                    edit.commit();
                                    Snackbar.make(view, "You are connected to the EPITECH API, your autolog number is " + autolog, Snackbar.LENGTH_LONG).show();
                                    System.out.println("You are connected to the EPITECH API, your autolog number is " + autolog);
                                    break;
                                case "false":
                                    System.out.println("Error while connecting to EPITECH API");
                                    Snackbar.make(view, "Error while connecting to EPITECH API", Snackbar.LENGTH_LONG).show();
                                    break;
                                default:
                                    System.out.println("Unexpected error");
                                    Snackbar.make(view, "Unexpected error", Snackbar.LENGTH_LONG).show();
                                    break;

                            }
                        } catch (JSONException e) {
                            System.out.println("Error while connecting to Epitech API");
                            Snackbar.make(view, "Error while connecting to Epitech API", Snackbar.LENGTH_LONG).show();
                            e.printStackTrace();
                        }
                    } else {
                        System.out.println("Unexpected error");
                        Snackbar.make(view, "Unexpected error", Snackbar.LENGTH_LONG).show();
                    }
                }
            });

        } else {
            System.out.println("Please provide a valid autolog");
            Snackbar.make(view, "Please provide a  valid autolog", Snackbar.LENGTH_LONG).show();
        }
    }
    }