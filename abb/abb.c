#define _XOPEN_SOURCE 500
#include "abb.h"
#include "lista.h"
#include <stdlib.h>
#define _SVID_SOURCE
#include <string.h>

#define apilar(lista,dato) lista_insertar_primero(lista,dato)
#define desapilar(lista) lista_borrar_primero(lista)

struct abb {
	abb_t* izq;
	abb_t* der;
	char* clave;
	void* dato;
	abb_comparar_clave_t cmp;
	abb_destruir_dato_t destruir_dato;
};


abb_t* abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato){
	if (!cmp) return NULL;
	abb_t* arbol = malloc(sizeof(abb_t));
	if (!arbol) return NULL;
	arbol->cmp = cmp;
	arbol->destruir_dato = destruir_dato;
	arbol->clave = NULL;
	arbol->dato = NULL;
	arbol->izq = NULL;
	arbol->der = NULL;
	return arbol;
}



bool abb_guardar(abb_t *arbol, const char *clave, void *dato) {
	
	if (!arbol->clave){
		arbol->clave = strdup(clave);
		arbol->dato = dato;
	}
	
	else {
	
	int cmp = arbol->cmp(arbol->clave,clave);
	if (cmp == 0 ) {
		
		if(arbol->destruir_dato) arbol->destruir_dato(arbol->dato);
		arbol->dato = dato;
		return true;
	}else if (cmp > 0){
		if (arbol->izq) {
			return abb_guardar(arbol->izq,clave,dato);
		}else{
			arbol->izq = abb_crear(arbol->cmp,arbol->destruir_dato);
			arbol->izq->clave = strdup(clave);
			arbol->izq->dato = dato;
			return true;
		}
	}else{
		if (arbol->der){
			return abb_guardar(arbol->der,clave,dato);
		}else{
			arbol->der = abb_crear(arbol->cmp,arbol->destruir_dato);
			arbol->der->clave = strdup(clave);
			arbol->der->dato = dato;
			return true;
		}
	}
	}
	return true;
}

void *abb_obtener(const abb_t *arbol, const char *clave){
	
	
	if (!arbol || !arbol->clave) return NULL;
	int cmp = arbol->cmp(arbol->clave,clave);
	if (cmp == 0 ) {
		return arbol->dato;
	}else if (cmp > 0){
		if (arbol->izq) {
			return abb_obtener(arbol->izq,clave);
		}else{
			return NULL;
		}
	}else{
		if (arbol->der){
			return abb_obtener(arbol->der,clave);
		}else{
			return NULL;
		}
	}
}

bool abb_pertenece(const abb_t *arbol, const char *clave){
	
	if (arbol == NULL || arbol->clave == NULL) return NULL;
	int cmp = arbol->cmp(arbol->clave,clave);
	if (cmp == 0 ) {
		return true;
	}else if (cmp > 0){
		if (arbol->izq) {
			return abb_pertenece(arbol->izq,clave);
		}else{
			return false;
		}
	}else{
		if (arbol->der){
			return abb_pertenece(arbol->der,clave);
		}else{
			return false;
		}
	}
}

size_t abb_cantidad(abb_t *arbol){
	if (arbol == NULL || !arbol->clave){
		return 0;
	}
	return abb_cantidad(arbol->izq) + abb_cantidad(arbol->der) + 1;
}



//busca el nodo mas chico o el mas grande
abb_t* abb_min_max(abb_t* min, abb_t* max){
	
	if(min){
	
		if (!min->izq) return min;
		return abb_min_max(min->izq,NULL);
	}
	if(max){
	
	if (!max->der) return max;
	return abb_min_max(NULL,max->der);
	}
	return NULL;
}

abb_t *abb_obtener_arbol(abb_t *arbol, const char *clave){
	
	
	if (!arbol || !arbol->clave) return NULL;
	int cmp = arbol->cmp(arbol->clave,clave);
	if (cmp == 0 ) {
		return arbol;
	}else if (cmp > 0){
		if (arbol->izq) {
			return abb_obtener(arbol->izq,clave);
		}else{
			return NULL;
		}
	}else{
		if (arbol->der){
			return abb_obtener(arbol->der,clave);
		}else{
			return NULL;
		}
	}
}

void reemplazar(abb_t* arbol, abb_t* arbol_auxiliar){
	if (!arbol->der){
		arbol_auxiliar->clave = arbol->clave;
		arbol_auxiliar->dato = arbol->dato;
		arbol_auxiliar = arbol;
		arbol = arbol->izq;
	}
	else
		reemplazar(arbol->der,arbol_auxiliar);
}

abb_t* buscar_nodo_a_reemplazar(abb_t*arbol){
	printf("buscar");
	if (!arbol->izq)
		return arbol;
	return buscar_nodo_a_reemplazar(arbol->izq);
}

void abb_intercambiar(abb_t* arbol,abb_t* otro_arbol){
	arbol->clave = otro_arbol->clave;
	arbol->dato = otro_arbol->dato;
}

