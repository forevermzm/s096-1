#include "list.h"
#include <stdio.h>

int sq( int x ) {
    return x * x;
}

int add1( int x ) {
    return x + 1;
}

int plus( int x, int y ) {
    return x + y;
}

int main(void) {
    int N = 5;
    List list = empty_list();
    
    // Test for list_append()
    
    for( int i = 0; i < N; ++i ) {
        list_append( &list, i );
    }
    
    list_print( list );
    int array1[] = {0, 1, 2, 3, 4};
    list_equals( &list, array1 );
    
    // Test for list_insert_before()
    
    list_insert_before( &list, -1, 0 );
    list_insert_before( &list, 2, 2 );
    list_insert_before( &list, 4, 4);
    int array2[] = { -1, 0, 1, 2, 2, 3, 4, 4 };
    list_print ( list );
    list_equals( &list, array2 );
    
    // Test for list_delete()
    list_delete ( &list, -1 );
    list_delete ( &list, 2 );
    list_delete ( &list, 4 );
    int array3[] = { 0, 1, 3 };
    list_print ( list );
    list_equals ( &list, array3 );
    
    // Test for list_apply()
    list_apply ( &list, add1 );
    list_apply ( &list, sq );
    int array4[] = { 1, 4, 16 };
    list_print ( list );
    list_equals ( &list, array4);
    
    // Test for list_reduce()
    int result = list_reduce ( &list, plus );
    printf("Result is %d, it passed the test: %d\n", result, result == 21 );
    
    list_clear( &list );
    return 0;
}
