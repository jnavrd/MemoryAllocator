//
// Created by juana on 7/6/2025.
//

#ifndef MEMORYALLOCATOR_VARIABLESIZEALLOCATOR_H
#define MEMORYALLOCATOR_VARIABLESIZEALLOCATOR_H
#include "cstddef"

class VariableSizeAllocator {
    private:
        void* memory_block = nullptr;
        void* first_free = nullptr;
    public:
        VariableSizeAllocator(size_t size); //constructor
        ~VariableSizeAllocator(); //destructor
        void* allocate(size_t size); //devuelve el puntero que se otorgo al user
        void deallocate(void* ptr); //recibe el puntero que debe liberar
};


#endif //MEMORYALLOCATOR_VARIABLESIZEALLOCATOR_H
