/*************************************************************************
 LmJniBridge  -  description
 -------------------
 début                : 2015
 copyright            : (C) 2015 par Rani Baghezza
 *************************************************************************/

//---------- Interface de la classe <LmJniBridge> (fichier LmJniBridge.h) ------
#ifndef LMJNICPPFACADE_H_
#define LMJNICPPFACADE_H_

#include "../cocos2d/cocos/platform/android/jni/JniHelper.h"
#include <string>
#include <vector>
#include "../../JSONParser/Includes/LmJParserWifiDirect.h"
#include "WifiDirectFacade.h"

extern "C" {
JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_jniFacade_JniCppFacade_onGettingPeers(
		JNIEnv* env, jobject thiz, jobject peers);

JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_jniFacade_JniCppFacade_onReceivingString(
		JNIEnv* env, jobject thiz, jstring s);

JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_jniFacade_JniCppFacade_onReceivingInt(
		JNIEnv* env, jobject thiz, jint i);

JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_jniFacade_JniCppFacade_onReceivingBool(
		JNIEnv* env, jobject thiz, jboolean b);

JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_jniFacade_JniCppFacade_onReceivingLong(
		JNIEnv* env, jobject thiz, jlong l);

JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_jniFacade_JniCppFacade_onReceivingFloat(
		JNIEnv* env, jobject thiz, jfloat f);

JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_jniFacade_JniCppFacade_onReceivingDouble(
		JNIEnv* env, jobject thiz, jdouble d);

JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_jniFacade_JniCppFacade_onReceivingBytes(
		JNIEnv* env, jobject thiz, jbyteArray bytes);

JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_jniFacade_JniCppFacade_onReceivingFile(
		JNIEnv* env, jobject thiz, jstring path);

JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_jniFacade_JniCppFacade_onReceivingChar(
		JNIEnv* env, jobject thiz, jchar c);

JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_jniFacade_JniCppFacade_onReceivingByte(
		JNIEnv* env, jobject thiz, jbyte byte);

}
;

class LmJniCppFacade {

public:

	static WifiDirectFacade* getWifiFacade();

	static void setWifiFacade(WifiDirectFacade* wifiFacade);

	inline static int toCObject(jint i) {
		return (int) i;
	}

	inline static bool toCObject(jboolean b) {
		return (bool) b;
	}

	inline static char toCObject(jchar c) {
		return (char) c;
	}

	inline static double toCObject(jdouble d) {
		return (double) d;
	}

	inline static float toCObject(jfloat f) {
		return (float) f;
	}

	inline static long toCObject(jlong l) {
		return (long) l;
	}

	inline static byte toCObject(jbyte b) {
		return (byte) b;
	}

	inline static bytes toCObject(jbyteArray byteArray, JNIEnv* env) {
		bytes res;
		jboolean isCopy;
		res.data = (byte*) env->GetByteArrayElements(byteArray, &isCopy);
		res.len = env->GetArrayLength(byteArray);
		return res;
	}

	inline static std::string toCObject(jstring jstr, JNIEnv* env) {
		const char *s = env->GetStringUTFChars(jstr, 0);
		return std::string(s);
	}

	inline static std::vector<std::string> toSTDStringList(jstring jstr,
			JNIEnv* env) {
		std::string str = toCObject(jstr, env);
		LmJParserWifiDirect parser = LmJParserWifiDirect();
		return parser.ParseJSONDeviceOperation(str);
	}

private:
	static WifiDirectFacade* _wifiDirectFacade;
};

#endif //LMJNICPPFACADE_H
