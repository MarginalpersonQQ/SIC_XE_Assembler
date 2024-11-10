#include "SICXE.h"

using namespace std;

class treenode {
public:
    string data;       
    string loc;        
    treenode* left = nullptr;
    treenode* right = nullptr;
};


class b_tree {
public:
    void b_treeinsert(string s, string lo);     
    void ino_show(treenode* root); 
    treenode* tree = nullptr;
}; 
b_tree btree;

void b_tree::b_treeinsert(string s, string lo) {
    treenode* newNode = new treenode();
    newNode->data = s;
    newNode->loc = lo;

    if (tree == nullptr) {
        tree = newNode;
        return;
    }

    treenode* p = tree;
    treenode* pre = nullptr;
    while (p != nullptr) {
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
    if (root != nullptr) {
        ino_show(root->left);  
        cout << "�Ÿ�: " << root->data << ", ��m: " << root->loc << endl;  
        ino_show(root->right);  
    }
}


bool FindBTree(string symbol) {
    if (btree.tree == nullptr) {
        return false;
    }
    else {
        treenode* tempnode = btree.tree;
        while (true) {
            if (tempnode->data == symbol) {
                return true;
            }
            else if (tempnode->left != nullptr && tempnode->data > symbol) {
                tempnode = tempnode->left;
            }
            else if (tempnode->right != nullptr && tempnode->data < symbol) {
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

void ShowBTree() {
    btree.ino_show(btree.tree);
}

