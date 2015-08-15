
#include <jni.h>  /* /usr/lib/jvm/java-1.7.0-openjdk-amd64/include/ */
#include <stdio.h>

#if 0
typedef struct {
    char *name;          /* Java里调用的函数名 */
    char *signature;    /* JNI字段描述符, 用来表示Java里调用的函数的参数和返回值类型 */
    void *fnPtr;          /* C语言实现的本地函数 */
} JNINativeMethod;
#endif

jstring JNICALL c_hello(JNIEnv *env, jobject cls, jstring str)
{
	//printf("this is c : %s\n", str);
	//return "return from C";

	const jbyte *cstr;
	cstr = (*env)->GetStringUTFChars(env, str, NULL);
	if (cstr == NULL) {
		return NULL; /* OutOfMemoryError already thrown */
	}
	printf("Get string from java :%s\n", cstr);
	(*env)->ReleaseStringUTFChars(env, str, cstr);

	return (*env)->NewStringUTF(env, "return from c");
}


static const JNINativeMethod methods[] = {
	{"hello", "(Ljava/lang/String;)Ljava/lang/String;", (void *)c_hello},
};




/* System.loadLibrary */
JNIEXPORT jint JNICALL
JNI_OnLoad(JavaVM *jvm, void *reserved)
{
	JNIEnv *env;
	jclass cls;

	if ((*jvm)->GetEnv(jvm, (void **)&env, JNI_VERSION_1_4)) {
		return JNI_ERR; /* JNI version not supported */
	}
	cls = (*env)->FindClass(env, "JNIDemo");
	if (cls == NULL) {
		return JNI_ERR;
	}

	/* 2. map java hello <-->c c_hello */
	if ((*env)->RegisterNatives(env, cls, methods, 1) < 0)
		return JNI_ERR;

	return JNI_VERSION_1_4;
}

