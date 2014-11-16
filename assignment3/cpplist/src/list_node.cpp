//
//  list_node.cpp
//  cpplist
//
//  Created by MiZhemin on 11/14/14.
//
//

#include <stdio.h>
#include "list_node.h"

List_Node::List_Node(): _value{ 0 }, _nextNode{ NULL } {}

List_Node::List_Node( int value ): _value{ value }, _nextNode{ NULL } {}

List_Node::~List_Node() {}

int& List_Node::getValue() { return _value; }

int List_Node::getValue() const { return _value; }

void List_Node::setNext( List_Node *next ) { _nextNode = next; }

List_Node *List_Node::next() { return _nextNode; }
