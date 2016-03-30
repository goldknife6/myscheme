#ifndef _ENV_SCHEMER
#define _ENV_SCHEMER

#include <string>
#include <map>
#include <memory>

class Object;

class Environment {
	std::map<std::string,Object*> value;
public:
	Environment(std::shared_ptr<Environment> env) {
	}
};



#endif/*_ENV_SCHEMER*/
