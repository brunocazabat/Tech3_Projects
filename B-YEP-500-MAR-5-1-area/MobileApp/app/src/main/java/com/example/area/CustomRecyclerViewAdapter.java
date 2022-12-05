package com.example.area;
import android.content.Context;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Toast;

import androidx.appcompat.app.AppCompatActivity;
import androidx.navigation.fragment.NavHostFragment;
import androidx.recyclerview.widget.RecyclerView;

import com.example.area.APIViewHolder;
import com.example.area.MainActivity;
import com.example.area.R;
import com.example.area.StateAPI;
import com.example.area.modules.sendCurrentMeteo;

import java.util.List;

public class CustomRecyclerViewAdapter extends RecyclerView.Adapter<APIViewHolder> {


    private List<StateAPI> stateAPIS;
    private Context context;
    private LayoutInflater mLayoutInflater;
    static int i;

    public CustomRecyclerViewAdapter(Context context, List<StateAPI> datas ) {
        i = 1;
        this.context = context;
        this.stateAPIS = datas;
        this.mLayoutInflater = LayoutInflater.from(context);
    }

    @Override
    public APIViewHolder onCreateViewHolder(final ViewGroup parent, int viewType) {
        View recyclerViewItem = mLayoutInflater.inflate(R.layout.recyclerview_item_layout, parent, false);
        return new APIViewHolder(recyclerViewItem);
    }


    @Override
    public void onBindViewHolder(APIViewHolder holder, int position) {
        StateAPI api = this.stateAPIS.get(position);
        int imageResId = this.getDrawableResIdByName(api.getApiName());
        holder.apiView.setImageResource(imageResId);
        holder.nameView.setText(api.getApiName() );
        holder.stateView.setText(api.getState());
        holder.itemView.setOnClickListener(new View.OnClickListener() {

            @Override
            public void onClick(View v) {
                AppCompatActivity activity = (AppCompatActivity)v.getContext();
                sendCurrentMeteo meteo1 = new sendCurrentMeteo();
               // activity.getSupportFragmentManager().beginTransaction().replace(R.id.recyclerViewArea, meteo1).addToBackStack(null).commit();
            }
        });
    }

    @Override
    public int getItemCount() {
        return this.stateAPIS.size();
    }

    public int getDrawableResIdByName(String resName)  {
        String pkgName = context.getPackageName();
        // Return 0 if not found.
        int resID = context.getResources().getIdentifier(resName , "drawable", pkgName);
        return resID;
    }

    private void handleRecyclerItemClick(RecyclerView recyclerView, View itemView) {
        int itemPosition = recyclerView.getChildLayoutPosition(itemView);
        StateAPI area  = this.stateAPIS.get(itemPosition);
    }
}