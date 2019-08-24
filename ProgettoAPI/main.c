//  main.c
//  ProgettoAPI
//
//  Created by Mattia Riviera on 17/08/2019.
//  Copyright © 2019 Mattia Riviera. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node *usrRoot = NULL;
struct nodeRel *relRoot = NULL;

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
    if(strcmp(node -> data.name, data.name) > 0){      // se è maggiore fa la funzione ricorsiva sul figlio a sx
        node -> left  = addUuserNode(node -> left, data);
    }
    if(strcmp(node -> data.name, data.name) < 0){     // se è minore fa la funzione ricorsiva sul figlio a dx
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

struct node* rmvusrNode(struct node* root, struct uuser data){
    
    if (root == NULL){
        return root;            // in questo caso non cancello nulla
    }
    if (strcmp(root -> data.name, data.name) > 0){
        root -> left = rmvusrNode(root -> left, data);
    }else if (strcmp(root -> data.name, data.name) < 0){
        root -> right = rmvusrNode(root ->right, data);
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
        root->right = rmvusrNode(root->right, temp->data);
    }
    return root;
}


void usrInOrder(struct node *root)
{
    if (root != NULL)
    {
        usrInOrder(root->left);
        printf("%s ", root->data.name);
        usrInOrder(root->right);
    }
}
struct node* searchUser (struct node *root, char name[15]){
    if (root == NULL|| strcmp(root ->data.name, name) == 0) return root;
    if (strcmp(root -> data.name, name) > 0) return searchUser(root -> left, name);
        return searchUser(root ->right, name);
}
// -----------------------------------------------------------------------------------------------------------------------------------------

struct relation {
    char name[15];
    char from[15];
    char to[15];
    struct relation *next;
};

struct nodeRel{
    struct relation *relation;
    struct nodeRel *father;
    struct nodeRel *left;
    struct nodeRel *right;
};

struct nodeRel *createRelNode(struct relation *relation){
    struct nodeRel *temp = malloc(sizeof(struct nodeRel));
    temp -> relation = relation;
    temp -> left = temp -> right = NULL;
    temp -> relation -> next = NULL;
    return temp;
}

// TODO da rivedere
void addEntityToRel(struct nodeRel* nodo, struct relation *dato){
    struct relation *temp = (nodo->relation);
    struct relation *pre =NULL;
    while ( temp!=NULL){
        pre = temp;
        temp = temp->next;
    }
    if(pre!=NULL){
        pre -> next = dato;
        pre -> next -> next = NULL;
        
    }
    
}

struct nodeRel* addRelNode(struct nodeRel* nodo, struct relation *dato){
    if (nodo == NULL){
        return createRelNode(dato);
    }
    if(strcmp(nodo -> relation -> name, dato -> name) > 0){      // se è maggiore fa la funzione ricorsiva sul figlio a sx
        nodo -> left  = addRelNode(nodo -> left, dato);
    }
    if(strcmp(nodo -> relation ->name, dato -> name) < 0){     // se è minore fa la funzione ricorsiva sul figlio a dx
        nodo -> right = addRelNode(nodo -> right, dato);
    }
    if(strcmp(nodo -> relation -> name, dato -> name) == 0){
        addEntityToRel(nodo, dato);
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


struct nodeRel* rmvRelNode(struct nodeRel* root, struct relation *dato){
    
    if (root == NULL) return root;            // in questo caso non cancello nulla
    if (strcmp(root -> relation -> name, dato -> name) > 0){
        root -> left = rmvRelNode(root -> left, dato);
    }else if (strcmp(root -> relation -> name, dato -> name) < 0){
        root -> right = rmvRelNode(root ->right, dato);
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
        root->right = rmvRelNode(root->right, temp->relation);
    }
    return root;
}
struct nodeRel* searchRel (struct nodeRel *root, struct relation rel){
    if (root == NULL || strcmp(root ->relation -> name, rel.name) == 0) return root;
    if (strcmp(root -> relation -> name, rel.name) > 0) return searchRel(root -> left, rel);
    return searchRel(root ->right, rel);
}

void relInOrder(struct nodeRel *root)
{
    if (root != NULL)
    {
        relInOrder(root->left);
        printf("%s ", root->relation -> name);
        printf("%s ", root->relation -> from);
        printf("%s | ", root->relation -> to);
        struct relation *temp = root -> relation -> next;
        while (temp != NULL){
            printf("%s ", temp -> name);
            printf("%s ", temp -> from);
            printf("%s | ", temp -> to);
            temp = temp -> next;
        }
        relInOrder(root->right);
    }
}

void rmvEntityWithName(struct nodeRel *nodo, char nome[15]){
    if (nodo != NULL ) //potrei evitare di farlo andare avanti e tornare indietro?
    {
        if(nodo -> left != NULL) rmvEntityWithName(nodo -> left, nome); // forse if
        while(1){
                    // Store head node
            struct relation* temp = nodo -> relation;
            struct relation* prec = nodo -> relation;
            // If head node itself holds the key to be deleted
            if (temp != NULL && (strcmp(temp -> from, nome) == 0 || strcmp(temp -> to, nome) == 0))
            {
                if(temp -> next == NULL){    //unico nodo e da eliminare
                    relRoot = rmvRelNode(relRoot, temp);
                    break;
                }else{
                    nodo -> relation = temp->next;   // Changed head
                    free(temp);               // free old head
                }
            }else{
                // Search for the key to be deleted, keep track of the
                // previous node as we need to change 'prev->next'
                while (temp != NULL && (strcmp(temp -> from, nome)  != 0 && strcmp(temp -> to, nome) != 0))
                {
                    prec = temp;
                    temp = temp->next;
                }
                
                // If key was not present in linked list
                if (temp == NULL) break;
                
                // Unlink the node from linked list
                prec->next = temp->next;
                
                free(temp);  // Free memory
            }
        }
        if ( nodo -> right != NULL ) rmvEntityWithName(nodo -> right, nome);
    }
}

void delRel(struct nodeRel *nodo, struct relation relazione)
{
    // Store head node
    struct relation* temp = nodo -> relation;
    struct relation* prec = nodo -> relation;
    
    // If head node itself holds the key to be deleted
    if (temp != NULL && strcmp(temp -> from, relazione.from) == 0&& strcmp(temp -> to, relazione.to) == 0)
    {
        if(temp -> next == NULL){    //unico nodo e da eliminare
            relRoot = rmvRelNode(relRoot, nodo -> relation);
            return;
        }else{
            nodo -> relation = temp->next;   // Changed head
            free(temp);               // free old head
            return;
        }
    }
    // Search for the key to be deleted, keep track of the
    // previous node as we need to change 'prev->next'
    while (temp != NULL && (strcmp(temp -> from, relazione.from)  != 0 || strcmp(temp -> to, relazione.to) != 0))
    {
        prec = temp;
        temp = temp->next;
    }
    
    // If key was not present in linked list
    if (temp == NULL) return;
    
    // Unlink the node from linked list
    prec->next = temp->next;
    
    free(temp);  // Free memory
}

//-------------------------------------------------------------------------------------------------//

int main(int argc, const char * argv[]) {
    char a[15], b[15], c[15], d[15];
    short j = 0;
    do {
        for (short i = 0; i < 15; i ++) a[i] = '\0';
        for (short i = 0; i < 15; i ++) b[i] = '\0';
        for (short i = 0; i < 15; i ++) c[i] = '\0';
        for (short i = 0; i < 15; i ++) d[i] = '\0';
        printf("pronto: ");
        for (short i = 0; i < 15; i++){
            char temp = getchar_unlocked();
            if (temp == '\n'){
                j = 1;
                break;
            }
            if (temp == ' ' || temp == EOF ) break;
            a[i] = temp;
        }
        
        if ( j == 0){
            for (short i = 0; i < 15; i++){
                char temp = getchar_unlocked();
                if (temp == ' ' || temp == EOF) break;
                if (temp == '\n') {
                    j = 1;
                    break;
                }
                b[i] = temp;
            }
        }
        
        if ( j == 0){
            for (short i = 0; i < 15; i++){
                char temp = getchar_unlocked();
                if (temp == ' ' || temp == EOF) break;
                if (temp == '\n') {
                    j = 1;
                    break;
                }
                c[i] = temp;
            }
        }
        
        if( j == 0){
            for (short i = 0; i < 15; i++){
                char temp = getchar_unlocked();
                if (temp == EOF || temp == '\n') break;
                d[i] = temp;
            }
        }
        j = 0;

        if (strcmp(a, "addent") == 0) {
            struct uuser temp;
            strcpy(temp.name, b);
            usrRoot = addUuserNode(usrRoot, temp);
            printf("aggiunto %s all'albero \n", b);
        }else if(strcmp(a, "delent") == 0){
            struct uuser temp;
            strcpy(temp.name, b);
            usrRoot = rmvusrNode(usrRoot, temp);
            rmvEntityWithName(relRoot, b);
        }else if(strcmp(a, "addrel") == 0){
            if (searchUser(usrRoot, c) != NULL && searchUser(usrRoot, d) != NULL){
                struct relation *temp = malloc(sizeof(struct relation*));
                strcpy(temp -> name, b);
                strcpy(temp -> from, c);
                strcpy(temp -> to, d);
                relRoot = addRelNode(relRoot, temp);
            }else printf("404: entity not found\n");
        }else if(strcmp(a, "delrel") == 0){
            struct relation temp;
            strcpy(temp.name, b);
            strcpy(temp.from, c);
            strcpy(temp.to, d);
            delRel(searchRel(relRoot, temp), temp);
        }else if(strcmp(a, "report") == 0){
            
        }
        
    } while ((strcmp(a, "end") != 0));
    printf("Hello, World!\n");
    return 0;
}
