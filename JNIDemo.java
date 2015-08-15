
public class JNIDemo {
	static { 		/* 1. load */
		System.loadLibrary("native"); /* libnative.so */
 	}
	public native int[] hello(int[] a);
	public static void main (String args[]) {
		JNIDemo d = new JNIDemo();	
		int [] a = {1, 2, 3}; 
		int [] b = null;
		int i;

		/* 2. map java hello <-->c c_hello */

		/* 3. call */
		b = d.hello(a);

		for (i = 0; i < b.length; i++)		
			System.out.println(b[i]);
	}
}

