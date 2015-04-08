#ifndef Node_h
#define Node_h
#include <iostream>
#include "Element.h"


class Node
{
	private:
	
	Element e;
	Node *fc, *ns;
	
	public:
	
	//Constructores
	Node(Element e): e(e), fc(NULL), ns(NULL){}
	Node(Element e, Node *hji, Node *hd): e(e), fc(hji), ns(hd){}
	//Observadores
	Node* firstchild() const {return fc;}
	Node* nextsibling() const {return ns;}
	Element element() const {return e;}
	//Modificadores
	void setElement(Element info) {this-> e =info ;}
	void setFirstChild(Node *child) {this->fc=child;}
	void setNextSibling(Node *hji) {this->ns=hji;}	
	
};
#endif
