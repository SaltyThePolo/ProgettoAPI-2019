//  main.c
//  ProgettoAPI
//
//  Created by Mattia Riviera on 17/08/2019.
//  Copyright © 2019 Mattia Riviera. All rights reserved.
//


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct uuser {
    char name[20];
    char rel[15];
    int count;
};

struct relation {
    char name[15];
    int from;
    int to;
};


 // inizio con la struttura dell'albero

struct node{
    struct uuser data;
    struct node *father;
    struct node *left;
    struct node *right;
};

struct node *newNode(struct uuser data){
    struct node *temp =  (struct node *)malloc(sizeof(struct node));
    temp->data = data;
    temp->left = temp->right = NULL;
    return temp;
}

/* A utility function to insert a new node with given key in BST */
struct node* insert(struct node* node, struct uuser data)
{
    /* If the tree is empty, return a new node */
    if (node == NULL) return newNode(data);
    
    /* Otherwise, recur down the tree */
    if (strcmp (data.name, node->data.name) > 0)
        node->left  = insert(node->left, data);
    else if (strcmp (data.name, node->data.name) > 0)
        node->right = insert(node->right, data );
    
    /* return the (unchanged) node pointer */
    return node;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
        printf("Hello, World!\n");
    return 0;
}
