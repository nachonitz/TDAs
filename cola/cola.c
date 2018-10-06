#include "cola.h"
#include <stdlib.h>
#include "testing.h"

typedef struct nodo {
    void* dato;
    struct nodo* siguiente;
} nodo_t;

struct cola {
    nodo_t* prim;
    nodo_t* ult;
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

cola_t* cola_crear(void) {
	cola_t* cola = malloc(sizeof(cola_t));

	if (cola == NULL) {
		return NULL;
	}

	cola->prim = NULL;
	cola->ult = NULL;
	return cola;
}

bool cola_esta_vacia(const cola_t *cola) {
	return cola->prim == NULL && cola->ult == NULL;
}

bool cola_encolar(cola_t *cola, void* valor) {
	nodo_t* nodo = nodo_crear(valor);
	if (!nodo) {
		return false;
	}
	if (cola_esta_vacia(cola)) {
		cola->prim = nodo;
	}
	else {
		cola->ult->siguiente = nodo;
	}

	cola->ult = nodo;

	return true;
}

void* cola_ver_primero(const cola_t *cola) {
	if (cola_esta_vacia(cola)) {
		return NULL;
	}
	return cola->prim->dato;
}

void* cola_desencolar(cola_t *cola) {
	if (cola_esta_vacia(cola)) {
		return NULL;
	}
	nodo_t* aux = cola->prim;
	if (cola->ult == cola->prim) {
		cola->prim = NULL;
		cola->ult = NULL;
	}
	else{
		cola->prim = cola->prim->siguiente;
	}
	return nodo_destruir(aux);
}

void cola_destruir(cola_t *cola, void destruir_dato(void*)) {
	if (destruir_dato == NULL) {
		while(!cola_esta_vacia(cola)) {
			cola_desencolar(cola);
		}
		free(cola);
		return;
	}
	while (!cola_esta_vacia(cola)) {
		void* dato = cola_desencolar(cola);		
		destruir_dato(dato);
	}
	free(cola);
}