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

import okhttp3.Call;
import okhttp3.Callback;
import okhttp3.MediaType;
import okhttp3.OkHttpClient;
import okhttp3.Request;
import okhttp3.RequestBody;
import okhttp3.Response;

import static android.content.Context.MODE_PRIVATE;

public class NewsSubjectFragment extends Fragment {
    Links _link = new Links();

    @Nullable
    @Override
    public View onCreateView(@NonNull LayoutInflater inflater,
                             @Nullable ViewGroup container,
                             @Nullable Bundle savedInstanceState) {
        return inflater.inflate(R.layout.subjectnews, container, false);
    }
    @Override
    public void onViewCreated(@NonNull View view, @Nullable Bundle savedInstanceState) {
        super.onViewCreated(view, savedInstanceState);

        view.findViewById(R.id.send).setOnClickListener(new View.OnClickListener() {
            final TextView subjectTxt = view.findViewById(R.id.subject);

            @Override
            public void onClick(View v) {
                String subject = subjectTxt.getText().toString();
                int j = 0;
                if (subject.isEmpty())
                    j = 1;
                if (j == 1) {
                    Snackbar.make(view, "One place haven't been filled, please enter something.", Snackbar.LENGTH_LONG).show();
                    System.out.println("One place haven't been filled, please enter something.");
                }
                else {
                    SharedPreferences shared = getActivity().getApplicationContext().getSharedPreferences("PrefArea", 0);
                    String savedmail = shared.getString("mailKey", "");
                    NewsSubjectToMail(v, subject,savedmail);
                }
            }
        });
    }

    @Override
    public void onResume() {
        ((AppCompatActivity)getActivity()).getSupportActionBar().show();
        super.onResume();
    }

    protected void NewsSubjectToMail(View v, @NonNull String subject, @NonNull String mail) {
        String url = _link.NewsSubject(subject);
        OkHttpClient httpClient = new OkHttpClient.Builder().build();
        MediaType mediaType = MediaType.parse("application/json");
        String sendStr = "{\"email\": \"" + mail + "\"}";
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
                                NavHostFragment.findNavController(NewsSubjectFragment.this).navigate(R.id.action_newsSubjectFragment_to_SecondFragment);
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
