//
//  list_node.h
//  cpplist
//
//  Created by MiZhemin on 11/14/14.
//
//

#ifndef cpplist_list_node_h
#define cpplist_list_node_h

class List_Node {
    int _value;
    List_Node *_nextNode;
public:
    // The empty constructor should create an empty list_node with no value and next.
    List_Node();
    
    List_Node( int value );
    
    // The deconstructor should clean up all memory allocated.
    ~List_Node();
    
    // Return the reference of the value in this node.
    int& getValue();
    
    // Return the value of this node.
    int getValue() const;
    
    // Set the next node.
    void setNext( List_Node *next );
    
    // Get the next node.
    List_Node *next();
    
    // print the node.
//    void print() const;
};

#endif
