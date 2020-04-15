#include <assert.h>
#include <stdio.h>


const bool RED = true;
const bool BLACK = false; 




// dot -Tps text.dot -o outfile.pdf

typedef struct  Node{
    bool color;
    int key;
    Node *left;
    Node *right;
    Node *p;     
}Node;


typedef struct Tree {
    Node * nil;
    Node * root;
}Tree;

void get(Node * node, FILE *fp, Tree * tree);
void rb_insert_fixup(Tree * tree, Node * z);
void left_rotate(Tree * tree, Node * x);
void right_rotate(Tree * tree, Node * y);
void rb_insert(Tree * tree, Node * z);
void create_graph(Tree *tree);
void rb_transplant(Tree *tree, Node * u, Node * v);
Node * rb_tree_minimum(Tree * tree, Node * x);
void rb_delete_fixup(Tree * tree, Node * x);
void rb_delete(Tree *tree, Node * z);

