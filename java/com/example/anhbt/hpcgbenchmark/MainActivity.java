package com.example.anhbt.hpcgbenchmark;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
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
    //EditText zDim = (EditText)findViewById(R.id.editText3);
    // Used to load the 'native-lib' library on application startup.
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

        runButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String nx;
                String ny;
                String nz;
                nx = String.valueOf(xDim.getText());
                ny = String.valueOf(yDim.getText());
                nz = String.valueOf(zDim.getText());
                result =  main(4,nx,ny,nz);
                if(result[0]==0){

                }
                else {
                    DecimalFormat df = new DecimalFormat("#.#####");
                    df.setRoundingMode(RoundingMode.CEILING);
                    double gflops = result[0];
                    double bandwidth = result[1];
                    resultNumber.setText(df.format(gflops));
                    BwResult.setText(Double.toString(bandwidth));
                    resultNumber.setVisibility(View.VISIBLE);
                    testResult.setVisibility(View.VISIBLE);
                    BandWidth.setVisibility(View.VISIBLE);
                    BwResult.setVisibility(View.VISIBLE);
                }
            }
        });


        //yDim.setOnEditorActionListener(new TextView.OnEditorActionListener() {
          //  @Override
            //public boolean onEditorAction(TextView v, int actionId, KeyEvent event) {
              //  boolean handled =  false;
                //if(actionId == EditorInfo.IME_ACTION_NEXT){
                  //  nx =Integer.parseInt( xDim.getText().toString());
                //}
                //return handled;
            //}
        //});

        //zDim.setOnEditorActionListener(new TextView.OnEditorActionListener() {
          //  @Override
            //public boolean onEditorAction(TextView v, int actionId, KeyEvent event) {
              //  boolean handled =  false;
                //if(actionId == EditorInfo.IME_ACTION_NEXT){
                  //  nx =Integer.parseInt( xDim.getText().toString());
                //}
                //return handled;
            //}
        //});

    }

    /**
     * A native method that is implemented by the 'native-main' native library,
     * which is packaged with this application.
     */

    public native double[] main(int argc, String nx, String ny, String nz);

    //public native String stringFromJNI();
}
