//
//  list_iterator.cpp
//  cpplist
//
//  Created by MiZhemin on 11/16/14.
//
//

#include "list.h"
#include "list_node.h"

List::iterator::iterator( List_Node *theNode ) : _node{theNode} {}
List::iterator& List::iterator::operator++() {
    _node = _node -> next();
    return *this;
}
int& List::iterator::operator*() { return _node-> getValue(); }
bool List::iterator::operator==( const iterator &rhs ) { return _node == rhs._node; }
bool List::iterator::operator!=( const iterator &rhs ) { return _node != rhs._node; }

List::const_iterator::const_iterator( List_Node *theNode ) : _node{theNode} {}
List::const_iterator& List::const_iterator::operator++() {
    _node = _node->next();
    return *this;
}
const int& List::const_iterator::operator*() { return _node -> getValue(); }
bool List::const_iterator::operator==( const const_iterator &rhs ) { return _node == rhs._node; }
bool List::const_iterator::operator!=( const const_iterator &rhs ) { return _node != rhs._node; }