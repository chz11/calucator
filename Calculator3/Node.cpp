#include "Node.h"
#include<cassert>
double NumberNode::Calc() const
{
	return number_;
}
BinaryNode::~BinaryNode()
{
	delete left_;
	delete right_;
}
UnaryNode::~UnaryNode()
{
	delete child_;
}
//double AddNode::Calc() const
//{
//	return left_->Calc() + right_->Calc();
//}
//double SubNode::Calc() const
//{
//	return left_->Calc() - right_->Calc();
//}
//double MultiplyNode::Calc() const
//{
//	return left_->Calc() * right_->Calc();
//}
//double DivideNode::Calc() const
//{
//	double divisor = right_->Calc();
//	if (divisor != 0.0)
//	{
//		return left_->Calc() / right_->Calc();
//	}
//	else
//	{
//		std::cout << "Erorr: Divisor can't is 0" << std::endl;
//	}
//}
double UMinusNode::Calc() const
{
	return -child_->Calc();
}
double FunctionNode::Calc() const
{
	return (*pFun_)(child_->Calc());
}
MutipleNode::~MutipleNode()
{
	std::vector<Node*>::const_iterator it;
	for (it = childs_.begin();it != childs_.end();++it)
	{
		delete *it;
	}
}

double SumNode::Calc() const
{
	std::vector<Node*>::const_iterator childIt = childs_.begin();
	std::vector<bool>::const_iterator positiveIt = positives_.begin();
	double result = 0.0;
	for (;childIt != childs_.end();++childIt,++positiveIt)
	{
		assert(childIt != childs_.end());
		double val = (*childIt)->Calc();
		if (*positiveIt)
		{
			result += val;
		}
		else
		{
			result -= val;
		}
	}
	assert(positiveIt == positives_.end());
	return result;
}

double ProductNode::Calc() const
{
	std::vector<Node*>::const_iterator childIt = childs_.begin();
	std::vector<bool>::const_iterator positiveIt = positives_.begin();
	double result = 1.0;
	for (;childIt != childs_.end();++childIt, ++positiveIt)
	{
		assert(childIt != childs_.end());
		double val = (*childIt)->Calc();
		if (*positiveIt)
		{
			result *= val;
		}
		else if(val != 0.0)
		{
			result /= val;
		}
		else
		{
			std::cout << "Division by zero" << std::endl;
			return HUGE_VAL;
		}
	}
	assert(positiveIt == positives_.end());
	return result;
}

double VariableNode::Calc() const
{
	double x = 0.0;
	if (storage_.IsInit(id_))
	{
		x = storage_.GetValue(id_);
	}
	else
	{
		std::cout << "Use of uninitialized variable" << std::endl;
	}
	return x;
}
bool VariableNode::IsLvalue() const
{
	return true;
}
void VariableNode::Assign(double val)
{
	storage_.SetValue(id_, val);
}

double AssignNode::Calc() const
{
	double x = 0.0;
	x = right_->Calc();
	left_->Assign(x);
	return x;
}