void * abb_borrar(abb_t* arbol, const char* clave){
	//abb_t* arbol_auxiliar = abb_crear(arbol->cmp,arbol->destruir_dato);
	if (!arbol || !arbol->clave) return NULL;
	//int cmp = (arbol->cmp(clave, arbol->clave));
	void*dato;
	abb_t* arbol_a_borrar = abb_obtener_arbol(arbol,clave);
	if (!arbol_a_borrar) return NULL;
	dato = arbol_a_borrar->dato;
/*	if (cmp > 0)
		abb_borrar(arbol->der, clave);
	else if (cmp < 0)
		abb_borrar(arbol->izq, clave);
	else if (cmp == 0){
		dato = arbol->dato;*/
		//arbol_auxiliar = arbol;
		/*if(!arbol->izq){
			arbol = arbol->der;
			
		}
		else if (!arbol->der)
			arbol = arbol->izq;
		else
			reemplazar(arbol->izq, arbol_auxiliar);
	}*/
	if (!arbol_a_borrar->izq){
		printf("%s",(char*)arbol_a_borrar->dato);
		printf("no hay izq");
		abb_t* aux = arbol_a_borrar;
		arbol_a_borrar = arbol_a_borrar->der;
		free(aux);
		return dato;
	}
	else if (!arbol_a_borrar->der){
		printf("no hay der");
		abb_t* aux = arbol_a_borrar;
		arbol_a_borrar = arbol_a_borrar->izq;
		free(aux);
		return dato;
	}
	abb_t* arbol_a_reemplazar = buscar_nodo_a_reemplazar(arbol->der);
	printf("%s",(char*)arbol_a_reemplazar->clave);
	abb_intercambiar (arbol_a_borrar,arbol_a_reemplazar);
	abb_t* aux = arbol_a_reemplazar;
	arbol_a_reemplazar = arbol_a_reemplazar->der;
	abb_destruir(aux);
	return dato;
}

/*
void *abb_borrar(abb_t *arbol, const char *clave){
	if (!arbol || !arbol->clave) return NULL;

	void* dato = NULL, *swap_dato = NULL	;
	abb_t* swap;
	char* swap_clave;

	int cmp = (arbol->cmp(clave, arbol->clave));

	if (cmp == 0){
		dato = arbol->dato;
		
	if (!arbol->izq && !arbol->der){
		arbol->dato=NULL; 
			free(arbol->clave);
			arbol->clave = NULL;
	} 
		
		else {			
		
			if (arbol->izq) {
				swap = abb_min_max(NULL,arbol->izq);
					if (!swap->clave)return NULL;
				
				swap_clave = strdup(swap->clave);
				swap_dato = abb_borrar(arbol->izq, swap->clave);
				if (!arbol->izq->clave){
					free(arbol->izq);
					arbol->izq = NULL;
				}
			} if (arbol->der) {
				swap = abb_min_max(arbol->der,NULL);
				if (!swap->clave)return NULL;
				swap_clave = strdup(swap->clave);
				swap_dato = abb_borrar(arbol->der, swap->clave);
				if (!arbol->der->clave){
					free(arbol->der);
					arbol->der = NULL;
				}
			}
			free(arbol->clave);
			arbol->clave = swap_clave;
			arbol->dato = swap_dato;
		}
	} 
	
	else if (cmp < 0)	dato = abb_borrar(arbol->izq, clave);
	else	dato = abb_borrar(arbol->der, clave);
	
	return dato;
}
*/



void abb_destruir(abb_t *arbol){
	if (!arbol) return;
	abb_destruir(arbol->izq);
	abb_destruir(arbol->der);
	if (arbol->destruir_dato)
			arbol->destruir_dato(arbol->dato);
	free(arbol->clave);
	free(arbol);
}


//ITERADOR INTERNO


void abb_in_order(abb_t * arbol, bool (*visitar)(const char *, void *, void *), void *extra){
	
	if (arbol) {
		abb_in_order(arbol->izq,visitar,extra);
		if (visitar)
			if(!visitar(arbol->clave,arbol->dato,extra)) return;
		abb_in_order(arbol->der,visitar,extra);
	}
	
}

//ITERADOR EXTERNO




void listar_izquierdos(const abb_t * arbol, lista_t* iter);

struct abb_iter{
	lista_t* pila; 
};


void listar_izquierdos(const abb_t * arbol, lista_t* iter){
	if (arbol)
		if(arbol->izq){
			//lista_insertar_primero(iter, arbol);
			apilar(iter,(void*)arbol->izq);
			listar_izquierdos(arbol->izq, iter);
		}
}

//pre: arbol creado
abb_iter_t *abb_iter_in_crear(const abb_t *arbol){
	
	//if  (arbol){
		abb_iter_t* abb_iter = calloc(1,sizeof(abb_iter_t));
		if (!abb_iter)  return NULL;
		lista_t* pila = lista_crear();
		if (!pila) return NULL;
		
		
		abb_iter->pila = pila;
		if(arbol->clave) {
			//lista_insertar_primero(pila, arbol);
			apilar(pila,(void*)arbol);
			listar_izquierdos(arbol, abb_iter->pila);
		}
		
		return abb_iter;
//	}

}

bool abb_iter_in_avanzar(abb_iter_t *iter){
	if(abb_iter_in_al_final(iter)) return false;
	
	abb_t* desapilado = (abb_t*)desapilar(iter->pila);
	
	if (!desapilado) return false; 
	if (desapilado->der) {
		apilar(iter->pila, desapilado->der);
		listar_izquierdos(desapilado->der,iter->pila);
	}
	return true;
}


const char *abb_iter_in_ver_actual(const abb_iter_t *iter){
		if (abb_iter_in_al_final(iter))  return NULL;
		return ((abb_t*)lista_ver_primero(iter->pila))->clave;	
}

bool abb_iter_in_al_final(const abb_iter_t *iter){
	return lista_esta_vacia(iter->pila);
}

void abb_iter_in_destruir(abb_iter_t* iter){
	lista_destruir(iter->pila,NULL);
	free(iter);
}
