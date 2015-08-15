
public class JNIDemo {
	static { 		/* 1. load */
		System.loadLibrary("native"); /* libnative.so */
 	}
	public native String hello(String str);
	public static void main (String args[]) {
		JNIDemo d = new JNIDemo();		

		/* 2. map java hello <-->c c_hello */

		/* 3. call */
		System.out.println(d.hello("this is java"));
	}
}

