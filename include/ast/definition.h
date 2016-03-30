#ifndef _DEFINITION_SCHEMER
#define _DEFINITION_SCHEMER

#include "astlist.h"
#include "defformals.h"
#include "env.h"

#include <deque>


class Definition : public AstList {
public:	
	Definition(std::deque<std::shared_ptr<AstTree>> &var) 
	:AstList(var) {

	}

};

class DefinitionNormal : public Definition {
public:	
	DefinitionNormal(std::deque<std::shared_ptr<AstTree>> &var) 
	:Definition(var) {

	}

};



class DefinitionVarlist : public Definition {
public:
	DefinitionVarlist(std::deque<std::shared_ptr<AstTree>> &var) 
	:Definition(var) {

	}

};


#endif/*_DEFINITION_SCHEMER*/
