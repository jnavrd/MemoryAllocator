#include <iostream>
#include "memory/PoolAllocator.h"

using namespace std;

int main() {

    PoolAllocator block = PoolAllocator();

    void* ptr = block.allocate();
    void* ptr2 = block.allocate();

    cout << ptr << endl;
    cout << ptr2 << endl;

    block.deallocate(ptr);
    block.deallocate(ptr2);

    //git prueba

    block.~PoolAllocator();

    return 0;
}
