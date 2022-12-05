package epicture.home;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.AsyncTask;
import android.widget.ImageView;

import java.io.InputStream;
import java.net.URL;

public class GetImageFromUrl extends AsyncTask<String, Void, Bitmap> {
    ImageView imageView;

    public GetImageFromUrl(ImageView imageView){
        this.imageView = imageView;
    }

    protected Bitmap doInBackground(String... url){
        String urlOfImage = url[0];
        Bitmap productImage = null;
        try {
            InputStream is = new URL(urlOfImage).openStream();
            productImage = BitmapFactory.decodeStream(is);

        } catch(Exception e) {
            e.printStackTrace();
        }
        return productImage;
    }

    protected void onPostExecute(Bitmap result){
        imageView.setImageBitmap(result);
    }
}