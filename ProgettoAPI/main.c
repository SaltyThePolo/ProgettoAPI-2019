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
short doppio = 0, ritornello = 0, massimo = 0;
struct nodeReceiver *receiverRoot = NULL;


// inizio con la struttura dell'albero entità
struct node{
    char nome[35];
    struct node *left;
    struct node *right;
};


// -----------------------------------------------------------------------------------------------------------------------------------------

struct nodeRel{
    char nameRel[35];
    struct nodeReceiver *nodeReceiver;
    struct nodeRel *left;
    struct nodeRel *right;
    short max;
    struct nodeMax *nodeMax;
};

struct nodeMax{
    char name[35];
    struct nodeMax *left;
    struct nodeMax *right;
};

struct nodeReceiver {
    char nameRec[35];
    short qty;
    struct nodeSender *nodeSender;
    struct nodeReceiver *left;
    struct nodeReceiver *right;
};

struct nodeSender{
    char nameSen[35];
    struct nodeSender *left;
    struct nodeSender *right;
};


struct relation{
    char name[35];
    char from[35];
    char to[35];
};

//--------------------------------------------------------------------------------------------------------------
//                                      PROTOTIPI
static inline struct node *createUsrNode(char nome[35]);
static inline struct node* addUuserNode(struct node* node, char nome [35]);
static inline struct node* minUsrValueNode(struct node* node);
static inline struct node* rmvusrNode(struct node* root,char nome[35]);
static inline struct node* searchUser (struct node *root, char nome[35]);
//--------------------------------------------------------------------------------------------------------------
static inline struct nodeRel* addRelNode(struct nodeRel* nodo, struct relation *dato);
static inline struct nodeReceiver* addRecNode(struct nodeReceiver *nodo, struct relation *dato);
static inline struct nodeSender* addSenNode(struct nodeSender *nodo, struct relation *dato);
static inline struct nodeMax* addMaxNode(struct nodeMax *nodo, char nome[35]);

static inline struct nodeRel *createRelNode(struct relation *relation);
static inline struct nodeReceiver *createRecNode(struct relation *relation);
static inline struct nodeSender *createSenNode(struct relation *relation);
static inline struct nodeMax *createMaxNode(char nome[35]);

static inline struct nodeRel* minRelValueNode(struct nodeRel* node);
static inline struct nodeReceiver* minRecValueNode(struct nodeReceiver* node);
static inline struct nodeSender* minSenValueNode(struct nodeSender* node);
static inline struct nodeMax* minMaxValueNode(struct nodeMax* node);

static inline struct nodeRel* rmvRelNode(struct nodeRel* root, struct nodeRel *nodo, struct relation *rel);
static inline struct nodeReceiver* rmvRecNode(struct nodeReceiver* root, struct nodeReceiver* nodo, struct relation *rel);
static inline struct nodeSender* rmvSenNode(struct nodeSender* root, char dato[35]);
static inline struct nodeMax* rmvMaxNode(struct nodeMax* root, char dato[35]);

static inline struct nodeReceiver* rmvEmptyRecNode(struct nodeReceiver *root, struct nodeReceiver *nodo);
static inline struct nodeRel* rmvEmptyRelNode(struct nodeRel *root, struct nodeRel *nodo);

static inline struct nodeRel* scanRel (struct nodeRel *root, char dato[35]);
static inline struct nodeReceiver* scanRec (struct nodeReceiver *root, char dato[35]);

static inline short reportRel(struct nodeRel *nodo, short i);
static inline short report2(struct nodeRel *nodo, short i);
static inline void reportRec(struct nodeReceiver *nodo, short i);

static inline short findMax(struct nodeReceiver *nodo, short i);

static inline void delSenTree(struct nodeSender **root);
static inline void delMaxTree(struct nodeMax **root);

static inline struct nodeReceiver* fillMaxTree (struct nodeRel* root, struct nodeReceiver* move, short max);

static inline void printwholetree(struct nodeMax* root);

static inline void program(void);


//-------------------------------------------------------------------------------------------------//

int main(int argc, const char * argv[]) {
    do {
        program();
    } while (ritornello != 100);
    return 0;
}


//---------------------------------------------------------------------------------------------------
static inline struct node *createUsrNode(char nome[35]){
    struct node *temp =  (struct node *)malloc(sizeof(struct node));
    strcpy(temp->nome, nome);
    temp->left = temp->right = NULL;
    return temp;
}

