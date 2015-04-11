#ifndef DOMTree_h
#define DOMTree_h
#include <iostream>
#include <string>
#include "node.h"

using std::string;
using std::cout;
using std::endl;

class DOM_Tree
{
	private:
		//Atributos
		Node *document;
	
		//Metodos
		Node* cpy_nodo(Node *root);  
		void  destroy(Node *root);
		void agregarhijo(Node *root, Element padre, Element hijo, bool &band);
		
	public:
		//Constructores
		DOM_Tree(): document(NULL){}
		DOM_Tree(Node* docum): document(docum){} //con parametros
		DOM_Tree(const DOM_Tree &a); //copia
		DOM_Tree(Element e, Lista<DOM_Tree > l); // a partir de una lista de hijos
		//Observadores
		bool es_nulo(){return (document==NULL);}
		Element raiz() {return document->element();}
		int max(int x, int y);
		DOM_Tree childNode(int p);
		DOM_Tree getElementByID(string id);
		void search_element(Node* raiz ,string id, bool &band, Node* &elemento);
		//modificadores
		void appendChild(DOM_Tree a);
		void appendChild(DOM_Tree a, int p);
		void removeChild(int pos);
		void agregarhijo(Element padre, Element hijo);
		void replaceChild(DOM_Tree a, int p);
		DOM_Tree despair(string &d);
		//Destructores
		void destroy();
		~DOM_Tree();
		//Sobrercargas
		DOM_Tree stringToDOMTree(string d);
		void appendChild(string a);
		void appendChild(string a, int p);
		DOM_Tree operator =(DOM_Tree const &tree);
		friend std::ostream& operator <<(std::ostream& out, DOM_Tree tree); //Sobrecarga del operador <<
		void imprimir_tree(Node* root, int tab);
};

//Constructores
DOM_Tree::DOM_Tree(const DOM_Tree &a) 
{
	this->document=this->cpy_nodo(a.document);	
}


DOM_Tree::DOM_Tree(Element e, Lista<DOM_Tree > l)
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

Node* DOM_Tree::cpy_nodo(Node *root) //copiar nodos desde el nodo raiz
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

int DOM_Tree::max(int x,int y)
{
	return(x<y ? y:x); 	
}

