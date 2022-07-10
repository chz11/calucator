#pragma once
typedef double (*PtrFun)(double);

class SymbolTable;
class FunctionTable
{
public:
	FunctionTable(SymbolTable& tbl);
	~FunctionTable();
	void Init(SymbolTable& tbl);
	unsigned int Size() const
	{
		return size_;
	}
	PtrFun GetFunction(unsigned int id) const
	{
		return pFuns_[id];
	}
private:
	PtrFun* pFuns_;
	unsigned int size_;
};

