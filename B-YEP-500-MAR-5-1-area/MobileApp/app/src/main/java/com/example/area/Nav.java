package com.example.area;

public class Nav {
    public String lab[] = new String[22];
    public int navid[][] = new int[3][21];

    private void setLab() {
        lab[0] = "First Fragment";
        lab[1] = "Second Fragment";
        lab[2] = "fragment_area_modules";
        lab[3] = "fragment_send_meteo_info_on_date";
        lab[4] = "fragment_send_meteo_on_date_precise";
        lab[5] = "temps_sup";
        lab[6] = "meteo_imgur";
        lab[7] = "newscategory";
        lab[8] = "subjectnew";
        lab[9] = "lastnews";
        lab[10] = "RememberDate";
        lab[11] = "creditepitech";
        lab[12] = "epitechbinome";
        lab[13] = "epitechmessage";
        lab[14] = "mail_on_new_mail";
        lab[15] = "mail_fragment";
        lab[16] = "market";
        lab[17] = "newvideo_fragment";
        lab[18] = "randomnewtoimgur";
        lab[19] = "xviews_fragment";
        lab[20] = "thumbnail_fragment";
        lab[21] = "DeletingUser";
    }

    private void setNavid() {
        navid[0][0] = -1;
        navid[0][1] = R.id.action_SecondFragment_to_FirstFragment;
        navid[0][2] = R.id.action_areaModules_to_FirstFragment;
        navid[0][3] = R.id.action_sendMeteoInfoOnDate_to_FirstFragment;
        navid[0][4] = R.id.action_sendMeteoOnDatePrecise_to_FirstFragment;
        navid[0][5] = R.id.action_tempsSupFragment_to_FirstFragment;
        navid[0][6] = R.id.action_meteoImgur_to_FirstFragment;
        navid[0][7] = R.id.action_newsCategoryFragment_to_FirstFragment;
        navid[0][8] = R.id.action_newsSubjectFragment_to_FirstFragment;
        navid[0][9] = R.id.action_lastNews_to_FirstFragment;
        navid[0][10] = R.id.action_rememberDate_to_FirstFragment;
        navid[0][11] = R.id.action_creditEpitech_to_FirstFragment;
        navid[0][12] = R.id.action_epitechBinome_to_FirstFragment;
        navid[0][13] = R.id.action_messageEpitech_to_FirstFragment;
        navid[0][14] = R.id.action_mailOnNewMail_to_FirstFragment;
        navid[0][15] = R.id.action_mailerFragment_to_FirstFragment;
        navid[0][16] = R.id.action_market_to_FirstFragment;
        navid[0][17] = R.id.action_newVideoFragment_to_FirstFragment;
        navid[0][18] = R.id.action_newsImgur_to_FirstFragment;
        navid[0][19] = R.id.action_XViewsFragment_to_FirstFragment;
        navid[0][20] = R.id.action_thumbailFragment_to_FirstFragment;
        navid[1][0] = R.id.action_FirstFragment_to_SecondFragment;
        navid[1][1] = -1;
        navid[1][2] = R.id.action_areaModules_to_SecondFragment;
        navid[1][3] = R.id.action_sendMeteoInfoOnDate_to_SecondFragment;
        navid[1][4] = R.id.action_sendMeteoOnDatePrecise_to_SecondFragment;
        navid[1][5] = R.id.action_tempsSupFragment_to_SecondFragment;
        navid[1][6] = R.id.action_meteoImgur_to_SecondFragment;
        navid[1][7] = R.id.action_newsCategoryFragment_to_SecondFragment;
        navid[1][8] = R.id.action_newsSubjectFragment_to_SecondFragment;
        navid[1][9] = R.id.action_lastNews_to_SecondFragment;
        navid[1][10] = R.id.action_rememberDate_to_SecondFragment;
        navid[1][11] = R.id.action_creditEpitech_to_SecondFragment;
        navid[1][12] = R.id.action_epitechBinome_to_SecondFragment;
        navid[1][13] = R.id.action_messageEpitech_to_SecondFragment2;
        navid[1][14] = R.id.action_mailOnNewMail_to_SecondFragment;
        navid[1][15] = R.id.action_mailerFragment_to_SecondFragment;
        navid[1][16] = R.id.action_market_to_SecondFragment;
        navid[1][17] = R.id.action_newVideoFragment_to_SecondFragment;
        navid[1][18] = R.id.action_newsImgur_to_SecondFragment;
        navid[1][19] = R.id.action_XViewsFragment_to_SecondFragment;
        navid[1][20] = R.id.action_thumbailFragment_to_SecondFragment;
        navid[2][0] = R.id.action_FirstFragment_to_deletingUser;
        navid[2][1] = R.id.action_SecondFragment_to_deletingUser;
        navid[2][2] = R.id.action_areaModules_to_deletingUser;
        navid[2][3] = R.id.action_sendMeteoInfoOnDate_to_deletingUser;
        navid[2][4] = R.id.action_sendMeteoOnDatePrecise_to_deletingUser;
        navid[2][5] = R.id.action_tempsSupFragment_to_deletingUser;
        navid[2][6] = R.id.action_meteoImgur_to_deletingUser;
        navid[2][7] = R.id.action_newsCategoryFragment_to_deletingUser;
        navid[2][8] = R.id.action_newsSubjectFragment_to_deletingUser;
        navid[2][9] = R.id.action_lastNews_to_deletingUser;
        navid[2][10] = R.id.action_rememberDate_to_deletingUser;
        navid[2][11] = R.id.action_creditEpitech_to_deletingUser;
        navid[2][12] = R.id.action_epitechBinome_to_deletingUser;
        navid[2][13] = R.id.action_messageEpitech_to_deletingUser;
        navid[2][14] = R.id.action_mailOnNewMail_to_deletingUser;
        navid[2][15] = R.id.action_mailerFragment_to_deletingUser;
        navid[2][16] = R.id.action_market_to_deletingUser;
        navid[2][17] = R.id.action_newVideoFragment_to_deletingUser;
        navid[2][18] = R.id.action_newsImgur_to_deletingUser;
        navid[2][19] = R.id.action_XViewsFragment_to_deletingUser;
        navid[2][20] = R.id.action_thumbailFragment_to_deletingUser;
    }

    public boolean CompareLab(CharSequence label, int x) {
        setLab();
        int j = -1;
        for (int i = 0; i != 21; i++) {
            if (lab[i].equals(label))
                j = i;
        }
        if (j == x) {
            System.out.println(lab[j]);
            return true;
        }
        return false;
    }

    public int SendId(CharSequence label, int x) {
        int j = -1;
        setNavid();
        for (int i = 0; i != 21; i++) {
            if (lab[i].equals(label))
                j = i;
        }
        return (navid[x][j]);
    }
}
