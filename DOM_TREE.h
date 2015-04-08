#ifndef DOMTree_h
#define DOMTree_h
#include <iostream>
#include "node.h"

class DOMTree
{
	private:
		//Atributos
		Node *document;
	
		//Metodos
		Node* cpy_nodo(Node *root); //* 
		void  destroy(Node *root);
		void altura(Node *root, int &a);
		void agregarhijo(Node *root, Element padre, Element hijo, bool &band);
		
	public:
		//Constructores
		DOMTree(): document(NULL){} //*
		DOMTree(const DOMTree &a);
		DOMTree(Element e, Lista<DOMTree > l);//*
		//Observadores
		bool es_nulo(){return (document==NULL);}
		Element raiz() {return document->element();}
		int altura();
		int max(int x, int y);
		//modificadores
		void insertsubarb(DOMTree a, int p);// + pos
		void elimsubar(int pos);//*
		void agregarhijo(Element padre, Element hijo);
		//Destructores
		void destroy();
		~DOMTree();
};

//Constructores
DOMTree::DOMTree(const DOMTree &a)
{
	this->document=this->cpy_nodo(a.document);	
}


DOMTree::DOMTree(Element e, Lista<DOMTree > l)
{

	Node *aux;
	aux=new Node(e);
	document=aux;
		
	if(!l.es_vacia())
	{
		document->setFirstChild(cpy_nodo(l.consultar_elemento(1).document));
		l.eliminar(1);
		aux=document->firstchild();
		while(!l.es_vacia())
		{
			aux->setNextSibling(cpy_nodo(l.consultar_elemento(1).document));
			l.eliminar(1);
			aux=aux->nextsibling();
		}	
	}
		
}

//Observadores

Node* DOMTree::cpy_nodo(Node *root)
{
	Node *aux;
	
	if(root==NULL)
		return NULL;
	else
	{
		aux=new Node(root->element(),this->cpy_nodo(root->firstchild()),this->cpy_nodo(root->nextsibling()));
		return(aux);
	}
}

void DOMTree::altura(Node *root, int &a)
{
	int ai, ad;
	
	if(root==NULL)
		a= -1;
	else
	{
			this->altura(root->firstchild(), ai);
			this->altura(root->nextsibling(), ad);
			if(root->firstchild()==NULL)
				a=max(ai,ad);
			else
				a=max(ai,ad)+1;	
	}
}


int DOMTree::max(int x,int y)
{
		return(x<y ? y:x); 	
}

//Modificadores


void DOMTree::insertsubarb(DOMTree a, int p)
{
	Node*aux;
	
	if(document->firstchild()==NULL)
		document->setFirstChild(this->cpy_nodo(a.document));
	else
	{
		aux=this->document->firstchild();
		while(aux->nextsibling()!=NULL)
		{
			aux=aux->nextsibling();
		}
		aux->setNextSibling(this->cpy_nodo(a.document));
	}
}


void DOMTree::elimsubar(int pos)
{
	Node *ant, *sig;
	int i;
	
		ant=document;
		
		if(pos==1)
		{
			sig=ant->firstchild();
			ant->setFirstChild(sig->nextsibling());
			sig->setNextSibling(NULL);
			this->destroy(sig);	
		}	
		else
		{
			i=2;
			ant=ant->firstchild();
			while(ant->nextsibling()!=NULL && i<pos-1)
			{
				ant=ant->nextsibling();
				i++;
			}
			if(i==pos)
			{
				sig=ant->nextsibling();
				ant->setNextSibling(sig->nextsibling());
				sig->setNextSibling(NULL);
				this->destroy(sig);
			}		
		}
}


void DOMTree:: agregarhijo(Node *root,Element padre, Element hijo, bool &band)
{
	
	if(root!=NULL)
	{
		if(root->element()== padre)
		{
			Node *aux, *aux2;
			aux= new Node(hijo);
			if(root->firstchild()==NULL) 
			{
				root->setFirstChild(cpy_nodo(aux));
	
			}
			else
			{
				aux2=root->firstchild();
				while(aux2->nextsibling()!=NULL)
				{
					aux2=aux2->nextsibling();
				}
				aux2->setNextSibling(cpy_nodo(aux));
			}
			band=true;
		}
		else
		{
			this->agregarhijo(root->firstchild(), padre,hijo, band);
			if(band==false)
			{
				this->agregarhijo(root->nextsibling(), padre, hijo, band);
			}
		}
	}
}

//Privados


int DOMTree::altura()
{
	int alt;
	altura(this->document, alt);	
	return alt;
}

void DOMTree:: agregarhijo(Element padre, Element hijo)
{
	bool band=false;
	this->agregarhijo(document, padre, hijo, band);
}


void DOMTree::destroy()
{
	this->destroy(document);
}


//Destructores


void DOMTree::destroy(Node *root)
{
	if(root!=NULL)
	{
		destroy(root->firstchild());
		destroy(root->nextsibling());
		delete(root);
	}	
}

DOMTree::~DOMTree()
{
	destroy(document);
}
#endif
