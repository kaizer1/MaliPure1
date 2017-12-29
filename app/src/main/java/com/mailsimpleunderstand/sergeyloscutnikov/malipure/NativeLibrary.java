package com.mailsimpleunderstand.sergeyloscutnikov.malipure;

/**
 * Created by SergeyLoscutnikov on 10/07/2017.
 */

public class NativeLibrary {
//    static
//    {
//        System.loadLibrary("Native-lib");
//    }
    public static native void init(int width, int height);
    public static native void step();
}
