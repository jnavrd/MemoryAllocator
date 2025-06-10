//
// Created by juana on 7/6/2025.
//

#include "VariableSizeAllocator.h"

#include <cstdlib>
#include <cstdio>

using namespace std;

void *VariableSizeAllocator::allocate(size_t size) {

    if(first_free == nullptr) {
        printf("No hay slots disponibles");
        return nullptr;
    }

    void* best_slot = nullptr; //el bloque que mejor se acomode al tamanio
    size_t best_size = SIZE_MAX;

    void* current_slot = first_free;
    void** next_free_slot = nullptr; //puntero a puntero. encontrar el proximo bloque en la free list

    printf("Looking for %zu bytes...\n", size + 16);
    while(current_slot != nullptr) //buscar el slot que mas se ajuste al tamanio pedido (best-fit)
    {
        size_t* size_location = (size_t*)((char*)current_slot + 8); //buscar el tamanio del bloque libre. size_location apunta a una direccion de memoria donde hay un size_t (size_t*)
        size_t slot_size = *size_location; //guardar el tamanio del bloque

        printf("Found slot at %p with size %zu\n", current_slot, slot_size);

        if(slot_size >= size && slot_size < best_size) {
            best_slot = current_slot;
            best_size = slot_size;
            printf("  -> New best fit!\n");
        }
        next_free_slot = (void**)current_slot; //puntero a puntero. apunta a una dir de memoria donde hay un puntero. encontrar el proximo bloque en la free list
        current_slot = *next_free_slot;
    }
    printf("Best choice: %p with size %zu\n", best_slot, best_size);

    void* assigned_slot = best_slot;

    if(best_slot == nullptr){
        printf("No hay un slot disponible");
        return nullptr;
    }

    if(best_size == size + 16) {

        void** next_free_ptr = (void**)best_slot; //encontrar el puntero al puntero del siguiente libre
        first_free = *next_free_ptr; //asignar a first free el puntero del siguiente libre
        size_t* assigned_slot_size = (size_t*)((char*)assigned_slot + 8);
        *assigned_slot_size = size + 16;

    } else if(best_size > size + 16) { //crear un nuevo slot, first free es este slot

        char* new_slot_pos = (char*)best_slot + 16 + size; //16 = 8 bytes de puntero y 8 bytes de size_t

        void** new_slot_next = (void**)new_slot_pos;
        *new_slot_next = *(void**)best_slot; // el valor almacenado (primer * despues del =) en la direccion donde esta el puntero (void**)

        size_t* new_slot_size = (size_t*)(new_slot_pos + 8);
        *new_slot_size = best_size - (16 + size); //el nuevo bloque tendra el tamanio del bloque anterior menos el size pedido mas 16 bytes para puntero y size_t

        first_free = new_slot_pos;

        size_t* assigned_slot_size = (size_t*)((char*)assigned_slot + 8);
        *assigned_slot_size = size + 16;

    }

    return (char*)assigned_slot + 16;
}


void VariableSizeAllocator::deallocate(void *ptr) {

    if(ptr == nullptr)
    {
        printf("El puntero no es valido");
        return;
    }

    void** freed_slot_ptr = (void**)((char*)ptr - 16); //allocate devuelve el bloque + 16, porque ahi estan los datos del user.
    *freed_slot_ptr = first_free;

    size_t* freed_size_ptr = (size_t*)((char*)ptr - 8); //-8 porque ptr es donde estan los datos del user.
    void* start_freed = (char*)ptr - 16;
    void* end_freed = (char*)start_freed + *freed_size_ptr;

    if((char*)end_freed == (char*)first_free)
    {
        printf("dentro del if");
        size_t* first_free_size = (size_t*)((char*)first_free + 8);
        *freed_size_ptr = *freed_size_ptr + *first_free_size;
        *freed_slot_ptr = *(void**)first_free;
    }

    first_free = (void*)((char*)ptr - 16);

    // Al final de deallocate():
    printf("Added to free list: %p, first_free now: %p\n", (char*)ptr - 16, first_free);

}


VariableSizeAllocator::VariableSizeAllocator(size_t size) {
    memory_block = malloc(size);
    first_free = memory_block;

    //el siguiente free todavia no existe, es un unico bloque
    void** next_free_ptr = (void**)first_free;
    *next_free_ptr = nullptr;

    size_t* size_location = (size_t*)((char*)first_free + 8);
    *size_location = size;

}

VariableSizeAllocator::~VariableSizeAllocator() {
    if (memory_block != nullptr)
    {
        free(memory_block);
        memory_block = nullptr;
        first_free = nullptr;
    }
}


