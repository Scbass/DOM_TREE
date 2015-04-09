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
	Element(string tagN, string ihTML): tag(tagN), iHTML(ihTML){}
	Element(Element const &e); //constructor copia
	//Observacion
	string tagName() {return tag;}
	Lista<string> attributeList() {return attrList;}
	string innerHTML() {return iHTML;}
	//Modificadfores
	void setTagName(string tagN) {this->tag=tagN;}
	void setAtributteList(Lista<string> l) {this->attrList=l;}
	void setInnnerHTML(string iHTML) {this->iHTML=iHTML;}
	void cpy_element(Element x);	
	//sobrecargas
	bool operator ==(Element x); //Sobrecarga del operador ==
	Element operator =(Element x);
};

//Constructor copia
Element::Element(Element const &e)
{
	this->cpy_element(e);
}

void Element::cpy_element(Element x)
{
	this->tag=x.tag;
	this->iHTML=x.iHTML;
	this->attrList=x.attrList;
}

//Sobrecargas

bool Element::operator ==(Element x) 
{
		return(this->tag == x.tag && this->iHTML == x.iHTML && this->attrList==x.attrList);
}

Element Element::operator =(Element x)
{
	this->cpy_element(x);
	return(*this);
}

#endif
