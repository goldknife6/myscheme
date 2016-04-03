#include <iostream>
#include <fstream>
#include <memory>


#include "lexer.h"
#include "parser.h"
#include "excpetion.h"
#include "gc.h"

static Object *add(Procedure* args,EnvironmentObject *env) {
	int num = args->numChildren();
	int acc = 0;
	for(int i = 1;i < num; i++) {
		std::shared_ptr<Expression> tmp = args->getExp(i);	
		NumberObject *obj = dynamic_cast<NumberObject*>(tmp->eval(env));
		if(!obj) {
			std::cout<<i<<std::endl;
			throw *new SchemeError("add call");
		}
		acc += obj->getValue();
	}
	return NumberObject::allocNumber(acc);
}

static Object *less(Procedure* args,EnvironmentObject *env) {
	int num = args->numChildren();
	if(num != 3) {
		throw *new IllFormedException(args->toString());
	}
	NumberObject *obj1 = dynamic_cast<NumberObject*>(args->getExp(1)->eval(env));
	NumberObject *obj2 = dynamic_cast<NumberObject*>(args->getExp(2)->eval(env));

	if(!obj1 || !obj2) {
		throw *new IllFormedException(args->toString());
	}

	return BooleanObject::allocBoolean(obj1->getValue() < obj2->getValue());
}

static Object *display(Procedure* args,EnvironmentObject *env) {
	int num = args->numChildren();
	Object *obj;
	for(int i = 1;i < num; i++) {
		std::shared_ptr<Expression> tmp = args->getExp(i);	
		obj = tmp->eval(env);
		if(!obj) {
			throw *new SchemeError("add call");
		}
		std::cout<<obj->toString();
	}
	return nullptr;
}


static void initEnv(EnvironmentObject *globalEnv) {
	globalEnv->put("+",NativeFunctionObject::allocNativeFunction(globalEnv,add));
	globalEnv->put("<",NativeFunctionObject::allocNativeFunction(globalEnv,less));
	globalEnv->put("display",NativeFunctionObject::allocNativeFunction(globalEnv,display));
}



int main(int argc,char *argv[])
{
	std::ifstream ifs;
	
	if (argc != 2) { 
		std::cerr<<"usage: "<<argv[0]<<"  <filename>"<<std::endl;
		exit(1);
	}

	ifs.open(argv[1]);
	
	if (!ifs.is_open()) {
		std::cerr<<"can't open file:  "<<argv[1]<<std::endl;
		exit(1);
	}

	//Lexer lexer(std::cin);
	Lexer lexer(ifs);
	
	Parser parser(lexer);


	EnvironmentObject *globalEnv = EnvironmentObject::allocEnv(nullptr);
	initEnv(globalEnv);
	std::shared_ptr<AstTree> tree = nullptr;

	try {
		tree = parser.beginParse();
	} catch (UnbalancedException &e) {
		e.printMsg();
	} catch (EOFException &e) {
		e.printMsg();
		return 0;
	} catch(IllFormedException &e) {
		e.printMsg();
	} catch (SchemeError &e) {
		e.printMsg();
		return 0;
	} catch (KeywordException &e) {
		e.printMsg();
	} catch (...) {
		std::cerr<<"what exception?1"<<std::endl;
	}
	
	while(true) {
		try {
			
			if(tree) {
				//std::cout<<tree->toString()<<std::endl;
				Object* obj = tree->eval(globalEnv);
				//std::cout<<tree<<std::endl;
				if(obj) {
					std::cout<<obj->toString()<<std::endl;
				}
				
			}
			
			//GarbageCollection::clean(globalEnv);
		} catch (UnboundException &e) {
			e.printMsg();
		} catch (NotAppException &e) {
			e.printMsg();
		} catch (EOFException &e) {
			e.printMsg();
			return 0;
		} catch(SchemeError &e) {
			e.printMsg();
			return 0;
		} catch(IllFormedException &e) {
			e.printMsg();
		} catch (ArugNotMutchException &e) {
			e.printMsg();
		}  catch (...) {
			std::cerr<<"what exception?2"<<std::endl;	
			throw;
		}

		try {
			tree = parser.beginParse();
		} catch (UnbalancedException &e) {
			tree = nullptr;
			e.printMsg();
		} catch (EOFException &e) {
			e.printMsg();
			return 0;
		} catch (SchemeError &e) {
			e.printMsg();
			return 0;
		} catch (KeywordException &e) {
			tree = nullptr;
			e.printMsg();
		} catch (...) {
			std::cerr<<"what exception?3"<<std::endl;
		}
	}
	
}
