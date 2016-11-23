#include "stdio.h"
struct node
{
  int val;            //value
  struct node* left;  //left child
  struct node* right; //right child
  int ht;             //height of the node
}; 

typedef struct node node;

int height(node* N) {
  if (N == NULL) {
      return 0;
  }
  return N->ht;
}

int max(int a, int b) {
  if (a > b) {
    return a;
  }
  else {
    return b;
  }
}

node* rol(node* N) {
  node* y = N->right;
  node* T2 = y->left;

  y->left = N;
  N->right = T2;

  N->ht = max(height(N->left), height(N->right))+1;
  y->ht = max(height(y->left), height(y->right))+1;
  return y;
}

node* ror(node* N) {
  node* x = N->left;
  node* T2 = N->right;

  x->right = N;
  N->left = T2;

  N->ht = max(height(N->left), height(N->right))+1; 
  x->ht = max(height(x->left), height(x->right))+1; 
  return x;
}

int getBalance(node* N) {
  if (N == NULL) {
    return 0;
  }
  return (height(N->left) - height(N->right));
}

node* insert(node* root, int new_val) {
  if (!root) {
      root = new node();
      root->val = new_val;
      root->left = NULL;
      root->right = NULL;
      root->ht = 1;
      return root;
  }
  else {
    if (new_val < root->val) {
      root->left = insert(root->left, new_val);
    }
    else /* (new_val > root->val) */ {
      root->right = insert(root->right, new_val);
    }
    // Update height of acestor node as we come out of recursion
    root->ht = (max(height(root->left), height(root->right))) + 1;
    
    // Check the balance factor of the node to see if we need to rebalance
    int balance = getBalance(root);

    // Check the 4 cases of imbalance
    if (balance < -1 && new_val < root->left->val)
      return ror(root);
    if (balance < -1 && new_val > root->right->val) 
      return rol(root);
    if (balance > 1 && new_val > root->left->val) {
      root->left = rol(root->left);
      return ror(root);
    }
    if (balance < -1 && new_val < root->right->val) {
      root->right = ror(root->right);
      return rol(root);
    }
    return root;
     
  }
}


void display(node* root) {
  if (root) {
    printf("%d", root->val);
    display(root->left);
    display(root->right);
  }
}

int main() {
  node* root = NULL;
  root = insert(root, 10);
  root = insert(root, 20);
  root = insert(root, 30);
  root = insert(root, 40);
  root = insert(root, 50);
  root = insert(root, 25);
}

