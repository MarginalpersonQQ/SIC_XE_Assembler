#include "SICXE.h"

using namespace std;

class treenode {
public:
    string data;       
    string loc;        
    treenode* left = NULL;   
    treenode* right = NULL; 
};


class b_tree {
public:
    void b_treeinsert(string s, string lo);     
    void ino_show(treenode* root); 
    treenode* tree = NULL; 
}; 
b_tree btree;

void b_tree::b_treeinsert(string s, string lo) {
    treenode* newNode = new treenode();
    newNode->data = s;
    newNode->loc = lo;

    if (tree == NULL) {  
        tree = newNode;
        return;
    }

    treenode* p = tree;
    treenode* pre = NULL;
    while (p != NULL) {
        pre = p;
        if (s > p->data) {
            p = p->right;  
        } 
		else if (s < p->data) {
            p = p->left;  
        } 
		else { 
            cout << "*Error* Symbol '" << s << "' already exists in the tree." << endl;
            delete newNode;
            return;
        }
    }

    
    if (s < pre->data) {
        pre->left = newNode;  
    } 
	else {
        pre->right = newNode; 
    }
}


void b_tree::ino_show(treenode* root) {
    if (root != NULL) {
        ino_show(root->left);  
        cout << "²Å¸¹: " << root->data << ", ¦ì¸m: " << root->loc << endl;  
        ino_show(root->right);  
    }
}


bool FindBTree(string symbol) {
    if (btree.tree == NULL) {
        return false;
    }
    else {
        treenode* tempnode = btree.tree;
        while (true) {
            if (tempnode->data == symbol) {
                return true;
            }
            else if (tempnode->left != NULL && tempnode->data > symbol) {
                tempnode = tempnode->left;
            }
            else if (tempnode->right != NULL && tempnode->data < symbol) {
                tempnode = tempnode->right;
            }
            else {
                return false;
            }
        }
    }
}

void InsertBTree(string symbol, string loc) {
    btree.b_treeinsert(symbol, loc);
}

