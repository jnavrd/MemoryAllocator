//
// Created by juana on 1/6/2025.
//

#include <cstdlib>
#include <cstdio>

#include "PoolAllocator.h"

void PoolAllocator::deallocate(void *ptr) {

    void** freed_slot_pointer = (void**)ptr;
    *freed_slot_pointer = first_free;
    first_free = ptr;

}

void *PoolAllocator::allocate() {

    if(first_free == nullptr) {
            std::printf("No hay slots disponibles");
            return nullptr;
    }
    void* assigned_slot = first_free;

    void** current_slot_pointer = (void**)first_free; //puntero al puntero del primer slot disponible
    first_free = *current_slot_pointer; //el primer slot disponible, es a donde apunta current_slot_pointer

    return assigned_slot;
}

PoolAllocator::PoolAllocator() {

    memory_block = malloc(1024);

    //crear la lista enlazada. asignar cada slot y su puntero al siguiente slot libre
    for(int i = 0; i < 15; i++) { //van a ser 16 slots de 64 bytes
        char* current_slot = (char*)memory_block + (i * 64); //se castea a char, char = 1 byte
        char* next_slot = (char*)memory_block + ((i + 1) * 64);

        //linkear lista
        void** slot_pointer = (void**)current_slot; //puntero a puntero. puntero = 8 bytes
        *slot_pointer = next_slot;
    }

    //el puntero al siguiente del ultmio slot apunta a nullptr
    char* last_slot = (char*)memory_block + (15 * 64); //el ultimo slot del bloque de memoria
    void** last_slot_pointer = (void**)last_slot;
    *last_slot_pointer = nullptr;

    first_free = memory_block; //el primero libre es donde comienza el bloque de memoria

}

PoolAllocator::~PoolAllocator() {

}


