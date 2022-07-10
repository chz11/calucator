#pragma once
#include<vector>
class SymbolTable;
class Storage
{
public:
	Storage(SymbolTable& tbl);
	void clear();
	void AddConstans(SymbolTable& tbl);
	bool IsInit(unsigned int id) const;
	double GetValue(unsigned int id) const;
	void SetValue(unsigned int id, double val);
	void AddValue(unsigned int id, double val);
private:
	std::vector<double> cells_;
	std::vector<bool> inits_;
};

