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
b_tree tree;

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


void FindBTree(string symbol) {
    if (tree == NULL) {
        return false;
    }
}

void InsertBTree(string symbol, string loc) {
    tree.b_treeinsert(symbol, loc);
}

