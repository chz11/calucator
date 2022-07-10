#pragma once

class Node;
class Scanner;
class Calc;
enum EStatus
{
	STATUS_OK,
	STATUS_ERROR,
	STATUS_QUIT,

};
class Parser
{
public:
	Parser(Scanner& scanner,Calc& calc);
	EStatus Parse();
	Node* Expr();
	Node* Term();
	Node* Factor();
	double Calculate() const;
private:
	Scanner& scanner_;
	Node* tree_;
	EStatus status_;
	Calc& calc_;
};

