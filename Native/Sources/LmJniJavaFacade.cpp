//------------------------------------------------------ Include personnel
#include "../Includes/LmJniJavaFacade.h"
#include <iostream>

#define JAVACLASS "org/cocos2dx/cpp/JniFacade"
#define PARAM_VOID "()V"
#define PARAM_STRING "(Ljava/lang/String;)V"
#define PARAM_BOOLEAN "(Z)V"
#define PARAM_INT "(I)V"
#define PARAM_BYTE "(B)V"
#define PARAM_BYTES "([B)V"
#define PARAM_CHAR "(C)V"
#define PARAM_LONG "(J)V"
#define PARAM_FLOAT "(F)V"
#define PARAM_DOUBLE "(D)V"

using namespace std;

void LmJniJavaFacade::callJavaMethod(const char* name, void* arg,
		const char* param) {
	NS_CC::JniMethodInfo method;
	NS_CC::JniHelper::getStaticMethodInfo(method, JAVACLASS, name, param);

	if (arg == PARAM_VOID) {
		method.env->CallStaticObjectMethod(method.classID, method.methodID);
	} else if (arg == PARAM_STRING) {

		method.env->CallStaticObjectMethod(method.classID, method.methodID,
				toJObject(PTR_TO_OBJ(arg, string), method.env));
			} else if (arg == PARAM_INT) {

				method.env->CallStaticObjectMethod(method.classID, method.methodID,
				toJObject(PTR_TO_OBJ(arg, int)));
	} else if (arg == PARAM_FLOAT) {

		method.env->CallStaticObjectMethod(method.classID, method.methodID,
				toJObject(PTR_TO_OBJ(arg, float)));
	} else if (arg == PARAM_LONG) {

		method.env->CallStaticObjectMethod(method.classID, method.methodID,
				toJObject(PTR_TO_OBJ(arg, long)));
	} else if (arg == PARAM_DOUBLE) {

		method.env->CallStaticObjectMethod(method.classID, method.methodID,
				toJObject(PTR_TO_OBJ(arg, double)));
	} else if (arg == PARAM_BOOLEAN) {

		method.env->CallStaticObjectMethod(method.classID, method.methodID,
				toJObject(PTR_TO_OBJ(arg, bool)));
	} else if (arg == PARAM_CHAR) {

		method.env->CallStaticObjectMethod(method.classID, method.methodID,
				toJObject(PTR_TO_OBJ(arg, char)));
	} else if (arg == PARAM_BYTE) {

		method.env->CallStaticObjectMethod(method.classID, method.methodID,
				toJByte(PTR_TO_OBJ(arg, byte)));
	} else if (arg == PARAM_BYTES) {

		method.env->CallStaticObjectMethod(method.classID, method.methodID,
				toJObject(PTR_TO_OBJ(arg, bytes), method.env));
	}
	}

void LmJniJavaFacade::send(string s) {
	callJavaMethod("send", (void*) &s, PARAM_STRING);
}

void LmJniJavaFacade::send(bool b) {
	callJavaMethod("send", (void*) &b, PARAM_BOOLEAN);
}

void LmJniJavaFacade::send(int i) {
	callJavaMethod("send", (void*) &i, PARAM_INT);
}

void LmJniJavaFacade::send(long l) {
	callJavaMethod("send", (void*) &l, PARAM_LONG);
}

void LmJniJavaFacade::send(char c) {
	callJavaMethod("send", (void*) &c, PARAM_CHAR);
}

void LmJniJavaFacade::send(double d) {
	callJavaMethod("send", (void*) &d, PARAM_DOUBLE);
}

void LmJniJavaFacade::sendFile(string path) {
	callJavaMethod("sendFile", (void*) &path, PARAM_STRING);
}

void LmJniJavaFacade::sendByte(byte b) {
	callJavaMethod("sendByte", (void*) &b, PARAM_BYTE);
}

void LmJniJavaFacade::sendBytes(bytes bytes) {
	callJavaMethod("sendBytes", (void*) &bytes, PARAM_BYTES);
}

void LmJniJavaFacade::send(float f) {
	callJavaMethod("send", (void*) &f, PARAM_FLOAT);
}

void LmJniJavaFacade::discoverPeers() {
	callJavaMethod("discoverPeers", (void*) 0, PARAM_VOID);
}

void LmJniJavaFacade::connectTo(string deviceName) {
	callJavaMethod("connectTo", (void*) (&deviceName), PARAM_STRING);

}

LmJniJavaFacade::LmJniJavaFacade(const LmJniJavaFacade & unLmJniBridge) {

}

LmJniJavaFacade::LmJniJavaFacade() {

}

LmJniJavaFacade::~LmJniJavaFacade() {

}

