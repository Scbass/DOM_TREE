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
		Nodo():prox(NULL){} // constructor
		Nodo(T a): info(a), prox(NULL) {};// constructor con parametros
		void mod_element(T e) {info=e;}
		void mod_prox(Nodo *proximo){prox=proximo;}
		T obtener_info() const{return (this->info);}
		Nodo* obtener_prox() const {return prox;}	
};

	
#endif
