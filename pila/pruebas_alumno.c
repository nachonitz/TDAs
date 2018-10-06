#include "pila.h"
#include "testing.h"
#include <stddef.h> 
#include <stdio.h> 

/* ******************************************************************
 *                   PRUEBAS UNITARIAS ALUMNO
 * *****************************************************************/

void pruebas_pila() {
	int numero1 = 1;
	int numero2 = 2;
	
	pila_t * pila = pila_crear();
	print_test("crear una pila", pila != NULL);
	print_test("pila vacía", pila_esta_vacia(pila) == true);
	print_test("apilar primer elemento", pila_apilar(pila,&numero1) == true);
	print_test("apilar segundo elemento", pila_apilar(pila,&numero2) == true);
	print_test("desapilar un elemento", pila_desapilar(pila) == &numero2);
	print_test("desapilar un elemento", pila_desapilar(pila) == &numero1);
	print_test("desapilar en pila vacía", pila_desapilar(pila) == NULL);
	print_test("ver tope vacío", pila_ver_tope(pila) == NULL);
	print_test("apilar null", pila_apilar(pila,NULL) == true);
	pila_destruir(pila);
    print_test("la pila fue destruida", true);	
}

void pruebas_pila_esta_vacia() {
	int numero1 = 1;
	pila_t* pila_pruebas_vacia = pila_crear();
	print_test("pila vacía", pila_esta_vacia(pila_pruebas_vacia));
	pila_apilar(pila_pruebas_vacia,&numero1);
	print_test("pila no vacía", !pila_esta_vacia(pila_pruebas_vacia));
	pila_apilar(pila_pruebas_vacia,&numero1);
	print_test("pila no vacía", !pila_esta_vacia(pila_pruebas_vacia));
	pila_desapilar(pila_pruebas_vacia);
	pila_desapilar(pila_pruebas_vacia);
	print_test("pila vacía", pila_esta_vacia(pila_pruebas_vacia));
	pila_destruir(pila_pruebas_vacia);
}

void pruebas_pila_ver_tope() {
	int numero1 = 1;
	int numero2 = 2;
	pila_t * pila_pruebas_ver_tope = pila_crear();
	pila_apilar(pila_pruebas_ver_tope,&numero1);
	print_test("ver tope numero1", pila_ver_tope(pila_pruebas_ver_tope) == &numero1);
	pila_apilar(pila_pruebas_ver_tope,&numero2);
	print_test("ver tope numero2", pila_ver_tope(pila_pruebas_ver_tope) == &numero2);
	pila_apilar(pila_pruebas_ver_tope,NULL);
	print_test("ver tope NULL", pila_ver_tope(pila_pruebas_ver_tope) == NULL);
	pila_desapilar(pila_pruebas_ver_tope);
	pila_desapilar(pila_pruebas_ver_tope);
	pila_desapilar(pila_pruebas_ver_tope);
	print_test("ver tope vacía", pila_ver_tope(pila_pruebas_ver_tope) == NULL);
	pila_destruir(pila_pruebas_ver_tope);
}

//PRUEBA DE APILAR MUCHAS COSAS
void prueba_volumen() {
	int numero1 = 1;

	pila_t * pila2 = pila_crear();
    for (int i = 0; i < 1000000; i++) {
    	pila_apilar(pila2,&numero1);
    }
    print_test("redimension de pila 1", pila_ver_tope(pila2) == &numero1 );

    for (int i = 1000000; i > 0; i--) {
    	pila_desapilar(pila2);
    }
    print_test("redimensión de pila 2", pila_ver_tope(pila2) == NULL);
    pila_destruir(pila2);
}

void pruebas_pila_alumno() {
	pruebas_pila();
	pruebas_pila_esta_vacia();
	pruebas_pila_ver_tope();
	prueba_volumen();
}


