#include "pila.h"
#include <stdlib.h>
#include "testing.h"
/* Definición del struct pila proporcionado por la cátedra.
 */
#define CAPACIDAD_MINIMA 10
#define FACTOR_REDIMENSION 2
#define RELACION_MAXIMA 4

struct pila {
    void** datos;
    size_t cantidad;  // Cantidad de elementos almacenados.
    size_t capacidad;  // Capacidad del arreglo 'datos'.
};

/* *****************************************************************
 *                    PRIMITIVAS DE LA PILA
 * *****************************************************************/

// ...


bool pila_redimensionar(pila_t* pila, size_t tam_nuevo) {
    void* datos_nuevo = realloc(pila->datos, tam_nuevo * sizeof(void*));

    // Cuando tam_nuevo es 0, es correcto si se devuelve NULL.
    // En toda otra situación significa que falló el realloc.
    if (tam_nuevo > 0 && datos_nuevo == NULL) {
        return false;
    }

    pila->datos = datos_nuevo;
    pila->capacidad = tam_nuevo;
    return true;
}
pila_t* pila_crear() {
	pila_t* pila = malloc(sizeof(pila_t));

	if (pila == NULL) {
		return NULL;
	}

	pila->datos = malloc(CAPACIDAD_MINIMA * sizeof(void*));
	if (pila->datos == NULL) {
		free(pila);
		return NULL;
	}

	pila->capacidad = CAPACIDAD_MINIMA;
	pila->cantidad = 0;

	return pila;
}

void pila_destruir(pila_t *pila) {
	free(pila->datos);
	free(pila);
}

bool pila_esta_vacia(const pila_t *pila) {
	return pila->cantidad == 0;
}
bool pila_apilar(pila_t *pila, void* valor) {
	if (pila->cantidad == pila->capacidad) {
		bool redimension = pila_redimensionar(pila,FACTOR_REDIMENSION*pila->capacidad);
		if (!redimension) {
			return false;
		}
	}
	pila->datos[pila->cantidad] = valor;
	pila->cantidad ++;
	
	return true;

}

void* pila_ver_tope(const pila_t *pila) {
	
	if (pila_esta_vacia(pila)) {
		return NULL;
	}

	void* tope = pila->datos[pila->cantidad-1];

	return tope;
}

void* pila_desapilar(pila_t *pila) {

	if (pila_esta_vacia(pila)) {
		return NULL;
	}


	if (pila->capacidad / pila->cantidad >= RELACION_MAXIMA && pila->capacidad > CAPACIDAD_MINIMA ) {
		bool redimension = pila_redimensionar(pila,pila->capacidad/FACTOR_REDIMENSION);
		if (!redimension) {
			return NULL;
		}
	}

	void* dato = pila->datos[pila->cantidad-1];
	pila->datos[pila->cantidad-1] = NULL;
	pila->cantidad --;

	return dato;
}
