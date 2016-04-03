#ifndef _OBJECT_SCHEMER
#define _OBJECT_SCHEMER

#include <string>
#include <iostream>
#include <sstream>
#include <map>
#include <list>

#include "excpetion.h"
#include "ast/asttree.h"

class Procedure;

class Object {
	bool marked = false;
public:
	static std::list<Object*> objectList;

	virtual std::string toString() =0;
	virtual Object *copyObject() =0;
	virtual ~Object() = default;

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
	
};

class EnvironmentObject : public Object {
	std::map<std::string,Object*> value;
	EnvironmentObject* outerEnv;
public:
	EnvironmentObject(EnvironmentObject *env)
	:outerEnv(env) {
		//static Object *add(Object** args)
		//put("+",NativeFunctionObject::allocNativeFunction(EnvironmentObject *e,FuncPointer fp) );
	}

	static EnvironmentObject* allocEnv(EnvironmentObject *val) {
		EnvironmentObject* obj = new EnvironmentObject(val);
		append(obj);
		return obj;
	};

	virtual EnvironmentObject *copyObject() override {
		EnvironmentObject* tmp = allocEnv(outerEnv);
		*tmp = *this;
		return tmp;
	}

	Object* get(std::string name) {
		auto it = value.find(name);
		if(it != value.end()) {
			return it->second;
		} else if (outerEnv != nullptr) {
			return outerEnv->get(name);
		}
		return nullptr;
	}
	EnvironmentObject *where(std::string name) {
		if(value.find(name) != value.end())
			return this;
		else if (outerEnv == nullptr)
			return nullptr;
		else
			return outerEnv->where(name);
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
		//std::cout<<"~Environment"<<std::endl;
	}
};

class NumberObject : public Object {
	int value;	
public:
	NumberObject(int v): value(v) {
	}
	int getValue() {
		return value;	
	}
	static NumberObject* allocNumber(int val) {	
		NumberObject* obj;
		obj = new NumberObject(val);
		append(obj);
		return obj;
	};

	virtual NumberObject *copyObject() override {
		NumberObject* obj = allocNumber(value);
		return obj;
	}

	virtual std::string toString() override {
		std::ostringstream os;
		os<<value;
		return "Number object :"+os.str() + "\n";
	}

	virtual ~NumberObject() {
		//std::cout<<toString()<<" destoryed"<<std::endl;
	}
};


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

	bool getValue() {
		return value;
	}

	virtual BooleanObject *copyObject() override {
		BooleanObject* obj = allocBoolean(value);
		return obj;
	}

	virtual std::string toString() override {
		if(value)
			return "\nBool object: true";
		return "\nBool object: false";
	}
	virtual ~BooleanObject() override {
		//std::cout<<toString()<<" destoryed"<<std::endl;
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

	virtual StringObject *copyObject() override {
		return allocString(value);
	}

	virtual std::string toString() override {
		return value + "\n";
	}
	virtual ~StringObject() override {
		//std::cout<<toString()<<" destoryed"<<std::endl;
	}
};

class DefFormals;
class Body;

class FunctionObject : public Object {
public:
	std::shared_ptr<DefFormals> def;
	std::shared_ptr<Body> body;
	EnvironmentObject *env;

	FunctionObject(std::shared_ptr<DefFormals> d,
		std::shared_ptr<Body> b,
		EnvironmentObject *e)
	:def(d),body(b),env(e) {
	}

	virtual std::shared_ptr<DefFormals> getParameters() {
		return 	def;
	}
	virtual std::shared_ptr<Body> getBody()  {
		return 	body;
	}
	virtual EnvironmentObject *makeEnv()  {
		return 	EnvironmentObject::allocEnv(env);
	}
	virtual EnvironmentObject* getEnv()  {
		return 	env;
	}
};



class NativeFunctionObject : public FunctionObject {
	typedef Object *(*FuncPointer)(Procedure*,EnvironmentObject*);
	FuncPointer backcall;
public:
	NativeFunctionObject(EnvironmentObject *env,FuncPointer fp)
	:FunctionObject(nullptr,nullptr,env),backcall(fp) {}

	static NativeFunctionObject *allocNativeFunction(EnvironmentObject *env,FuncPointer fp) {
		NativeFunctionObject* obj = new NativeFunctionObject(env,fp);
		append(obj);
		return obj;
	};


	virtual Object *copyObject() override {
		throw *new SchemeError("NativeFunctionObject copyObject called");
	}

	virtual std::string toString() override {
		return "\nNativeFunctionObject";
	}

	virtual ~NativeFunctionObject() override {
		std::cout<<"~NativeFunctionObject called"<<std::endl;
	}

	Object *invoke(Procedure* args,EnvironmentObject *env) {
		return backcall(args,env);	
	}
};



class NormalFunctionObject : public FunctionObject {
	std::string name;
public: 
	NormalFunctionObject(std::shared_ptr<DefFormals> d,
		std::shared_ptr<Body> b,
		EnvironmentObject *env)
	:FunctionObject(d,b,env) {}

	static NormalFunctionObject *allocNormalFunction(std::shared_ptr<DefFormals> d,
					std::shared_ptr<Body> b,
					EnvironmentObject *env) {
		NormalFunctionObject* obj = new NormalFunctionObject(d,b,env);
		append(obj);
		return obj;
	};

	virtual Object *copyObject() override {
		return allocNormalFunction(def,body,env);
	}

	virtual std::string toString() override {
		return "\nNormalFunctionObject " + name;
	}

	virtual ~NormalFunctionObject() override {
		std::cout<<name<<" ~NormalFunctionObject"<<std::endl;
	}
};
#endif/*_OBJECT_SCHEMER*/
