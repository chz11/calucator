#pragma once
#include<iostream>
#include<cmath>
#include<vector>
#include<cassert>
#include "Storage.h"
#include "FunctionTable.h"
class NonCopyable
{
protected:
	NonCopyable() {}
	~NonCopyable() {}
private:
	NonCopyable(const NonCopyable&);
	const NonCopyable& operator= (const NonCopyable&);
};
class Node : private NonCopyable
{
public:
	virtual double Calc() const = 0;
	virtual bool IsLvalue() const
	{
		return false;
	}
	virtual void Assign(double)
	{
		assert(!"Assign called incorrectly");
	}
	virtual ~Node()
	{

	}

};

class NumberNode : public Node
{
public:
	NumberNode(double number):number_(number) {}
	double Calc() const;
private:
	const double number_;
};

class BinaryNode : public Node
{
public:
	BinaryNode(Node* left, Node* right) :left_(left), right_(right)
	{

	}
	~BinaryNode();
protected:
	Node* const left_;
	Node* const right_;
};

class UnaryNode : public Node
{
public:
	UnaryNode(Node* child) :child_(child) {};
	~UnaryNode();
protected:
	Node* child_;
};

class FunctionNode : public UnaryNode
{
public:
	FunctionNode(Node* child,PtrFun pFun):UnaryNode(child),pFun_(pFun) {}
	double Calc() const;
private:
	PtrFun pFun_;
};
//class AddNode : public BinaryNode
//{
//public:
//	AddNode(Node* left, Node* right) :BinaryNode(left, right) {}
//	double Calc() const;
//};
//class SubNode : public BinaryNode
//{
//public:
//	SubNode(Node* left, Node* right) :BinaryNode(left, right) {}
//	double Calc() const;
//};
//class MultiplyNode : public BinaryNode
//{
//public:
//	MultiplyNode(Node* left, Node* right) :BinaryNode(left, right) {}
//	double Calc() const;
//};
//class DivideNode : public BinaryNode
//{
//public:
//	DivideNode(Node* left, Node* right) :BinaryNode(left, right) {}
//	double Calc() const;
//};
class UMinusNode : public UnaryNode
{
public:
	UMinusNode(Node* child):UnaryNode(child){}
	double Calc() const;
};

class MutipleNode : public Node
{
public:
	MutipleNode(Node* node)
	{
		AppendChild(node, true);
	}
	void AppendChild(Node* node, bool positives)
	{
		childs_.push_back(node);
		positives_.push_back(positives);
	}
	~MutipleNode();
protected:
	std::vector<Node*> childs_;
	std::vector<bool> positives_;
};

class SumNode : public MutipleNode
{ 
public:
	SumNode(Node* node):MutipleNode(node) {}
	double Calc() const;
};

class ProductNode : public MutipleNode
{
public:
	ProductNode(Node* node) :MutipleNode(node) {}
	double Calc() const;
};

class VariableNode : public Node
{
public:
	VariableNode(unsigned int id,Storage& storage):id_(id),storage_(storage) {}
	double Calc() const;
	bool IsLvalue() const;
	void Assign(double val);
private:
	const unsigned int id_;
	Storage& storage_;
};
class AssignNode : public BinaryNode
{
public:
	AssignNode(Node* left,Node* right):BinaryNode(left,right) 
	{
		assert(left->IsLvalue());
	}
	double Calc() const;
};