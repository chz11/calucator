#pragma once
#include<string>
enum EToken
{
	TOKEN_END,
	TOKEN_ERROR,
	TOKEN_NUMBER,
	TOKEN_PLUS,
	TOKEN_MINUS,
	TOKEN_MULTIPLY,
	TOKEN_DIVIDE,
	TOKEN_LPARENTHESIS,
	TOKEN_RPARENTHESIS,
	TOKEN_IDENTIFIER,
	TOKEN_ASSIGN
};
class Scanner
{
public:
	Scanner(const std::string& buf);
	void Accept();
	double Number() const;
	EToken Token() const;
	std::string GetSymbol() const;
	bool IsEmpty() const;
	bool IsDone() const;
	~Scanner()
	{

	}
private:
	void SkipWhite();
	std::string buf_;
	unsigned int curPos_;
	EToken token_;
	double number_;
	std::string symbol_;
	bool isEmpty_;
};

