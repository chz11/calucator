#pragma once
#include "Storage.h"
#include "SymbolTable.h"
#include "FunctionTable.h"
class Parser;
class Calc
{
	friend class Parser;
public:
	Calc():funTbl_(symTbl_),storage_(symTbl_) {}
	bool IsFunction(unsigned int id) const
	{
		return id < funTbl_.Size();
	}
	PtrFun GetFunction(unsigned int id)
	{
		return funTbl_.GetFunction(id);
	}
private:
	unsigned int FindSymbol(const std::string& str) const;
	unsigned int AddSymbol(const std::string& str);
	Storage& GetStorage();
	SymbolTable symTbl_;
	FunctionTable funTbl_;
	Storage storage_;	
};

