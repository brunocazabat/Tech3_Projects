package com.example.area;

import android.content.SharedPreferences;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;
import androidx.fragment.app.Fragment;
import androidx.fragment.app.FragmentManager;
import androidx.fragment.app.FragmentTransaction;
import androidx.navigation.fragment.NavHostFragment;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import com.google.android.material.snackbar.Snackbar;

import org.json.JSONException;
import org.json.JSONObject;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

import okhttp3.Call;
import okhttp3.Callback;
import okhttp3.OkHttpClient;
import okhttp3.Request;
import okhttp3.Response;

public class SecondFragment extends Fragment {

    private RecyclerView recyclerView;
    SharedPreferences _pref;

    public static SecondFragment newInstance() {
        SecondFragment fragment = new SecondFragment();
        Bundle args = new Bundle();
        fragment.setArguments(args);
        return fragment;
    }

    @Override
    public View onCreateView(
            LayoutInflater inflater, ViewGroup container,
            Bundle savedInstanceState
    ) {
        return inflater.inflate(R.layout.fragment_menu, container, false);
    }

    public void onViewCreated(@NonNull View view, Bundle savedInstanceState) {
        super.onViewCreated(view, savedInstanceState);
        findUser(view);
        TextView welcomeTxtView = view.findViewById(R.id.howyadoin2);
        String welcomeMsg = "Hey " + _pref.getString("firstnameKey", null) + " " +
                _pref.getString("nameKey", null) + ",";
        welcomeTxtView.setText(welcomeMsg);
        view.findViewById(R.id.buttonGetStarted).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Nav nav = new Nav();
                SharedPreferences shared = getActivity().getApplicationContext().getSharedPreferences("PrefArea", 0);
                boolean passed = false;
                if (!nav.CompareLab(NavHostFragment.findNavController(SecondFragment.this).getCurrentDestination().getLabel(), 1)) {
                    NavHostFragment.findNavController(SecondFragment.this)
                            .navigate(nav.SendId(NavHostFragment.findNavController(SecondFragment.this).getCurrentDestination().getLabel(), 1));
                    passed = shared.getBoolean("passed", false);
                    SharedPreferences.Editor edit = _pref.edit();
                    edit.putBoolean("passed", true);
                    edit.commit();
                }
                shared = getActivity().getApplicationContext().getSharedPreferences("PrefArea", 0);
                passed = shared.getBoolean("passed", false);
                NavHostFragment.findNavController(SecondFragment.this)
                        .navigate(R.id.action_SecondFragment_to_areaModules);
                FragmentManager fm = getFragmentManager();

                if (fm != null && passed == true) {
                    AreaModules fragment = new AreaModules();
                    Bundle args = new Bundle();
                    fragment.setArguments(args);
                    FragmentTransaction ft = fm.beginTransaction();
                    ft.replace(R.id.activity_main_frame_layout, fragment);
                    ft.commit();
                }
            }
        });
    }
    @Override
    public void onResume() {
        ((AppCompatActivity)getActivity()).getSupportActionBar().show();
        super.onResume();
    }

    private void findUser(View view) {
        _pref = getActivity().getApplicationContext().getSharedPreferences("PrefArea", 0);
        String mail = _pref.getString("mailKey", "");
        if (!mail.isEmpty()) {
            Links link = new Links();
            String url = link.getGetUser() + "?search=" + mail;
            OkHttpClient client = new OkHttpClient().newBuilder().build();
            Request request = new Request.Builder()
                    .url(url)
                    .method("GET", null)
                    .build();
            client.newCall(request).enqueue(new Callback() {
                @Override
                public void onFailure(Call call, IOException e) {
                    System.out.println("Unable to recover datas from server");
                    e.printStackTrace();
                }

                @Override
                public void onResponse(Call call, Response response) throws IOException {
                    if (response.isSuccessful()) {
                        String resp = response.body().string();
                        String name = "";
                        String firstname = "";
                        String creationDate = "";
                        try {
                            JSONObject JObject = new JSONObject(resp);
                            SharedPreferences.Editor edit = _pref.edit();
                            if (!_pref.contains("isGoogle?")) {
                                name = JObject.getString("name");
                                firstname = JObject.getString("firstname");
                                creationDate = JObject.getString("date_of_creation");
                                edit.putString("nameKey", name);
                                edit.putString("firstnameKey", firstname);
                                edit.putString("creationDateKey", creationDate);
                                edit.commit();
                            }
                        } catch (JSONException e) {
                            System.out.println("Error " + e);
                            e.printStackTrace();
                        }
                    }
                }
            });
        }

    }
}