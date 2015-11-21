package com.github.thecjw.jnifiltertestapp;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;

public class LauncherActivity extends AppCompatActivity {

  private static final String TAG = LauncherActivity.class.getSimpleName();

  @Override
  protected void onCreate(Bundle savedInstanceState) {
    super.onCreate(savedInstanceState);
    setContentView(R.layout.activity_launcher);
  }
}
