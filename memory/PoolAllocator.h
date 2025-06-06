//
// Created by juana on 1/6/2025.
//

#ifndef MEMORYALLOCATOR_POOLALLOCATOR_H
#define MEMORYALLOCATOR_POOLALLOCATOR_H


class PoolAllocator {

    private:
        void* memory_block = nullptr;
        void* first_free = nullptr;

    public:
        PoolAllocator(); //constructor
        ~PoolAllocator(); //destructor
        void* allocate(); //devuelve el puntero que se otorgo al user
        void deallocate(void* ptr); //recibe el puntero que debe liberar
};
#endif //MEMORYALLOCATOR_POOLALLOCATOR_H
