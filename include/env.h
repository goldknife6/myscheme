#ifndef _ENV_SCHEMER
#define _ENV_SCHEMER

#include "object.h"
#include <string>

class Env {
public:
	virtual void put(std::string name, Object value);
   	virtual Object get(std::string name);
};



#endif/*_ENV_SCHEMER*/
