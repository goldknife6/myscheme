#ifndef _GC_SCHEMER
#define _GC_SCHEMER

#include "object.h"

extern std::list<Object*> Object::objectList;
namespace GarbageCollection {
	void mark(Object *obj) {
		if(obj->getMarked()) 
			return;
		obj->setMarked();
		EnvironmentObject *env = dynamic_cast<EnvironmentObject *>(obj);
		auto begin = env->getIterBegin();
		auto end = env->getIterEnd();
		for(;begin != end; begin++) {
			Object *foo = begin->second;
			if(typeid(*foo) == typeid(EnvironmentObject)) {
				mark(begin->second);
			} else if (typeid(*foo) == typeid(FunctionObject)) {
				foo->setMarked();
				FunctionObject *func = dynamic_cast<FunctionObject*>(foo);
				mark(func->getEnv());
			} else {
				foo->setMarked();
			}
		}
			
	}
	void sweep() {
		auto begin = Object::objectList.begin();
		auto end = Object::objectList.end();
		for(;begin != end;) {
			if((*begin)->getMarked()) {
				(*begin)->cleanMarked();
				begin++;
			} else {
				Object::release(*begin);
				begin = Object::objectList.erase(begin);
			}
		}

	}
}
#endif/*_GC_SCHEMER*/
