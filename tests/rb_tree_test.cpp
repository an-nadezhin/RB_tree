#include "rb_tree.h"
#include "gtest/gtest.h"
#include "iostream"
void red_checking(Node * node, Tree * tree);
/*
void create_tree(Tree * tree) {
    Node node_nil, node2, node3, node4, node5, node6, node7, n1, n2, n3, n4;
    node5.key = 13;
    node6.key = 23;
    node7.key = 54;
    node4.key = 89;
    node2.key = 57;
    node3.key = 34;
    n1.key = 14;
    n2.key = 74;
    n3.key = 45;
    n4.key = 32;
    node_nil.color = false;
    node_nil.key = 0;
    tree->nil = &node_nil;
    tree->root = &node_nil;
    rb_insert(tree, &node2);
    rb_insert(tree, &node3);
    rb_insert(tree, &node4);
    rb_insert(tree, &node5);
    rb_insert(tree, &node6);
    rb_insert(tree, &node7);
    rb_insert(tree, &n1);
    rb_insert(tree, &n2);
    rb_insert(tree, &n3);
    rb_insert(tree, &n4);
    rb_delete(tree, &node4);
    rb_delete(tree, &n3);
    create_graph(tree);
 //   printf("%d", tree->root->color);
}
*/
int check_red(Tree * tree) {
    if(tree->root != tree->nil) {
        red_checking(tree->root, tree);
    }    
    return 1;
}

void red_checking(Node * node, Tree * tree) {
    if(node->color == RED) {
        EXPECT_EQ(node->left->color, BLACK);
        EXPECT_EQ(node->right->color, BLACK);
    }
    if(node->left != tree->nil)
        red_checking(node->left, tree);
    if(node->right != tree->nil)
        red_checking(node->right, tree);
}

TEST(RB_TREE_TEST, COMMON_TESTS) {
    Tree * tree = (Tree*)calloc(sizeof(Tree), 1);
    Node node_nil, node2, node3, node4, node5, node6, node7, n1, n2, n3, n4;
    node5.key = 13;
    node6.key = 23;
    node7.key = 54;
    node4.key = 89;
    node2.key = 57;
    node3.key = 34;
    n1.key = 14;
    n2.key = 74;
    n3.key = 45;
    n4.key = 32;
    node_nil.color = false;
    node_nil.key = 0;
    tree->nil = &node_nil;
    tree->root = &node_nil;
    rb_insert(tree, &node2);
    rb_insert(tree, &node3);
    rb_insert(tree, &node4);
    rb_insert(tree, &node5);
    rb_insert(tree, &node6);
    rb_insert(tree, &node7);
    rb_insert(tree, &n1);
    rb_insert(tree, &n2);
    rb_insert(tree, &n3);
    rb_insert(tree, &n4);
    rb_delete(tree, &node4);
    rb_delete(tree, &n3);
    create_graph(tree);
    
    EXPECT_FALSE(tree->nil->color);
    EXPECT_FALSE(tree->root->color);
    EXPECT_EQ(check_red(tree), 1);

}


