package com.example.area;


import android.view.View;
import android.widget.ImageView;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.recyclerview.widget.RecyclerView;

public class APIViewHolder extends RecyclerView.ViewHolder {

    public ImageView apiView;
    public TextView nameView;
    public TextView stateView;

    // @itemView: recyclerview_item_layout.xml
    public APIViewHolder(@NonNull View itemView) {
        super(itemView);
        this.apiView = (ImageView)itemView.findViewById(R.id.imageView_logo);
        this.nameView = (TextView) itemView.findViewById(R.id.textView_areaName);
        this.stateView = (TextView)itemView.findViewById(R.id.textView_areaState);
    }
}