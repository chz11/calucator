#include "SymbolTable.h"
#include "Exception.h"
unsigned int SymbolTable::Add(const std::string& str)
{
	dictionary_[str] = curId_;
	return curId_++;
}
unsigned int SymbolTable::Find(const std::string& str) const
{
	std::map<const std::string, unsigned int>::const_iterator it;
	it = dictionary_.find(str);
	if (it != dictionary_.end())
	{
		return it->second;
	}
	else
	{
		return IDNOTFOUND;
	}

}
void SymbolTable::Clear()
{
	dictionary_.clear();
	curId_ = 0;
}

//function object、functor
//让一个类对象使用起来向一个函数
class IsEquaIId
{
public:
	IsEquaIId(unsigned int id):id_(id) {}
	bool operator()(const std::pair<const std::string, unsigned int>& it) const
	{
		return it.second == id_;
	}
private:
	unsigned int id_;
};


std::string SymbolTable::GetSymbolName(unsigned int id) const
{
	std::map<const std::string, unsigned>::const_iterator it;
	it = find_if(dictionary_.begin(), dictionary_.end(),IsEquaIId(id));
	if (it == dictionary_.end())
	{
		throw Exception("Internal error:missing entry in symbol table.");
	}
	return it->first;
}