static inline struct node* addUuserNode(struct node* node, char nome [35]){
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

static inline struct node* minUsrValueNode(struct node* node){
    struct node* current = node;
    
    /* loop down to find the leftmost leaf */
    while (current && current->left != NULL)
        current = current->left;
    
    return current;
}

static inline struct node* rmvusrNode(struct node* root,char nome[35]){
    
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


static inline struct node* searchUser (struct node *root, char nome[35]){
    if (root == NULL|| strcmp(root ->nome, nome) == 0) return root;
    if (strcmp(root -> nome, nome) > 0) return searchUser(root -> left, nome);
    return searchUser(root ->right, nome);
}

//---------------------------------------------------------------------------------------------------
static inline void program(){
    char a[10], b[35], c[35], d[35];
    massimo = 0;
    for (short i = 0; i < 10; i++){
        char temp = fgetc(stdin);
        if (temp == '\n'){
            a[i] = '\0';
            break;
        }
        if (temp == ' ') {
            a[i] = '\0';
            break;
        }
        a[i] = temp;
    }
    if (strcmp(a, "addent") == 0) {
        for (short i = 0; i < 35; i++){
            char temp = fgetc(stdin);
            if (temp == ' '){
                b[i] = '\0';
                break;
            }
            if (temp == '\n') {
                b[i] = '\0';
                break;
            }
            b[i] = temp;
        }
        usrRoot = addUuserNode(usrRoot, b);
        ritornello = 1;
    }else if(strcmp(a, "delent") == 0){
        for (short i = 0; i < 35; i++){
            char temp = fgetc(stdin);
            if (temp == ' '){
                b[i] = '\0';
                break;
            }
            if (temp == '\n') {
                b[i] = '\0';
                break;
            }
            b[i] = temp;
        }
        
        if (searchUser(usrRoot, b) != NULL){
            usrRoot = rmvusrNode(usrRoot, b);
            relRoot = scanRel(relRoot, b);
        }
        ritornello = 2;
    }else if(strcmp(a, "addrel") == 0){
        for (short i = 0; i < 35; i++){
            char temp = fgetc(stdin);
            if (temp == ' '){
                b[i] = '\0';
                break;
            }
            if (temp == '\n') {
                b[i] = '\0';
                break;
            }
            b[i] = temp;
        }
        for (short i = 0; i < 35; i++){
            char temp = fgetc(stdin);
            if (temp == ' ') {
                c[i] = '\0';
                break;
            }
            if (temp == '\n') {
                c[i] = '\0';
                
                break;
            }
            c[i] = temp;
        }
        for (short i = 0; i < 35; i++){
            char temp = fgetc(stdin);
            if (temp == '\n') {
                d[i] = '\0';
                break;
            }
            d[i] = temp;
        }
        if (searchUser(usrRoot, b) != NULL && searchUser(usrRoot, c) != NULL){
            struct relation temp;
            strcpy(temp.name, d);
            strcpy(temp.from, b);
            strcpy(temp.to, c);
            relRoot = addRelNode(relRoot, &temp);
        }
        ritornello = 3;
    }else if(strcmp(a, "delrel") == 0){
        for (short i = 0; i < 35; i++){
            char temp = fgetc(stdin);
            if (temp == ' '){
                b[i] = '\0';
                break;
            }
            if (temp == '\n') {
                b[i] = '\0';
                break;
            }
            b[i] = temp;
        }
        for (short i = 0; i < 35; i++){
            char temp = fgetc(stdin);
            if (temp == ' ') {
                c[i] = '\0';
                break;
            }
            if (temp == '\n') {
                c[i] = '\0';
                break;
            }
            c[i] = temp;
        }
        for (short i = 0; i < 35; i++){
            char temp = fgetc(stdin);
            if (temp == '\n') {
                d[i] = '\0';
                break;
            }
            d[i] = temp;
        }
        if (searchUser(usrRoot, b) != NULL && searchUser(usrRoot, c) != NULL){
            struct relation temp;
            strcpy(temp.name, d);
            strcpy(temp.from, b);
            strcpy(temp.to, c);
            relRoot = rmvRelNode(relRoot, NULL, &temp);
            ritornello = 4;
        }
    }else if(strcmp(a, "report") == 0){
        if(relRoot == NULL) fputs("none\n", stdout);
        else {
            //reportRel(relRoot, 0);
            //fputc('\n', stdout);
            report2(relRoot, 0);
            fputc('\n', stdout);
            //fputc('\n', stdout);
        }
        ritornello = 5;
    }else if(strcmp(a, "end") == 0) ritornello = 100;
}

static inline struct nodeRel* addRelNode(struct nodeRel* nodo, struct relation *dato){
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
        if(massimo == nodo -> max){
            nodo -> nodeMax = addMaxNode(nodo -> nodeMax, dato -> to);
            massimo = 0;
        }else if(massimo > nodo -> max){
            nodo -> max = massimo;
            delMaxTree(&(nodo -> nodeMax));
            fillMaxTree(nodo, nodo -> nodeReceiver, massimo);
            massimo = 0;
        }
    }
    return nodo;
}

static inline struct nodeReceiver* addRecNode(struct nodeReceiver *nodo, struct relation *dato){
    if (nodo == NULL){
        massimo = 1;
        return createRecNode(dato);
    }
    if(strcmp(nodo -> nameRec, dato -> to) > 0){      // se è maggiore fa la funzione ricorsiva sul figlio a sx
        nodo -> left  = addRecNode(nodo -> left, dato);
    }
    if(strcmp(nodo -> nameRec, dato -> to) < 0){     // se è minore fa la funzione ricorsiva sul figlio a dx
        nodo -> right = addRecNode(nodo -> right, dato);
    }
    if(strcmp(nodo -> nameRec, dato -> to) == 0){
        nodo -> nodeSender = addSenNode(nodo -> nodeSender, dato);
        if(doppio == 0){
            nodo -> qty ++;
            massimo = nodo -> qty;
        }else{
            doppio = 0;
        }
    }
    return nodo;
}

static inline struct nodeSender* addSenNode(struct nodeSender *nodo, struct relation *dato){
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

static inline struct nodeMax* addMaxNode(struct nodeMax *nodo, char nome[35]){
    if (nodo == NULL){
        return createMaxNode(nome);
    }
    if(strcmp(nodo -> name, nome) > 0){      // se è maggiore fa la funzione ricorsiva sul figlio a sx
        nodo -> left  = addMaxNode(nodo -> left, nome);
    }
    if(strcmp(nodo -> name, nome) < 0){     // se è minore fa la funzione ricorsiva sul figlio a dx
        nodo -> right = addMaxNode(nodo -> right, nome);
    }
    return nodo;
}



static inline struct nodeRel *createRelNode(struct relation *relation){
    struct nodeRel *temp = malloc(sizeof(struct nodeRel));
    strcpy(temp -> nameRel, relation -> name);
    temp -> left = temp -> right = NULL;
    temp -> nodeReceiver = createRecNode(relation);
    temp -> nodeMax = createMaxNode(relation -> to);
    temp -> max = 1;
    return temp;
}

static inline struct nodeReceiver *createRecNode(struct relation *relation){
    struct nodeReceiver *temp = malloc(sizeof(struct nodeReceiver));
    strcpy(temp -> nameRec, relation -> to);
    temp -> qty = 1;
    temp -> left = temp -> right = NULL;
    temp -> nodeSender = createSenNode(relation);
    return temp;
}

static inline struct nodeSender *createSenNode(struct relation *relation){
    doppio = 0;
    struct nodeSender *temp = malloc(sizeof(struct nodeSender));
    strcpy(temp -> nameSen, relation -> from);
    temp -> left = temp -> right = NULL;
    return temp;
}

struct nodeMax *createMaxNode(char nome[35]){
    struct nodeMax *temp = malloc(sizeof(struct nodeMax));
    strcpy(temp -> name, nome);
    temp -> left = temp -> right = NULL;
    return temp;
}



static inline struct nodeRel* minRelValueNode(struct nodeRel* node){
    struct nodeRel* current = node;
    // loop down to find the leftmost leaf
    while (current && current->left != NULL)
        current = current->left;
    
    return current;
}

static inline struct nodeReceiver* minRecValueNode(struct nodeReceiver* node){
    struct nodeReceiver* current = node;
    // loop down to find the leftmost leaf
    while (current && current->left != NULL)
        current = current->left;
    return current;
}

static inline struct nodeSender* minSenValueNode(struct nodeSender* node){
    struct nodeSender* current = node;
    // loop down to find the leftmost leaf
    while (current && current->left != NULL)
        current = current->left;
    return current;
}

static inline struct nodeMax* minMaxValueNode(struct nodeMax* node){
    struct nodeMax* current = node;
    // loop down to find the leftmost leaf
    while (current && current->left != NULL)
        current = current->left;
    return current;
}



//Given a binary search tree and a key, this function deletes the key
//and returns the new root
static inline struct nodeRel* rmvRelNode(struct nodeRel* root, struct nodeRel* nodo, struct relation *rel){
    if (nodo == NULL) {
        // base case
        if (root == NULL) return root;
        
        // If the key to be deleted is smaller than the root's key,
        // then it lies in left subtree
        if (strcmp(rel -> name, root -> nameRel) < 0)
            root->left = rmvRelNode(root->left, nodo, rel);
        
        // If the key to be deleted is greater than the root's key,
        // then it lies in right subtree
        else if (strcmp(rel -> name, root -> nameRel) > 0)
            root->right = rmvRelNode(root->right, nodo, rel);
        
        // if key is same as root's key, then This is the node
        // to be deleted
        else if(root != NULL){
            root ->nodeReceiver = rmvRecNode(root -> nodeReceiver, NULL, rel);
            if ( massimo == root -> max){
                root -> nodeMax = rmvMaxNode(root -> nodeMax, rel -> to);
                root -> max = findMax(root -> nodeReceiver, 0);
                massimo = 0;
             }
            if ((root -> nodeMax == NULL && root -> nodeReceiver != NULL)){ // || massimo == 1000;
                massimo = findMax(root -> nodeReceiver, 0);
                delMaxTree(&(root -> nodeMax));
                fillMaxTree(root, root -> nodeReceiver, massimo);
                root -> max = massimo;
                massimo = 0;
            }
            /* }else{
            delMaxTree(&(root -> nodeMax));
            massimo = findMax(root -> nodeReceiver, 0);
            root -> max = massimo;
            fillMaxTree(root, root -> nodeReceiver, massimo);
            massimo = 0;
        }*/
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
static inline struct nodeReceiver* rmvRecNode(struct nodeReceiver* root, struct nodeReceiver* nodo, struct relation *rel){
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
            doppio = 0;
            root -> nodeSender = rmvSenNode( root -> nodeSender, rel -> from);
            if (doppio == 1){
                massimo = root -> qty;
                root -> qty --;
                doppio = 0;
            }
            if ( root -> nodeSender == NULL){
                //if(massimo != 0) massimo = 1000;
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
static inline struct nodeSender* rmvSenNode(struct nodeSender* root, char dato[35]){
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
        massimo = 1;
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

static inline struct nodeMax* rmvMaxNode(struct nodeMax* root, char dato[35]){
    // base case
    if (root == NULL) return root;
    
    // If the key to be deleted is smaller than the root's key,
    // then it lies in left subtree
    if (strcmp(dato, root -> name) < 0)
        root->left = rmvMaxNode(root->left, dato);
    
    // If the key to be deleted is greater than the root's key,
    // then it lies in right subtree
    else if (strcmp(dato, root -> name) > 0)
        root->right = rmvMaxNode(root -> right, dato);
    
    // if key is same as root's key, then This is the node
    // to be deleted
    else
    {
        doppio = 1;
        // node with only one child or no child
        if (root->left == NULL)
        {
            struct nodeMax *temp = root -> right;
            free(root);
            return temp;
        }
        else if (root -> right == NULL)
        {
            struct nodeMax *temp = root -> left;
            free(root);
            return temp;
        }
        
        // node with two children: Get the inorder successor (smallest
        // in the right subtree)
        struct nodeMax* temp = minMaxValueNode(root -> right);
        
        // Copy the inorder successor's content to this node
        strcpy(root -> name, temp -> name);
        
        // Delete the inorder successor
        root -> right = rmvMaxNode(root -> right, temp -> name);
    }
    return root;
}



static inline short reportRel(struct nodeRel *nodo, short i){
    if (nodo != NULL)
    {
        if (nodo -> left != NULL) i = reportRel(nodo->left, i);
        if (i != 0) fputc(' ', stdout);
        fputs(nodo -> nameRel, stdout);
        fputc(' ', stdout);
        i = findMax (nodo -> nodeReceiver, 0);
        reportRec(nodo -> nodeReceiver, i);
        fprintf(stdout, "%d;", i); //??
        if (nodo -> right != NULL) i = reportRel(nodo->right, i);
    }
    return i;
}

static inline void reportRec(struct nodeReceiver *nodo, short i){
    if (nodo != NULL)
    {
        if (nodo -> left != NULL) reportRec(nodo -> left, i);
        if (nodo -> qty == i){
            fputs(nodo -> nameRec, stdout);
            fputc(' ', stdout);
        }
        if (nodo -> right != NULL) reportRec(nodo -> right, i);
    }
}

static inline short report2(struct nodeRel *nodo, short i){
    if (nodo != NULL)
    {
        if (nodo -> left != NULL) i = report2(nodo->left, i);
        if (i != 0) fputc(' ', stdout);
        else i = 1;
        fputs(nodo -> nameRel, stdout);
        fputc(' ', stdout);
        printwholetree(nodo -> nodeMax);
        fprintf(stdout, "%d;", nodo -> max); //??
        if (nodo -> right != NULL) i = reportRel(nodo->right, i);
    }
    return i;
}



static inline short findMax(struct nodeReceiver *nodo, short i){
    if(nodo != NULL){
        if (nodo -> left != NULL) i = findMax(nodo -> left, i);
        if (nodo -> qty > i) i = nodo -> qty;
        if (nodo -> right != NULL) i = findMax(nodo -> right, i);
    }
    return i;
}



static inline void delSenTree(struct nodeSender **root){
    if(*root == NULL) return;
    delSenTree(&((*root) -> left));
    delSenTree(&((*root) -> right));
    free(*root);
    *root = NULL;
}

static inline void delMaxTree(struct nodeMax **root){
    if(*root == NULL) return;
    delMaxTree(&((*root) -> left));
    delMaxTree(&((*root) -> right));
    free(*root);
    *root = NULL;
}



static inline struct nodeRel* scanRel (struct nodeRel *root, char dato[35]){
    if (root != NULL){
        if( root -> left != NULL) root -> left = scanRel(root -> left, dato);
        if( root -> right != NULL) root -> right = scanRel(root -> right, dato);
        receiverRoot = root -> nodeReceiver;
        massimo = 0;
        root -> nodeReceiver = scanRec(root -> nodeReceiver, dato);
        if(massimo == 1){
            delMaxTree(&(root -> nodeMax));
            massimo = findMax(root -> nodeReceiver, 0);
            root -> max = massimo;
            fillMaxTree(root, root -> nodeReceiver, massimo);
            massimo = 0;
        }
        if ( root -> nodeReceiver == NULL) root = rmvEmptyRelNode(root, root);
    }
    return root;
}

static inline struct nodeReceiver* scanRec (struct nodeReceiver *root, char dato[35]){
    
    if (root != NULL) {
        if( root -> left != NULL) root -> left = scanRec(root -> left, dato);
        if( root -> right != NULL) root -> right = scanRec(root -> right, dato);
        
        if(strcmp(root -> nameRec, dato) == 0) {
            massimo = 1;
            delSenTree(&(root -> nodeSender));
            root = rmvEmptyRecNode(root, root); // problema qui, anche se root è un'altro nodo mi torna sempre la radice dell'albero
            
        }
        else {
            doppio = 0;
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



static inline struct nodeReceiver* rmvEmptyRecNode(struct nodeReceiver *root, struct nodeReceiver *nodo){
    // base case
    if (root == NULL) return root;
    
    // If the key to be deleted is smaller than the root's key,
    // then it lies in left subtree
    if (strcmp(nodo -> nameRec, root -> nameRec) < 0 )
        root->left = rmvEmptyRecNode(root->left, nodo);
    
    // If the key to be deleted is greater than the root's key,
    // then it lies in right subtree
    else if (strcmp(nodo -> nameRec, root -> nameRec) > 0 )
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

static inline struct nodeRel* rmvEmptyRelNode(struct nodeRel *root, struct nodeRel *nodo){
    // base case
    if (root == NULL) return root;
    
    // If the key to be deleted is smaller than the root's key,
    // then it lies in left subtree
    if (strcmp(nodo -> nameRel, root -> nameRel) < 0 )
        root->left = rmvEmptyRelNode(root->left, nodo);
    
    // If the key to be deleted is greater than the root's key,
    // then it lies in right subtree
    else if (strcmp(nodo -> nameRel, root -> nameRel) > 0 )
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



static inline struct nodeReceiver* fillMaxTree (struct nodeRel* root, struct nodeReceiver* move, short max){
    if(move != NULL){
        if(move -> qty == max) root -> nodeMax = addMaxNode(root -> nodeMax, move ->nameRec);
        if( move -> left != NULL) move -> left = fillMaxTree(root , move -> left, max);
        if( move -> right != NULL) move -> right = fillMaxTree(root , move -> right, max);
    }
    return move;
}

static inline void printwholetree(struct nodeMax* root){
    if (root != NULL){
        if(root -> left != NULL) printwholetree(root -> left);
        fputs(root -> name, stdout);
        fputc(' ', stdout);
        if(root -> right != NULL) printwholetree(root -> right);
    }
}