DOM_Tree DOM_Tree::childNode(int p) //retorna el arbol hijo en la posicion p del arbol padre
{
	Node *aux;
	DOM_Tree tree;
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

DOM_Tree DOM_Tree::getElementByID(string id) //retorna el arbol de tag correspondiente al id
{
	DOM_Tree tree;
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

void DOM_Tree::search_element(Node* raiz ,string id, bool &band, Node* &elemento ) //localiza el tag, moviendose dentro del arbol
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

void DOM_Tree::appendChild(DOM_Tree a) //añade un hijo al arbol en la ultima posicion
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

void DOM_Tree::appendChild(DOM_Tree a, int p) //añade un hijo al arbol en la pos indicada
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

void DOM_Tree::removeChild(int pos) //elimina el arbol hijo en la pos indicada
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


void DOM_Tree:: agregarhijo(Node *root,Element padre, Element hijo, bool &band)
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

void DOM_Tree::replaceChild(DOM_Tree a, int p) //reemplaza un hijo en la posicion indicada
{
	this->removeChild(p);
	this->appendChild(a, p);
}

DOM_Tree DOM_Tree::despair(string &d) //crea los nodos padres a partir de un string
{
	string aux, tag, inner, atributo;
	Node *doc;
	Lista<string> l;
	
	aux=d[0];
	if(aux=="<")
	d.erase(d.begin());
	aux=d[0];
	while(!(aux==">") && !(aux==" "))
	{
	tag=tag+aux;
	d.erase(d.begin());
	aux=d[0];
	}
	if(aux==" ")
	{
	d.erase(d.begin());
	aux=d[0];
	while(!(aux==">"))
	{
		while(!(aux==">") && !(aux==" "))
		{
		atributo=atributo+aux;
		d.erase(d.begin());
		aux=d[0];
		}
		d.erase(d.begin());
		l.insertarEnd(atributo);
		atributo.erase();
		if(aux==" ")
		aux=d[0];
	}
	}
	else
	d.erase(d.begin());
	aux=d[0];		
	while(!(aux=="<"))
	{
		inner=inner+aux;
		d.erase(d.begin());
		aux=d[0];
	}
	Element elem(tag,inner,l);
	doc=new Node(elem);
	DOM_Tree tree(doc);
	l.~Lista();
	return(tree);
}

void DOM_Tree:: agregarhijo(Element padre, Element hijo)
{
	bool band=false;
	this->agregarhijo(document, padre, hijo, band);
}


void DOM_Tree::destroy() //vaciar el domtree
{
	this->destroy(document);
}


//Destructores


void DOM_Tree::destroy(Node *root) 
{
	if(root!=NULL)
	{
		destroy(root->firstchild());
		destroy(root->nextsibling());
		delete(root);
	}	
}

DOM_Tree::~DOM_Tree()
{
	destroy(document);
}


//sobrecargas
DOM_Tree DOM_Tree::operator =(DOM_Tree const &tree)
{
	this->document=this->cpy_nodo(tree.document);
	return(*this);
	
}

DOM_Tree DOM_Tree::stringToDOMTree(string d) //transforma un string en DOMTree
{
	string tag, inner, aux, atributo;
	Node *doc2;
	DOM_Tree tree1, tree2;
	Lista<string> l; 
	
	
	tree1=despair(d);
	d.erase(d.begin());
	aux=d[0];
	if(aux=="/")
	{
		while(!(aux==">"))
		{
		d.erase(d.begin());
		aux=d[0];
		}
		d.erase(d.begin());
	}
	if(d.length()>0)
	tree2=despair(d);
	
	while(d.length()>1)
	{
		tag.erase(); //Limpieza de variables
		inner.erase();
		d.erase(d.begin());
		aux=d[0];
		if(!(aux=="/"))
		{
			while(!(aux==">") && !(aux==" "))
			{
			tag=tag+aux;
			d.erase(d.begin());
			aux=d[0];
			}
			if(aux==" ")
			{
			d.erase(d.begin());
			aux=d[0];
			while(!(aux==">"))
			{
				while(!(aux==">") && !(aux==" "))
				{
				atributo=atributo+aux;
				d.erase(d.begin());
				aux=d[0];
				}
			d.erase(d.begin());
			l.insertarEnd(atributo);
			atributo.erase();
			if(aux==" ")
			aux=d[0];
			}
			}
			else
			d.erase(d.begin());
			aux=d[0];		
			while(!(aux=="<"))
			{
			inner=inner+aux;
			d.erase(d.begin());
			aux=d[0];
			}
			Element elem2(tag,inner,l);
			doc2= new Node(elem2);
			DOM_Tree aux(doc2);
			tree2.appendChild(aux);
			l.~Lista();
		}
		else
		{
			while(!(aux==">"))
			{
			d.erase(d.begin());
			aux=d[0];
			}
			d.erase(d.begin());
		}
	}
	tree1.appendChild(tree2);
return(tree1);
}

void DOM_Tree::appendChild(string a)
{
	DOM_Tree tree;
	
	tree=stringToDOMTree(a);
	appendChild(tree);
}

void DOM_Tree::appendChild(string a, int p)
{
	DOM_Tree tree;
	
	tree=stringToDOMTree(a);
	appendChild(tree,p);
}

std::ostream& operator <<(std::ostream& out, DOM_Tree tree) //Sobrecarga del operador <<
{
	int tab=0;
	
	out<<"<"<<tree.document->element().tagName()<<">";
	if(!tree.document->element().attributeList().es_vacia())
			out<<tree.document->element().attributeList();
	out<<">";
	out<<tree.document->element().innerHTML()<<endl;
	tree.imprimir_tree(tree.document->firstchild(), tab);
	
	return (out);
}

void DOM_Tree::imprimir_tree( Node* root, int tab)
{
	
	if(root!=NULL)
	{
		int i;
		
		for (i=0; i<tab; i++)
		{
			cout<<"	";
		}
		
		cout<<"<"<<root->element().tagName();
		if(!root->element().attributeList().es_vacia())
			cout<<root->element().attributeList();
		cout<<">";
		cout<<root->element().innerHTML();
		if((root->nextsibling()!=NULL && root->firstchild()==NULL) || (root->nextsibling()==NULL && root->firstchild()==NULL))
		cout<<"<"<<"/"<<root->element().tagName()<<">"<<endl;
		else
		cout<<endl;
		this->imprimir_tree(root->firstchild(), tab++);
		this->imprimir_tree(root->nextsibling(), 1);
		if(root->nextsibling()==NULL && root->firstchild()!=NULL)
		cout<<"<"<<"/"<<root->element().tagName()<<">"<<endl;
		
	}
}


#endif
