#ifndef Lista_h
#define Lista_h
#include <iostream>
#include "Nodo.h"


template <class gen>
class Lista
{
	private:
		Nodo<gen> *first, *last;
		int lon;
	public:
		Lista<gen>(): first(NULL), last(NULL),lon(0) {} // constructor
		Lista<gen>(Lista<gen> const &l); //constructor copia
		bool es_vacia() const {return first == NULL;} // Comprueba si la lista esta vacia
		bool buscar(gen e); // busca un elemento (y)
		int longitud() const {return lon;} // Retorna la cantidad de elementos que tiene la lista
		gen consultar_elemento (int pos); //Retorna que elemento esta en una posicion dada
		void insertar(gen e, int pos); // inserta un elemento en la lista en la posicion indicada
		void insertarEnd(gen e); //insertar al final 
		void eliminar(int pos); // elimina un elemento de la lista 
		void modificar(gen e, int pos); // modifica el elemento de la posicion dada de la lista
		void copiar(const Lista<gen> &l); //copia una lista a otra
		void invertir();
		void vaciar();
		Lista<gen>& operator =(const Lista &l); // Sobrecarga del operador asignacion =
		template <class eve>
		friend std::ostream& operator <<(std::ostream& out, Lista<eve> l); //Sobrecarga del operador <<
		bool operator ==(Lista<gen> l1); 
		~Lista();
		
};

template<class gen>
Lista<gen>::Lista(Lista<gen> const &l)
{
	this->copiar(l);
}

template<class gen>
bool Lista<gen>::buscar(gen e)
{
	Nodo<gen> *aux;
	if(first != NULL)
	{
		aux=first;
	
		while(aux->obtener_info()!= e && aux->obtener_prox()!= NULL)
		{
			aux=aux->obtener_prox();	
		}	
		return(aux->obtener_info() == e);
	}
	else
		return false;
}


template<class gen>
gen	Lista<gen>::consultar_elemento(int pos)
{
	Nodo<gen> *aux;
	int i;
	
	
	if(0<pos && pos<=lon)
	{
		if(pos==1)
		{
			return first->obtener_info();
		}
		else	
		{
			aux=first;
			for (i=2;i<pos+1;i++)
			{
				aux=aux->obtener_prox();
			}
			return aux->obtener_info();
		}
	}	
	else
	{
		std::cout<<"posicion invalida"<<std::endl;
		return(gen());
	}
}

template <class gen>
void Lista<gen>::insertarEnd(gen e)
{
	Nodo<gen> *aux;  
	aux = new Nodo<gen>(e);
	
	if(first == NULL)
		first = aux;
		
	else
		last->mod_prox(aux);
	last = aux;
	lon++;
}
template <class gen>
void Lista<gen>::insertar(gen e, int pos)
{
	Nodo<gen> *aux = new Nodo<gen>(e);	
	Nodo<gen> *ant, *sig;
	int i;

	if(pos>0 && pos<=lon+1)
	{
		if(pos==1)
		{
			aux->mod_prox(first);
			first=aux;	
			last=aux;
		}
		else
		{
			if(pos==lon+1)
			{
				insertarEnd(e);	
			}
			else
			{
				ant=first;
				sig=ant->obtener_prox();
				for(i=2; i<pos; i++)
				{
					ant=sig;
					sig=sig->obtener_prox();
				}
				ant->mod_prox(aux);
				aux->mod_prox(sig);
				
			}	
		}
		lon++;
	}
	else
	{
		std::cout<<"Inserción en una posicion invalida";
	}
			
}
	
template <class gen>
void Lista<gen>::eliminar(int pos)
{
	Nodo<gen> *aux, *ant;
	int i;
	
	aux=first;
	if(pos > 0 && pos<=lon+1)
	{
		if(pos==1)
		{
			first=aux->obtener_prox();
			delete aux;
			if(lon==1)
				last=first;
		}
		else
		{
			for(i=1; i<pos;i++)
			{
				ant=aux;
				aux=aux->obtener_prox();	
			}
			ant->mod_prox(aux->obtener_prox());
			delete aux;	
			if(ant==NULL)
				last=ant;			
		}
		lon--;
	}
	else
	{
		std::cout<<"Posicion invalida"<<std::endl;
	}
}

template <class gen>
void Lista<gen>::modificar(gen e, int pos)
{
	Nodo<gen> *aux;
	int i;
	if(0 < pos && pos<=lon)
	{
		if(pos==1)
			first->mod_element(e);
		else
		{
			aux=first;
			for(i=1; i<pos; i++)
			{
				aux=aux->obtener_prox();
			}
			aux->mod_element(e);	
		}	
	}
	else
		std::cout<<"posicion invalida"<<std::endl;
}

template <class gen>
void Lista<gen>::copiar(const Lista<gen> &l)
{
	if(!l.es_vacia())
	{	
		Nodo<gen> *aux;
		Nodo<gen> *aux2, *sig;
	
		aux2=l.first;
		aux=new Nodo<gen>(aux2->obtener_info());
		aux2=aux2->obtener_prox();
		this->first = aux;
	
		while(aux2!=NULL)
		{
			sig= new Nodo<gen>(aux2->obtener_info());
			aux->mod_prox(sig);
			aux=sig;
			sig=sig->obtener_prox();
			aux2=aux2->obtener_prox();
		}
		this->last=aux;
		this->lon=l.lon;
	}
	else
	{
		this->first=NULL;
		this->last=NULL;
		this->lon=0;
	}
}

template<class gen>
void Lista<gen>::invertir()
{
	Nodo<gen> *ant, *sig;
	if(lon!=1 && lon!=0)
	{
		last=first;
		ant=first;
		sig=ant->obtener_prox();
		sig=sig->obtener_prox();
		first=first->obtener_prox();
		ant->mod_prox(NULL);
		while(sig!=NULL)
		{
			first->mod_prox(ant);
			ant=first;
			first=sig;
			sig=sig->obtener_prox();
		}
		first->mod_prox(ant);
	}
}
template <class gen>
void Lista<gen>::vaciar()
{
	Nodo<gen> *aux;
	
	while(first!=NULL)
	{
		aux=first;
		first=first->obtener_prox();
		delete aux;	
	}
	last=NULL;
	lon=0;
	
}

template <class gen>
Lista<gen>::~Lista()
{
	this->vaciar();
}





//Sobrecarga de operadores

template <class gen>
Lista<gen>& Lista<gen>::operator = (const Lista<gen> &l)
{
	this->copiar(l);
	return(*this);	
}

template <class gen>
std::ostream& operator <<(std::ostream& out, Lista<gen> l) 
{
		Nodo<gen> *aux;
		
		aux = l.first;
		while(aux != NULL)
		{
			out<< aux->obtener_info() << " ";
			aux=aux->obtener_prox();	
		}
		return(out);
}

template <class gen>
bool Lista<gen>::operator ==(Lista<gen> l1)
{
	bool band=true;
	Nodo<gen> *aux, *aux2;
	
	aux=this->first;
	aux2=l1.first;
	while(aux!=NULL && aux2!=NULL && band==true)
	{
		if(aux->obtener_info()!=aux2->obtener_info())
			band=false;
	}
	
	if(aux==NULL && aux2!=NULL)
		band=false;
	else
	{
		if(aux2==NULL && aux!=NULL)
			band=false;
	}	
	return(band);
}	
#endif
