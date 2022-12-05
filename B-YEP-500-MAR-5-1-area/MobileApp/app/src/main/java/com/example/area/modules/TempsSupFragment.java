package com.example.area.modules;

import android.content.SharedPreferences;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;
import androidx.fragment.app.Fragment;
import androidx.fragment.app.FragmentManager;
import androidx.fragment.app.FragmentTransaction;
import androidx.navigation.fragment.NavHostFragment;

import com.example.area.Links;
import com.example.area.MainActivity;
import com.example.area.R;
import com.example.area.SecondFragment;
import com.google.android.material.snackbar.Snackbar;

import org.json.JSONException;
import org.json.JSONObject;

import java.io.IOException;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Locale;

import okhttp3.Call;
import okhttp3.Callback;
import okhttp3.MediaType;
import okhttp3.OkHttpClient;
import okhttp3.Request;
import okhttp3.RequestBody;
import okhttp3.Response;

import static android.content.Context.MODE_PRIVATE;

public class TempsSupFragment extends Fragment{
    Links _link = new Links();

    @Nullable
    @Override
    public View onCreateView(@NonNull LayoutInflater inflater,
                             @Nullable ViewGroup container,
                             @Nullable Bundle savedInstanceState) {
        return inflater.inflate(R.layout.tempsup, container, false);
    }

    public int goodNumber(@NonNull String str, int i) {
        int res = 0;
        int j = 0;
        SimpleDateFormat sdfyear = new SimpleDateFormat("yyyy", Locale.getDefault());
        String year = sdfyear.format(new Date());
        switch (i) {
            case 1: j = Integer.parseInt(str);
                if (j < 1 || j > 24)
                    res = 1;
                else if (j < 10 && str.length() > 1)
                    res = 2;
                break;
            case 2: j = Integer.parseInt(str);
                if (j < 1 || j > 60)
                    res = 1;
                else if (j < 10 && str.length() > 1)
                    res = 2;
                break;
        }
        return (res);
    }

    @Override
    public void onViewCreated(@NonNull View view, @Nullable Bundle savedInstanceState) {
        super.onViewCreated(view, savedInstanceState);

        view.findViewById(R.id.send).setOnClickListener(new View.OnClickListener() {
            final TextView cityTxt = view.findViewById(R.id.City);
            final TextView updateTxt = view.findViewById(R.id.update);
            final TextView tempTxt = view.findViewById(R.id.temperature);
            @Override
            public void onClick(View v) {
                String[] mail = new String[3];
                mail[0] = cityTxt.getText().toString();
                mail[1] = updateTxt.getText().toString();
                mail[2] = tempTxt.getText().toString();
                int j = 0;
                int k = 0;
                for (int i = 0; i != 3; i++) {
                    if (mail[i].isEmpty()) {
                        j += 1;
                    } else if (i == 2) {
                        k = 0;
                        for (int l = 0; l != mail[i].length() -1; l++) {
                            char[] c = mail[i].toCharArray();
                            if ((c[l] < '0') || (c[l] > '9')) {
                                j += 1;
                                k += 1;
                            }
                        }
                        if (k == 0) {
                            int l = 0;
                            int ints = mail[1].indexOf("s");
                            int intmin = mail[1].indexOf("min");
                            int inth = mail[1].indexOf("h");
                            if (ints != -1) {
                                String[] temp = mail[1].split("s");
                                if (temp[0].length() == mail[1].length() - 1) {
                                    k = 0;
                                    for (int x = 0; x != temp[0].length() -1; x++) {
                                        char[] c = temp[0].toCharArray();
                                        if ((c[x] < '0') || (c[x] > '9')) {
                                            k += 1;
                                        }
                                    }
                                    if (k == 0)
                                        l = goodNumber(temp[0], 2);
                                }
                            } else if (intmin != -1) {
                                String[] temp1 = mail[1].split("min");
                                if (temp1[0].length() == mail[1].length() - 3) {
                                    k = 0;
                                    for (int x = 0; x != temp1[0].length() - 1; x++) {
                                        char[] c = temp1[0].toCharArray();
                                        if ((c[x] < '0') || (c[x] > '9')) {
                                            k += 1;
                                        }
                                    }
                                    if (k == 0)
                                        l = goodNumber(temp1[1], 2);
                                }
                            } else if (inth != -1) {
                                String[] temp2 = mail[1].split("h");
                                if (temp2[0].length() == mail[1].length() - 1) {
                                    k = 0;
                                    for (int x = 0; x != temp2[0].length() - 1; x++) {
                                        char[] c = temp2[0].toCharArray();
                                        if ((c[x] < '0') || (c[x] > '9')) {
                                            k += 1;
                                        }
                                    }
                                    if (k == 0)
                                        l = goodNumber(temp2[0], 1);
                                }
                            } else
                                l = 1;
                            if (l == 1) {
                                j += 1;
                            } else if (l == 2) {
                                String[] temp = mail[i].split("0");
                                mail[i] = temp[1];
                            }
                        }
                    }
                }
                if (j != 0) {
                    Snackbar.make(view, "One or many place haven't been filled or isn't a good number, please enter something.", Snackbar.LENGTH_LONG).show();
                    System.out.println("One or many place haven't been filled or isn't a good number, please enter something.");
                }
                else {
                    SharedPreferences shared = getActivity().getApplicationContext().getSharedPreferences("PrefArea", 0);
                    String savedmail = shared.getString("mailKey", "");
                    GetMailWhenTempSupFromDB(v, mail[0], mail[1], mail[2], savedmail);
                }
            }
        });
    }

