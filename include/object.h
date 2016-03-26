#ifndef _OBJECT_SCHEMER
#define _OBJECT_SCHEMER

#include <string>
#include <iostream>
#include <sstream>

class Object {
public:
	virtual std::string toString() =0;
};

class Number : public Object {

	int value;	
public:

	Number(int v = 0): value(v) {
	}

	int getValue() {
		return value;
	}
	
	virtual std::string toString() override {
		std::ostringstream os;
		os<<value;
		return os.str();
	}
};

class String : public Object {

	std::string value;	

public:

	String(std::string v ): value(v) {
	}

	std::string getValue() {
		return value;
	}

	virtual std::string toString() override {
	}
};

class Function : public Object {

public:
	virtual std::string toString() override {
	}
};
#endif/*_OBJECT_SCHEMER*/
