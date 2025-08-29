#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
class node{
  public :
  int data;
  node* left;
  node* right;
  
  node(int value){
      data = value;
      left = NULL;
      right = NULL;
  }
};
node* buildTree(vector<int>& arr ,int& id){
    id++;
    if(id >= arr.size() || arr[id]==(-1) ) {return NULL;}
    node* newnode = new node(arr[id]);
    newnode->left = buildTree(arr,id);
    newnode->right = buildTree(arr,id);
    return newnode;
}
void inorder(node* root){
    if(root==NULL) return ;
    inorder(root->left);
    cout << root->data << endl;
    inorder(root->right);
}
void preorder(node* root){
    if(root==NULL) return ;
    cout << root->data << endl;
    preorder(root->left);
    preorder(root->right);
}
void postorder(node* root){
    if(root==NULL) return ;
    postorder(root->left);
    postorder(root->right);
    cout << root->data << endl;
}
void levalorder(node* root){
    if(root==NULL) return ;
    queue<node*> q;
    q.push(root);
    while(!q.empty()){
        node* curr = q.front();
        q.pop();
        cout << curr->data << endl;
        if(curr->left!=NULL) q.push(curr->left);
        if(curr->right!=NULL) q.push(curr->right);
    }
}
void levalorder_printlevalwise(node* root){
    if(root==NULL) return ;
    queue<node*> q;
    q.push(root);
    while(!q.empty()){
        int size = q.size();
        for(int i = 0;i<size;i++){
        node* curr = q.front();
        q.pop();
        cout << curr->data << " ";
        if(curr->left!=NULL) q.push(curr->left);
        if(curr->right!=NULL) q.push(curr->right);
        }
        cout << endl;
    }
}
void levalorder_maxlevalwise(node* root){
    if(root==NULL) return ;
    queue<node*> q;
    q.push(root);
    while(!q.empty()){
        int size = q.size();
        int levalmax = 0;
        for(int i = 0;i<size;i++){
        node* curr = q.front();
        q.pop();
        levalmax = max(curr->data,levalmax);
        if(curr->left!=NULL) q.push(curr->left);
        if(curr->right!=NULL) q.push(curr->right);
        }
        cout << levalmax <<endl;
    }
}
void deleteDeepest(Node* root, Node* d_node) {
    queue<Node*> q;
    q.push(root);

    while (!q.empty()) {
        Node* temp = q.front();
        q.pop();

        if (temp->left) {
            if (temp->left == d_node) {
                temp->left = nullptr;
                delete d_node;
                return;
            } else {
                q.push(temp->left);
            }
        }

        if (temp->right) {
            if (temp->right == d_node) {
                temp->right = nullptr;
                delete d_node;
                return;
            } else {
                q.push(temp->right);
            }
        }
    }
}
Node* deleteNode(Node* root, int key) {
    if (root == nullptr) return nullptr;

    // Special case: only one node and it's the one to delete
    if (root->left == nullptr && root->right == nullptr) {
        if (root->data == key) {
            delete root;
            return nullptr;
        } else {
            return root;
        }
    }

    Node* key_node = nullptr;
    Node* temp;
    queue<Node*> q;
    q.push(root);

    // Level Order Traversal
    while (!q.empty()) {
        temp = q.front();
        q.pop();

        if (temp->data == key)
            key_node = temp;  // target node

        if (temp->left)
            q.push(temp->left);
        if (temp->right)
            q.push(temp->right);
    }
    
    if (key_node != nullptr) {
        int x = temp->data;            // deepest node's value
        deleteDeepest(root, temp);     // delete deepest node
        key_node->data = x;            // copy value to target
    }

    return root;
}
// find min value node in a BST (used in case 3 of deletion)
node* findmin(node* root) {
    while (root && root->left != NULL)
        root = root->left;
    return root;
}

// BST deletion function
node* deletenode_bst(node* root, int key) {
    if (root == NULL) return NULL;

    if (key < root->data) {
        root->left = deletenode_bst(root->left, key);
    }
    else if (key > root->data) {
        root->right = deletenode_bst(root->right, key);
    }
    else {
        // found the node
        // case 1: no child
        if (root->left == NULL && root->right == NULL) {
            delete root;
            return NULL;
        }
        // case 2: one child
        else if (root->left == NULL) {
            node* temp = root->right;
            delete root;
            return temp;
        }
        else if (root->right == NULL) {
            node* temp = root->left;
            delete root;
            return temp;
        }
        // case 3: two children
        else {
            node* temp = findmin(root->right);
            root->data = temp->data;
            root->right = deletenode_bst(root->right, temp->data);
        }
    }

    return root;
}
,
int main() {
    vector<int> arr = {1, 2, 4, -1, -1, 5, -1, -1, 3, -1, 6, -1, -1};
    int idx = -1;
    node* root = buildTree(arr, idx);
    levalorder_maxlevalwise(root);
    return 0;
} 