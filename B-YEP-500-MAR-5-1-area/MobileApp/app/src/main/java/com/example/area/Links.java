package com.example.area;

public class Links {
    private String _dbLink = "http://10.0.2.2:8080/";
    public final String _clientIdGoogle = "524667447554-g52kl8ts59u6o367c5nm73httevmbrn8.apps.googleusercontent.com";
    public final String _clientSecretGoogle = "fRdllhgXfys6pXYepCBrIOWn";


    /* Gestion connection DB */
    public final String getLoginUser()
    {
        return (_dbLink + "db/loginUser");
    } // String Login User
    public final String getDeleteUser(){ return (_dbLink + "db/deleteUser");} // String Delete User
    public final String getCreateUser(){
        return (_dbLink + "db/createUser");
    } // String Create User
    public final String getGetUser() { return (_dbLink + "db/getUser");} // String Get User
    // Google
    public final String googleCredentials() {return (_dbLink + "google");}
    /* APIs */
    // Imgur
    public final String getImgurAccessToken() {return (_dbLink + "imgur/access_token_via_pin");} // String gen access token Imgur
    public final String imgurThumbnail() { return (_dbLink + "youtube/sendThumbnailToImgur"); } // String YouTube To Imgur

    // Epitech
    public final String epitechLogin() { return(_dbLink + "epitech/login/");} // String Connection API Epitech
    public final String epitechGetBinomes() {return(_dbLink + "epitech/binomes/");} // String Récupération Binomes
    public final String epitechGetMessages() {return(_dbLink + "epitech/sendMessageMail");} // String Récupération Messages envoyés

    // Météo
    public final String meteoSendCurrentMail() {return(_dbLink + "meteo/sendCurrentMeteoMail");} // String envoie météo actuelle via mail
    public final String meteoSendDateMail() {return(_dbLink + "scheduler/scheduler");} // String envoie météo via mail date précise
    public final String meteoSendToImgur() {return(_dbLink + "meteo/sendMeteoToImgur");} // String envoie météo sur Imgur

    // Automate
    public final String Automate() {return (_dbLink + "automate/create");} // String for automate

    // Mailer
    public final String MailOnNewMail(String mail) {return (_dbLink + "mailer/connectListen?email=" + mail);} // String For Mailer Listener

    // News
    public final String imgurRandomNews() {return (_dbLink + "news/sendRandomNewsToImgur");} // Send Random News to Imgur
    public final String newsCategory(String category) {return (_dbLink + "news/sendMailFromNewsCategory/" + category);} // String News By Category
    public final String NewsSubject(String subject) {return (_dbLink + "news/sendMailFromNewsSubject/" + subject);} // String News By Subject

}
