package com.smallmaocat.narutosenki;

import android.os.Environment;
import android.util.Log;
import org.cocos2dx.lib.Cocos2dxActivity;

import java.io.File;
import java.io.FileWriter;
import java.io.PrintWriter;
import java.io.StringWriter;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Locale;

public class MainActivity extends Cocos2dxActivity {

    private static final String TAG = "NarutoSenkiDiag";

    @Override
    protected void onCreate(android.os.Bundle savedInstanceState) {
        Thread.setDefaultUncaughtExceptionHandler(new Thread.UncaughtExceptionHandler() {
            @Override
            public void uncaughtException(Thread thread, Throwable ex) {
                dump("UNCAUGHT on " + thread.getName(), ex);
                android.os.Process.killProcess(android.os.Process.myPid());
                System.exit(10);
            }
        });
        try {
            super.onCreate(savedInstanceState);
        } catch (Throwable t) {
            dump("onCreate failed", t);
            throw new RuntimeException(t);
        }
    }

    @Override
    protected void onStart() {
        try { super.onStart(); } catch (Throwable t) { dump("onStart failed", t); throw new RuntimeException(t); }
    }

    @Override
    protected void onResume() {
        try { super.onResume(); } catch (Throwable t) { dump("onResume failed", t); throw new RuntimeException(t); }
    }

    @Override
    public void onLoadNativeLibraries() {
        try {
            super.onLoadNativeLibraries();
            write("load native libs OK");
        } catch (Throwable t) {
            dump("onLoadNativeLibraries FAILED", t);
            throw new RuntimeException(t);
        }
    }

    private void dump(String stage, Throwable t) {
        StringWriter sw = new StringWriter();
        PrintWriter pw = new PrintWriter(sw);
        pw.println("========== " + stage + " ==========");
        pw.println("time: " + new SimpleDateFormat("yyyy-MM-dd HH:mm:ss", Locale.US).format(new Date()));
        pw.println("device: " + android.os.Build.MANUFACTURER + " " + android.os.Build.MODEL);
        pw.println("android: " + android.os.Build.VERSION.RELEASE + " (API " + android.os.Build.VERSION.SDK_INT + ")");
        pw.println("abilist: " + java.util.Arrays.toString(android.os.Build.SUPPORTED_ABIS));
        pw.println();
        t.printStackTrace(pw);
        pw.println();
        pw.println("--- cause chain ---");
        Throwable c = t.getCause();
        int i = 0;
        while (c != null && i < 10) {
            pw.println("[" + i + "] " + c.getClass().getName() + ": " + c.getMessage());
            StackTraceElement[] st = c.getStackTrace();
            for (int j = 0; j < Math.min(st.length, 15); j++) pw.println("      at " + st[j]);
            c = c.getCause();
            i++;
        }
        write(sw.toString());
        Log.e(TAG, sw.toString());
    }

    private void write(String text) {
        try {
            File dir = Environment.getExternalStoragePublicDirectory(Environment.DIRECTORY_DOWNLOADS);
            if (dir != null && !dir.exists()) dir.mkdirs();
            File f = new File(dir, "naruto_crash.txt");
            FileWriter fw = new FileWriter(f, true);
            fw.write(text);
            fw.write("\n\n");
            fw.flush();
            fw.close();
        } catch (Throwable ignored) { }
    }
}
