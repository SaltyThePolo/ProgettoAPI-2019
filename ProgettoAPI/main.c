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
    char name[15];
    int count;
};



 // inizio con la struttura dell'albero entità
struct node{
    struct uuser data;
    struct node *father;
    struct node *left;
    struct node *right;
};

struct node *createUsrNode(struct uuser data){
    struct node *temp =  (struct node *)malloc(sizeof(struct node));
    temp->data = data;
    temp->left = temp->right = NULL;
    return temp;
}

struct node* addUuserNode(struct node* node, struct uuser data){
    if (node == NULL){
        return createUsrNode(data);
    }
    if(strcmp(node -> data.name, data.name) < 0){      // se è maggiore fa la funzione ricorsiva sul figlio a sx
        node -> left  = addUuserNode(node -> left, data);
    }
    if(strcmp(node -> data.name, data.name) > 0){     // se è minore fa la funzione ricorsiva sul figlio a dx
        node -> right = addUuserNode(node -> right, data);
    }
    return node;
}

struct node* minUsrValueNode(struct node* node)
{
    struct node* current = node;
    
    /* loop down to find the leftmost leaf */
    while (current && current->left != NULL)
        current = current->left;
    
    return current;
}

struct node* deleteUuserNode(struct node* root, struct uuser data){
    
    if (root == NULL){
        return root;            // in questo caso non cancello nulla
    }
    if (strcmp(root -> data.name, data.name) < 0){
        root -> left = deleteUuserNode(root -> left, data);
    }else if (strcmp(root -> data.name, data.name) > 0){
        root -> right = deleteUuserNode(root ->right, data);
    }else{ // sono nel posto giusto
        // node with only one child or no child
        if (root->left == NULL)
        {
            struct node *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL)
        {
            struct node *temp = root->left;
            free(root);
            return temp;
        }
        // node with two children: Get the inorder successor (smallest
        // in the right subtree)
        struct node* temp = minUsrValueNode(root->right);
        
        // Copy the inorder successor's content to this node
        root->data = temp->data;
        
        // Delete the inorder successor
        root->right = deleteUuserNode(root->right, temp->data);
    }
    return root;
}

// parte degli alberi per le relazioni

struct relation {
    char name[15];
    char from[15];
    char to[15];
    struct relation *next;
};

struct nodeRel{
    struct relation relation;
    struct nodeRel *father;
    struct nodeRel *left;
    struct nodeRel *right;
};

struct nodeRel *createRelNode(struct relation relation){
    struct nodeRel *temp =  (struct nodeRel *)malloc(sizeof(struct nodeRel));
    temp->relation = relation;
    temp->left = temp->right = NULL;
    return temp;
}

void addEntityToRelation(struct nodeRel* nodo, struct relation dato){
    struct relation *temp = NULL;
    while ( nodo -> relation.next != 0){
        temp = nodo -> relation.next;
    }
    if (temp != NULL){
    temp -> next = &dato;
    }else{
        nodo -> relation.next = &dato;
    }
}

void rmvEntityWithRel(struct nodeRel* nodo, struct relation dato){
    struct relation *temp = &nodo -> relation;
    struct relation *pretemp = NULL;
    while (strcmp(temp -> name, dato.name) != 0 || strcmp(temp -> from, dato.from) != 0 || strcmp(temp -> to, dato.to) != 0){
        pretemp = temp;
        temp = temp -> next;
    }
    if (pretemp == NULL){
        struct relation delete = nodo -> relation;
        nodo -> relation = *nodo -> relation.next;
        free (&delete);
    }
    if (temp != 0 && pretemp != NULL){
        pretemp -> next = temp -> next;
        free(temp);
    }
}

