package junit.framework;

import java.lang.Thread;
import junit.framework.CtsRecord;

/**
* {@hide}
*/
public class CtsPlugin {

    private Thread ctsThread;

    public CtsPlugin() {

    }

    /*
      Start new thread to load plugin function.
    */
    public void startThread() {
        System.out.println("new thread");
        if (ctsThread == null) {
            ctsThread = new Thread(){
                @Override
                public void run() {
                    System.out.println("call loadCtsPlugin");
                    loadCtsPlugin();
                }
            };
        }
        ctsThread.start();
    }

    /*
      Load plugin function.
      If more than one case need plugin, use package/class/method name to distinguis them, like
      if ("android.net.cts".equals(mPackage)) {
          if ("android.net.cts.ConnectivityManagerTest".equals(mClass) && "testGetNetworkInfo".equals(mMethod)) {
              System.out.println("loadCtsPlugin testGetNetworkInfo");
          }
      } else if ("android.net.cts.legacy.api22".equals(mPackage)) {
          if ("android.net.cts.legacy.api22.ConnectivityManagerLegacyTest".equals(mClass) &&
            "testStartUsingNetworkFeature_enableHipri".equals(mMethod)) {
              System.out.println("loadCtsPlugin testStartUsingNetworkFeature_enableHipri");
          }
      }
    */
    private void loadCtsPlugin() {
        System.out.println("in loadCtsPlugin");
        String mPackage = CtsRecord.getCtsPackage();
        String mClass = CtsRecord.getCtsClass();
        String mMethod = CtsRecord.getCtsMethod();
        if ("android.net.cts".equals(mPackage)) {
            if ("android.net.cts.ConnectivityManagerTest".equals(mClass) && "testGetNetworkInfo".equals(mMethod)) {
                System.out.println("loadCtsPlugin testGetNetworkInfo");
            }
        }
    }

    /*
      Reset preset condition which set by plugin function and destroy thread.
    */
    public void endThread() {
        System.out.println("end plugin thread");
        resetCtsPlugin();
        ctsThread = null;
    }

    /*
      Reset plugin function.
      If more than one case need reset plugin, use package/class/method name to distinguis them, like
      if ("android.net.cts".equals(mPackage)) {
          if ("android.net.cts.ConnectivityManagerTest".equals(mClass) && "testGetNetworkInfo".equals(mMethod)) {
              System.out.println("resetCtsPlugin testGetNetworkInfo");
          }
      } else if ("android.net.cts.legacy.api22".equals(mPackage)) {
          if ("android.net.cts.legacy.api22.ConnectivityManagerLegacyTest".equals(mClass) &&
            "testStartUsingNetworkFeature_enableHipri".equals(mMethod)) {
              System.out.println("resetCtsPlugin testStartUsingNetworkFeature_enableHipri");
          }
      }
    */
    private void resetCtsPlugin() {
        System.out.println("resetCtsPlugin");
        String mPackage = CtsRecord.getCtsPackage();
        String mClass = CtsRecord.getCtsClass();
        String mMethod = CtsRecord.getCtsMethod();
        if ("android.net.cts".equals(mPackage)) {
            if ("android.net.cts.ConnectivityManagerTest".equals(mClass) && "testGetNetworkInfo".equals(mMethod)) {
                System.out.println("resetCtsPlugin testGetNetworkInfo");
            }
        }
    }
}
