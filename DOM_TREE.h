#ifndef DOMTree_h
#define DOMTree_h
#include <iostream>
#include <string>
#include "node.h"

using std::string;
using std::cout;
using std::endl;
class DOMTree
{
	private:
		//Atributos
		Node *document;
	
		//Metodos
		Node* cpy_nodo(Node *root);  
		void  destroy(Node *root);
		void altura(Node *root, int &a);
		void agregarhijo(Node *root, Element padre, Element hijo, bool &band);
		
	public:
		//Constructores
		DOMTree(): document(NULL){}
		DOMTree(Node* docum): document(docum){} //con parametros0
		DOMTree(const DOMTree &a); //copia
		DOMTree(Element e, Lista<DOMTree > l); // a partir de una lista de hijos
		//Observadores
		bool es_nulo(){return (document==NULL);}
		Element raiz() {return document->element();}
		int altura();
		int max(int x, int y);
		DOMTree childNode(int p);
		DOMTree getElementByID(string id);
		void search_element(Node* raiz ,string id, bool &band, Node* &elemento);
		//modificadores
		void appendChild(DOMTree a);
		void appendChild(DOMTree a, int p);
		void removeChild(int pos);
		void agregarhijo(Element padre, Element hijo);
		void replaceChild(DOMTree a, int p);
		//Destructores
		void destroy();
		~DOMTree();
		//Sobrercargas
		DOMTree stringToDOMTree(string d);
		void appendChild(string a);
		void appendChild(string a, int p);
		DOMTree operator =(DOMTree const &tree);
		/*
		friend std::ostream& operator <<(std::ostream& out, DOMTree tree); //Sobrecarga del operador <<
		friend std::ostream imprimir_tree(std::ostream& out, Node* root, int tab);
		*/ 
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

DOMTree DOMTree::childNode(int p)
{
	Node *aux;
	DOMTree tree;
	int i;
	aux=document;
	if(p==1)
	{
		tree.document=cpy_nodo(aux->firstchild());
		tree.document->setNextSibling(NULL);
	}
	else
	{
		i=2;
		aux=aux->firstchild();
		while(aux->nextsibling()!=NULL && i<p-1)
			{
				aux=aux->nextsibling();
				i++;
			}
			if(i==p)
			{
				tree.document=cpy_nodo(aux);
				tree.document->setNextSibling(NULL);
			}		
	}
	return(tree);
}

DOMTree DOMTree::getElementByID(string id)
{
	DOMTree tree;
	Node *aux=NULL;
	bool band = false;
	
	this->search_element(document, id, band, aux);
	tree.document=cpy_nodo(aux);
	if(tree.document->nextsibling()!=NULL)
	{
		tree.document->setNextSibling(NULL);
	}
	return(tree);
	
}

void DOMTree::search_element(Node* raiz ,string id, bool &band, Node* &elemento )
{
	if(raiz!=NULL)
	{
		if(raiz->element().tagName()==id)
		{
			elemento=raiz;
			band=true;
		}
		else
		{
			search_element(raiz->firstchild(), id, band, elemento);
			if(band == false)
			{
				search_element(raiz->firstchild(), id, band, elemento);
			}
		}
	}	
}
//Modificadores

void DOMTree::appendChild(DOMTree a)
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


void DOMTree::appendChild(DOMTree a, int p)
{
	Node *prev, *next, *aux;
	
	prev=document->firstchild();
	aux=prev;
	if(prev!=NULL)
	{	
		next=prev->nextsibling();
			if(p==1)
			{
				
				document->setFirstChild(a.document);
				a.document->setNextSibling(prev);
			}
			else
			{
			p-=2;
			while(next!=NULL && p!=0) //muevo el apuntador a una pos antes de donde quiero insertar
			{
				aux=next;
				next=next->nextsibling();
				if(p!=1)
					prev=aux;
				p--;
			}	
			a.document->setNextSibling(next);
			aux->setNextSibling(a.document);
			}	
	}
}

void DOMTree::removeChild(int pos)
{
	Node *prev, *next, *aux;
	
	prev=document->firstchild();
	aux=prev;
	if(prev!=NULL)
	{	
		next=prev->nextsibling();
			if(pos==1)
			{
				document->setFirstChild(next);
				next=NULL;
				this->destroy(aux->firstchild());
				delete(aux);
			}
			else
			{
			pos--;
			while(next!=NULL && pos!=0) //muevo el apuntador a donde quiero eliminar
			{
				aux=next;
				next=next->nextsibling();
				if(pos!=1)
					prev=aux;
				pos--;
			}
			if(next!=NULL || pos==0) //evalua que no trate de eliminar en una pos que no existe
			{
				prev->setNextSibling(next);
				next=NULL;
				this->destroy(aux->firstchild());
				delete(aux);
			
			}
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

void DOMTree::replaceChild(DOMTree a, int p)
{
	this->removeChild(p);
	this->appendChild(a, p);
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


//sobrecargas
DOMTree DOMTree::operator =(DOMTree const &tree)
{
	this->document=this->cpy_nodo(tree.document);
	return(*this);
	
}

DOMTree DOMTree::stringToDOMTree(string d)
{
	string tag, inner, aux;
	Node *doc, *doc2, *child;
	int i;
	
	d.erase();
	aux=d[0];
	d.erase();
	tag=aux;
	aux=d[0];
	while(!(aux=="<"))
	{
		inner=inner+aux;
		d.erase();
		aux=d[0];
	}
	Element elem(tag,inner);
	doc=new Node(elem);
	child=doc->firstchild();
	while(d.length()!=0)
	{
		d.erase();
		tag=d[0];
		if(!(tag=="/"))
		{
			d.erase();
			d.erase();
			aux=d[0];
			inner=aux;
			d.erase();
			aux=d[0];
			while(!(aux=="<"))
			{
				inner=inner+aux;
				d.erase();
				aux=d[0];
			}
			Element elem2(tag,inner);
			doc2= new Node(elem2);
			child=doc2;
			child=child->nextsibling();
		}
		else
		{
			for(i=1;i<=3;i++)
			d.erase();
		}
	}
	DOMTree tree(doc);
return(tree);
}

void DOMTree::appendChild(string a)
{
	DOMTree tree;
	
	tree=stringToDOMTree(a);
	appendChild(tree);
}

void DOMTree::appendChild(string a, int p)
{
	DOMTree tree;
	
	tree=stringToDOMTree(a);
	appendChild(tree,p);
}
/*
std::ostream& operator <<(std::ostream& out, DOMTree tree) //Sobrecarga del operador <<
{
	int tab=0;
	
	out<<"<"<<tree.document->element().tagName()<<">"<<endl;
	tree.imprimir_tree(out,tree.document->firstchild(), tab);
	
	return (out);
}

std::ostream DOMTree::imprimir_tree(std::ostream& out, Node* root, int tab)
{
	
	if(root!=NULL)
	{
		int i;
		for (i=0; i<tab; i++)
		{
			out<<"	";
		}
		
		out<<"<"<<root->element().tagName();
		if(!root->element().attributeList().es_vacia())
			out<<root->element().attributeList();
		out<<">";
		out<<root->element().innerHTML()<<endl;
		
		out<<this->imprimir_tree(out, root->firstchild(), tab++)<<endl;
		out<<this->imprimir_tree(out, root->nextsibling(), tab++)<<endl;
		out<<"<"<<"/"<<root->element().tagName()<<">";
	}
	return(out);
}
*/





#endif
