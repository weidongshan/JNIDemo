
#include <jni.h>  /* /usr/lib/jvm/java-1.7.0-openjdk-amd64/include/ */
#include <stdio.h>
#include <stdlib.h>
 
#if 0
typedef struct {
    char *name;          /* Java里调用的函数名 */
    char *signature;    /* JNI字段描述符, 用来表示Java里调用的函数的参数和返回值类型 */
    void *fnPtr;          /* C语言实现的本地函数 */
} JNINativeMethod;
#endif

jintArray c_hello(JNIEnv *env, jobject cls, jintArray arr)
{
	jint *carr;
	jint *oarr;
	jintArray rarr;
	
	jint i, n = 0;
	carr = (*env)->GetIntArrayElements(env, arr, NULL);
	if (carr == NULL) {
		return 0; /* exception occurred */
	}

	n = (*env)->GetArrayLength(env, arr);
	oarr = malloc(sizeof(jint) * n);
	if (oarr == NULL)
	{
		(*env)->ReleaseIntArrayElements(env, arr, carr, 0);
		return 0;
	}

	for (i = 0; i < n; i++)
	{
		oarr[i] = carr[n-1-i];
	}
	
	(*env)->ReleaseIntArrayElements(env, arr, carr, 0);

	/* create jintArray */
	rarr = (*env)->NewIntArray(env, n);
	if (rarr == NULL)
	{
		return 0;
	}

	(*env)->SetIntArrayRegion(env, rarr, 0, n, oarr);
	free(oarr);
	
	return rarr;
}


static const JNINativeMethod methods[] = {
	{"hello", "([I)[I", (void *)c_hello},
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

