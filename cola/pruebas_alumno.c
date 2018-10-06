#include "cola.h"
#include "testing.h"
#include <stddef.h> 
#include <stdio.h> 

/* ******************************************************************
 *                   PRUEBAS UNITARIAS ALUMNO
 * *****************************************************************/

void destuir_dato(void* dato) {
	printf("destrucción datos... OK\n");
}
void pruebas_cola() {
	int numero1 = 1;
	int numero2 = 2;
	cola_t * cola = cola_crear();
	print_test("crear una cola", cola != NULL);
	print_test("cola vacía", cola_esta_vacia(cola));
	print_test("encolar primer elemento", cola_encolar(cola,&numero1) == true);
	print_test("encolar segundo elemento", cola_encolar(cola,&numero2) == true);
	print_test("desencolar un elemento", cola_desencolar(cola) == &numero1);
	print_test("desencolar un elemento", cola_desencolar(cola) == &numero2);
	print_test("desencolar en pila vacía", cola_desencolar(cola) == NULL);
	print_test("ver primero vacío", cola_ver_primero(cola) == NULL);
	print_test("encolar null", cola_encolar(cola,NULL));
	cola_destruir(cola,NULL);
    print_test("la cola fue destruida", true);
}

void pruebas_cola_esta_vacia() {
	int numero1 = 1;
	cola_t* cola_pruebas_vacia = cola_crear();
	print_test("cola vacía", cola_esta_vacia(cola_pruebas_vacia));
	cola_encolar(cola_pruebas_vacia,&numero1);
	print_test("cola no vacía", !cola_esta_vacia(cola_pruebas_vacia));
	cola_encolar(cola_pruebas_vacia,&numero1);
	print_test("cola no vacía", !cola_esta_vacia(cola_pruebas_vacia));
	cola_desencolar(cola_pruebas_vacia);
	cola_desencolar(cola_pruebas_vacia);
	print_test("cola vacía", cola_esta_vacia(cola_pruebas_vacia));
	cola_destruir(cola_pruebas_vacia,NULL);
}

void pruebas_cola_ver_primero() {
	int numero1 = 1;
	int numero2 = 2;
	cola_t * cola_pruebas_ver_primero = cola_crear();
	cola_encolar(cola_pruebas_ver_primero,&numero1);
	print_test("ver primero numero1", cola_ver_primero(cola_pruebas_ver_primero) == &numero1);
	cola_encolar(cola_pruebas_ver_primero,&numero2);
	print_test("ver primero numero1", cola_ver_primero(cola_pruebas_ver_primero) == &numero1);
	cola_encolar(cola_pruebas_ver_primero,NULL);
	cola_desencolar(cola_pruebas_ver_primero);
	cola_desencolar(cola_pruebas_ver_primero);
	print_test("ver primero NULL", cola_ver_primero(cola_pruebas_ver_primero) == NULL);
	cola_desencolar(cola_pruebas_ver_primero);
	print_test("ver primero vacía", cola_ver_primero(cola_pruebas_ver_primero) == NULL);
	cola_destruir(cola_pruebas_ver_primero,NULL);
}
//ENCOLAR Y DESENCOLAR 50 ELEMENTOS
void prueba_cola_volumen() {
	int numero1 = 1;
	cola_t * cola2 = cola_crear();

	for (int i = 0; i < 1000000; i++) {
		cola_encolar(cola2,&numero1);
	}
	for (int j = 0; j < 1000000; j++) {
		cola_desencolar(cola2);
	}
	print_test("cola vacía", cola_esta_vacia(cola2));
	cola_encolar(cola2,&numero1);
	print_test("cola no vacía", !cola_esta_vacia(cola2));
	cola_destruir(cola2,destuir_dato);
}

void pruebas_cola_alumno() {
	pruebas_cola();
	pruebas_cola_esta_vacia();
	pruebas_cola_ver_primero();
	prueba_cola_volumen();
}
