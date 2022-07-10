#include "Storage.h"
#include "SymbolTable.h"
#include<cmath>
#include<assert.h>
#include<iostream>
Storage::Storage(SymbolTable& tbl)
{
	AddConstans(tbl);
}
void Storage::clear()
{
	cells_.clear();
	inits_.clear();
}
void Storage::AddConstans(SymbolTable& tbl)
{
	std::cout << "varible list" << std::endl;
	unsigned int id = tbl.Add("e");
	AddValue(id, exp(1.0));
	std::cout << "e=" << exp(1.0) << std::endl;
	id = tbl.Add("pi");
	AddValue(id, 2.0 * acos(0.0));//·´ÓàÏÒ¦°=2.0 * acos(0.0)
	std::cout << "pi" << 2.0 * acos(0.0) << std::endl;
}
bool Storage::IsInit(unsigned int id) const
{
	return id < cells_.size() && inits_[id];
}
double Storage::GetValue(unsigned int id) const
{
	assert(id < cells_.size());
	return cells_[id];
}
void Storage::SetValue(unsigned int id, double val)
{
	assert(id <= cells_.size());
	if (id < cells_.size())
	{
		cells_[id] = val;
		inits_[id] = true;
	}
	else if (id == cells_.size())
	{
		AddValue(id, val);
	}
}
void Storage::AddValue(unsigned int id, double val)
{
	cells_.resize(id + 1);
	inits_.resize(id + 1);
	cells_[id] = val;
	inits_[id] = true;
}