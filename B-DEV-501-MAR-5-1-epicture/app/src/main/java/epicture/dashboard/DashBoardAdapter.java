package epicture.dashboard;

import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

import androidx.annotation.NonNull;
import androidx.appcompat.widget.AppCompatImageView;
import androidx.appcompat.widget.AppCompatTextView;
import androidx.recyclerview.widget.RecyclerView;

import com.bumptech.glide.Glide;
import com.squareup.picasso.Picasso;

import java.util.List;

import epicture.R;
import epicture.dashboard.model.Photo;

public class DashBoardAdapter extends RecyclerView.Adapter<DashBoardAdapter.PhotoVIEW> {

    private Context mContext;
    private List<Photo> photos;
    private LayoutInflater layoutInflater;

    public DashBoardAdapter(Context context, List<Photo> photos) {
        this.mContext = context;
        this.photos = photos;
        layoutInflater = LayoutInflater.from(context);
    }

    public void updatePhotosList(List<Photo> list) {
        photos = list;
        notifyDataSetChanged();
    }

    @Override
    public void onBindViewHolder(@NonNull PhotoVIEW holder, int position, @NonNull List<Object> payloads) {
        super.onBindViewHolder(holder, position, payloads);
    }

    @Override
    public long getItemId(int position) {
        return super.getItemId(position);
    }

    @NonNull
    @Override
    public PhotoVIEW onCreateViewHolder(@NonNull ViewGroup parent, int viewType) {
        return new PhotoVIEW(layoutInflater.inflate(R.layout.item, parent, false));
    }

    @Override
    public void onBindViewHolder(@NonNull PhotoVIEW holder, int position) {

        Glide.with(mContext).load("https://i.imgur.com/" + photos.get(position).getId() + ".gif").into(holder.photo);
        Picasso.with(mContext)
                .load("https://i.imgur.com/" + photos.get(position).getId() + ".jpg")
                .into(holder.photo);
        holder.upvote.setText(photos.get(position).getUpvote());
        holder.downvote.setText(photos.get(position).getDownvote());
        holder.views.setText(photos.get(position).getViews());
        holder.title.setText(photos.get(position).getTitle());

    }

    @Override
    public int getItemCount() {
        return photos.size();
    }

    public static class PhotoVIEW extends RecyclerView.ViewHolder {
        private AppCompatImageView photo;
        private AppCompatTextView title;
        private AppCompatTextView views;
        private AppCompatTextView upvote;
        private AppCompatTextView downvote;

        public PhotoVIEW(View itemView) {
            super(itemView);
            photo = itemView.findViewById(R.id.photo);
            title = itemView.findViewById(R.id.title);
            views = itemView.findViewById(R.id.views);
            upvote = itemView.findViewById(R.id.upvote);
            downvote = itemView.findViewById(R.id.downvote);

        }
    }
}
