#ifndef _OBJECT_SCHEMER
#define _OBJECT_SCHEMER

#include <string>
#include <iostream>
#include <sstream>
#include <map>
#include <list>

#include "excpetion.h"

class Object {
	bool marked = false;
public:
	static std::list<Object*> objectList;

	virtual std::string toString() =0;
	bool getMarked() {
		return 	marked;
	}
	void setMarked() {
		marked = true;
	}
	void cleanMarked() {
		marked = false;
	}
	static void append(Object* obj) {
		objectList.push_back(obj);
	}

	static void release(Object *obj) {
		delete obj;
	};
	virtual ~Object() = default;
};

class EnvironmentObject : public Object {
	std::map<std::string,Object*> value;
	EnvironmentObject* outerEnv;
public:
	EnvironmentObject(EnvironmentObject *env)
	:outerEnv(env) {
	}

	static EnvironmentObject* allocEnv(EnvironmentObject *val) {
		EnvironmentObject* obj = new EnvironmentObject(val);
		append(obj);
		return obj;
	};

	Object* get(std::string name) {
		throw *new SchemeError("Environment get");
	}

	auto getIterBegin()->decltype(value.begin()) {
		return value.begin();
	}

	auto getIterEnd()->decltype(value.end()) {
		return value.end();
	}

	void put(std::string name,Object* obj) {
		value[name] = obj;
	}

	EnvironmentObject *makeEnv() {
		return allocEnv(outerEnv);
	}

	EnvironmentObject *outer() {
		return outerEnv;
	}

	virtual std::string toString() override {
		throw *new SchemeError("Environment toString");
	}
	virtual ~EnvironmentObject() override {
		throw *new SchemeError("Environment ~Environment");
	}
};

class NumberObject : public Object {
	int value;	
public:
	NumberObject(int v): value(v) {
	}

	static NumberObject* allocNumber(int val) {
		NumberObject* obj = new NumberObject(val);
		append(obj);
		return obj;
	};

	virtual std::string toString() override {
		std::ostringstream os;
		os<<value;
		return "Number object :"+os.str();
	}

	virtual ~NumberObject() {
		std::cout<<toString()<<" destoryed"<<std::endl;
	}
};
/*
class Id : public Object {
	std::string value;	
public:
	NumberObject(int v = 0): value(v) {
	}
};*/

class BooleanObject : public Object {
	bool value;	
public:
	BooleanObject(bool v): value(v) {
	}

	static BooleanObject* allocBoolean(bool val) {
		BooleanObject* obj = new BooleanObject(val);
		append(obj);
		return obj;
	};

	virtual std::string toString() override {
		if(value)
			return "Bool object: true";
		return "Bool object: false";
	}
	virtual ~BooleanObject() override {
		throw *new SchemeError("BooleanObject ~BooleanObject");
	}
};


class StringObject : public Object {
	std::string value;	
public:
	StringObject(std::string v): value(v) {
	}

	static StringObject* allocString(std::string val) {
		StringObject* obj = new StringObject(val);
		append(obj);
		return obj;
	};

	virtual std::string toString() override {
		return value;
	}
	virtual ~StringObject() override {
		throw *new SchemeError("StringObject ~StringObject");
	}
};


class FunctionObject : public Object {
public:
	virtual EnvironmentObject* getEnv()=0;
};

class PrimFunction : public FunctionObject {
public:
/*
	virtual ~PrimFunction() override {
		throw *new PrimFunction("PrimFunction ~PrimFunction");
	}
*/
};

class NormalFunction : public FunctionObject {
	std::string name;
public:
	

};
#endif/*_OBJECT_SCHEMER*/
