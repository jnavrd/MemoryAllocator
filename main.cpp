#include <iostream>
#include "memory/PoolAllocator.h"
#include "memory/VariableSizeAllocator.h"

using namespace std;

int main() {

    PoolAllocator block = PoolAllocator();
    VariableSizeAllocator allocator(1024);  // Pool más pequeño para testing

    printf("Test 1: Allocations basicas \n");
    void* ptr1 = allocator.allocate(32);
    void* ptr2 = allocator.allocate(32);
    void* ptr3 = allocator.allocate(128);

    printf("ptr1: %p, ptr2: %p, ptr3: %p\n", ptr1, ptr2, ptr3);

    printf("\n=== Test 2: Deallocate y reuso ===\n");
    printf("ptr2 antes de deallocate: %p\n", ptr2);
    allocator.deallocate(ptr2);

// Agregar este debug en allocate() para ver qué encuentra:
    void* ptr4 = allocator.allocate(32);
    printf("ptr4 despues de allocate: %p\n", ptr4);
    printf("Son iguales? %s\n", (ptr4 == ptr2) ? "SI" : "NO");

    printf("Test 3: Coalescing test \n");
    allocator.deallocate(ptr1);  // Ahora ptr1 y ptr2 deberían ser adyacentes
    void* ptr5 = allocator.allocate(100); // Debería usar el bloque fusionado
    printf("ptr5 (coalesced): %p\n", ptr5);

    printf("Test 4: Overflow test \n");
    void* big_ptr = allocator.allocate(2000);  // Más grande que 1024
    printf("big_ptr: %p\n", big_ptr);  // Debería ser nullptr

    //prueba de reutilizacion de memoria
   /* void* ptr = block.allocate();
    void* ptr2 = block.allocate();

    cout << "Dir puntero 1: " << ptr << "\n" << "Dir puntero 2: " << ptr2 << endl;

    block.deallocate(ptr);
    block.deallocate(ptr2);

    void* ptr3 = block.allocate();

    cout << "Dir puntero 3: " << ptr3 << endl;

    void* ptr4 = block.allocate();

    cout << "Dir puntero 3: " << ptr4 << endl;


    if(ptr4 == ptr)
        cout << "se reutilizo la dir de memoria" << endl;
    else
        cout << "No se reutilizo" << endl;*/

   //prueba de agotamiento de memoria

   /*for(int i = 0; i < 17; i++)
    {
        void* newPtr = block.allocate();
        cout << newPtr << endl;
    }*/

    return 0;
}
