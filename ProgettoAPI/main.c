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

struct nodeRel{
    char nameRel[15];
    struct nodeReceiver *nodeReceiver;
    struct nodeMax *nodeMax;
    struct nodeRel *father;
    struct nodeRel *left;
    struct nodeRel *right;
};

struct nodeReceiver {
    char nameRec[15];
    struct nodeSender *nodeSender;
    struct nodeReceiver *father;
    struct nodeReceiver *left;
    struct nodeReceiver *right;
};

struct nodeSender{
    char nameSen[15];
    struct nodeSender *father;
    struct nodeSender *left;
    struct nodeSender *right;
};

struct nodeMax{
    char name[15];
    int qty;
    struct nodeMax *father;
    struct nodeMax *left;
    struct nodeMax *right;
};

struct relation{
    char name[15];
    char from[15];
    char to[15];
};

//--------------------------------------------------------------------------------------------------------------
//                                      PROTOTIPI
struct nodeRel* addRelNode(struct nodeRel* nodo, struct relation *dato);
struct nodeReceiver* addRecNode(struct nodeReceiver *nodo, struct relation *dato);
struct nodeSender* addSenNode(struct nodeSender *nodo, struct relation *dato);
struct nodeMax* addMaxNode(struct nodeMax *nodo, struct relation *dato);

struct nodeRel *createRelNode(struct relation *relation);
struct nodeReceiver *createRecNode(struct relation *relation);
struct nodeSender *createSenNode(struct relation *relation);
struct nodeMax *createMaxNode(struct relation *relation);


struct nodeRel* minRelValueNode(struct nodeRel* node)
{
    struct nodeRel* current = node;
    
    /* loop down to find the leftmost leaf */
    while (current && current->left != NULL)
        current = current->left;
    
    return current;
}


/*struct nodeRel* rmvRelNode(struct nodeRel* root, struct relation *dato){
    
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
 */

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
        }else if(strcmp(a, "addrel") == 0){
            if (searchUser(usrRoot, c) != NULL && searchUser(usrRoot, d) != NULL){
                struct relation *temp = malloc(sizeof(struct relation));
                strcpy(temp -> name, d);
                strcpy(temp -> from, b);
                strcpy(temp -> to, c);
                relRoot = addRelNode(relRoot, temp);
                free(temp);
            }
        }else if(strcmp(a, "delrel") == 0){

        }else if(strcmp(a, "report") == 0){
            
        }
        
    } while ((strcmp(a, "end") != 0));
    return 0;
}

    
//---------------------------------------------------------------------------------

struct nodeRel* addRelNode(struct nodeRel* nodo, struct relation *dato){
    if (nodo == NULL){
        return createRelNode(dato);
    }
    if(strcmp(nodo -> nameRel, dato -> name) > 0){      // se è maggiore fa la funzione ricorsiva sul figlio a sx
        nodo -> left  = addRelNode(nodo -> left, dato);
    }
    if(strcmp(nodo -> nameRel, dato -> name) < 0){     // se è minore fa la funzione ricorsiva sul figlio a dx
        nodo -> right = addRelNode(nodo -> right, dato);
    }
    if(strcmp(nodo -> nameRel, dato -> name) == 0){
        addRecNode(nodo -> nodeReceiver, dato);
    }
    return nodo;
}

struct nodeReceiver* addRecNode(struct nodeReceiver *nodo, struct relation *dato){
    if (nodo == NULL){
        return createRecNode(dato);
    }
    if(strcmp(nodo -> nameRec, dato -> to) > 0){      // se è maggiore fa la funzione ricorsiva sul figlio a sx
        nodo -> left  = addRecNode(nodo -> left, dato);
    }
    if(strcmp(nodo -> nameRec, dato -> to) < 0){     // se è minore fa la funzione ricorsiva sul figlio a dx
        nodo -> right = addRecNode(nodo -> right, dato);
    }
    if(strcmp(nodo -> nameRec, dato -> to) == 0){
        addSenNode(nodo -> nodeSender, dato);
    }
    return nodo;
}

struct nodeSender* addSenNode(struct nodeSender *nodo, struct relation *dato){
    if (nodo == NULL){
        return createSenNode(dato);
    }
    if(strcmp(nodo -> nameSen, dato -> from) > 0){      // se è maggiore fa la funzione ricorsiva sul figlio a sx
        nodo -> left  = addSenNode(nodo -> left, dato);
    }
    if(strcmp(nodo -> nameSen, dato -> from) < 0){     // se è minore fa la funzione ricorsiva sul figlio a dx
        nodo -> right = addSenNode(nodo -> right, dato);
    }
    return nodo;
}

struct nodeMax* addMaxNode(struct nodeMax *nodo, struct relation *dato){
    if (nodo == NULL){
        return createMaxNode(dato);
    }
    if(strcmp(nodo -> name, dato -> to) > 0){      // se è maggiore fa la funzione ricorsiva sul figlio a sx
        nodo -> left  = addMaxNode(nodo -> left, dato);
    }
    if(strcmp(nodo -> name, dato -> to) < 0){     // se è minore fa la funzione ricorsiva sul figlio a dx
        nodo -> right = addMaxNode(nodo -> right, dato);
    }
    return nodo;
}

struct nodeRel *createRelNode(struct relation *relation){
    struct nodeRel *temp = malloc(sizeof(struct nodeRel));
    strcpy(temp -> nameRel, relation -> name);
    temp -> left = temp -> right = NULL;
    temp -> nodeReceiver = createRecNode(relation);
    temp -> nodeMax = createMaxNode(relation);
    return temp;
}

struct nodeReceiver *createRecNode(struct relation *relation){
    struct nodeReceiver *temp = malloc(sizeof(struct nodeReceiver));
    strcpy(temp -> nameRec, relation -> to);
    temp -> left = temp -> right = NULL;
    temp -> nodeSender = createSenNode(relation);
    return temp;
}

struct nodeSender *createSenNode(struct relation *relation){
    struct nodeSender *temp = malloc(sizeof(struct nodeSender));
    strcpy(temp -> nameSen, relation -> from);
    temp -> left = temp -> right = NULL;
    return temp;
}

struct nodeMax *createMaxNode(struct relation *relation){
    struct nodeMax *temp = malloc(sizeof(struct nodeMax));
    strcpy(temp -> name, relation -> to);
    temp -> qty = 1;
    temp -> left = temp -> right = NULL;
    return temp;
}
