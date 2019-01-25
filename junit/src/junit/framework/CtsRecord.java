package junit.framework;

import junit.framework.CtsPlugin;

/**
* Contains current cts package, class, method.
*
* {@hide}
*/
public class CtsRecord {

    private static String mPackage;
    private static String mClass;
    private static String mMethod;

    public CtsRecord() {

    }

    /*
      Save current cts package name.
    */
    public static void setCtsPackage(String ctsPackage) {
        mPackage = ctsPackage;
        System.out.println("setCtsPackage mPackage:"+mPackage);
    }

    /*
      Save current cts class name.
    */
    public static void setCtsClass(String ctsClass) {
        mClass = ctsClass;
    }

    /*
      Save current cts method name.
    */
    public static void setCtsMethod(String ctsMethod) {
        mMethod = ctsMethod;
        if (preferCtsCase()){
            System.out.println("startThread");
            CtsPlugin mCtsPlugin = new CtsPlugin();
            mCtsPlugin.startThread();
        }
    }

    /*
      Reset preset condition which set by plugin function.
    */
    public static void endThread() {
        if (preferCtsCase()) {
            System.out.println("endThead");
            CtsPlugin mCtsPlugin = new CtsPlugin();
            mCtsPlugin.endThread();
        }
    }

    /*
      Return current cts package name.
    */
    public static String getCtsPackage() {
        return mPackage;
    }

    /*
      Return current cts class name.
    */
    public static String getCtsClass() {
        return mClass;
    }

    /*
      Return current cts method name.
    */
    public static String getCtsMethod() {
        return mMethod;
    }

    /*
      Compare current cts case(include package, class and method) to preferred.
      Return true if they are equal.
    */
    private static boolean preferCtsCase() {
        boolean preferred = false;
        System.out.println("preferCtsCase mClass:"+mClass+" mMethod:"+mMethod);
        if (prefCtsPackage() && prefCtsClass() && prefCtsMethod())
            preferred = true;
        return preferred;
    }

    /*
      Compare current cts package to preferred.
      Return true if they are equal.
      If more than one package need plugin, use like
        if (mPackage!= null &&
            ("android.net.cts".equals(mPackage) ||
             "android.net.cts.legacy.api22".equals(mPackage)))
            preferred = true;
    */
    private static boolean prefCtsPackage() {
        boolean preferred = false;
        if (mPackage!= null &&
            "android.net.cts".equals(mPackage))
            preferred = true;
        return preferred;
    }

    /*
      Compare current cts class to preferred.
      Return true if they are equal.
      If more than one class need plugin, use like
      if (mClass != null &&
            ("android.net.cts.ConnectivityManagerTest".equals(mClass) ||
             "android.net.cts.legacy.api22.ConnectivityManagerLegacyTest".equals(mClass)))
            preferred = true;
    */
    private static boolean prefCtsClass() {
        boolean preferred = false;
        if (mClass != null &&
            "android.net.cts.ConnectivityManagerTest".equals(mClass))
            preferred = true;
        return preferred;
    }

    /*
      Compare current cts method to preferred.
      Return true if they are equal.
      If more than one method need plugin, use like
      if (mMethod != null &&
            ("testGetNetworkInfo".equals(mMethod) ||
             "testStartUsingNetworkFeature_enableHipri".equals(mMethod)))
            preferred = true;
    */
    private static boolean prefCtsMethod() {
        boolean preferred = false;
        if (mMethod != null &&
            "testGetNetworkInfo".equals(mMethod))
            preferred = true;
        return preferred;
    }

}
