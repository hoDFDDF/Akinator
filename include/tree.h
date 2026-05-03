#ifndef _TREE_H_
#define _TREE_H_

#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <stdio.h>

#include "TreeError_t.h"

#define max(a, b) ((a) > (b) ? (a) : (b))

typedef const char* tree_data_type; 

union expr_tree_type{
    char* operat;
    char* varible;
    int numb;
};

struct Node_t{
    Node_t* left_child;
    Node_t* right_child;
    Node_t* parent;
    expr_tree_type tree_data;
};

struct ExpressionTree{
    Node_t* root;
    size_t size;
};

struct LoadNodeProgress{
    Node_t* node;
    size_t rank;
};

enum Child {
    LEFT_CHILD,
    RIGHT_CHILD
};


struct Node_Info{ 
    LoadNodeProgress* nodes_array;
    size_t capacity; 
    size_t size;

};

void TreeCtor(Tree_t* tree);
Node_t* NodeCtor(tree_data_type data);
TreeError_t TreeInsert(Tree_t* tree, Node_t* node, tree_data_type data, Child child);
TreeError_t TreeDelete(Tree_t* tree, Node_t* node);

size_t MaxDepthOfBInaryTree(Node_t* node);

#endif //_TREE_H_