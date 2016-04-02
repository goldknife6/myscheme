#include <iostream>
#include <fstream>
#include <memory>


#include "lexer.h"
#include "parser.h"
#include "excpetion.h"
#include "gc.h"

static Object *add(std::shared_ptr<AstTree>* args,EnvironmentObject *env) {
	int i = 0;
	int acc = 0;
	while(args[i]) {
		NumberObject *obj = dynamic_cast<NumberObject*>(args[i]->eval(env));
		if(!obj)
			throw *new SchemeError("add call");
		acc += obj->getValue();
		i++;		
	}
	delete [] args;
	return NumberObject::allocNumber(acc);
}

static Object *less(std::shared_ptr<AstTree>* args,EnvironmentObject *env) {
	int i = 0;
	int acc = 0;
	while(args[i]) {
		NumberObject *obj = dynamic_cast<NumberObject*>(args[i]->eval(env));
		if(!obj)
			throw *new SchemeError("add call");
		acc += obj->getValue();
		i++;		
	}
	delete [] args;
	return NumberObject::allocNumber(acc);
}


static void initEnv(EnvironmentObject *globalEnv) {
	globalEnv->put("+",NativeFunctionObject::allocNativeFunction(globalEnv,add));
	globalEnv->put("<",NativeFunctionObject::allocNativeFunction(globalEnv,less));
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

	Lexer lexer(std::cin);
	//Lexer lexer(ifs);
	
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
			
			if(tree) {std::cout<<tree->toString()<<std::endl;
				Object* obj = tree->eval(globalEnv);
				if(obj) {
					std::cout<<obj->toString()<<std::endl;
				}
				
			}
			
			GarbageCollection::mark(globalEnv);
			GarbageCollection::sweep();
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
