#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "abb.h"
#include "testing.h"
#define VOLUMEN 1000
#define NO_CLAVE "pollo"

bool concatenar(const char* clave, void* dato, void* extra) {
	if (clave){
		strcat((char*)extra,clave);
        printf("%s\n", (char*)extra);
    	return true;
    }
    return false;
 }

void prueba_abb_vacio(){
	
	abb_t* abb_vacio = abb_crear(strcmp, free);
	print_test("ABB creado", abb_vacio != NULL);
	print_test("ABB vacio", abb_cantidad(abb_vacio) == 0);
	print_test("Prueba de obtener una clave, NULL", abb_obtener(abb_vacio, NO_CLAVE) == NULL );
	print_test("Prueba de buscar una clave y que no exista, false", abb_pertenece(abb_vacio, NO_CLAVE) == false );
	print_test("Prueba de borrar una clave y que no exista, NULL", abb_borrar(abb_vacio, NO_CLAVE) == NULL );
    abb_destruir(abb_vacio);  
}

void prueba_iterador_abb(){
	
    char * clave[] = {"1","2","3","4","5"};
	abb_t* abb_a_iterar = abb_crear(strcmp, NULL);
  	char dato ='0';
	print_test("ABB creado", abb_a_iterar != NULL);
	print_test("ABB vacio", abb_cantidad(abb_a_iterar) == 0);
	print_test("Prueba de guardar clave desordenada (3)", abb_guardar(abb_a_iterar, clave[2], &dato) == true );
	print_test("Prueba de guardar clave desordenada (5)", abb_guardar(abb_a_iterar, clave[4], &dato) == true );
	print_test("Prueba de guardar clave desordenada (4)", abb_guardar(abb_a_iterar, clave[3], &dato) == true );
	print_test("Prueba de guardar clave desordenada (1)", abb_guardar(abb_a_iterar, clave[0], &dato) == true );
	print_test("Prueba de guardar clave desordenada (2)", abb_guardar(abb_a_iterar, clave[1], &dato) == true );
	print_test("Prueba cantidad, arbol debe tener 5 nodos", abb_cantidad(abb_a_iterar) == 5);
	abb_iter_t* iterador = abb_iter_in_crear(abb_a_iterar);
	print_test("ITERADOR creado", iterador != NULL);
	print_test("Prueba ver clave actual = (1)", strcmp(abb_iter_in_ver_actual(iterador), clave[0]) == 0);
	print_test("Prueba avanzar", abb_iter_in_avanzar(iterador) == true);
	print_test("Prueba ver clave actual = (2)", strcmp(abb_iter_in_ver_actual(iterador), clave[1]) == 0);
	print_test("Prueba avanzar", abb_iter_in_avanzar(iterador) == true);
	print_test("Prueba ver clave actual = (3)", strcmp(abb_iter_in_ver_actual(iterador), clave[2]) == 0);
	print_test("Prueba avanzar", abb_iter_in_avanzar(iterador) == true);
	print_test("Prueba ver clave actual = (4)", strcmp(abb_iter_in_ver_actual(iterador), clave[3]) == 0);
	print_test("Prueba avanzar", abb_iter_in_avanzar(iterador) == true);
	print_test("Prueba ver clave actual = (5)", strcmp(abb_iter_in_ver_actual(iterador), clave[4]) == 0);
	print_test("Prueba avanzar hasta NULL, true", abb_iter_in_avanzar(iterador) == true);
	print_test("Prueba avanzar hasta NULL, iterador esta en NULL", abb_iter_in_ver_actual(iterador) == NULL);
	print_test("Prueba iterador al final", abb_iter_in_al_final(iterador) == true);
	print_test("Prueba avanzar es invalido, false", abb_iter_in_avanzar(iterador) == false);
    
    
    char cat[10];
    memset(cat,'\0',10);
    print_test("Prueba iterador interno, concatenar e imprimir todas las claves", true);
	abb_in_order(abb_a_iterar, &concatenar, cat);
     print_test("Se esta por destruir el iterador del abb", true);
    abb_iter_in_destruir(iterador);
    print_test("Se esta por destruir el abb", true);
    abb_destruir(abb_a_iterar);
}

