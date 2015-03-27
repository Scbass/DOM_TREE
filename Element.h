#ifndef Element_h
#define Element_h
#include <iostream>
#include <string>
#include <list>

using std::string;
using std::cout;
using std::list;

class Element
{

	private:
	
	string tag, iHTML;
	list<string> attrList;

	public:
	
	//Constructor
	Element(string tagN): tag(tagN), iHTML(""){} 
	//Observacion
	string tagName() {return tag;}
	list<string> attributeList() {return attrList;}
	string innerHTML() {return iHTML;}
	//Modificadfores
	void setTagName(string tagN) {this->tag=tagN;}
	void setAtributteList(list<string> l) {this->attrList=l;}
	void setInnnerHTML(string iHTML) {this->iHTML=iHTML;}	

};
#endif
