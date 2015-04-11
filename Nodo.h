#ifndef Nodo_h
#define Nodo_h

#include <iostream>

template <class T>
class Nodo
{
	private:
		T info;
		Nodo<T> *prox;
	public:
		//constructores
		Nodo():prox(NULL){}
		Nodo(T a): info(a), prox(NULL) {};//Con parametros
		//modificadores
		void mod_element(T e) {info=e;}
		void mod_prox(Nodo *proximo){prox=proximo;}
		//observadores
		T obtener_info() const{return (this->info);}
		Nodo* obtener_prox() const {return prox;}	
};

	
#endif