void prueba_destruir() {
    
    
    int ** dato = calloc(6,sizeof(int*));
    
      for (int i=0;i<6;i++){
     	dato[i] = (int*) calloc(1,sizeof(int));
		*dato[i] = i;
	 }
    
    
    char * clave[] = {"1","2","3","4","5"};
    abb_t* abb = abb_crear(strcmp, free);
    print_test("ABB creado", abb != NULL);
	print_test("ABB vacio", abb_cantidad(abb) == 0);
	print_test("Prueba de guardar clave(1)", abb_guardar(abb, clave[0], dato[0]) == true );
    print_test("Prueba de guardar clave(2)", abb_guardar(abb, clave[1], dato[1]) == true );
	print_test("Prueba sobreescribir dato en clave(1)", abb_guardar(abb, clave[0], dato[5]) == true );
    print_test("Prueba borrar clave (1)", abb_borrar(abb, clave[0]) == dato[5]);  free(dato[5]);
  	print_test("Prueba clave (1) no esta en el abb", abb_pertenece(abb, clave[0]) == false);
    print_test("Prueba de guardar clave(3)", abb_guardar(abb, clave[2], dato[2]) == true );
    print_test("Prueba de guardar clave(4)", abb_guardar(abb, clave[3], dato[3]) == true );
    print_test("Prueba de guardar clave(5)", abb_guardar(abb, clave[4], dato[4]) == true );
    print_test("Se esta por destruir el abb", true);
    abb_destruir(abb);
    free(dato);
    
}

static void prueba_abb_volumen(size_t largo, bool debug) //copie la del hash
{
    abb_t* abb = abb_crear(strcmp, NULL);

    const size_t largo_clave = 10;
    char (*claves)[largo_clave] = malloc(largo * largo_clave);

    unsigned* valores[largo];

    // Inserta 'largo' parejas en el abb 
    bool ok = true;
    for (unsigned i = 0; i < largo; i++) {
        valores[i] = malloc(sizeof(int));
        sprintf(claves[i], "%08d", i);
        *valores[i] = i;
        ok = abb_guardar(abb, claves[i], valores[i]);
        if (!ok) break;
    }

    if (debug) print_test("Prueba abb almacenar muchos elementos", ok);
    if (debug) print_test("Prueba abb la cantidad de elementos es correcta", abb_cantidad(abb) == largo);

    // Verifica que devuelva los valores correctos 
    for (size_t i = 0; i < largo; i++) {
        ok = abb_pertenece(abb, claves[i]);
        if (!ok) break;
        ok = abb_obtener(abb, claves[i]) == valores[i];
        if (!ok) break;
    }

    if (debug) print_test("Prueba abb pertenece y obtener muchos elementos", ok);
    if (debug) print_test("Prueba abb la cantidad de elementos es correcta", abb_cantidad(abb) == largo);

    // Verifica que borre y devuelva los valores correctos 
    for (size_t i = 0; i < largo; i++) {
        ok = (abb_borrar(abb, claves[i]) == valores[i]);
        if (!ok) break;
    }

    if (debug) print_test("Prueba abb borrar muchos elementos", ok);
    if (debug) print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(abb) == 0);

    // Destruye el abb y crea uno nuevo que sí libera 
    abb_destruir(abb);
    abb = abb_crear(strcmp, free);

    // Inserta 'largo' parejas en el abb 
    ok = true;
    for (size_t i = 0; i < largo; i++) {
        ok = abb_guardar(abb, claves[i], valores[i]);
        if (!ok) break;
    }

    free(claves);

    // Destruye el abb - debería liberar los enteros 
    abb_destruir(abb);

}



void pruebas_abb_alumno() {
 
 	prueba_abb_vacio();
    prueba_destruir();
    prueba_iterador_abb();
    prueba_abb_volumen(VOLUMEN, true);

}


