#include "rb_tree.h"

void left_rotate(Tree * tree, Node * x) {

    assert(x->right != tree->nil);
    assert(tree->root->p == tree->nil);

    Node * y = x->right;
    x->right = y->left;
    
    if(y->left != tree->nil)
        y->left->p = x;
    y->p = x->p;
    if(x->p == tree->nil)
        tree->root = y;
    else if(x == x->p->left)
        x->p->left = y;
    else
        x->p->right = y;
    y->left = x;
    x->p = y;
}


void right_rotate(Tree * tree, Node * y) {

    assert(y->left != tree->nil);
    assert(tree->root->p == tree->nil);

    Node * x = y->left;
    y->left = x->right;
    
    if(x->right != tree->nil)
        x->right->p = y;
    x->p = y->p;
    if(y->p == tree->nil)
        tree->root = x;
    else if(y == y->p->left)
        y->p->left = x;
    else
        y->p->right = x;
    x->right = y;
    y->p = x;
}

void rb_insert(Tree * tree, Node * z){
    Node * y = tree->nil;
    Node * x = tree->root;
    while(x != tree->nil) {
        y = x;
        if(z->key < x->key)
            x = x->left;
        else
            x = x->right;
    }
    z->p = y;
    if(y == tree->nil)
        tree->root = z;
    else if(z->key < y->key)
        y->left = z;
    else
        y->right = z;
    z->left = tree->nil;
    z->right = tree->nil;
    z->color = RED;
    rb_insert_fixup(tree, z);
}
 
void create_graph(Tree *tree) {
    FILE *fp;
    fp = fopen("text.dot", "w+");
    fprintf(fp, "graph K4 {\n");
    get(tree->root, fp, tree);
    fprintf(fp, "}");
    fclose(fp);
}

void get(Node * node, FILE *fp, Tree * tree) {
    fprintf(fp, "%d -- %d;\n", node->p->key, node->key);
    if(node->left != tree->nil) {
        get(node->left, fp, tree);
    }
 
    if(node->right != tree->nil) {
        get(node->right, fp, tree);
    }
    fprintf(fp, "%d [style=filled, fillcolor=%s]\n", node->key, (node->color ? "red":"grey"));
}


void rb_insert_fixup(Tree * tree, Node * z) {
    while(z->p->color == RED) {
        if(z->p == z->p->p->left) {
            Node * y = z->p->p->right;
            if (y->color == RED) {
                z->p->color = BLACK;
                y->color = BLACK;
                z->p->p->color = RED;
                z = z->p->p;
            } else {
                if(z == z->p->right) {
                    z = z->p;
                    left_rotate(tree, z);
                } 
                z->p->color = BLACK;
                z->p->p->color = RED;
                right_rotate(tree, z->p->p);
                
            }
        } else {
            Node * y = z->p->p->left;
            if (y->color == RED) {
                z->p->color = BLACK;
                y->color = BLACK;
                z->p->p->color = RED;
                z = z->p->p;
            } else { 
                if(z == z->p->left) {
                    z = z->p;
                    right_rotate(tree, z);
                } 
                z->p->color = BLACK;
                z->p->p->color = RED;
                left_rotate(tree, z->p->p);
                
            }
        }
    }
    tree->root->color = BLACK;
}


void rb_transplant(Tree *tree, Node * u, Node * v) {
    if(u->p == tree->nil)
        tree->root = v;
    else if(u == u->p->left)
        u->p->left = v;
    else 
        u->p->right = v;
    v->p = u->p;
}

Node * rb_tree_minimum(Tree * tree, Node * x){
    while(x->left != tree->nil)
        x = x->left;
    return x;
}

void rb_delete_fixup(Tree * tree, Node * x) {
    while((x != tree->root) && (x->color == BLACK)) {
        if(x == x->p->left) {
            Node * w = x->p->right;
            if(w->color == RED) {
                w->color = BLACK;
                x->p->color = RED;
                left_rotate(tree, x->p);
                w = x->p->right;
            }
            if((w->left->color == BLACK) && (w->right->color == BLACK)) {
                w->color = RED;
                x = x->p;
            } else {
                if(w->right->color == BLACK) {
                    w->left->color = BLACK;
                    w->color = RED;
                    right_rotate(tree, w);
                    w = x->p->right;
                }
                w->color = x->p->color;
                x->p->color = BLACK;
                w->right->color = BLACK;
                left_rotate(tree, x->p);
                x = tree->root;
            }
        } else {
            Node * w = x->p->left;
            if(w->color == RED) {
                w->color = BLACK;
                x->p->color = RED;
                right_rotate(tree, x->p);
                w = x->p->left;
            }
            if((w->right->color == BLACK) && (w->left->color == BLACK)) {
                w->color = RED;
                x = x->p;
            } else {
                if(w->left->color == BLACK) {
                    w->right->color = BLACK;
                    w->color = RED;
                    left_rotate(tree, w);
                    w = x->p->left;
                }
                w->color = x->p->color;
                x->p->color = BLACK;
                w->left->color = BLACK;
                right_rotate(tree, x->p);
                x = tree->root;
            }
        }
    }
    x->color = BLACK;
}


void rb_delete(Tree *tree, Node * z) {
    Node * y = z;
    Node * x;
    bool orig_color = y->color;
    if(z->left == tree->nil) {
        x = z->right;
        rb_transplant(tree, z, z->right);
    } else if(z->right == tree->nil) {
        x = z->left;
        rb_transplant(tree, z, z->left);
    } else {
        y = rb_tree_minimum(tree, z->right);
        orig_color = y->color;
        x = y->right;
        if(y->p == z)
            x->p = y;
        else {
            rb_transplant(tree, y, y->right);
            y->right = z->right;
            y->right->p = y;
        }
        rb_transplant(tree, z, y);
        y->left = z->left;
        y->left->p = y;
        y->color = z->color;
    }
    if(orig_color == BLACK) 
        rb_delete_fixup(tree, x);
}


