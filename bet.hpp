
/* Name: Andrew Stade
Date: 11/6/2020
Section: COP 4530 */

int checkSign(string expression);		// Return differing values based on operator  (taken from hw3)
bool checkAlnum(string expression);		// Tests if character is alphanumeric  (taken from hw3)

BET::BET()		// default zero-parameter constructor
{
	start = new BinaryNode;
}

BET::BET(const string postfix)		// one-parameter constructor
{
	start = new BinaryNode;
	buildFromPostfix(postfix);
}

BET::BET(const BET& x)			// copy constructor
{
	start = clone(x.start);
}

BET::~BET()		// destructor 
{
	makeEmpty(start);
}

bool BET::buildFromPostfix(const string& postfix)		// builds tree from postfix
{
	stack<BinaryNode*> stack;
	stringstream s(postfix);
	string temp;
	int count1 = 0;
	int count2 = 0;
	
	if(postfix.empty() == true)		// error check
	{
		cout << "Wrong postfix expression" << endl;
		start = nullptr;
		return false;
	}
	
	if(empty() == false)		// clear node
	{
		makeEmpty(start);
	}
	
	while(s >> temp)		// use sstream for tokens
	{
		BinaryNode *myNode = new BinaryNode(temp);		// creates a node
		
		if(checkAlnum(temp) == true)		// take alnum and push to stack
		{
			count1++;
			stack.push(myNode);
		}
		else if(checkSign(temp) != 0)		// else if its a number or letter
		{
			count2++;
			if(count1 == count2)	// error check
			{
				cout << "Wrong postfix expression" << endl;
				start = nullptr;
				return false;
			}
			else
			{
				myNode->left = stack.top();
				stack.pop();
				myNode->right = stack.top();
				stack.pop();
				stack.push(myNode);
			}
		}
	}
	
	if(count1 != count2)
	{
		start = stack.top();
	}
	
	if(stack.empty() == true)		// error check
	{
		cout << "Wrong postfix expression" << endl;
		start = nullptr;
		return false;
	}
	
	return true;
}

const BET & BET::operator=(const BET & x)		// assignment operator
{
	start = clone(x.start);
	return *this;
}

void BET::printInfixExpression()			// print infix
{
	printInfixExpression(start);
	cout << endl;
}

void BET::printPostfixExpression()			// print postfix
{
	printPostfixExpression(start);
	cout << endl;
}

size_t BET::size()		// return amount of nodes
{
	return (size(start));
}

size_t BET::leaf_nodes()	// return amount of leaf nodes
{
	return (leaf_nodes(start));
}

bool BET::empty()		// return true if empty
{
	if(start == nullptr)
	{
		return true;
	}
	return false;
}

void BET::printInfixExpression(BinaryNode *n)	// print infix (with parentheses)
{
	bool checkParentheses = false;	// used to track once a parentheses is open "("
	
	if(n != nullptr)
	{
		if(n->left == nullptr && n->right == nullptr)	// start node w/o children
		{
			cout << n->data << " ";
		}
		else
		{
			if(checkSign(n->data) != 0 && checkSign(n->right->data) != 0)
			{
				if(checkSign(n->data) >= checkSign(n->right->data))
				{
					if(checkSign(n->data) == 2)
					{
						cout << "( ";
						checkParentheses = true;
					}
				}
			}
			
			printInfixExpression(n->right);
			if(checkParentheses == true)
			{
				cout << ") ";
			}
			checkParentheses = false;		// resets parentheses
			
			cout << n->data << " ";
			
			if(checkSign(n->data) != 0 && checkSign(n->left->data) != 0)
			{
				if(checkSign(n->data) >= checkSign(n->left->data))
				{
					cout << "( ";
					checkParentheses = true;
				}
			}
			
			printInfixExpression(n->left);
			if(checkParentheses == true)
			{
				cout << ") ";
			}
			checkParentheses = false;	// resets parentheses
		}
	}
}

void BET::makeEmpty(BinaryNode* &t)		// delete all nodes (taken from textbook)
{
	if(t != nullptr)
	{
		makeEmpty(t->left);
		makeEmpty(t->right);
		delete t;
	}
}

BET::BinaryNode * BET::clone(BinaryNode *t) const		// clone all nodes (taken from textbook)
{
	if(t == nullptr)
	{
		return nullptr;
	}
	else
	{
		return new BinaryNode(t->data, clone(t->left), clone(t->right));
	}
}

void BET::printPostfixExpression(BinaryNode *n)		// print postfix
{
	if(size(n) == 0)	// segfault (?)
	{
		return;
	}
	else if(start->left == nullptr && start->right == nullptr)
	{
		cout << start->data << endl;
	}
	else
	{
		printPostfixExpression(n->right);
		printPostfixExpression(n->left);
		cout << n->data << " ";
	}
}

size_t BET::size(BinaryNode *t)		// return amount of nodes in subtree
{
	if(t == nullptr)
	{
		return 0;
	}
	else
	{
		return(size(t->left) + size(t->right) + 1);
	}
}

size_t BET::leaf_nodes(BinaryNode *t)	// return amount of leaf nodes in subtree
{
	if(t == nullptr)
	{
		return 0;
	}
	else if((t->left == nullptr) && (t->right == nullptr))
	{
		return 1;
	}
	else
	{
		return (leaf_nodes(t->left) + leaf_nodes(t->right));
	}
}

bool checkAlnum(string str)			// Check if character is alphanumeric (taken from hw3)
{
	for(int i = 0; i < int(str.size()); i++)
	{
		if(isalnum(str[i]) == false)		// C++ reference
		{
			return false;
		}
	}
	return true;
}

int checkSign(string str)		// Return differing values based on operator (taken from hw3)
{
	if(str == "(" || str == ")")
	{
		return (3);
	}
	else if(str == "*" || str == "/")
	{
		return (2);
	}
	else if(str == "+" || str == "-")
	{
		return (1);
	}
	else
		return 0;
}
