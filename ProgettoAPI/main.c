//
//  main.c
//  ProgettoAPI
//
//  Created by Mattia Riviera on 17/08/2019.
//  Copyright © 2019 Mattia Riviera. All rights reserved.
//


#include <stdio.h>
#include <stdlib.h>

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
    int key;
    struct node *father;
    struct node *left;
    struct node *right;
};

// A utility function to create a new BST node
struct node *newNode(int item){
    struct node *temp =  (struct node *)malloc(sizeof(struct node));
    temp->key = item;
    temp->left = temp->right = NULL;
    return temp;
}


int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    return 0;
}
