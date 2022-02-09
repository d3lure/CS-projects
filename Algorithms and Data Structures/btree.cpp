#include <iostream>
#include <cstring>
#include <algorithm>
//#include <stdio.h>
#include <sstream>
using namespace std;
  
class Node {
    Node **childs; 
    int num_keys;
    bool leaf;  //true when node is leaf, otherwise false  
    int *keys;  // array of keys
    int t;      // order t of the tree

public:
    Node(int t, bool is_leaf);
    ~Node();
    Node* search(int key);
    void save();
    void print_all();
    void insert_when_not_full(int new_key);
    void split_node(int index, Node *child);
    
friend class BTree;
};

class BTree {
    Node *root;
    int t;  // degree/order of the tree

public:
    
    BTree(int order) {  
        root = NULL;
        t = order;
    }

    ~BTree();
  
    void print_all() {   
        if(root != NULL) root->print_all();
    }
  
    Node* search(int key) {  
        if (root == NULL) return NULL;
        else return root->search(key);
    }

    void insert(int new_key);

    void save() {
        cout << this->t << endl;
        this->root->save();
        cout << endl;
    }

    void load(int order, string tree);
};
  
Node::Node(int t, bool is_leaf) {
   
    this->t = t;
    this->leaf = is_leaf;

    this->keys = new int[2*t-1];
    this->childs = new Node* [2*t];
  
    this->num_keys = 0;
}

BTree::~BTree() {
    delete root;
}

Node::~Node() {
    delete[] keys;
    delete[] childs;
}

void BTree::insert(int new_key) {
    if (root != NULL) {   
        if (root->num_keys == 2*t-1) {
            
            Node *new_root = new Node(t, false);
            new_root->childs[0] = root;
  
            // split the old root and move 1 key to the new root
            new_root->split_node(0, root);
  
            //find place for new key
            int i = 0;
            if (new_root->keys[0] < new_key) i++;
            new_root->childs[i]->insert_when_not_full(new_key);
            root = new_root;
        }
        else {
            root->insert_when_not_full(new_key);
        } 
    }
    else {
        root = new Node(t, true);
        root->keys[0] = new_key;
        root->num_keys = 1;
    }
}
  
void Node::insert_when_not_full(int new_key) {
    
    //start from end
    int index = num_keys-1;
  
    if (leaf == false) {
        while (index >= 0 && keys[index] > new_key) index--;
  
        // check if the found child is full
        if (childs[index+1]->num_keys == 2*t-1) {
            split_node(index+1, childs[index+1]);
            if (keys[index+1] < new_key) index++;
        }
        childs[index+1]->insert_when_not_full(new_key);
    }
    else {
        // find index where new_key can be inserted
        while (index >= 0 && keys[index] > new_key) {
            keys[index+1] = keys[index];
            index--;
        }
        keys[index+1] = new_key;
        num_keys++;
    }
}

//split a full child of a node
void Node::split_node(int index, Node *child) {

    Node *new_node = new Node(child->t, child->leaf);
    new_node->num_keys = t - 1;
    
    //move second half of keys and childs to new_node
    for (int i = 0; i < t-1; i++) {
        new_node->keys[i] = child->keys[i+t];
    }
    if (child->leaf == false) {
        for (int i = 0; i < t; i++) {
            new_node->childs[i] = child->childs[i+t];
        }      
    }
    child->num_keys = t - 1;
  
    // create space for new child and mid key
    for (int i = num_keys; i >= index+1; i--) {
        childs[i+1] = childs[i];
    }
    childs[index+1] = new_node;
    
    for (int i = num_keys-1; i >= index; i--) {
        keys[i+1] = keys[i];
    } 

    //middle key of child goes to this node
    keys[index] = child->keys[t-1];
    num_keys++;
}

Node *Node::search(int key) {
    int i = 0;
    while (i < num_keys && key > keys[i]) i++;
    if (keys[i] == key) return this;
    if (leaf == true) return NULL;
    return this->childs[i]->search(key);
}

void Node::print_all() {
    int i;
    for (i = 0; i < this->num_keys; i++) {
        if (leaf == false) childs[i]->print_all();
        cout << keys[i] << " ";
    }
    //print last child's subtree
    if (leaf == false) childs[i]->print_all();
}
  
void Node::save() {
    int i;
    for (i = 0; i < this->num_keys; i++) {
        if(i==0) cout << "( ";
        if (leaf == false) {
            childs[i]->save();
            cout << keys[i] << " ";
            
        }
        else {
            cout << keys[i] << " ";
            if(i==num_keys-1) cout << ") ";
        }
    }
    if (leaf == false) {
        childs[i]->save();
        if(i==num_keys) cout << ") ";
    }
}

void BTree::load(int order, string tree) {
    this->root = NULL;
    this->t = order;
    int* nums = new int[tree.length()];

    tree.erase(remove(tree.begin(), tree.end(), ')'), tree.end());
    tree.erase(remove(tree.begin(), tree.end(), '('), tree.end());

    char* arr = new char[tree.length()];
    strcpy(arr, tree.c_str());

    int i = 0;
    char *token = strtok(arr, " ");
    do {
        nums[i] = atoi(token);
        i++;
    } while(token = strtok(NULL, " "));

    for(int j = i-1; j>=i/2; j--) insert(nums[j]);
    for(int j = 0; j<i/2; j++) insert(nums[j]);

    delete[] arr, nums;

} 

int main() {
    char command;
    string tree_format;
    BTree btree = BTree(0);

    while(cin>>command) {
        int x;
        switch(command) {
            case 'I': {
                cin >> x;
                btree = BTree(x);
                break;
            }
            case 'A': {
                cin>>x;
                btree.insert(x);
                break;
            }
            case '?': {
                cin>>x;
                if (btree.search(x) != NULL) cout << x << " +\n" ;
                else cout << x << " -\n";
                break;
            }
            case 'P': {
                btree.print_all();
                putchar('\n');
                break;
            }
            case 'S': {
                btree.save();
                break;
            }
            case 'L': {
                cin >> x;
                getline(cin, tree_format);
                getline(cin, tree_format);
                btree.load(x, tree_format);
                break;
            }
            case '#': break;
            case 'X': return 0;
        }
    }
    return 0;
}



