#include "vector.h"
#include "print_array.h"

int main()
{
    struct Vector vector = create_vector(); // Tested
    push_back(&vector, 7); // Tested
    push_back(&vector, 8); // Tested
    insert(&vector, 1, 5); // Tested
    erase(&vector, 2); // Tested
    // delete_vector(&vector); // Tested

    print_array(vector.array, vector.size);
    return 0;
}