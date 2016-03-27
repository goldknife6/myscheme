#ifndef _ENV_SCHEMER
#define _ENV_SCHEMER

#include "object.h"
#include <string>
#include <map>

class Env {
	std::map<std::string,Object*> value;
	Env *outer;
public:
	Env(Env *o = nullptr)
	:outer(o) {
	
	}

	virtual void put(std::string name, Object *obj) {
		std::map<std::string,Object*>::iterator it = value.find(name);
		if (it != value.end())
			delete it->second;

		value[name] = obj;
	}
   	virtual Object *get(std::string name) {
		std::map<std::string,Object*>::iterator it = value.find(name);
		if (it != value.end())
			return it->second;

		return nullptr;
	}
};



#endif/*_ENV_SCHEMER*/
