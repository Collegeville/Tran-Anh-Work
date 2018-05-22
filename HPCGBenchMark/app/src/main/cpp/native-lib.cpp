#include <jni.h>
#include <string>
#include "main.cpp"

extern "C" JNIEXPORT jstring

JNICALL
Java_com_example_anhbt_hpcgbenchmark_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

extern "C" JNIEXPORT jint
JNICALL
Java_com_example_anhbt_hpcgbenchmark_MainActivity_hpcg(JNIEnv *env, jint nx, jint ny, jint nz){
    return main.main(nx, ny, nz);
}