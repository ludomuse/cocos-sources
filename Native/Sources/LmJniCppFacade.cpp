#include "../Includes/LmJniCppFacade.h"

WifiDirectFacade* LmJniCppFacade::_wifiDirectFacade = NULL;

WifiDirectFacade* LmJniCppFacade::getWifiFacade() {
	return _wifiDirectFacade;
}

void LmJniCppFacade::setWifiFacade(WifiDirectFacade* wifiFacade) {
	_wifiDirectFacade = wifiFacade;
}

JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_jniFacade_JniCppFacade_onGettingPeers(
		JNIEnv* env, jobject thiz, jstring peers) {
	LmJniCppFacade::getWifiFacade()->onGettingPeers(
			LmJniCppFacade::toSTDStringList(peers, env));
}

JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_jniFacade_JniCppFacade_onReceivingString(
		JNIEnv* env, jobject thiz, jstring s) {
	LmJniCppFacade::getWifiFacade()->onReceiving(
			LmJniCppFacade::toCObject(s, env));
}

JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_jniFacade_JniCppFacade_onReceivingInt(
		JNIEnv* env, jobject thiz, jint i) {
	LmJniCppFacade::getWifiFacade()->onReceiving(LmJniCppFacade::toCObject(i));
}

JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_jniFacade_JniCppFacade_onReceivingBool(
		JNIEnv* env, jobject thiz, jboolean b) {
	LmJniCppFacade::getWifiFacade()->onReceiving(LmJniCppFacade::toCObject(b));
}

JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_jniFacade_JniCppFacade_onReceivingLong(
		JNIEnv* env, jobject thiz, jlong l) {
	LmJniCppFacade::getWifiFacade()->onReceiving(LmJniCppFacade::toCObject(l));
}

JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_jniFacade_JniCppFacade_onReceivingFloat(
		JNIEnv* env, jobject thiz, jfloat f) {
	LmJniCppFacade::getWifiFacade()->onReceiving(LmJniCppFacade::toCObject(f));
}

JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_jniFacade_JniCppFacade_onReceivingDouble(
		JNIEnv* env, jobject thiz, jdouble d) {
	LmJniCppFacade::getWifiFacade()->onReceiving(LmJniCppFacade::toCObject(d));
}

JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_jniFacade_JniCppFacade_onReceivingBytes(
		JNIEnv* env, jobject thiz, jbyteArray bytes) {
	LmJniCppFacade::getWifiFacade()->onReceiving(
			LmJniCppFacade::toCObject(bytes, env));
}

JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_jniFacade_JniCppFacade_onReceivingFile(
		JNIEnv* env, jobject thiz, jstring path) {
	LmJniCppFacade::getWifiFacade()->onReceivingFile(
			LmJniCppFacade::toCObject(path, env));
}

JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_jniFacade_JniCppFacade_onReceivingByte(
		JNIEnv* env, jobject thiz, jbyte byte) {
	LmJniCppFacade::getWifiFacade()->onReceivingByte(
			LmJniCppFacade::toCObject(byte));
}

JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_jniFacade_JniCppFacade_onReceivingChar(
		JNIEnv* env, jobject thiz, jchar c) {
	LmJniCppFacade::getWifiFacade()->onReceiving(LmJniCppFacade::toCObject(c));
}

