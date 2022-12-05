package com.example.area;

import android.content.Intent;
import android.content.SharedPreferences;
import android.os.Bundle;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.cardview.widget.CardView;
import androidx.fragment.app.Fragment;
import androidx.fragment.app.FragmentManager;
import androidx.fragment.app.FragmentTransaction;
import androidx.navigation.fragment.NavHostFragment;

import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

import com.example.area.modules.CreditEpitech;
import com.example.area.modules.EpitechBinome;
import com.example.area.modules.LastNews;
import com.example.area.modules.MailOnNewMail;
import com.example.area.modules.MailerFragment;
import com.example.area.modules.Market;
import com.example.area.modules.MessageEpitech;
import com.example.area.modules.MeteoImgur;
import com.example.area.modules.NewVideoFragment;
import com.example.area.modules.NewsCategoryFragment;
import com.example.area.modules.NewsImgur;
import com.example.area.modules.NewsSubjectFragment;
import com.example.area.modules.RememberDate;
import com.example.area.modules.TempsSupFragment;
import com.example.area.modules.ThumbailFragment;
import com.example.area.modules.XViewsFragment;
import com.example.area.modules.sendCurrentMeteo;
import com.example.area.modules.sendMeteoOnDatePrecise;


public class AreaModules extends Fragment {
    private CardView area1;
    private CardView area2;
    private CardView area3;
    private CardView area4;
    private CardView area5;
    private CardView area6;
    private CardView area7;
    private CardView area8;
    private CardView area9;
    private CardView area10;
    private CardView area11;
    private CardView area12;
    private CardView area13;
    private CardView area14;
    private CardView area15;
    private CardView area16;
    private CardView area17;
    private CardView area18;

    public static void newInstance(String param1, String param2) {
        Bundle args = new Bundle();
    }

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        // Inflate the layout for this fragment
        View view = inflater.inflate(R.layout.fragment_area_modules, container, false);
        area1 = (CardView)view.findViewById(R.id.area1);
        area2 = (CardView)view.findViewById(R.id.area2);
        area3 = (CardView)view.findViewById(R.id.area3);
        area4 = (CardView)view.findViewById(R.id.area4);
        area5 = (CardView)view.findViewById(R.id.area5);
        area6 = (CardView)view.findViewById(R.id.area6);
        area7 = (CardView)view.findViewById(R.id.area7);
        area8 = (CardView)view.findViewById(R.id.area8);
        area9 = (CardView)view.findViewById(R.id.area9);
        area10 = (CardView)view.findViewById(R.id.area10);
        area11 = (CardView)view.findViewById(R.id.area11);
        area12 = (CardView)view.findViewById(R.id.area12);
        area13 = (CardView)view.findViewById(R.id.area13);
        area14 = (CardView)view.findViewById(R.id.area14);
        area15 = (CardView)view.findViewById(R.id.area15);
        area16 = (CardView)view.findViewById(R.id.area16);
        area17 = (CardView)view.findViewById(R.id.area17);
        area18 = (CardView)view.findViewById(R.id.area18);

