#ifndef _PROCEDURE_SCHEMER
#define _PROCEDURE_SCHEMER

#include "astlist.h"
#include "env.h"

class Procedure : public AstList {
public:
	Procedure(std::deque<AstTree*> &deque)
	:AstList(deque) {
		
	}

	virtual std::string toString() override {
		std::string s;
		s += "(proc  ";
		std::string sep("");
		AstTree *p;
		
		for(int i = 0; (i < numChildren()) && (p = child(i)); i++) {
			s += sep;
			s += p->toString();
			sep = "  ";
		}
		s += ") ";
		return s;
	}

	virtual void check() override {
		std::cout<<"Procedure check not impelmented"<<std::endl;
	}

	virtual std::shared_ptr<Object> eval(std::shared_ptr<Environment> e) override {
		AstTree *fristChild = child(0);

		if (!fristChild) return nullptr;

		try {
			std::shared_ptr<Object> p = fristChild->eval(e);

			std::shared_ptr<NormalFunction> f = std::dynamic_pointer_cast<NormalFunction>(p);

			if(!f.use_count()) 
				throw *new NotAppException(fristChild->toString());

			std::shared_ptr<Environment> newEnv = f->makeEnv();
			DefFormals* def = f->parameters();
			def->eval(newEnv);

			Body* b = f->body();
			return b->eval(newEnv);		
	
		} catch (UnboundException &e) {
			if(fristChild->toString() == "+")
				e.printMsg();
		}


		
		
		return nullptr;
	}
};




#endif/*_PROCEDURE_SCHEMER*/
