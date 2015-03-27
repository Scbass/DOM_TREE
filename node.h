#ifndef Node_h
#define Node_h
#include <iostream>
#include "Element.h"

template<class M>
class Node
{
	private:
	
	M e;
	Node<M> *fc, *ns;
	
	public:
	
	//Constructores
	Node(M e): e(e), fc(NULL), ns(NULL){}
	Node(M e, Node *hji, Node *hd): e(e), fc(hji), ns(hd){}
	//Observadores
	Node* firstchild() const {return fc;}
	Node* nextsibling() const {return ns;}
	M element() const {return e;}
	//Modificadores
	void setElement(M e) {this->info=e;}
	void setFirstChild(Node *child) {this->fc=child;}
	void setNextSibling(Node *hji) {this->ns=hji;}	
	
};
#endif
