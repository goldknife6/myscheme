#ifndef _ENV_SCHEMER
#define _ENV_SCHEMER

#include <string>
#include <map>
#include <memory>

class Object;
class Function;

class Environment {
	std::map<std::string,std::shared_ptr<Object>> value;
	std::shared_ptr<Environment> outer;
public:
	Environment(std::shared_ptr<Environment> e)
	:outer(e) {
		std::cout<<"Environment"<<std::endl;
		if(e != nullptr)
			return;
	}

	~Environment() {
		std::cout<<"~Environment"<<std::endl;	
	}
	void put(std::string name, std::shared_ptr<Object> obj) {
		value[name] = obj;
	}

   	std::shared_ptr<Object> get(const std::string &name) {
		std::map<std::string,std::shared_ptr<Object>>::iterator it;
		it = value.find(name);
		
		if(it != value.end()) {
			return it->second;
		} else if (it == value.end() && outer!= nullptr) {
			return outer->get(name);
		} else {
			return nullptr;
		}
	}

	std::shared_ptr<Environment> outerEnv() {
		return outer;
	}
};



#endif/*_ENV_SCHEMER*/
