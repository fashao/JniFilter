package com.github.thecjw.jnifiltertestapp.xposed;

import android.content.Context;
import android.util.Log;
import android.widget.Toast;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.channels.FileChannel;

import de.robv.android.xposed.IXposedHookLoadPackage;
import de.robv.android.xposed.XC_MethodHook;
import de.robv.android.xposed.callbacks.XC_LoadPackage;

import static de.robv.android.xposed.XposedHelpers.findAndHookMethod;

/**
 * Created by N on 2015/11/21.
 */
public class XposedDispatcher implements IXposedHookLoadPackage {

  private static final String TAG = XposedDispatcher.class.getSimpleName();
  private static final String nativeLibraryName1 = "libjnifilter_test.so";
  private static final String nativeLibraryName2 = "libcrystax.so";
  private static final String libjiaguEntryClassName = "com.qihoo.util.StubApplication";

  private static void copyFile(File src, File dst) throws IOException {

    if (!dst.exists()) {
      dst.createNewFile();
    }

    FileChannel in = new FileInputStream(src).getChannel();
    FileChannel out = new FileOutputStream(dst).getChannel();
    out.transferFrom(in, 0, in.size());
  }

  private void loadJniFilterTestLib(Context context) {
    try {
      String libPath1 = context.getFilesDir().getAbsolutePath() + "/" + nativeLibraryName1;
      String libPath2 = context.getFilesDir().getAbsolutePath() + "/" + nativeLibraryName2;
      // Visual Studio will push so file to tmp folder after build.
      String sourcePath1 = "/data/local/tmp/" + nativeLibraryName1;
      String sourcePath2 = "/data/local/tmp/" + nativeLibraryName2;
      copyFile(new File(sourcePath1), new File(libPath1));
      copyFile(new File(sourcePath2), new File(libPath2));

      System.load(libPath2);
      System.load(libPath1);
    } catch (Exception e) {
      Log.d(TAG, e.getMessage());
    }
  }

  @Override
  public void handleLoadPackage(XC_LoadPackage.LoadPackageParam loadPackageParam) throws Throwable {

    try {
      Class<?> clazz = loadPackageParam.classLoader.loadClass(libjiaguEntryClassName);

      findAndHookMethod(libjiaguEntryClassName,
          loadPackageParam.classLoader,
          "attachBaseContext",
          Context.class,
          new XC_MethodHook() {
            @Override
            protected void beforeHookedMethod(MethodHookParam param) throws Throwable {
              Context context = (Context) param.args[0];
              String packageName = context.getPackageName();
              Log.d(TAG, String.format("%s is protected by libjiagu.", packageName));
              loadJniFilterTestLib(context);
            }
          }
      );

    } catch (Exception e) {
      // Just ignore.
    }
  }

}
