#ifndef _OBJECT_SCHEMER
#define _OBJECT_SCHEMER

#include <string>
#include <iostream>
#include <sstream>
#include <ast/defformals.h>
#include <ast/body.h>
#include <env.h>
#include <excpetion.h>

class Object {
public:
	virtual std::string toString() =0;
	
};

class Number : public Object {

	int value;	
public:

	Number(int v = 0): value(v) {
	}

};

class Id : public Object {

	std::string value;	

};

class Bool : public Object {

	bool value;	

};


class String : public Object {

	std::string value;	

};


class Function : public Object {
public:

};

class PrimFunction : public Function {
public:
	

};

class NormalFunction : public Function {
	std::string name;
public:
	

};
#endif/*_OBJECT_SCHEMER*/