    @Override
    public void onResume() {
        ((AppCompatActivity)getActivity()).getSupportActionBar().show();
        super.onResume();
    }

    protected void GetMailWhenTempSupFromDB(View v, @NonNull String city, @NonNull String update, @NonNull String temp, @NonNull String mail) {
        String url = _link.Automate();
        OkHttpClient httpClient = new OkHttpClient.Builder().build();
        MediaType mediaType = MediaType.parse("application/json");
        String sendStr = "{\"update\": \""+ update +"\", \"action\": \"MAIL_METEO\", \"target\": \"" + mail + "\", \"query\": [\""+ city+ "\", "+ Integer.parseInt(temp) +"]}";
        RequestBody body = RequestBody.create(mediaType, sendStr);

        Request request = new Request.Builder()
                .url(url)
                .method("POST", body)
                .build();

        httpClient.newCall(request).enqueue(new Callback() {
            @Override
            public void onFailure(Call call, IOException e) {
                System.out.println("Connection to API Failed: " + e);
            }

            @Override
            public void onResponse(Call call, Response response) throws IOException {
                if (response.isSuccessful()) {
                    String resp = response.body().string();
                    String result = "";
                    try {
                        JSONObject JObject = new JSONObject(resp);
                        result = JObject.getString("success");
                        FragmentManager fm = getFragmentManager();
                        SharedPreferences shared = getActivity().getApplicationContext().getSharedPreferences("PrefArea", 0);
                        boolean passed = shared.getBoolean("passed", false);

                        switch (result) {
                            case "true":
                                NavHostFragment.findNavController(TempsSupFragment.this).navigate(R.id.action_tempsSupFragment_to_SecondFragment);
                                if (fm != null && passed == true) {
                                    SecondFragment fragment = new SecondFragment();
                                    Bundle args = new Bundle();
                                    fragment.setArguments(args);
                                    FragmentTransaction ft = fm.beginTransaction();
                                    ft.replace(R.id.activity_main_frame_layout, fragment);
                                    ft.commit();
                                }
                                System.out.println("A mail will be sent");
                                Snackbar.make(v, "A mail will be sent", Snackbar.LENGTH_LONG).show();
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

}
