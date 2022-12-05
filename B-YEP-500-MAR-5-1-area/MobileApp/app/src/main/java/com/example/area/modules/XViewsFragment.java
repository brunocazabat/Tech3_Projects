package com.example.area.modules;

import android.content.SharedPreferences;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.AsyncTask;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;
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

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;
import org.w3c.dom.Text;

import java.io.IOException;
import java.io.InputStream;
import java.net.MalformedURLException;
import java.net.URL;

import okhttp3.Call;
import okhttp3.Callback;
import okhttp3.MediaType;
import okhttp3.OkHttpClient;
import okhttp3.Request;
import okhttp3.RequestBody;
import okhttp3.Response;

import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Date;
import java.util.Locale;

import static android.content.Context.MODE_PRIVATE;

public class XViewsFragment extends Fragment {
    Links _link = new Links();

    @Nullable
    @Override
    public View onCreateView(@NonNull LayoutInflater inflater,
                             @Nullable ViewGroup container,
                             @Nullable Bundle savedInstanceState) {
        return inflater.inflate(R.layout.xviews_fragment, container, false);
    }

    @Override
    public void onViewCreated(@NonNull View view, @Nullable Bundle savedInstanceState) {
        super.onViewCreated(view, savedInstanceState);


        view.findViewById(R.id.send).setOnClickListener(new View.OnClickListener() {
            final TextView ChannelId = view.findViewById(R.id.channelid);
            final TextView YtbView = view.findViewById(R.id.ytb_view);
            @Override
            public void onClick(View v) {
                String channelid = ChannelId.getText().toString();
                String views = YtbView.getText().toString();
                int ytb_view = -1;
                int k = 0;
                for (int x = 0; x != views.length() -1; x++) {
                    char[] c = views.toCharArray();
                    if ((c[x] < '0') || (c[x] > '9')) {
                        k += 1;
                    }
                }
                if (k != 0)
                    ytb_view = Integer.parseInt(YtbView.getText().toString());
                if (channelid.isEmpty()) {
                        Snackbar.make(view, "A space is empty, Please enter something.", Snackbar.LENGTH_LONG).show();
                        System.out.println("A space is empty, Please enter something.");
                }
                if (ytb_view != -1) {
                        Snackbar.make(view, "A space is empty, Please enter something.", Snackbar.LENGTH_LONG).show();
                        System.out.println("A space is empty, Please enter something.");
                }
                else {
                    SharedPreferences shared = getActivity().getApplicationContext().getSharedPreferences("PrefArea", 0);
                    String savedmail = shared.getString("mailKey", "");
                    System.out.println(savedmail);
                    XviewToMail(v, channelid, savedmail, ytb_view);
                }
            }
        });
    }

    @Override
    public void onResume() {
        ((AppCompatActivity)getActivity()).getSupportActionBar().show();
        super.onResume();
    }

    protected void XviewToMail(View v, @NonNull String channelid, @NonNull String mail, @NonNull int ytb_view) {
        String url = _link.Automate();
        OkHttpClient httpClient = new OkHttpClient.Builder().build();
        MediaType mediaType = MediaType.parse("application/json");
        String sendStr = "{\"update\": \"30s\", \"action\": \"MAIL_NEW_VIEWS\", \"target\": \"" + mail + "\", \"query\": [\"" + channelid + "\", " + ytb_view + "]}";
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
                        result = JObject.getString("success");
                        FragmentManager fm = getFragmentManager();
                        SharedPreferences shared = getActivity().getApplicationContext().getSharedPreferences("PrefArea", 0);
                        boolean passed = shared.getBoolean("passed", false);

                        switch (result) {
                            case "true":
                                NavHostFragment.findNavController(XViewsFragment.this).navigate(R.id.action_XViewsFragment_to_SecondFragment);
                                if (fm != null && passed == true) {
                                    SecondFragment fragment = new SecondFragment();
                                    Bundle args = new Bundle();
                                    fragment.setArguments(args);
                                    FragmentTransaction ft = fm.beginTransaction();
                                    ft.replace(R.id.activity_main_frame_layout, fragment);
                                    ft.commit();
                                }
                                System.out.println("A mail has been send");
                                Snackbar.make(v, "A mail has been send", Snackbar.LENGTH_LONG).show();
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
