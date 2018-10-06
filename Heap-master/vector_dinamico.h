#ifndef VECTOR_DINAMICO_H
#define VECTOR_DINAMICO_H

#include <stdlib.h>
#include <stdbool.h>

/*******************************************************************
 *                DEFINICION DE LOS TIPOS DE DATOS
 ******************************************************************/

typedef struct vector {
    size_t tam;
    void** datos;
} vector_t;


/*******************************************************************
 *                    PRIMITIVAS DEL VECTOR
 ******************************************************************/

// Crea un vector de tamaño tam
// Post: vector es una vector vacío de tamaño tam
vector_t* vector_crear(size_t tam);

// Destruye el vector. Si se recibe la funcionn destruir_dato por parametro,
// para cada uno de los elementos del vecotr llama a destruir_dato.
// Pre: la lista fue creada. destruir_dato es una funcionn capaz de destruir
// los datos del vecotr, o NULL en caso de que no se la utilice.
// Post: se eliminaron todos los elementos del vector.
// Pre: el vector fue creado
// Post: se eliminaron todos los elementos del vector.
void vector_destruir(vector_t* vector, void destruir_dato(void*));

// Cambia el tamaño del vector
// Pre: el vector fue creado
// Post: el vector cambió de tamaño a nuevo_tam y devuelve true
// o el vector queda intacto y devuelve false si no se pudo cambiar el tamaño
// a nuevo_tam
bool vector_redimensionar(vector_t* vector, size_t nuevo_tam);

// Devuleve el dato guardado en la posición pos del vector
// Pre: el vector fue creado
// Post: se almacenó en valor el dato en la posición pos. Devuelve false si la
// posición es inválida (fuera del rango del vector, que va de 0 a tamaño-1)
void* vector_obtener(vector_t* vector, size_t pos);

// Almacena el valor en la posición pos
// Pre: el vector fue creado
// Post: se almacenó el valor en la posición pos. Devuelve false si la posición
// es inválida (fuera del rango del vector, que va de 0 a tamaño-1) y true si
// se guardó el valor con éxito.
bool vector_guardar(vector_t* vector, size_t pos, void* valor);

// Devuelve el tamaño del vector
// Pre: el vector fue creado
size_t vector_obtener_tamanio(vector_t* vector);

#endif // VECTOR_DINAMICO_H
