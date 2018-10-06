#ifndef LISTA_H
#define LISTA_H

#include <stdbool.h>
#include <stdio.h>


typedef struct lista lista_t;

// Crea una lista.
// Post: devuelve una nueva lista vacía.
lista_t *lista_crear(void);

// Devuelve verdadero o falso, según si la lista tiene o no elementos.
// Pre: la lista fue creada.
bool lista_esta_vacia(const lista_t *lista);

// Agrega un nuevo elemento al principio de la lista. Devuelve falso en caso de error.
// Pre: la lista fue creada.
// Post: se agregó un nuevo elemento a la lista.
bool lista_insertar_primero(lista_t *lista, void *dato);

// Agrega un nuevo elemento al final de la lista. Devuelve falso en caso de error.
// Pre: la lista fue creada.
// Post: se agregó un nuevo elemento a la lista.
bool lista_insertar_ultimo(lista_t *lista, void *dato);

// Saca el primer elemento de la lista. Si la cola tiene elementos, se quita el
// primero de la lista, y se devuelve su valor, si está vacía, devuelve NULL.
// Pre: la lista fue creada.
// Post: se devolvió el valor del primer elemento anterior, la lista
// contiene un elemento menos, si la lista no estaba vacía.
void *lista_borrar_primero(lista_t *lista);

// Obtiene el valor del primer elemento de la lista. Si la lista tiene
// elementos, se devuelve el valor del primero, si está vacía devuelve NULL.
// Pre: la lista fue creada.
// Post: se devolvió el primer elemento de la lista, cuando no está vacía.
void *lista_ver_primero(const lista_t *lista);

// Obtiene el valor del ultimo elemento de la lista. Si la lista tiene
// elementos, se devuelve el valor del ultimo, si está vacía devuelve NULL.
// Pre: la lista fue creada.
// Post: se devolvió el ultimo elemento de la lista, cuando no está vacía.
void *lista_ver_ultimo(const lista_t* lista);

// Obtiene el valor del largo de la lista.
// Pre: la lista fue creada.
// Post: se devolvió el largo de la lista.
size_t lista_largo(const lista_t *lista);

// Destruye la lista. Si se recibe la función destruir_dato por parámetro,
// para cada uno de los elementos de la lista llama a destruir_dato.
// Pre: la lista fue creada. destruir_dato es una función capaz de destruir
// los datos de la lista, o NULL en caso de que no se la utilice.
// Post: se eliminaron todos los elementos de la lista.
void lista_destruir(lista_t *lista, void destruir_dato(void *));


// Se realiza una iteración interna.
// Pre: se recibe una lista, una función y un extra.
// Posta: se itera sobre la lista aplicando la funcion recibida.
void lista_iterar(lista_t *lista, bool visitar(void *dato, void *extra), void *extra);


typedef struct lista_iter lista_iter_t;

// Crea un iterador.
// Post: devuelve un iterador.
lista_iter_t *lista_iter_crear(lista_t *lista);

// El iterador avanza sobre la lista.
// Pre: el iterador fue creado.
// Post: devuelve true en caso de que se pueda seguir avanzando,
// caso contrario devuelve false.
bool lista_iter_avanzar(lista_iter_t *iter);

// Obtiene el valor del elemento actual de la lista (al que apunta el iterador).
// Pre: el iterador fue creado.
// Post: se devolvió el elemento actual de la lista.
void *lista_iter_ver_actual(const lista_iter_t *iter);

// Devuelve verdadero o falso, según si el iterador se encuentra
// o no al final de la lista (se encuentra al final cuando está apuntando
// a NULL).
// Pre: el iterador fue creado.
bool lista_iter_al_final(const lista_iter_t *iter);

// Destruye el iterador.
// Pre: la lista fue creada.
// Post: se elimina el iterador.
void lista_iter_destruir(lista_iter_t *iter);

// Insera un valor en donde está apuntando el iterador.
// Pre: el iterador fue creado.
// Post: se devuelve true o false, según si se pudo insertar
// el valor a la lista.
bool lista_iter_insertar(lista_iter_t *iter, void *dato);

// Borra el elemento al que está apuntando el iterador.
// Pre: el iterador fue creado.
// Post: se devuelve el elemento borrado o NULL.
void *lista_iter_borrar(lista_iter_t *iter);



// Realiza pruebas sobre la implementación del alumno.
void pruebas_lista_alumno(void);

#endif // LISTA_H