#include "Parser.h"
#include<cassert>
#include "Node.h"
#include "Scanner.h"
#include "Calc.h"
#include "Exception.h"
Parser::Parser(Scanner& scanner,Calc& calc) :scanner_(scanner), tree_(0),calc_(calc),status_(STATUS_OK)
{

}

EStatus Parser::Parse()
{
	tree_ = Expr();
	if (!scanner_.IsDone())
	{
		status_ = STATUS_ERROR;
	}
	return status_;
}

Node* Parser::Expr()
{
	Node* node = Term();
	EToken token = scanner_.Token();
	/*if (token == TOKEN_PLUS)
	{
		scanner_.Accept();
		Node* nodeRight = Expr();
		node = new AddNode(node,nodeRight);
	}
	else if (token == TOKEN_MINUS)
	{
		scanner_.Accept();
		Node* nodeRight = Expr();
		node = new SubNode(node, nodeRight);
	}*/
	if (token == TOKEN_PLUS || token == TOKEN_MINUS)
	{
		//Expr :=Term('+' | '-')
		MutipleNode* mutipleNode = new SumNode(node);
		do {
			scanner_.Accept();
			Node* nextNode = Term();
			mutipleNode->AppendChild(nextNode, (token == TOKEN_PLUS));
			token = scanner_.Token();
		} while (token == TOKEN_PLUS || token == TOKEN_MINUS);
		node = mutipleNode;
	}
	else if (token == TOKEN_ASSIGN)
	{
		//Expr := Term = Expr
		scanner_.Accept();
		Node* nodeRignt = Expr();
		if (node->IsLvalue())
		{
			node = new AssignNode(node, nodeRignt);
		}
		else
		{
			status_ = STATUS_ERROR;
			//std::cout << "The left-hand side of an assignment must be a variable" << std::endl;
			//Todo 抛出异常
			throw SyntaxError("The left-hand side of an assignment must be a variable");
		}
	}
	return node;
}
Node* Parser::Term()
{
	Node* node = Factor();
	EToken token = scanner_.Token();
	//if (token == TOKEN_MULTIPLY)
	//{
	//	scanner_.Accept();
	//	Node* nodeRight = Term();
	//	node = new MultiplyNode(node, nodeRight);
	//}
	//else if (token == TOKEN_DIVIDE)
	//{
	//	scanner_.Accept();
	//	Node* nodeRight = Term();
	//	node = new DivideNode(node, nodeRight);
	//}
	if (token == TOKEN_MULTIPLY || token == TOKEN_DIVIDE)
	{
		//Expr :=Term('+' | '-')
		MutipleNode* mutipleNode = new ProductNode(node);
		do {
			scanner_.Accept();
			Node* nextNode = Factor();
			mutipleNode->AppendChild(nextNode, (token == TOKEN_MULTIPLY));
			token = scanner_.Token();
		} while (token == TOKEN_MULTIPLY || token == TOKEN_DIVIDE);
		node = mutipleNode;
	}
	return node;
}
Node* Parser::Factor()
{
	Node* node;
	EToken token = scanner_.Token();
	if (token == TOKEN_LPARENTHESIS)
	{
		scanner_.Accept();
		node = Expr();
		if (scanner_.Token() == TOKEN_RPARENTHESIS)
		{
			scanner_.Accept();

		}
		else
		{
			status_ = STATUS_ERROR;
			//todo: 抛出异常
			//std::cout << " missing parenthesis" << std::endl;
			throw SyntaxError("missing parenthesis");
			node = 0;
		}

	}
	else if (token == TOKEN_NUMBER)
	{
		node = new NumberNode(scanner_.Number());
		scanner_.Accept();
	}
	else if (token == TOKEN_IDENTIFIER)
	{
		std::string symbol = scanner_.GetSymbol();
		unsigned int id = calc_.FindSymbol(symbol);
		scanner_.Accept();
		if (scanner_.Token() == TOKEN_LPARENTHESIS)
		{
			scanner_.Accept();
			node = Expr();
			if (scanner_.Token() == TOKEN_RPARENTHESIS)
			{
				scanner_.Accept();
				if (id != IDNOTFOUND&&calc_.IsFunction(id))
				{
					node = new FunctionNode(node, calc_.GetFunction(id));
				}
				else
				{
					status_ = STATUS_ERROR;
					char buf[256] = { 0 };
					sprintf(buf, "Unknow function \"%s\"", symbol.c_str());
					throw SyntaxError(buf);
					//std::cout << "Unknow function: " << symbol << std::endl;
				}
			}
			else
			{
				status_ = STATUS_ERROR;
				throw SyntaxError("Mising RPARENTHESIS in a function call");
				//std::cout << "Mising RPARENTHESIS in a function call" << std::endl;
			}
		}
		else
		{
			if (id == IDNOTFOUND)
			{
				id = calc_.AddSymbol(symbol);
			}
			node = new VariableNode(id, calc_.GetStorage());
		}		
	}
	else if (token == TOKEN_MINUS)
	{
		scanner_.Accept();
		node = new UMinusNode(Factor());
	}
	else
	{
		status_ = STATUS_ERROR;
		//todo: 抛出异常
		//std::cout << " not a valid expression" << std::endl;
		throw SyntaxError("not a valid expression");
		
		node = 0;
	}
	return node;
}

double Parser::Calculate() const
{
	assert(tree_!= 0);
	return tree_->Calc();
}