        return view;
    }

    @Override
    public void onViewCreated(@NonNull View view, @Nullable Bundle savedInstanceState) {
        view.findViewById(R.id.area1).setOnClickListener(mListener);
        view.findViewById(R.id.area2).setOnClickListener(mListener);
        view.findViewById(R.id.area3).setOnClickListener(mListener);
        view.findViewById(R.id.area4).setOnClickListener(mListener);
        view.findViewById(R.id.area5).setOnClickListener(mListener);
        view.findViewById(R.id.area6).setOnClickListener(mListener);
        view.findViewById(R.id.area7).setOnClickListener(mListener);
        view.findViewById(R.id.area8).setOnClickListener(mListener);
        view.findViewById(R.id.area9).setOnClickListener(mListener);
        view.findViewById(R.id.area10).setOnClickListener(mListener);
        view.findViewById(R.id.area11).setOnClickListener(mListener);
        view.findViewById(R.id.area12).setOnClickListener(mListener);
        view.findViewById(R.id.area13).setOnClickListener(mListener);
        view.findViewById(R.id.area14).setOnClickListener(mListener);
        view.findViewById(R.id.area15).setOnClickListener(mListener);
        view.findViewById(R.id.area16).setOnClickListener(mListener);
        view.findViewById(R.id.area17).setOnClickListener(mListener);
        view.findViewById(R.id.area18).setOnClickListener(mListener);


        super.onViewCreated(view, savedInstanceState);
    }

    private final View.OnClickListener mListener = v -> {
        FragmentManager fm = getFragmentManager();
        SharedPreferences shared = getActivity().getApplicationContext().getSharedPreferences("PrefArea", 0);
        boolean passed = shared.getBoolean("passed", false);

        switch (v.getId()) {
            case R.id.area1: // Meteo On Current Date
                NavHostFragment.findNavController(this).navigate(R.id.action_areaModules_to_sendMeteoInfoOnDate);
                if (fm != null && passed == true) {
                    sendCurrentMeteo fragment = new sendCurrentMeteo();
                    Bundle args = new Bundle();
                    fragment.setArguments(args);
                    FragmentTransaction ft = fm.beginTransaction();
                    ft.replace(R.id.activity_main_frame_layout, fragment);
                    ft.commit();
                }
                break;
            case R.id.area2: // Meteo On Specific Date
                NavHostFragment.findNavController(this).navigate(R.id.action_areaModules_to_sendMeteoOnDatePrecise);
                if (fm != null && passed == true) {
                    sendMeteoOnDatePrecise fragment = new sendMeteoOnDatePrecise();
                    Bundle args = new Bundle();
                    fragment.setArguments(args);
                    FragmentTransaction ft = fm.beginTransaction();
                    ft.replace(R.id.activity_main_frame_layout, fragment);
                    ft.commit();
                }
                break;
            case R.id.area3: // Meteo to Imgur
                NavHostFragment.findNavController(this).navigate(R.id.action_areaModules_to_meteoImgur);
                if (fm != null && passed == true) {
                    MeteoImgur fragment = new MeteoImgur();
                    Bundle args = new Bundle();
                    fragment.setArguments(args);
                    FragmentTransaction ft = fm.beginTransaction();
                    ft.replace(R.id.activity_main_frame_layout, fragment);
                    ft.commit();
                }
                break;
            case R.id.area4: // If It's Too Hot
                NavHostFragment.findNavController(this).navigate(R.id.action_areaModules_to_tempsSupFragment);
                if (fm != null && passed == true) {
                    TempsSupFragment fragment = new TempsSupFragment();
                    Bundle args = new Bundle();
                    fragment.setArguments(args);
                    FragmentTransaction ft = fm.beginTransaction();
                    ft.replace(R.id.activity_main_frame_layout, fragment);
                    ft.commit();
                }
                break;
            case R.id.area5: // Random News To Imgur
                NavHostFragment.findNavController(this).navigate(R.id.action_areaModules_to_newsImgur);
                if (fm != null && passed == true) {
                    NewsImgur fragment = new NewsImgur();
                    Bundle args = new Bundle();
                    fragment.setArguments(args);
                    FragmentTransaction ft = fm.beginTransaction();
                    ft.replace(R.id.activity_main_frame_layout, fragment);
                    ft.commit();
                }
                break;
            case R.id.area6: // News By Category
                NavHostFragment.findNavController(this).navigate(R.id.action_areaModules_to_newsCategoryFragment2);
                if (fm != null && passed == true) {
                    NewsCategoryFragment fragment = new NewsCategoryFragment();
                    Bundle args = new Bundle();
                    fragment.setArguments(args);
                    FragmentTransaction ft = fm.beginTransaction();
                    ft.replace(R.id.activity_main_frame_layout, fragment);
                    ft.commit();
                }
                break;
            case R.id.area7: // News By Subject
                NavHostFragment.findNavController(this).navigate(R.id.action_areaModules_to_newsSubjectFragment);
                if (fm != null && passed == true) {
                    NewsSubjectFragment fragment = new NewsSubjectFragment();
                    Bundle args = new Bundle();
                    fragment.setArguments(args);
                    FragmentTransaction ft = fm.beginTransaction();
                    ft.replace(R.id.activity_main_frame_layout, fragment);
                    ft.commit();
                }
                break;
            case R.id.area8: // Last News
                NavHostFragment.findNavController(this).navigate(R.id.action_areaModules_to_lastNews2);
                if (fm != null && passed == true) {
                    LastNews fragment = new LastNews();
                    Bundle args = new Bundle();
                    fragment.setArguments(args);
                    FragmentTransaction ft = fm.beginTransaction();
                    ft.replace(R.id.activity_main_frame_layout, fragment);
                    ft.commit();
                }
                break;
            case R.id.area9: // EPITECH Credits
                NavHostFragment.findNavController(this).navigate(R.id.action_areaModules_to_creditEpitech);
                if (fm != null && passed == true) {
                    CreditEpitech fragment = new CreditEpitech();
                    Bundle args = new Bundle();
                    fragment.setArguments(args);
                    FragmentTransaction ft = fm.beginTransaction();
                    ft.replace(R.id.activity_main_frame_layout, fragment);
                    ft.commit();
                }
                break;
            case R.id.area10: // EPITECH Binomes
                NavHostFragment.findNavController(this).navigate(R.id.action_areaModules_to_epitechBinome);
                if (fm != null && passed == true) {
                    EpitechBinome fragment = new EpitechBinome();
                    Bundle args = new Bundle();
                    fragment.setArguments(args);
                    FragmentTransaction ft = fm.beginTransaction();
                    ft.replace(R.id.activity_main_frame_layout, fragment);
                    ft.commit();
                }
                break;
            case R.id.area11: // EPITECH Message
                NavHostFragment.findNavController(this).navigate(R.id.action_areaModules_to_messageEpitech);
                if (fm != null && passed == true) {
                    MessageEpitech fragment = new MessageEpitech();
                    Bundle args = new Bundle();
                    fragment.setArguments(args);
                    FragmentTransaction ft = fm.beginTransaction();
                    ft.replace(R.id.activity_main_frame_layout, fragment);
                    ft.commit();
                }
                break;
            case R.id.area12: // Mail On new Mail
                NavHostFragment.findNavController(this).navigate(R.id.action_areaModules_to_mailOnNewMail);
                if (fm != null && passed == true) {
                    MailOnNewMail fragment = new MailOnNewMail();
                    Bundle args = new Bundle();
                    fragment.setArguments(args);
                    FragmentTransaction ft = fm.beginTransaction();
                    ft.replace(R.id.activity_main_frame_layout, fragment);
                    ft.commit();
                }
                break;
            case R.id.area13: // Mailer
                NavHostFragment.findNavController(this).navigate(R.id.action_areaModules_to_mailerFragment);
                if (fm != null && passed == true) {
                    MailerFragment fragment = new MailerFragment();
                    Bundle args = new Bundle();
                    fragment.setArguments(args);
                    FragmentTransaction ft = fm.beginTransaction();
                    ft.replace(R.id.activity_main_frame_layout, fragment);
                    ft.commit();
                }
                break;
            case R.id.area14: // Remember Date
                NavHostFragment.findNavController(this).navigate(R.id.action_areaModules_to_rememberDate2);
                if (fm != null && passed == true) {
                    RememberDate fragment = new RememberDate();
                    Bundle args = new Bundle();
                    fragment.setArguments(args);
                    FragmentTransaction ft = fm.beginTransaction();
                    ft.replace(R.id.activity_main_frame_layout, fragment);
                    ft.commit();
                }
                break;
            case R.id.area15: // Market
                NavHostFragment.findNavController(this).navigate(R.id.action_areaModules_to_market);
                if (fm != null && passed == true) {
                    Market fragment = new Market();
                    Bundle args = new Bundle();
                    fragment.setArguments(args);
                    FragmentTransaction ft = fm.beginTransaction();
                    ft.replace(R.id.activity_main_frame_layout, fragment);
                    ft.commit();
                }
                break;
            case R.id.area16: // New Video
                NavHostFragment.findNavController(this).navigate(R.id.action_areaModules_to_newVideoFragment);
                if (fm != null && passed == true) {
                    NewVideoFragment fragment = new NewVideoFragment();
                    Bundle args = new Bundle();
                    fragment.setArguments(args);
                    FragmentTransaction ft = fm.beginTransaction();
                    ft.replace(R.id.activity_main_frame_layout, fragment);
                    ft.commit();
                }
                break;
            case R.id.area17: // X Views
                NavHostFragment.findNavController(this).navigate(R.id.action_areaModules_to_XViewsFragment);
                if (fm != null && passed == true) {
                    XViewsFragment fragment = new XViewsFragment();
                    Bundle args = new Bundle();
                    fragment.setArguments(args);
                    FragmentTransaction ft = fm.beginTransaction();
                    ft.replace(R.id.activity_main_frame_layout, fragment);
                    ft.commit();
                }
                break;
            case R.id.area18: // Thumbnail
                NavHostFragment.findNavController(this).navigate(R.id.action_areaModules_to_thumbailFragment);
                if (fm != null && passed == true) {
                    ThumbailFragment fragment = new ThumbailFragment();
                    Bundle args = new Bundle();
                    fragment.setArguments(args);
                    FragmentTransaction ft = fm.beginTransaction();
                    ft.replace(R.id.activity_main_frame_layout, fragment);
                    ft.commit();
                }
                break;
            default:
                break;
        }
    };
}