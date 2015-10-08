#ifndef LMJNIJAVAFACADE_H_
#define LMJNIJAVAFACADE_H_

#include <string>
#include "helpers.h"
#include "cocos2d.h"

class LmJniJavaFacade {

public:

	static void send(std::string s);

	static void send(bool b);

	static void send(int i);

	static void send(long l);

	static void send(char c);

	static void send(double d);

	static void sendFile(std::string path);

	static void sendByte(byte b);

	static void sendBytes(bytes byte);

	static void send(float f);

	static void discoverPeers();

	static void connectTo(std::string deviceName);

	inline static jint toJObject(int i) {
		return (jint) i;
	}

	inline static jboolean toJObject(bool b) {
		return (jboolean) b;
	}

	inline static jchar toJObject(char c) {
		return (jchar) c;
	}

	inline static jdouble toJObject(double d) {
		return (jdouble) d;
	}

	inline static jfloat toJObject(float f) {
		return (jfloat) f;
	}

	inline static jlong toJObject(long l) {
		return (jlong) l;
	}

	inline static jbyte toJByte(byte b) {
		return (jbyte) b;
	}

	inline static jbyteArray toJObject(bytes byteArray, JNIEnv* env) {
		jbyteArray res = env->NewByteArray(toJObject(byteArray.len));
		env->SetByteArrayRegion(res, (jsize) 0, (jsize) (byteArray.len),
				(const jbyte *) byteArray.data);
		//env->SetByteArrayRegion(jbytearray array, jsize start, jsize len, const jbyte *);
		return res;
	}

	inline static jstring toJObject(std::string jstr, JNIEnv* env) {
		return env->NewStringUTF(jstr.c_str());
	}

	static void callJavaMethod(const char* name, void* o, const char* param);

	LmJniJavaFacade(const LmJniJavaFacade & unLmJniBridge);

	LmJniJavaFacade();

	virtual ~LmJniJavaFacade();

};

#endif // LMJNIJAVAFACADE_H
