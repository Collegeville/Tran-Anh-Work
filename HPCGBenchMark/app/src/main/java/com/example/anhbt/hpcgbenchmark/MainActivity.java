package com.example.anhbt.hpcgbenchmark;

import android.os.AsyncTask;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ProgressBar;
import android.widget.RelativeLayout;
import android.widget.TextView;

import java.math.RoundingMode;
import java.text.DecimalFormat;

public class MainActivity extends AppCompatActivity {
    double[] result;
    char[] dimensions;

    TextView resultNumber;
    EditText xDim;
    EditText yDim;
    EditText zDim;
    TextView testResult;
    TextView BandWidth;
    TextView BwResult;
    ProgressBar loading;
    Button runButton;
    static {
        System.loadLibrary("native-main");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        runButton = findViewById(R.id.button);
        xDim = findViewById(R.id.editText);
        yDim = findViewById(R.id.editText2);
        zDim = findViewById(R.id.editText3);
        resultNumber = findViewById(R.id.Result);
        testResult = findViewById(R.id.editText4);
        BandWidth = findViewById(R.id.BandWidth);
        BwResult = findViewById(R.id.BwResult);
        loading = findViewById(R.id.progressBar);

        runButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                resultNumber.setVisibility(View.INVISIBLE);
                testResult.setVisibility(View.INVISIBLE);
                BandWidth.setVisibility(View.INVISIBLE);
                BwResult.setVisibility(View.INVISIBLE);
                loading.setVisibility(View.VISIBLE);
                String nx;
                String ny;
                String nz;
                nx = String.valueOf(xDim.getText());
                ny = String.valueOf(yDim.getText());
                nz = String.valueOf(zDim.getText());
                hpcg runTask = new hpcg();
                runTask.execute(nx,ny,nz);

            }
        });

    }
    private class hpcg extends AsyncTask<String, Void, double[]> {
        double[] result;

        //String nx, ny, nz;
        //public hpcg(String nx, String ny, String nz){
        //this.nx = nx;
        //this.ny = ny;
        //this.nz = nz;
        //}
        @Override
        protected double[] doInBackground(String...strings) {
            result =  main(4,strings[0],strings[1],strings[2]);
            if(result[0]==0){
                return null;
            }
            else{
                return result;
            }
        }


        @Override
        protected void onPostExecute(double[] finalResult){
                loading.setVisibility(View.INVISIBLE);
                DecimalFormat df = new DecimalFormat("#.#####");
                df.setRoundingMode(RoundingMode.CEILING);
                double gflops = finalResult[0];
                double bandwidth = finalResult[1];
                resultNumber.setText(df.format(gflops));
                BwResult.setText(Double.toString(bandwidth));
                resultNumber.setVisibility(View.VISIBLE);
                testResult.setVisibility(View.VISIBLE);
                BandWidth.setVisibility(View.VISIBLE);
                BwResult.setVisibility(View.VISIBLE);
        }
    }
    public native double[] main(int argc, String nx, String ny, String nz);
}
