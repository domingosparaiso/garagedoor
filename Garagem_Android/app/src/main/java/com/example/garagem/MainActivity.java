package com.example.garagem;

import android.os.AsyncTask;
import android.os.Bundle;
import android.os.Handler;
import android.widget.Button;
import android.widget.TextView;
import androidx.appcompat.app.AppCompatActivity;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.URL;

public class MainActivity extends AppCompatActivity implements Runnable {

    private Button btnGarage;
    private Button btnLight;
    private TextView txtResult;
    private TextView txtStatus;

@Override
    public void run() {
        new FetchUrlTask().execute("status");
    }

@Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        btnGarage = findViewById(R.id.btnGarage);
        btnLight = findViewById(R.id.btnLight);
        txtResult = findViewById(R.id.txtResult);
        txtStatus = findViewById(R.id.txtStatus);

        btnGarage.setOnClickListener(v -> {
            new FetchUrlTask().execute("garage");
        });
        btnLight.setOnClickListener(v -> {
            new FetchUrlTask().execute("light");
        });

        // timer
        Handler handler = new Handler();
        handler.postDelayed(this, 5000);
    }

    private class FetchUrlTask extends AsyncTask<String, Void, String> {

        @Override
        protected String doInBackground(String... urls) {
            String result = "";
            try {
                URL url = new URL("http://192.168.1.80/" + urls[0]);
                HttpURLConnection connection = (HttpURLConnection) url.openConnection();
                connection.setRequestMethod("GET");

                BufferedReader reader = new BufferedReader(
                        new InputStreamReader(connection.getInputStream())
                );

                StringBuilder sb = new StringBuilder();
                String line;
                sb.append(urls[0]).append("\n");
                while ((line = reader.readLine()) != null) {
                    sb.append(line).append("\n");
                }

                reader.close();
                result = sb.toString();
            } catch (Exception e) {
                result = urls[0] + "\nError: " + e.getMessage();
            }
            return result;
        }

        @Override
        protected void onPostExecute(String result) {
            String h = result.substring(0,result.indexOf('\n'));
            String s = result.substring(result.indexOf('\n')+1);
            if(h.equals("status")) {
                txtStatus.setText(s);
            } else {
                txtResult.setText(s);
            }
        }
    }
}
