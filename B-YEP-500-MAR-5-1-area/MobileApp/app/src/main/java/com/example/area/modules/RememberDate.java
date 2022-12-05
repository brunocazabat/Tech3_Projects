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

public class RememberDate extends Fragment{
    Links _link = new Links();

    @Nullable
    @Override
    public View onCreateView(@NonNull LayoutInflater inflater,
                             @Nullable ViewGroup container,
                             @Nullable Bundle savedInstanceState) {
        return inflater.inflate(R.layout.rememberdate, container, false);
    }

    public int goodNumber(@NonNull String str, int i) {
        int res = 0;
        int j = 0;
        SimpleDateFormat sdfyear = new SimpleDateFormat("yyyy", Locale.getDefault());
        String year = sdfyear.format(new Date());
        switch (i) {
            case 0: break;
            case 1: j = Integer.parseInt(str);
                if (j < Integer.parseInt(year)){
                    res = 1;
                    System.out.println(j);
                }
                break;
            case 2: j = Integer.parseInt(str);
                if (j < 1 || j > 12)
                    res = 1;
                else if (j < 10 && str.length() > 1)
                    res = 2;
                break;
            case 3: j = Integer.parseInt(str);
                if (j < 1 || j > 31){
                    res = 1;
                    System.out.println(j);
                }
                else if (j < 10 && str.length() > 1)
                    res = 2;
                break;
            case 4: j = Integer.parseInt(str);
                if (j < 0 || j > 24){
                    res = 1;
                    System.out.println(j);
                }
                else if (j < 10 && str.length() > 1)
                    res = 2;
                break;
            case 5: j = Integer.parseInt(str);
                if (j < 0 || j > 60){
                    res = 1;
                    System.out.println(j);
                }
                else if (j < 10 && str.length() > 1)
                    res = 2;
                break;
        }
        return (res);
    }

    @Override
    public void onViewCreated(@NonNull View view, @Nullable Bundle savedInstanceState) {
        super.onViewCreated(view, savedInstanceState);

        view.findViewById(R.id.send2).setOnClickListener(new View.OnClickListener() {
            final TextView yearTxt = view.findViewById(R.id.Year2);
            final TextView monthTxt = view.findViewById(R.id.Month2);
            final TextView dayTxt = view.findViewById(R.id.Day2);
            final TextView hourTxt = view.findViewById(R.id.Hour2);
            final TextView minuteTxt = view.findViewById(R.id.Minutes2);

            @Override
            public void onClick(View v) {
                String[] mail = new String[5];
                mail[0] = yearTxt.getText().toString();
                mail[1] = monthTxt.getText().toString();
                mail[2] = dayTxt.getText().toString();
                mail[3] = hourTxt.getText().toString();
                mail[4] = minuteTxt.getText().toString();
                int j = 0;
                int k = 0;
                for (int i = 0; i != 5; i++) {
                    if (mail[i].isEmpty()) {
                        j += 1;
                    } else if (i > 0) {
                        k = 0;
                        for (int l = 0; l != mail[i].length() -1; l++) {
                            char[] c = mail[i].toCharArray();
                            if ((c[l] < '0') || (c[l] > '9')) {
                                j += 1;
                                k += 1;
                            }
                        }
                        if (k == 0) {
                            int l = goodNumber(mail[i], i + 1);
                            if (l == 1) {
                                j += 1;
                            } else if (l == 2) {
                                if (mail[i].equals("00") || mail[i].equals("0"))
                                    mail[i] = "0";
                                else {
                                    String[] temp = mail[i].split("0");
                                    mail[i] = temp[1];
                                }
                            }
                        }
                    }
                }
                if (j != 0) {
                    Snackbar.make(view, "One or many place haven't been filled or isn't a good number, please enter something.", Snackbar.LENGTH_LONG).show();
                    System.out.println("One or many place haven't been filled or isn't a good number, please enter something.");
                }
                else {
                    SimpleDateFormat sdfyear = new SimpleDateFormat("yyyy", Locale.getDefault());
                    SimpleDateFormat sdfmonth = new SimpleDateFormat("MM", Locale.getDefault());
                    SimpleDateFormat sdfday = new SimpleDateFormat("dd", Locale.getDefault());
                    SimpleDateFormat sdfhour = new SimpleDateFormat("HH", Locale.getDefault());
                    SimpleDateFormat sdfminute = new SimpleDateFormat("mm", Locale.getDefault());
                    String year = sdfyear.format(new Date());
                    String month = sdfmonth.format(new Date());
                    String day = sdfday.format(new Date());
                    String hour = sdfhour.format(new Date());
                    String minute = sdfminute.format(new Date());
                    boolean good = false;
                    int x = 0;
                    if (Integer.parseInt(mail[0]) >= Integer.parseInt(year)) {
                        if (Integer.parseInt(mail[0]) > Integer.parseInt(year))
                            x = 1;
                        if (Integer.parseInt(mail[1]) >= Integer.parseInt(month) || x == 1 ) {
                            if (Integer.parseInt(mail[1]) > Integer.parseInt(month))
                                x = 1;
                            if (Integer.parseInt(mail[2]) >= Integer.parseInt(day) || x == 1) {
                                if (Integer.parseInt(mail[2]) > Integer.parseInt(day))
                                    x = 1;
                                if (Integer.parseInt(mail[3]) >= Integer.parseInt(hour) + 1 || x == 1) {
                                    if (Integer.parseInt(mail[3]) > Integer.parseInt(hour))
                                        x = 1;
                                    if (Integer.parseInt(mail[4]) >= Integer.parseInt(minute) || x == 1) {
                                        good = true;
                                    }
                                }
                            }
                        }
                    }
                    if (good) {
                        SharedPreferences shared = getActivity().getApplicationContext().getSharedPreferences("PrefArea", 0);
                        String savedmail = shared.getString("mailKey", "");
                        GetRappelToMailFromDB(v, mail[0], mail[1], mail[2], mail[3], mail[4], savedmail);
                    }
                    else {
                        Snackbar.make(view, "Please enter a future date", Snackbar.LENGTH_LONG).show();
                        System.out.println("Please enter a future date");
                    }
                }
            }
        });
    }

    @Override
    public void onResume() {
        ((AppCompatActivity)getActivity()).getSupportActionBar().show();
        super.onResume();
    }

    protected void GetRappelToMailFromDB(View v, @NonNull String year, @NonNull String month, @NonNull String day, @NonNull String hour, @NonNull String minutes, @NonNull String mail) {
        String url = _link.meteoSendDateMail();
        OkHttpClient httpClient = new OkHttpClient.Builder().build();
        MediaType mediaType = MediaType.parse("application/json");
        String sendStr = "{\"actions\": \"MAIL\", \"actionParameter\": \"" + mail + "\", \"date\": {\"year\": "+ Integer.parseInt(year) + ", \"month\": "+
                (Integer.parseInt(month) - 1) + ", \"day\": " + Integer.parseInt(day) + ", \"hour\": " + Integer.parseInt(hour) + ", \"mins\": " + Integer.parseInt(minutes) + ", \"sec\": 0}}";
        RequestBody body = RequestBody.create(mediaType, sendStr);
        System.out.println(sendStr);

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
                        result = JObject.getString("success");
                        FragmentManager fm = getFragmentManager();
                        SharedPreferences shared = getActivity().getApplicationContext().getSharedPreferences("PrefArea", 0);
                        boolean passed = shared.getBoolean("passed", false);

                        switch (result) {
                            case "true":
                                NavHostFragment.findNavController(RememberDate.this).navigate(R.id.action_rememberDate_to_SecondFragment);
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
