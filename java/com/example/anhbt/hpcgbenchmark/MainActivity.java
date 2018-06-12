package com.example.anhbt.hpcgbenchmark;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.KeyEvent;
import android.view.inputmethod.EditorInfo;
import android.widget.EditText;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {
    int nx = 10;
    int ny = 10;
    int nz = 10;
    char[] dimensions;
    //EditText xDim = (EditText)findViewById(R.id.editText);
    //EditText yDim = (EditText)findViewById(R.id.editText2);
    //EditText zDim = (EditText)findViewById(R.id.editText3);
    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-main");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        //xDim.setOnEditorActionListener(new TextView.OnEditorActionListener() {
          //  @Override
            //public boolean onEditorAction(TextView v, int actionId, KeyEvent event) {
              //  boolean handled =  false;
                //if(actionId == EditorInfo.IME_ACTION_NEXT){
                  //  nx =Integer.parseInt( xDim.getText().toString());
                //}
                //return handled;
            //}
        //});

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


        int result =  main(1, '0');
        System.out.print(result);
        //String test = stringFromJNI();

    }

    /**
     * A native method that is implemented by the 'native-main' native library,
     * which is packaged with this application.
     */

    public native int main(int argc, char test);

    //public native String stringFromJNI();
}
