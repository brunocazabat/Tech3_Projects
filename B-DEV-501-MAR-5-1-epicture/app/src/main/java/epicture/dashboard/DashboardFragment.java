package epicture.dashboard;

import android.graphics.Rect;
import android.os.Bundle;
import android.os.Handler;
import android.os.Looper;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.fragment.app.Fragment;
import androidx.lifecycle.Observer;
import androidx.lifecycle.ViewModelProviders;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

import epicture.R;
import epicture.dashboard.model.Photo;
import okhttp3.Call;
import okhttp3.Callback;
import okhttp3.OkHttpClient;
import okhttp3.Request;
import okhttp3.Response;

public class DashboardFragment extends Fragment {

    private static final String TAG = DashboardFragment.class.getSimpleName();
    private Button button;

    private TextView textView;
    private DashBoardAdapter adapter;

    @Override
    public void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setHasOptionsMenu(true);
    }

    public View onCreateView(@NonNull LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        View root = inflater.inflate(R.layout.fragment_dashboard, container, false);
        return root;
    }


    @Override
    public void onViewCreated(@NonNull View view, @Nullable Bundle savedInstanceState) {
        super.onViewCreated(view, savedInstanceState);
        fetchData();
        setUpView(view);
        setAdapter(view);
    }

    private void setUpView(View view) {
        textView = view.findViewById(R.id.text_dashboard);
    }

    private void setAdapter(View view) {
        adapter = new DashBoardAdapter(getContext(), new ArrayList<Photo>());
        RecyclerView recyclerView = view.findViewById(R.id.rv_of_photos);
        recyclerView.setLayoutManager(new LinearLayoutManager(getActivity()));
        recyclerView.setAdapter(adapter);
        recyclerView.addItemDecoration(new RecyclerView.ItemDecoration() {
            @Override
            public void getItemOffsets(@NonNull Rect outRect, @NonNull View view, @NonNull RecyclerView parent, @NonNull RecyclerView.State state) {
                outRect.bottom = 30;
            }
        });
    }

    private void fetchData() {
        OkHttpClient httpClient = new OkHttpClient.Builder().build();

        Request request = new Request.Builder()
                .url("https://api.imgur.com/3/gallery/user/rising/0.json")
                .header("Authorization", "Client-ID 2482a548e2389d7")
                .header("User-Agent", "oui")
                .build();

        httpClient.newCall(request).enqueue(new Callback() {
            @Override
            public void onFailure(Call call, IOException e) {
                Log.e(TAG, "An error has occurred " + e);
            }

            @Override
            public void onResponse(Call call, Response response) throws IOException {
                try {
                    JSONObject data = new JSONObject(response.body().string());
                    JSONArray items = data.getJSONArray("data");
                    final List<Photo> photos = new ArrayList<>();

                    for (int i = 0; i < items.length(); i++) {
                        JSONObject item = items.getJSONObject(i);
                        Photo photo = new Photo();
                        if (item.getBoolean("is_album")) {
                            photo.setId(item.getString("cover"));
                        } else {
                            photo.setId(item.getString("id"));
                        }

                        photo.setViews(item.getString("views"));
                        photo.setUpvote(item.getString("ups"));
                        photo.setDownvote(item.getString("downs"));
                        photo.setTitle(item.getString("title"));
                        photos.add(photo);
                    }
                    new Handler(Looper.getMainLooper()).post(
                            new Runnable() {
                                @Override
                                public void run() {
                                    updateDataItems(photos);
                                }
                            }
                    );

                } catch (JSONException e) {
                    e.printStackTrace();
                }
            }

        });
    }

    private void updateDataItems(List<Photo> list) {
        if (adapter != null) {
            adapter.updatePhotosList(list);
        }
    }
}