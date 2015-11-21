package com.github.thecjw.jnifiltertestapp;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.channels.FileChannel;

public class LauncherActivity extends AppCompatActivity {

  private static final String TAG = LauncherActivity.class.getSimpleName();

  private static final String nativeLibraryName = "libjnifilter_test.so";

  private static void copyFile(File src, File dst) throws IOException {

    if (!dst.exists()) {
      dst.createNewFile();
    }

    FileChannel in = new FileInputStream(src).getChannel();
    FileChannel out = new FileOutputStream(dst).getChannel();
    out.transferFrom(in, 0, in.size());
  }

  @Override
  protected void onCreate(Bundle savedInstanceState) {
    super.onCreate(savedInstanceState);
    setContentView(R.layout.activity_launcher);

    try {
      String libPath = "/data/data/" + getPackageName() + "/" + nativeLibraryName;
      // Visual Studio will push so file to tmp folder after build.
      String sourcePath = "/data/local/tmp/" + nativeLibraryName;
      copyFile(new File(sourcePath), new File(libPath));
      System.load(libPath);

    } catch (Exception e) {
      Log.d(TAG, e.getMessage());
    }
  }
}
