package com.example.area;

public class StateAPI {
    private String apiName;
    private String apiImage;
    private String apiState;
    private int id;

    public StateAPI(String apiName, String apiImage, String apiState, int id) {
        this.apiName = apiName;
        this.apiImage = apiImage;
        this.apiState = apiState;
        this.id = id;
    }

    public String getState() {
        return this.apiState;
    }

    public void setState(boolean state) {
        this.apiState = apiState;
    }

    public String getApiName() {
        return this.apiName;
    }

    public void setApiName(String apiName) {
        this.apiName = apiName;
    }

    public String getApiImage() {
        return apiImage;
    }

    public void setApiImage(String apiImage) {
        this.apiImage = apiImage;
    }

    public void setApiId(int id) {this.id = id;}

    public int getApiId() {return this.id;}
}
