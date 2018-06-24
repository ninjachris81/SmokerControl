package net.ninjachris81.smokercontrol;

import android.app.Activity;
import android.app.AlertDialog;
import android.databinding.DataBindingUtil;
import android.os.AsyncTask;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.CheckBox;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.ToggleButton;

import net.ninjachris81.smokercontrol.databinding.ActivityMainBinding;

import java.util.HashMap;

import static android.app.PendingIntent.getActivity;

public class MainActivity extends AppCompatActivity {

    private TCPClient mTcpClient;
    private HashMap<String, String> valueMap;

    private ToggleButton isRunningBtn;

    private CheckBox isAutoStop;

    private SmokerData smokerData;
    private ActivityMainBinding smokerDataBinding;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        smokerDataBinding = DataBindingUtil.setContentView(this, R.layout.activity_main);
        smokerData = new SmokerData();
        smokerDataBinding.setSmokerData(smokerData);

        isRunningBtn = findViewById(R.id.isRunning);
        isAutoStop = findViewById(R.id.autoStop);

        new ConnectTask().execute();
    }

    public class ConnectTask extends AsyncTask<String,String,TCPClient> {

        @Override
        protected TCPClient doInBackground(String... message) {

            //we create a TCPClient object and
            mTcpClient = new TCPClient(new TCPClient.OnMessageReceived() {
                @Override
                //here the messageReceived method is implemented
                public void messageReceived(String key, String value) {
                    //this method calls the onProgressUpdate
                    publishProgress(key, value);
                }
            }, new TCPClient.OnConnected() {
                @Override
                public void connectedChanged(final boolean isConnected) {
                    runOnUiThread(new Runnable() {
                        @Override
                        public void run() {
                            smokerData.setConnectedState(isConnected ? "Connected" : "Disconnected");
                            smokerDataBinding.setSmokerData(smokerData);
                        }
                    });
                }
            });
            mTcpClient.run();

            return null;
        }

        @Override
        protected void onProgressUpdate(final String... values) {
            super.onProgressUpdate(values);

            runOnUiThread(new Runnable() {
                @Override
                public void run() {
                    switch(values[0]) {
                        case "OHU":
                            smokerData.setOutsideHumidity(Float.parseFloat(values[1]));
                            break;
                        case "OTE":
                            smokerData.setOutsideTemp(Float.parseFloat(values[1]));
                            break;
                        case "ITE":
                            smokerData.setInsideTemp(Float.parseFloat(values[1]));
                            break;
                        case "MTE":
                            smokerData.setMeatTemp(Float.parseFloat(values[1]));
                            break;
                        case "PNA":
                            smokerData.setProfileName(values[1]);
                            break;
                        case "PIT":
                            smokerData.setInsideTargetTemp(Float.parseFloat(values[1]));
                            break;
                        case "PMT":
                            smokerData.setMeatTargetTemp(Float.parseFloat(values[1]));
                            break;
                        case "PAS":
                            isAutoStop.setChecked(Boolean.parseBoolean(values[1]));
                            break;
                        case "RUN":
                            isRunningBtn.setChecked(Boolean.parseBoolean(values[1]));
                            break;
                        case "DUR":
                            smokerData.setDuration(Long.parseLong(values[1]));
                            break;
                    }
                    smokerDataBinding.setSmokerData(smokerData);
                }
            });

        }
    }
}
