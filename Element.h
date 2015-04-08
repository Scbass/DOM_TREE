#ifndef Element_h
#define Element_h
#include <iostream>
#include <string>
#include "link_l.h"
using std::string;
using std::cout;

class Element
{

	private:
	
	string tag, iHTML;
    Lista<string> attrList;

	public:
	
	//Constructor
	Element(string tagN): tag(tagN), iHTML(""){} 
	//Observacion
	string tagName() {return tag;}
	Lista<string> attributeList() {return attrList;}
	string innerHTML() {return iHTML;}
	//Modificadfores
	void setTagName(string tagN) {this->tag=tagN;}
	void setAtributteList(Lista<string> l) {this->attrList=l;}
	void setInnnerHTML(string iHTML) {this->iHTML=iHTML;}	
	//sobrecargas
	bool operator ==(Element x); //Sobrecarga del operador ==
	
};


bool Element::operator ==(Element x) 
{
		return(this->tag == x.tag && this->iHTML == x.iHTML && this->attrList==x.attrList);
}

#endif
