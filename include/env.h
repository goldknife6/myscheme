#ifndef _ENV_SCHEMER
#define _ENV_SCHEMER

#include <string>
#include <map>
#include <memory>

class Object;

class Environment {
	std::map<std::string,Object*> value;
	std::shared_ptr<Environment> outerEnv;
public:
	Environment(std::shared_ptr<Environment> env)
	:outerEnv(env) {
	}

	Object* get(std::string name) {
	}

	void put(std::string name,Object* obj) {
	}

	std::shared_ptr<Environment> makeEnv() {
		return std::shared_ptr<Environment>(new Environment(outerEnv));
	}

	std::shared_ptr<Environment> outer() {
		return outerEnv;
	}
};



#endif/*_ENV_SCHEMER*/
