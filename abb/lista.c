#include "lista.h"
#include <stdlib.h>
#include "testing.h"
#include <stdio.h>

typedef struct nodo {
	void* dato;
	struct nodo* siguiente;
}nodo_t;

struct lista{
	nodo_t* prim;
	nodo_t* ult;
	size_t largo;
};

struct lista_iter{
	nodo_t* act;
	nodo_t* ant;
	lista_t* lista;
};

nodo_t* nodo_crear(void* valor) {
	nodo_t* nodo = malloc(sizeof(nodo_t));

	if(!nodo) {
		return NULL;
	}
	nodo->dato = valor;
	nodo->siguiente = NULL;
	return nodo;
}

void* nodo_destruir(nodo_t* nodo) {
	void* dato = nodo->dato;
	free(nodo);
	return dato;
}

lista_t *lista_crear(void) {
	lista_t* lista = malloc(sizeof(lista_t));
	if (lista == NULL){
		return NULL;
	}
	lista->prim = NULL;
	lista->ult = NULL;
	lista->largo = 0;
	return lista;
}

bool lista_esta_vacia(const lista_t *lista) {
	return lista->prim == NULL && lista->ult == NULL;
}

bool lista_insertar_primero(lista_t *lista, void *dato) {
	nodo_t* nodo = nodo_crear(dato);
	if (!nodo) {
		return false;
	}
	if (lista_esta_vacia(lista)) {
		lista->prim = nodo;
		lista->ult = nodo ;
		lista->largo++;
		return true;
	}
	nodo->siguiente = lista->prim;
	lista->prim = nodo;
	lista->largo++;
	return true;
}

bool lista_insertar_ultimo(lista_t *lista, void *dato) {
	nodo_t* nodo = nodo_crear(dato);
	if (!nodo) {
		return false;
	}
	if (lista_esta_vacia(lista)) {
		lista->prim = nodo;
		lista->ult = nodo ;
		lista->largo++;
		return true;
	}

	lista->ult->siguiente = nodo;
	lista->ult = nodo;
	lista->largo++;
	return true;
}

void *lista_borrar_primero(lista_t *lista) {
	if (lista_esta_vacia(lista)) {
		return NULL;
	}
	if (lista->ult == lista->prim) {
		nodo_t* aux = lista->prim;
		lista->prim = NULL;
		lista->ult = NULL;
		lista->largo--;
		return nodo_destruir(aux);
	}
	nodo_t* aux = lista->prim;
	lista->prim = lista->prim->siguiente;
	lista->largo--;
	return nodo_destruir(aux);
}

void *lista_ver_primero(const lista_t *lista) {
	if (lista_esta_vacia(lista)) {
		return NULL;
	}
	return lista->prim->dato;
}

void *lista_ver_ultimo(const lista_t* lista) {
	if (lista_esta_vacia(lista)) {
		return NULL;
	}
	return lista->ult->dato;
}

size_t lista_largo(const lista_t *lista) {
	return lista->largo;
}

void lista_destruir(lista_t *lista, void destruir_dato(void *)) {
	if (!destruir_dato) {
		while (!lista_esta_vacia(lista)) {
			lista_borrar_primero(lista);
		}
		free(lista);
		return;
	}
	while (!lista_esta_vacia(lista)) {
		void* dato = lista_borrar_primero(lista);		
		destruir_dato(dato);
	}
	free(lista);
}

void lista_iterar(lista_t *lista, bool visitar(void *dato, void *extra), void *extra) {
	if (!visitar) return;
	nodo_t* actual = lista->prim;
	while (actual) {
		if (!visitar(actual->dato,extra)) return;
		actual = actual->siguiente;
	}
}

lista_iter_t *lista_iter_crear(lista_t *lista) {
	lista_iter_t* iter = malloc(sizeof(lista_iter_t));
	if (!iter) return NULL;
	iter->lista = lista;
	iter->act = lista->prim;
	iter->ant = NULL;
	return iter;
}

bool lista_iter_avanzar(lista_iter_t *iter) {
	if (lista_esta_vacia(iter->lista)) return false;
	if (!iter->act) return false;
	iter->ant = iter->act;
	iter->act = iter->act->siguiente;
	return true;
}

void *lista_iter_ver_actual(const lista_iter_t *iter) {
	if (!iter->act) return NULL;
	return iter->act->dato;
}

bool lista_iter_al_final(const lista_iter_t *iter) {
	return iter->act == NULL;
}

void lista_iter_destruir(lista_iter_t *iter) {
	free(iter);
}

bool lista_iter_insertar(lista_iter_t *iter, void *dato) {
	if (lista_esta_vacia(iter->lista) || iter->act == iter->lista->prim) {
		lista_insertar_primero(iter->lista,dato);
		iter->act = iter->lista->prim;
		return true;
	}
	if (lista_iter_al_final(iter)) {
		lista_insertar_ultimo(iter->lista,dato);
		iter->act = iter->lista->ult;
		return true;
	}

	nodo_t* nodo = nodo_crear(dato);
	if (!nodo) return false;

	nodo->siguiente = iter->act;
	iter->act = nodo;
	iter->ant->siguiente = iter->act;
	iter->lista->largo++;
	return true;
}

void *lista_iter_borrar(lista_iter_t *iter) {
	if (lista_esta_vacia(iter->lista)) {
		return NULL;
	}
	if (iter->act == iter->lista->prim) {
		iter->act = iter->act->siguiente;
		return lista_borrar_primero(iter->lista);
	}
	if (lista_iter_al_final(iter)) {
		return NULL;
	}
	if (iter->act == iter->lista->ult) {
		iter->lista->ult = iter->ant;
	}

	nodo_t* nodo = iter->act;
	iter->ant->siguiente = iter->act->siguiente;
	iter->act = iter->act->siguiente;
	iter->lista->largo--;
	return nodo_destruir(nodo);
}