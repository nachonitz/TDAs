#include "lista.h"
#include "testing.h"
#include <stddef.h>
#include <stdio.h>

/* ******************************************************************
 *                   PRUEBAS UNITARIAS ALUMNO
 * *****************************************************************/

bool imprimir_dato(void*dato,void*extra) {
	printf("iterador interno funciona correctamente \n");
	return true;
}

//PRUEBAS DE LA LISTA
void pruebas_lista() {
	int numero1 = 1;
	int numero2 = 2;

	lista_t * lista = lista_crear();
	print_test("crea una lista", lista != NULL);
	print_test("lista vacía", lista_esta_vacia(lista));
	print_test("lista insertar primero", lista_insertar_primero(lista,&numero1) == true);
	print_test("lista no vacía", !lista_esta_vacia(lista));
	print_test("lista insertar ultimo", lista_insertar_ultimo(lista,&numero2) == true);
	print_test("borrar primero", lista_borrar_primero(lista) == &numero1);
	print_test("ver primero", lista_ver_primero(lista) == &numero2);
	print_test("ver ultimo", lista_ver_ultimo(lista) == &numero2);
	print_test("borrar primero", lista_borrar_primero(lista) == &numero2);
	print_test("borrar en lista vacia", lista_borrar_primero(lista) == NULL);
	print_test("ver primero en lista vacía", lista_ver_primero(lista) == NULL);
	print_test("insertar null", lista_insertar_primero(lista,NULL) == true);
	print_test("borrar primero", lista_borrar_primero(lista) == NULL);	
	print_test("lista insertar primero", lista_insertar_primero(lista,&numero1) == true);
	lista_destruir(lista,NULL);
    print_test("la lista fue destruida", true);
}

void pruebas_lista_esta_vacia() {
	int numero1 = 1;
	lista_t* lista_pruebas_vacia = lista_crear();
	print_test("lista vacía", lista_esta_vacia(lista_pruebas_vacia));
	lista_insertar_ultimo(lista_pruebas_vacia,&numero1);
	print_test("lista no vacía", !lista_esta_vacia(lista_pruebas_vacia));
	lista_insertar_ultimo(lista_pruebas_vacia,&numero1);
	print_test("lista no vacía", !lista_esta_vacia(lista_pruebas_vacia));
	lista_borrar_primero(lista_pruebas_vacia);
	lista_borrar_primero(lista_pruebas_vacia);
	print_test("lista vacía", lista_esta_vacia(lista_pruebas_vacia));
	lista_destruir(lista_pruebas_vacia,NULL);
}

void pruebas_lista_ver_primero() {
	int numero1 = 1;
	int numero2 = 2;
	lista_t * lista_pruebas_ver_primero = lista_crear();
	lista_insertar_primero(lista_pruebas_ver_primero,&numero1);
	print_test("ver primero numero1", lista_ver_primero(lista_pruebas_ver_primero) == &numero1);
	lista_insertar_primero(lista_pruebas_ver_primero,&numero2);
	print_test("ver primero numero2", lista_ver_primero(lista_pruebas_ver_primero) == &numero2);
	lista_insertar_primero(lista_pruebas_ver_primero,NULL);
	print_test("ver primero NULL", lista_ver_primero(lista_pruebas_ver_primero) == NULL);
	lista_borrar_primero(lista_pruebas_ver_primero);
	lista_borrar_primero(lista_pruebas_ver_primero);
	lista_borrar_primero(lista_pruebas_ver_primero);
	print_test("ver primero vacía", lista_ver_primero(lista_pruebas_ver_primero) == NULL);
	lista_destruir(lista_pruebas_ver_primero,NULL);
}

void pruebas_lista_volumen() {
	int numero1 = 1;
	lista_t * lista_pruebas_volumen = lista_crear();
	for (int i = 0; i < 100000; i++) {
    	lista_insertar_primero(lista_pruebas_volumen,&numero1);
    }
    for (int i = 0; i < 100000; i++) {
    	lista_borrar_primero(lista_pruebas_volumen);
    }
    lista_destruir(lista_pruebas_volumen,NULL);
    print_test("la lista fue destruida", true);
}

//PRUEBAS DEL ITERADOR INTERNO
void pruebas_iterador_interno() {
	int numero1 = 1;
	int numero2 = 2;

	lista_t * lista2 = lista_crear();
	lista_insertar_primero(lista2,&numero1);
	lista_insertar_ultimo(lista2,&numero2);
	lista_iterar(lista2,imprimir_dato,NULL);
	lista_destruir(lista2,NULL);
}

//PRUEBAS DEL ITERADOR EXTERNO
void pruebas_iterador_externo() {
	int numero1 = 1;
	int numero2 = 2;
	
	lista_t * lista3 = lista_crear();
	lista_insertar_primero(lista3,&numero1);
	lista_insertar_ultimo(lista3,&numero2);
	lista_iter_t * iter = lista_iter_crear(lista3);
	print_test("crear una iterador", iter != NULL);
	print_test("avanzar", lista_iter_avanzar(iter) == true);
	print_test("ver actual", lista_iter_ver_actual(iter) == &numero2);
	print_test("esta al final", lista_iter_al_final(iter) == false);
	print_test("borrar", lista_iter_borrar(iter) == &numero2);
	print_test("esta al final", lista_iter_al_final(iter) == true);
	print_test("insertar", lista_iter_insertar(iter,&numero2) == true);
	print_test("esta al final", lista_iter_al_final(iter) == false);
	print_test("borrar",lista_iter_borrar(iter) == &numero2);
	print_test("esta al final", lista_iter_al_final(iter) == true);
	print_test("avanzar",lista_iter_avanzar(iter) == false);
	print_test("largo",lista_largo(lista3) == 1);
	print_test("ver actual", lista_iter_ver_actual(iter) == NULL);
	print_test("esta al final", lista_iter_al_final(iter) == true);

	//PRUEBA DE VOLUMEN
	for (int i = 0; i < 100000; i++) {
    	lista_iter_insertar(iter,&numero1);
    }
    for (int i = 0; i < 100000; i++) {
    	lista_iter_borrar(iter);
    }
	lista_iter_destruir(iter);
	lista_destruir(lista3,NULL);
}

void pruebas_lista_alumno() {
	pruebas_lista();
	pruebas_lista_esta_vacia();
	pruebas_lista_ver_primero();
	pruebas_lista_volumen();
	pruebas_iterador_interno();
	pruebas_iterador_externo();
}
