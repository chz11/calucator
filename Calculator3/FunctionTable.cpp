#include "FunctionTable.h"
#include<iostream>
#include<cmath>
#include "SymbolTable.h"
#include<cassert>
struct FunctionEntry
{
	PtrFun pFun_;
	std::string funName;
};
FunctionEntry Entrys[] =
{
	log, "log",
	log10,"log10",
	exp,"exp",
	sqrt,"sqrt",
	sin,"sin",
	cos,"cos",
	tan,"tan",
	sinh,"sinh",
	cosh,"cosh",
	tanh,"tanh",
	asin,"asin",
	acos,"acos",
	atan,"atan"

};
FunctionTable::FunctionTable(SymbolTable& tbl):size_(sizeof(Entrys)/sizeof(Entrys[0]))
{
	
	Init(tbl);
}
void FunctionTable::Init(SymbolTable& tbl)
{
	std::cout << "function list:"<<std::endl;
	pFuns_ = new PtrFun[size_];
	for (unsigned int i = 0;i < size_;++i)
	{
		pFuns_[i] = Entrys[i].pFun_;
		unsigned int j = tbl.Add(Entrys[i].funName);
		assert(i == j);
		std::cout << Entrys[i].funName << std::endl;
	}
}
FunctionTable::~FunctionTable()
{
	delete pFuns_;
}