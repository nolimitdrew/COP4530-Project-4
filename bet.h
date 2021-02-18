
/* Name: Andrew Stade
Date: 11/6/2020
Section: COP 4530 */

#ifndef BET_H
#define BET_H

#include <iostream>
#include <sstream>
#include <stack>

using namespace std;

class BET
{
	struct BinaryNode
	{
		string data;
		BinaryNode *left;
		BinaryNode *right;
		BinaryNode(const string & d = string{}, BinaryNode *l = nullptr, BinaryNode *r = nullptr) : data{d}, left{l}, right{r} {}
	};
	
	public:
		BET();											// constructor
		BET(const string postfix);						// one-parameter constructor
		BET(const BET&);								// copy constructor
		~BET();											// destructor
		bool buildFromPostfix(const string& postfix);
		const BET & operator=(const BET &);				// assignment operator
		void printInfixExpression();
		void printPostfixExpression();
		size_t size();
		size_t leaf_nodes();
		bool empty();
		
	private:
		void printInfixExpression(BinaryNode *n);
		void makeEmpty(BinaryNode* &t);
		BinaryNode * clone(BinaryNode *t) const;
		void printPostfixExpression(BinaryNode *n);
		size_t size(BinaryNode *t);
		size_t leaf_nodes(BinaryNode *t);
		BinaryNode *start;
};

#include "bet.hpp"
#endif