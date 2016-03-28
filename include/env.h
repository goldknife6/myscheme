#ifndef _ENV_SCHEMER
#define _ENV_SCHEMER

#include <string>
#include <map>
#include <memory>

class Object;

class Environment {
	std::map<std::string,std::shared_ptr<Object>> value;
	std::shared_ptr<Environment> outer;
public:
	Environment(std::shared_ptr<Environment> e = nullptr)
	:outer(e) {
	}

	void put(std::string name, std::shared_ptr<Object> obj) {
		value[name] = obj;
	}

   	std::shared_ptr<Object> get(std::string name) {
		std::map<std::string,std::shared_ptr<Object>>::iterator it;
		it = value.find(name);

		if (it != value.end())
			return it->second;

		return nullptr;
	}
};



#endif/*_ENV_SCHEMER*/
