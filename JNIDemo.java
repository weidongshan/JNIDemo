
public class JNIDemo {
	static { 		/* 1. load */
		System.loadLibrary("native"); /* libnative.so */
 	}
	public native int hello(int[] a);
	public static void main (String args[]) {
		JNIDemo d = new JNIDemo();	
		int [] a = {1, 2, 3}; 

		/* 2. map java hello <-->c c_hello */

		/* 3. call */
		System.out.println(d.hello(a));
	}
}

