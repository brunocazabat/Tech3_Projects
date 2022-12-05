package com.example.area;

import android.content.SharedPreferences;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.fragment.app.Fragment;
import androidx.fragment.app.FragmentManager;
import androidx.fragment.app.FragmentTransaction;
import androidx.navigation.fragment.NavHostFragment;

import com.example.area.modules.sendCurrentMeteo;
import com.google.android.material.snackbar.Snackbar;

import org.json.JSONException;
import org.json.JSONObject;

import java.io.IOException;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

import okhttp3.Call;
import okhttp3.Callback;
import okhttp3.MediaType;
import okhttp3.OkHttpClient;
import okhttp3.Request;
import okhttp3.RequestBody;
import okhttp3.Response;

public class RegisterFragment extends Fragment {
    Links _link = new Links();

    @Nullable
    @Override
    public View onCreateView(@NonNull LayoutInflater inflater,
                             @Nullable ViewGroup container,
                             @Nullable Bundle savedInstanceState) {
        return inflater.inflate(R.layout.fragment_register, container, false);
    }

    private static boolean isEmailValid(String email) {
        String expression = "^[\\w\\.-]+@([\\w\\-]+\\.)+[A-Z]{2,4}$";
        Pattern pattern = Pattern.compile(expression, Pattern.CASE_INSENSITIVE);
        Matcher matcher = pattern.matcher(email);
        return matcher.matches();
    }

    @Override
    public void onViewCreated(@NonNull View view, @Nullable Bundle savedInstanceState) {
        super.onViewCreated(view, savedInstanceState);

        view.findViewById(R.id.register).setOnClickListener(new View.OnClickListener() {
            final TextView fnameText = view.findViewById(R.id.firstname);
            final TextView lnameText = view.findViewById(R.id.name);
            final TextView mailText = view.findViewById(R.id.mail);
            final TextView pwdText = view.findViewById(R.id.password);
            final TextView pwd1Text = view.findViewById(R.id.password1);

            @Override
            public void onClick(View v) {
                String[] reg = new String[5];
                reg[0] = fnameText.getText().toString();
                reg[1] = lnameText.getText().toString();
                reg[2] = mailText.getText().toString();
                String mdp = pwdText.getText().toString();
                String confirmMdp = pwd1Text.getText().toString();
                boolean empty[] = {false, false, false, false, false};
                int j = 0;
                for (int i = 0; i != 3; i++) {
                    if (reg[i].length() == 0) {
                        j += 1;
                        empty[i] = true;
                    }
                }
                if (j > 0) {
                    if (j == 1) {
                        Snackbar.make(view, "A space is empty, Please enter something.", Snackbar.LENGTH_LONG).show();
                        System.out.println("A space is empty, Please enter something.");
                    } else {
                        Snackbar.make(view, "Multiple space are empty, Please enter something.", Snackbar.LENGTH_LONG).show();
                        System.out.println("Multiple space are empty, Please enter something.");
                    }
                }
                else if (isEmailValid(reg[2]) == false) {
                    Snackbar.make(view, "Please enter a valid email.", Snackbar.LENGTH_LONG).show();
                    System.out.println("Please enter a valid email.");
                }
                else if (!mdp.equals(confirmMdp)) {
                    Snackbar.make(view, "The password are different, please check to make them the same.", Snackbar.LENGTH_LONG).show();
                    System.out.println("The password are different, please check to make them the same.");
                }
                else {
                    createToDB(v, reg[0], reg[1], reg[2], mdp);
                }
            }
        });
    }

    protected void createToDB(View v, @NonNull String firstname, @NonNull String name, @NonNull String mail, @NonNull String pwd) {
        String url = _link.getCreateUser();
        OkHttpClient httpClient = new OkHttpClient.Builder().build();
        MediaType mediaType = MediaType.parse("application/json");
        String sendStr = "{\"firstname\": \"" + firstname + "\", \"name\": \"" + name + "\", \"email\": \"" + mail + "\", \"password\": \"" + pwd + "\"}";
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
                    FragmentManager fm = getFragmentManager();
                    SharedPreferences shared = getActivity().getApplicationContext().getSharedPreferences("PrefArea", 0);
                    boolean passed = shared.getBoolean("passed", false);

                    try {
                        JSONObject JObject = new JSONObject(resp);
                        result = JObject.getString("success");
                        switch (result) {
                            case "true":
                                System.out.println("Account created!");
                                Snackbar.make(v, "Account created. Welcome " + firstname + " " + name, Snackbar.LENGTH_LONG).show();
                                NavHostFragment.findNavController(RegisterFragment.this).navigate(R.id.action_registerFragment_to_FirstFragment);
                                if (fm != null && passed == true) {
                                    loginFragment fragment = new loginFragment();
                                    Bundle args = new Bundle();
                                    fragment.setArguments(args);
                                    FragmentTransaction ft = fm.beginTransaction();
                                    ft.replace(R.id.activity_main_frame_layout, fragment);
                                    ft.commit();
                                }
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
