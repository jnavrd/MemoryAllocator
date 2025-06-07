#include <iostream>
#include "memory/PoolAllocator.h"

using namespace std;

int main() {

    PoolAllocator block = PoolAllocator();

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
