#pragma once
#include<map>
#include<string>
#define IDNOTFOUND 0xffffffff
class SymbolTable
{

public:
	SymbolTable():curId_(0) {}
	unsigned int Add(const std::string& str);
	unsigned int Find(const std::string& str) const;
	void Clear();
	std::string GetSymbolName(unsigned int id) const;
private:
	std::map<const std::string, unsigned int> dictionary_;
	unsigned int curId_;

};

