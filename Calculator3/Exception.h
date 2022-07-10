#pragma once
#include<exception>
#include<string>
class Exception : public std::exception
{
public:
	explicit Exception(const char* message) :message_(message)
	{
		FillStackTrace();
	}
	virtual ~Exception() throw()//表示不抛出异常
	{

	}
	const char* StackTrace() const throw();
	virtual const char* what() const throw();
private:
	void FillStackTrace();
	std::string message_;
	std::string stackTrace_;
};

class SyntaxError : public Exception
{
public:
	explicit SyntaxError(const char* message) :Exception(message)
	{

	}
	~SyntaxError()
	{

	}
};
