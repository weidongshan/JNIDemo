

javac JNIDemo.java
gcc -I/usr/lib/jvm/java-1.7.0-openjdk-amd64/include/ -fPIC -shared -o libnative.so native.c
export LD_LIBRARY_PATH=.
java JNIDemo 


