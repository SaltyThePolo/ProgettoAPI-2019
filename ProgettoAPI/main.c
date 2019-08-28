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
short doppio = 0;
struct nodeReceiver *receiverRoot = NULL;


// inizio con la struttura dell'albero entità
struct node{
    char nome[30];
    struct node *left;
    struct node *right;
};

struct node *createUsrNode(char nome[30]){
    struct node *temp =  (struct node *)malloc(sizeof(struct node));
    strcpy(temp->nome, nome);
    temp->left = temp->right = NULL;
    return temp;
}

struct node* addUuserNode(struct node* node, char nome [30]){
    if (node == NULL){
        return createUsrNode(nome);
    }
    if(strcmp(node -> nome, nome) > 0){      // se è maggiore fa la funzione ricorsiva sul figlio a sx
        node -> left  = addUuserNode(node -> left, nome);
    }
    if(strcmp(node -> nome, nome) < 0){     // se è minore fa la funzione ricorsiva sul figlio a dx
        node -> right = addUuserNode(node -> right, nome);
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

struct node* rmvusrNode(struct node* root,char nome[30]){
    
    if (root == NULL){
        return root;            // in questo caso non cancello nulla
    }
    if (strcmp(root -> nome, nome) > 0){
        root -> left = rmvusrNode(root -> left, nome);
    }else if (strcmp(root -> nome, nome) < 0){
        root -> right = rmvusrNode(root ->right, nome);
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
        strcpy(root->nome, temp->nome);
        
        // Delete the inorder successor
        root->right = rmvusrNode(root->right, temp->nome);
    }
    return root;
}


struct node* searchUser (struct node *root, char nome[30]){
    if (root == NULL|| strcmp(root ->nome, nome) == 0) return root;
    if (strcmp(root -> nome, nome) > 0) return searchUser(root -> left, nome);
    return searchUser(root ->right, nome);
}

// -----------------------------------------------------------------------------------------------------------------------------------------

struct nodeRel{
    char nameRel[30];
    struct nodeReceiver *nodeReceiver;
    struct nodeRel *left;
    struct nodeRel *right;
};

struct nodeReceiver {
    char nameRec[30];
    short qty;
    struct nodeSender *nodeSender;
    struct nodeReceiver *left;
    struct nodeReceiver *right;
};

struct nodeSender{
    char nameSen[30];
    struct nodeSender *left;
    struct nodeSender *right;
};


struct relation{
    char name[30];
    char from[30];
    char to[30];
};

//--------------------------------------------------------------------------------------------------------------
//                                      PROTOTIPI
struct nodeRel* addRelNode(struct nodeRel* nodo, struct relation *dato);
struct nodeReceiver* addRecNode(struct nodeReceiver *nodo, struct relation *dato);
struct nodeSender* addSenNode(struct nodeSender *nodo, struct relation *dato);

struct nodeRel *createRelNode(struct relation *relation);
struct nodeReceiver *createRecNode(struct relation *relation);
struct nodeSender *createSenNode(struct relation *relation);

struct nodeRel* minRelValueNode(struct nodeRel* node);
struct nodeReceiver* minRecValueNode(struct nodeReceiver* node);
struct nodeSender* minSenValueNode(struct nodeSender* node);

struct nodeRel* rmvRelNode(struct nodeRel* root, struct nodeRel *nodo, struct relation *rel);
struct nodeReceiver* rmvRecNode(struct nodeReceiver* root, struct nodeReceiver* nodo, struct relation *rel);
struct nodeSender* rmvSenNode(struct nodeSender* root, char dato[30]);

struct nodeReceiver* rmvEmptyRecNode(struct nodeReceiver *root, struct nodeReceiver *nodo);
struct nodeRel* rmvEmptyRelNode(struct nodeRel *root, struct nodeRel *nodo);

struct nodeRel* scanRel (struct nodeRel *root, char dato[30]);
struct nodeReceiver* scanRec (struct nodeReceiver *root, char dato[30]);

short reportRel(struct nodeRel *nodo, short i);
void reportRec(struct nodeReceiver *nodo, short i);

short findMax(struct nodeReceiver *nodo, short i);

void delSenTree(struct nodeSender **root);

//void getLine(char *in);//, FILE *fin
//short program(char* string);


//-------------------------------------------------------------------------------------------------//

int main(int argc, const char * argv[]) {
    char a[30], b[30], c[30], d[30];
    short j = 0;
    do {
        for (short i = 0; i < 30; i ++) a[i] = '\0';
        for (short i = 0; i < 30; i ++) b[i] = '\0';
        for (short i = 0; i < 30; i ++) c[i] = '\0';
        for (short i = 0; i < 30; i ++) d[i] = '\0';
        for (short i = 0; i < 30; i++){
            char temp = getchar_unlocked();
            if (temp == '\n'){
                j = 1;
                break;
            }
            if (temp == ' ' || temp == EOF ) break;
            a[i] = temp;
        }
        
        if ( j == 0){
            for (short i = 0; i < 30; i++){
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
            for (short i = 0; i < 30; i++){
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
            for (short i = 0; i < 30; i++){
                char temp = getchar_unlocked();
                if (temp == EOF || temp == '\n') break;
                d[i] = temp;
            }
        }
        j = 0;
        if (strcmp(a, "addent") == 0) {
            usrRoot = addUuserNode(usrRoot, b);
        }else if(strcmp(a, "delent") == 0){
            if (searchUser(usrRoot, b) != NULL){
                usrRoot = rmvusrNode(usrRoot, b);
                relRoot = scanRel(relRoot, b);
            }
        }else if(strcmp(a, "addrel") == 0){
            if (searchUser(usrRoot, b) != NULL && searchUser(usrRoot, c) != NULL){
                struct relation *temp = malloc(sizeof(struct relation));
                strcpy(temp -> name, d);
                strcpy(temp -> from, b);
                strcpy(temp -> to, c);
                relRoot = addRelNode(relRoot, temp);
                free(temp);
            }
        }else if(strcmp(a, "delrel") == 0){
            if (searchUser(usrRoot, b) != NULL && searchUser(usrRoot, c) != NULL){
                struct relation *temp = malloc(sizeof(struct relation));
                strcpy(temp -> name, d);
                strcpy(temp -> from, b);
                strcpy(temp -> to, c);
                relRoot = rmvRelNode(relRoot, NULL, temp);
                free(temp);
            }
            
        }else if(strcmp(a, "report") == 0){
            if(relRoot == NULL) fputs("none\n", stdout);
            else {
                reportRel(relRoot, 0);
                fputs("\n", stdout);
            }
        }
        
    } while ((strcmp(a, "end") != 0));
    return 0;
}


//---------------------------------------------------------------------------------
/*
 void getLine(char *in){ //, FILE *fin
 short i = 0;
 char a;
 do{
 a = fgetc(stdin);//fin
 in[i] = a;
 i++;
 }while (a != '\n');
 
 in[i-1] = '\0';
 }
 
 short program(char* string){
 short i = 0, x = 0;
 char temp[30];
 
 while(string[i] != '\0' && string[x] != ' '){
 temp[i] = string [x];
 i++;
 x++;
 }
 temp[i] = '\0';
 i = 0;
 x++;
 if (strcmp(temp, "addent") == 0) {
 while(string[x] != '\0' && string[x] != ' ' && string[x] != '\n'){
 temp[i] = string [x];
 i++;
 x++;
 }
 temp[i] = '\0';
 usrRoot = addUuserNode(usrRoot, temp);
 return 1;
 }else if(strcmp(temp, "delent") == 0){
 while(string[x] != '\0' && string[x] != ' ' && string[x] != '\n'){
 temp[i] = string [x];
 i++;
 x++;
 }
 if (searchUser(usrRoot, temp) != NULL){ //toglibile?
 usrRoot = rmvusrNode(usrRoot, temp);
 relRoot = scanRel(relRoot, temp);
 }
 
 
 }else if(strcmp(temp, "addrel") == 0){
 char from[30], to[30], rel[30];
 while(string[x] != ' '){
 from[i] = string [x];
 i++;
 x++;
 }
 from[i] = '\0';
 i=0;
 x++;
 while(string[x] != ' '){
 to[i] = string [x];
 i++;
 x++;
 }
 to[i] = '\0';
 i=0;
 x++;
 while(string[x] != '\0' && string[x] != ' ' && string[x] != '\n'){
 rel[i] = string [x];
 i++;
 x++;
 }
 rel[i] = '\0';
 
 if (searchUser(usrRoot, from) != NULL && searchUser(usrRoot, to) != NULL){
 struct relation *temp = malloc(sizeof(struct relation));
 strcpy(temp -> name, rel);
 strcpy(temp -> from, from);
 strcpy(temp -> to, to);
 relRoot = addRelNode(relRoot, temp);
 free(temp);
 }
 return 2;
 
 }else if(strcmp(temp, "delrel") == 0){
 char from[30], to[30], rel[30];
 while(string[x] != ' '){
 from[i] = string [x];
 i++;
 x++;
 }
 from[i] = '\0';
 i=0;
 x++;
 while(string[x] != ' '){
 to[i] = string [x];
 i++;
 x++;
 }
 to[i] = '\0';
 i=0;
 x++;
 while(string[i] != '\0' && string[x] != ' ' && string[x] != '\n'){
 rel[i] = string [x];
 i++;
 x++;
 }
 rel[i] = '\0';
 if (searchUser(usrRoot, from) != NULL && searchUser(usrRoot, to) != NULL){
 struct relation *temp = malloc(sizeof(struct relation));
 strcpy(temp -> name, rel);
 strcpy(temp -> from, from);
 strcpy(temp -> to, to);
 relRoot = rmvRelNode(relRoot, NULL, temp);
 free(temp);
 }
 return 3;
 }else if(strcmp(temp, "report") == 0){
 if(relRoot == NULL) fputs("none\n", stdout);
 else {
 reportRel(relRoot, 0);
 fputs("\n", stdout);
 }
 return 4;
 }else if(strcmp(temp, "end") == 0){
 return 100;
 }
 return 0;
 }
 */

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
        if(doppio == 0){
            nodo -> qty ++;
        }else{
            doppio = 0;
        }
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
    if(strcmp(nodo -> nameSen, dato -> from) == 0){
        doppio = 1;
    }
    return nodo;
}


struct nodeRel *createRelNode(struct relation *relation){
    struct nodeRel *temp = malloc(sizeof(struct nodeRel));
    strcpy(temp -> nameRel, relation -> name);
    temp -> left = temp -> right = NULL;
    temp -> nodeReceiver = createRecNode(relation);
    return temp;
}

struct nodeReceiver *createRecNode(struct relation *relation){
    struct nodeReceiver *temp = malloc(sizeof(struct nodeReceiver));
    strcpy(temp -> nameRec, relation -> to);
    temp -> qty = 1;
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



struct nodeRel* minRelValueNode(struct nodeRel* node)
{
    struct nodeRel* current = node;
    
    // loop down to find the leftmost leaf
    while (current && current->left != NULL)
        current = current->left;
    
    return current;
}

struct nodeReceiver* minRecValueNode(struct nodeReceiver* node){
    struct nodeReceiver* current = node;
    // loop down to find the leftmost leaf
    while (current && current->left != NULL)
        current = current->left;
    return current;
}

struct nodeSender* minSenValueNode(struct nodeSender* node){
    struct nodeSender* current = node;
    // loop down to find the leftmost leaf
    while (current && current->left != NULL)
        current = current->left;
    return current;
}



//Given a binary search tree and a key, this function deletes the key
//and returns the new root
struct nodeRel* rmvRelNode(struct nodeRel* root, struct nodeRel* nodo, struct relation *rel){
    if (nodo == NULL) {
        // base case
        if (root == NULL) return root;
        
        // If the key to be deleted is smaller than the root's key,
        // then it lies in left subtree
        if (strcmp(rel -> name, root -> nameRel) < 0 )
            root->left = rmvRelNode(root->left, nodo, rel);
        
        // If the key to be deleted is greater than the root's key,
        // then it lies in right subtree
        else if (strcmp(rel -> name, root -> nameRel) > 0 )
            root->right = rmvRelNode(root->right, nodo, rel);
        
        // if key is same as root's key, then This is the node
        // to be deleted
        else if(root != NULL){
            root ->nodeReceiver = rmvRecNode(root -> nodeReceiver, NULL, rel);
            if ( root -> nodeReceiver == NULL){
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
                strcpy(root -> nameRel, temp -> nameRel);
                root -> nodeReceiver = temp -> nodeReceiver;
                
                // Delete the inorder successor
                root -> right = rmvRelNode(root -> right, temp, rel);
            }
        }
        return root;
    } else {
        // base case
        if (root == NULL) return root;
        
        // If the key to be deleted is smaller than the root's key,
        // then it lies in left subtree
        if (strcmp(nodo -> nameRel, root -> nameRel) < 0 )
            root->left = rmvRelNode(root->left, nodo, rel);
        
        // If the key to be deleted is greater than the root's key,
        // then it lies in right subtree
        else if (strcmp(nodo -> nameRel, root -> nameRel) > 0)
            root->right = rmvRelNode(root->right, nodo, rel);
        
        // if key is same as root's key, then This is the node
        // to be deleted
        else{
            // node with only one child or no child
            if (root->left == NULL){
                struct nodeRel *temp = root->right;
                free(root);
                return temp;
            }else if (root->right == NULL){
                struct nodeRel *temp = root->left;
                free(root);
                return temp;
            }
        }
    }
    return root;
}

//Given a binary search tree and a key, this function deletes the key
//and returns the new root
struct nodeReceiver* rmvRecNode(struct nodeReceiver* root, struct nodeReceiver* nodo, struct relation *rel){
    if (nodo == NULL) {
        // base case
        if (root == NULL) return root;
        // If the key to be deleted is smaller than the root's key,
        // then it lies in left subtree
        if (strcmp(rel -> to, root -> nameRec) < 0 ) root->left = rmvRecNode(root->left, nodo, rel);
        
        // If the key to be deleted is greater than the root's key,
        // then it lies in right subtree
        else if (strcmp(rel -> to, root -> nameRec) > 0) root->right = rmvRecNode(root->right, nodo, rel);
        
        // if key is same as root's key, then This is the node
        // to be deleted
        else if(root != NULL){
            root -> nodeSender = rmvSenNode( root -> nodeSender, rel -> from);
            if (doppio == 1){
                root -> qty --;
                doppio = 0;
            }
            if ( root -> nodeSender == NULL){
                // node with only one child or no child
                if (root->left == NULL){
                    struct nodeReceiver *temp = root->right;
                    free(root);
                    return temp;
                }
                else if (root->right == NULL){
                    struct nodeReceiver *temp = root->left;
                    free(root);
                    return temp;
                }
                
                // node with two children: Get the inorder successor (smallest
                // in the right subtree)
                struct nodeReceiver* temp = minRecValueNode(root->right);
                
                // Copy the inorder successor's content to this node
                strcpy(root -> nameRec, temp -> nameRec);
                root -> qty = temp -> qty;
                root -> nodeSender = temp -> nodeSender;
                
                // Delete the inorder successor
                root -> right = rmvRecNode(root -> right, temp, rel);
            }
        }
        return root;
    } else {
        // base case
        if (root == NULL) return root;
        
        // If the key to be deleted is smaller than the root's key,
        // then it lies in left subtree
        if (strcmp(nodo -> nameRec, root -> nameRec) < 0 )
            root->left = rmvRecNode(root->left, nodo, rel);
        
        // If the key to be deleted is greater than the root's key,
        // then it lies in right subtree
        else if (strcmp(nodo -> nameRec, root -> nameRec) > 0)
            root->right = rmvRecNode(root->right, nodo, rel);
        
        // if key is same as root's key, then This is the node
        // to be deleted
        else{
            // node with only one child or no child
            if (root->left == NULL){
                struct nodeReceiver *temp = root->right;
                free(root);
                return temp;
            }else if (root->right == NULL){
                struct nodeReceiver *temp = root->left;
                free(root);
                return temp;
            }
        }
    }
    return root;
}

/* Given a binary search tree and a key, this function deletes the key
 and returns the new root */
struct nodeSender* rmvSenNode(struct nodeSender* root, char dato[30]){
    // base case
    if (root == NULL) return root;
    
    // If the key to be deleted is smaller than the root's key,
    // then it lies in left subtree
    if (strcmp(dato, root -> nameSen) < 0)
        root->left = rmvSenNode(root->left, dato);
    
    // If the key to be deleted is greater than the root's key,
    // then it lies in right subtree
    else if (strcmp(dato, root -> nameSen) > 0)
        root->right = rmvSenNode(root -> right, dato);
    
    // if key is same as root's key, then This is the node
    // to be deleted
    else
    {
        doppio = 1;
        // node with only one child or no child
        if (root->left == NULL)
        {
            struct nodeSender *temp = root -> right;
            free(root);
            return temp;
        }
        else if (root -> right == NULL)
        {
            struct nodeSender *temp = root -> left;
            free(root);
            return temp;
        }
        
        // node with two children: Get the inorder successor (smallest
        // in the right subtree)
        struct nodeSender* temp = minSenValueNode(root -> right);
        
        // Copy the inorder successor's content to this node
        strcpy(root -> nameSen, temp -> nameSen);
        
        // Delete the inorder successor
        root -> right = rmvSenNode(root -> right, temp -> nameSen);
    }
    return root;
}



short reportRel(struct nodeRel *nodo, short i){
    if (nodo != NULL)
    {
        if (nodo -> left != NULL) i = reportRel(nodo->left, i);
        if (i != 0) fputs(" ", stdout);
        fputs(nodo -> nameRel, stdout);
        fputs(" ", stdout);
        i = findMax (nodo -> nodeReceiver, 0);
        reportRec(nodo -> nodeReceiver, i);
        printf("%d;", i);
        if (nodo -> right != NULL) i = reportRel(nodo->right, i);
    }
    return i;
}

void reportRec(struct nodeReceiver *nodo, short i){
    if (nodo != NULL)
    {
        if (nodo -> left != NULL) reportRec(nodo -> left, i);
        if (nodo -> qty == i){
            fputs(nodo -> nameRec, stdout);
            fputs(" ", stdout);
        }
        if (nodo -> right != NULL) reportRec(nodo -> right, i);
    }
}



short findMax(struct nodeReceiver *nodo, short i){
    if(nodo != NULL){
        if (nodo -> left != NULL) i = findMax(nodo -> left, i);
        if (nodo -> qty > i) i = nodo -> qty;
        if (nodo -> right != NULL) i = findMax(nodo -> right, i);
    }
    return i;
}



void delSenTree(struct nodeSender **root){
    if(*root == NULL) return;
    delSenTree(&((*root) -> left));
    delSenTree(&((*root) -> right));
    free(*root);
    *root = NULL;
}



struct nodeRel* scanRel (struct nodeRel *root, char dato[30]){
    if (root != NULL){
        if( root -> left != NULL) root -> left = scanRel(root -> left, dato);
        if( root -> right != NULL) root -> right = scanRel(root -> right, dato);
        receiverRoot = root -> nodeReceiver;
        root -> nodeReceiver = scanRec(root -> nodeReceiver, dato);
        if ( root -> nodeReceiver == NULL) root = rmvEmptyRelNode(root, root);
    }
    return root;
}

struct nodeReceiver* scanRec (struct nodeReceiver *root, char dato[30]){
    
    if (root != NULL) {
        if( root -> left != NULL) root -> left = scanRec(root -> left, dato);
        if( root -> right != NULL) root -> right = scanRec(root -> right, dato);
        
        if(strcmp(root -> nameRec, dato) == 0) {
            delSenTree(&(root -> nodeSender));
            root = rmvEmptyRecNode(root, root); // problema qui, anche se root è un'altro nodo mi torna sempre la radice dell'albero
            
        }
        else {
            root -> nodeSender = rmvSenNode(root -> nodeSender, dato);
            if (doppio == 1) {
                root -> qty --;
                doppio = 0;
            }
            if (root -> nodeSender == NULL) root = rmvEmptyRecNode(root, root);
        }
        
    }
    return root;
}



struct nodeReceiver* rmvEmptyRecNode(struct nodeReceiver *root, struct nodeReceiver *nodo){
    // base case
    if (root == NULL) return root;
    
    // If the key to be deleted is smaller than the root's key,
    // then it lies in left subtree
    if (strcmp(nodo -> nameRec, root -> nameRec) < 0 )
        root->left = rmvEmptyRecNode(root->left, nodo);
    
    // If the key to be deleted is greater than the root's key,
    // then it lies in right subtree
    else if (strcmp(nodo -> nameRec, root -> nameRec) > 0)
        root->right = rmvEmptyRecNode(root->right, nodo);
    
    // if key is same as root's key, then This is the node
    // to be deleted
    else{
        // node with only one child or no child
        if (root->left == NULL){
            struct nodeReceiver *temp = root->right;
            free(root);
            return temp;
        }else if (root->right == NULL){
            struct nodeReceiver *temp = root->left;
            free(root);
            return temp;
        }
        // node with two children: Get the inorder successor (smallest
        // in the right subtree)
        struct nodeReceiver* temp = minRecValueNode(root->right);
        
        // Copy the inorder successor's content to this node
        strcpy(root -> nameRec, temp -> nameRec);
        root -> qty = temp -> qty;
        root -> nodeSender = temp -> nodeSender;
        
        // Delete the inorder successor
        root -> right = rmvEmptyRecNode(root -> right, temp);
    }
    return root;
}

struct nodeRel* rmvEmptyRelNode(struct nodeRel *root, struct nodeRel *nodo){
    // base case
    if (root == NULL) return root;
    
    // If the key to be deleted is smaller than the root's key,
    // then it lies in left subtree
    if (strcmp(nodo -> nameRel, root -> nameRel) < 0 )
        root->left = rmvEmptyRelNode(root->left, nodo);
    
    // If the key to be deleted is greater than the root's key,
    // then it lies in right subtree
    else if (strcmp(nodo -> nameRel, root -> nameRel) > 0)
        root->right = rmvEmptyRelNode(root->right, nodo);
    
    // if key is same as root's key, then This is the node
    // to be deleted
    else{
        // node with only one child or no child
        if (root->left == NULL){
            struct nodeRel *temp = root->right;
            free(root);
            return temp;
        }else if (root->right == NULL){
            struct nodeRel *temp = root->left;
            free(root);
            return temp;
        }
        // node with two children: Get the inorder successor (smallest
        // in the right subtree)
        struct nodeRel* temp = minRelValueNode(root->right);
        
        // Copy the inorder successor's content to this node
        strcpy(root -> nameRel, temp -> nameRel);
        root -> nodeReceiver = temp -> nodeReceiver;
        
        // Delete the inorder successor
        root -> right = rmvEmptyRelNode(root -> right, temp);
    }
    return root;
}

