#pragma once

#include<iostream>
#include<fstream>
using namespace std;
#include<string>

struct Node {
    Node* left;
	Node* right;
	int height;
	int key;            //Hashed value of key
    string filePath;
	int lineNumber;
};

int height(Node* N){  // to get height of the tree
    if (N == NULL)
        return 0;
    return N->height;
}

int max(int a, int b){
    return (a > b) ? a : b;
}

// to allocate a new node with the given attributes
Node* newNode(int hashedKey,string value,string fPath,int line){
    Node *node = new Node();
    node->key = hashedKey;
    node->filePath = fPath;
    node->lineNumber = line;

    ofstream outFile;
    outFile.open(node->filePath, ios::app);

    outFile << value << endl;

    node->left = NULL;
    node->right = NULL;
    node->height = 1;   // new node is initially added at leaf  
              
    return(node);
}
 
Node* rightRotate(Node* y){   // to right rotate subtree with root y
    Node* x = y->left;
    Node* T2 = x->right;

    // Perform rotation  
    x->right = y;
    y->left = T2;

    // Update heights  
    y->height = max(height(y->left),
        height(y->right)) + 1;
    x->height = max(height(x->left),
        height(x->right)) + 1;

    // Return new root  
    return x;
}

Node* leftRotate(Node* x){ // to left rotate subtree with root x
    Node* y = x->right;
    Node* T2 = y->left;

    // Perform rotation  
    y->left = x;
    x->right = T2;

    // Update heights  
    x->height = max(height(x->left),
        height(x->right)) + 1;
    y->height = max(height(y->left),
        height(y->right)) + 1;

    // Return new root  
    return y;
}

int getBalance(Node* N){   // to get balance factor of node N
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

//To insert a key in the subtree with root node and return new root of the subtree (recursive ftn)
Node* insert(Node* node, int key,string value,string fPath, int line){
    // 1. Perform the normal BST insertion 
    if (node == NULL)
        return(newNode(key,value,fPath,line));

    if (key < node->key)
        node->left = insert(node->left, key,value, fPath,line);
    else if (key > node->key)
        node->right = insert(node->right, key,value,  fPath, line);
    else // duplicate keys are not allowed in BST  
        return node;

    // 2. Update height of this ancestor node 
    node->height = 1 + max(height(node->left),
        height(node->right));

    // 3. Get the balance factor of this ancestor node to check if it become unbalanced
    int balance = getBalance(node);

    // If this node becomes unbalanced, then there are 4 cases

    // Left Left Case  
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    // Right Right Case  
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    // Left Right Case  
    if (balance > 1 && key > node->left->key){
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    // Right Left Case  
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    /* return the (unchanged) node pointer */
    return node;
}

// to get node with minimum key value form the tree
Node* minValueNode(Node* node){
    Node* current = node;
    /* loop down to find the leftmost leaf */
    while (current->left != NULL)
        current = current->left;
    return current;
}

Node* deleteNode(Node* root, int key){

    // STEP 1: PERFORM STANDARD BST DELETE  
    if (root == NULL)
        return root;

    // If key to be deleted is smaller than roots key then go left
    if (key < root->key)
        root->left = deleteNode(root->left, key);
  
    // If the key to be deleted is greater than roots key, go right
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
 
    // if key to be deleted equals the root's key, then this is the node to be deleted
    else {
        cout << "Deleted node\n";
        cout << "Key: " << root->key << endl;
        cout << "File: " << root->filePath << endl;
        cout << "Line No: " << root->lineNumber << endl << endl;

        string data,toDel;
        ifstream inFile;
        inFile.open(root->filePath);
  
        ofstream outFile;
        outFile.open("temp.txt");
        int line = 1;
        while (!inFile.eof()) {
            getline(inFile, data);
            if (line == root->lineNumber) {
                toDel = data;
                outFile << "" << endl;
            }
            else {
                outFile << data << endl;
            }
            line++;
        }
        inFile.close();
        outFile.close();
        string old = "temp.txt";
        remove((root->filePath).c_str());
        rename(old.c_str(), root -> filePath.c_str());

        cout << "Value: " << toDel << endl;
        inFile.close();


        // node with only one child or no child  
        if ((root->left == NULL) || (root->right == NULL)) {

            Node* temp = root->left ? root->left : root->right;

            // No child case  
            if (temp == NULL) {
                temp = root;
                root = NULL;
            }
            else // One child case  
                *root = *temp; // Copy the contents of  
                               // the non-empty child  

            free(temp);
        }
        else { 
            // For node with two children, get the smallest node in right subtree
            Node* temp = minValueNode(root->right);

            // Copy its data to this node(root)
            root->key = temp->key;

            // Delete that node whose data is copied here  
            root->right = deleteNode(root->right,temp->key);
        }
    }
      
    //if the tree has only one node 
    if (root == NULL)
        return root;

    // Step 2: update height of the current node 
    root->height = 1 + max(height(root->left),height(root->right));

    // Step 3: Get the balance factor of this ancestor node to check if it become unbalanced
    int balance = getBalance(root);

    // If this node becomes unbalanced, then there are 4 cases 

    // Left Left Case  
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    // Left Right Case  
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Right Case  
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    // Right Left Case  
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}

void preOrderSearch(Node* root,unsigned int key) {
    if (root != nullptr) {
        if (root->key == key) {
            string data;
            ifstream inFile;
            inFile.open(root->filePath);
            for (int i = 1; i <= root->lineNumber; i++) {
                getline(inFile, data);
            }
            cout << "Value: " << data << endl;
        }
        
        preOrderSearch(root->left,key);
        preOrderSearch(root->right,key);

    }
}
// To print the pre order traversal of the tree
void preOrder(Node* root){
    if (root != nullptr) {
        cout << "Key: "<<root->key << endl;
        cout << "File: " << root->filePath << endl;
        cout << "Line Number: " << root->lineNumber << endl;
        cout << endl;
        preOrder(root->left);
        preOrder(root->right);

    }
}

// While deleting a machine its data are taken using this to shift to next machine
void preOrder1(Node* root, string& str) {  // To get the key and value of of nodes
    if (root != nullptr) {
        str += "^";
        str += to_string(root->key);

        string data;
        ifstream inFile;
        inFile.open(root->filePath);
        for (int i = 1; i <= root->lineNumber; i++) {
            getline(inFile, data);
        }

        str += "*";
        str += data;

        preOrder1(root->left, str);
        preOrder1(root->right, str);
    }
}

//When new machine is added, some nodes from the successor have to shift in newMachine
void preOrder2(Node* root, string& str, unsigned int newKey) {   // to get data of the nodes to shift back
    if (root != nullptr) {
        if (root->key <= newKey) {

            str += "^";  // to indicate start of a key
            str += to_string(root->key);

            string data;
            ifstream inFile;
            inFile.open(root->filePath);
            for (int i = 1; i <= root->lineNumber; i++) {
                getline(inFile, data);
            }

            str += "*";   // to indicate start of a value
            str += data;
        }
        preOrder2(root->left, str, newKey);
        preOrder2(root->right, str, newKey);
    }
}

// To get the keys of nodes from a machine to delete them when they are copied to new machine
void preOrder3(Node* root, string& str, unsigned int newKey) {
    if (root != nullptr) {
        if (root->key <= newKey) {
            str += to_string(root->key);
            str += ',';
        }

        preOrder3(root->left, str,newKey);
        preOrder3(root->right, str,newKey);
    }
}