#include "list.h"

#include <stdio.h>
#include <stdlib.h>

struct List_node_s {
  List_node *next;
  int value;
};

List empty_list( void ) {
  return (List) { .length = 0, .front = NULL };
}

// Allocate memory for a single List_node
List_node* create_node( int value ) {
  List_node *new_node = malloc( sizeof( List_node ) );
  new_node->value = value;
  new_node->next = NULL;
  return new_node;
}

// Implement this
void list_append( List *list, int value ) {
  /* Function to append a new node containing 'value'
   * to the end of List *list. For example,
   * applied to { 5 -> 10 } as
   * list_append( list, 9 ); results in
   * { 5 -> 10 -> 9 }
   */
    List_node *node = create_node(value);
    if ( list -> length == 0 ) {
        list -> front = node;
        list -> length += 1;
    } else {
        List_node *current_node = list -> front;
        while ( current_node -> next != NULL ) {
            current_node = current_node -> next;
        }
        current_node -> next = node;
        list -> length += 1;
    }
}

// Implement this
void list_insert_before( List *list, int insert, int before ) {
  /* This function should take a pointer to a List *list,
   * a value to insert 'insert', and a value to insert before 'before'.
   * A new node should be inserted directly before the first
   * occurrence of "before" in the current list, like so:
   *
   * Starting with { 0 -> 5 -> 4 -> 5 }, call list_insert_before( list, -1, 5 ):
   * results in { 0 -> -1 -> 5 -> 4 -> 5 }
   *
   * NOTE: if the value 'before' does not exist in 'list', this
   * function should not modify the list or append anywhere.
   */
    if (list->length != 0) {
        List_node *current_node = list->front;
        List_node *node = create_node( insert );
        if ( current_node -> value == before ) {
            node -> next = current_node;
            list -> front = node;
            list -> length += 1;
        } else {
            while (1) {
                if ( current_node -> next == NULL ) {
                    break;
                } else if ( current_node -> next -> value == before ) {
                    node -> next = current_node -> next;
                    current_node -> next = node;
                    list -> length += 1;
                    break;
                } else {
                    current_node = current_node -> next;
                }
            }
        }
    }
}

// Implement this
void list_delete( List *list, int value ) {
  /* Delete all occurrences of the value 'value' in list.
   * For example, starting with { 0 -> 5 -> 4 -> 5 }
   * call list_delete( list, 5 ):
   * results in { 0 -> 4 }
   * If there are no values to delete, the function should
   * do nothing.
   */
    if ( list -> length != 0) {
        List_node *current_node = list -> front;
        if ( current_node -> value == value ) {
            list -> front = current_node -> next;
            list -> length -= 1;
        } else {
            while (1) {
                if ( current_node -> next == NULL) {
                    break;
                } else if ( current_node -> next -> value == value ) {
                    current_node -> next = current_node -> next -> next;
                    list -> length -= 1;
                } else {
                    current_node = current_node -> next;
                }
            }
        }
    }
}

// Implement this
void list_apply( List *list, int (*function_ptr)(int) ) {
  /* Applies the function pointed to by function_ptr
   * to every value at nodes in list 'list'.
   * For example, starting with { 1 -> 2 -> 3 } and
   * a function 
   *
   *     int sq(int x) { return x * x; }
   * 
   * call to list_apply( list, sq );
   * results in { 1 -> 4 -> 9 }
   */
    if ( list -> length != 0 ) {
        List_node *current_node = list -> front;
        while (1) {
            int value = function_ptr( current_node -> value );
            current_node -> value = value;
            if ( current_node -> next == NULL ){
                break;
            } else {
                current_node = current_node -> next;
            }
        }
    }
}

int list_reduce( List *list, int (*function_ptr)(int, int) ) {
  /* Takes an associative function pointed to by function_ptr
   * and returns the result of reducing the list with it.
   * For example, starting with { 1 -> 2 -> 3 } and
   * a function
   *
   *    int plus( int x, int y ) { return x + y; }
   * 
   * list_reduce( list, plus );
   * will return 1 + 2 + 3 = 6.
   * If the provided list contains 0 elements,
   * you should return 0; if the list has only one
   * element, return the value of that element.
   */
    if ( list -> length == 0 ) {
        return 0;
    } else {
        List_node *current_node = list -> front;
        int result = 0;
        while (1) {
            result = function_ptr( result, current_node -> value );
            current_node = current_node -> next;
            if ( current_node == NULL ) {
                return result;
            }
        }
    }
}

// Print out a linked list in human-readable form
void list_print( List list ) {
  if( list.front == NULL ) {
    printf( "{}\n" );
  } else {
    printf( "{ " );

    List_node *p = list.front;
    size_t length = list.length;

    while( p->next != NULL && length > 0 ) {
      printf( "%d -> ", p->value );
      p = p->next; --length;
    }
    printf( "%d }\n", p->value );

    if( length != 1 ) {
      printf( "Error: badly formed list.\n" );
      exit( EXIT_FAILURE );
    }
  }
}

// Frees the memory in List *list
void list_clear( List *list ) {
  List_node *front = list->front;
  size_t length = list->length;

  while( front != NULL && length > 0 ) {
    List_node *next = front->next;
    free( front );
    front = next;
    --length;
  }

  if( length != 0 ) {
    printf( "Error: failed to clean up list properly.\n" );
    exit( EXIT_FAILURE );
  }
}

void list_equals ( List *list, int *array ){
    if ( list -> length == 0 ) {
        printf("List is empty.\n");
    }
    List_node *current_node = list -> front;
    for ( size_t i = 0 ; i < list -> length ; i ++ ) {
        if ( current_node -> value != array[i] ) {
            printf("List element [%zu] is %d, array[%zu] is %d\n", i, current_node -> value, i, array[i]);
            return;
        } else {
            current_node = current_node -> next;
        }
    }
    printf("List is equal.\n");
}