void rmvEntityWithName(struct nodeRel *nodo, char nome[15]){
        if (nodo != NULL)
        {
            rmvEntityWithName(nodo -> left, nome);
            struct relation *temp = &nodo -> relation;
            struct relation *pretemp = NULL;
            while (strcmp(temp -> from, nome) != 0 || strcmp(temp -> to, nome) != 0){
                if(temp == NULL){
                    break;
                }
                pretemp = temp;
                temp = temp -> next;
            }
            if (pretemp == NULL){
                struct relation delete = nodo -> relation;
                nodo -> relation = *nodo -> relation.next;
                free (&delete);
            }
            if (temp != NULL && pretemp != NULL){
                pretemp -> next = temp -> next;
                free(temp);
            }
            rmvEntityWithName(nodo ->right, nome);
        }
}

struct nodeRel* addRelNode(struct nodeRel* nodo, struct relation dato){
    if (nodo == NULL){
        return createRelNode(dato);
    }
    if(strcmp(nodo -> relation.name, dato.name) < 0){      // se è maggiore fa la funzione ricorsiva sul figlio a sx
        nodo -> left  = addRelNode(nodo -> left, dato);
    }
    if(strcmp(nodo -> relation.name, dato.name) > 0){     // se è minore fa la funzione ricorsiva sul figlio a dx
        nodo -> right = addRelNode(nodo -> right, dato);
    }
    if(strcmp(nodo -> relation.name, dato.name) == 0){
        addEntityToRelation(nodo, dato);
    }
    return nodo;
}

struct nodeRel* minRelValueNode(struct nodeRel* node)
{
    struct nodeRel* current = node;
    
    /* loop down to find the leftmost leaf */
    while (current && current->left != NULL)
        current = current->left;
    
    return current;
}


struct nodeRel* deleteRelNode(struct nodeRel* root, struct relation dato){
    
    if (root == NULL){
        return root;            // in questo caso non cancello nulla
    }
    if (strcmp(root -> relation.name, dato.name) < 0){
        root -> left = deleteRelNode(root -> left, dato);
    }else if (strcmp(root -> relation.name, dato.name) > 0){
        root -> right = deleteRelNode(root ->right, dato);
    }else{ // sono nel posto giusto
        
        // node with only one child or no child
        if (root->left == NULL)
        {
            struct nodeRel *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL)
        {
            struct nodeRel *temp = root->left;
            free(root);
            return temp;
        }
        // node with two children: Get the inorder successor (smallest
        // in the right subtree)
        struct nodeRel* temp = minRelValueNode(root->right);
        // Copy the inorder successor's content to this node
        root->relation = temp->relation;
        // Delete the inorder successor
        root->right = deleteRelNode(root->right, temp->relation);
    }
    return root;
}

void inorder(struct node *root)
{
    if (root != NULL)
    {
        inorder(root->left);
        printf("%s ", root->data.name);
        inorder(root->right);
    }
}


int main(int argc, const char * argv[]) {
    char a[15], b[15], c[15];
    struct node *root = NULL;
    do {
        printf("inserisci input: ");
        for (int i = 0; i < 15; i++){
            char temp = getchar_unlocked();
            if (a[i] == ' ' || a[i] == EOF || i > 14) break;
            a[i] = temp;
        }
        printf("inserisci input: ");
        for (int i = 0; i < 15; i++){
            char temp = getchar_unlocked();
            if (a[i] == ' ' || a[i] == EOF || i > 14) break;
            a[i] = temp;
        }
        printf("inserisci input: ");
        for (int i = 0; i < 15; i++){
            char temp = getchar_unlocked();
            if (a[i] == ' ' || a[i] == EOF || i > 14) break;
            a[i] = temp;
        }

        if (strcmp(a, "addent") == 0) {
            struct uuser temp;
            strcpy(temp.name, b);
            root = addUuserNode(root, temp);
            printf("aggiunto %s all'albero \n", b);
        }else if(strcmp(a, "delent") == 0){
            
        }else if(strcmp(a, "addrel") == 0){
            
        }else if(strcmp(a, "delrel") == 0){
            
        }else if(strcmp(a, "report") == 0){
            inorder(root);
        }
        
    } while ((strcmp(a, "end") != 0));
    printf("Hello, World!\n");
    
    return 0;
}
