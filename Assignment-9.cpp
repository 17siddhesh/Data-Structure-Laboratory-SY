/*Implement binary search tree and perform following operations: a) Insert (Handle insertion of duplicate entry) b) Delete c) Search d) Display tree (Traversal) e) Display - Depth of tree f) Display - Mirror image g) Create a copy h) Display all parent nodes with their child nodes i) Display leaf nodes j) Display tree level wise.*/
#include <iostream>
using namespace std;

// Node structure for BST
struct Node {
    int key;         // data value
    int count;       // to handle duplicates
    Node* left;      // left child
    Node* right;     // right child
};

// Create a new node
Node* createNode(int key) {
    Node* n = new Node;
    n->key = key;
    n->count = 1;
    n->left = NULL;
    n->right = NULL;
    return n;
}

// Insert a node (handles duplicates by increasing count)
Node* insertNode(Node* root, int key) {
    if (root == NULL) return createNode(key);
    if (key < root->key)
        root->left = insertNode(root->left, key);
    else if (key > root->key)
        root->right = insertNode(root->right, key);
    else
        root->count++;
    return root;
}

// Find minimum value node in a subtree
Node* findMin(Node* root) {
    while (root && root->left != NULL) root = root->left;
    return root;
}

// Delete a node from the BST
Node* deleteNode(Node* root, int key) {
    if (root == NULL) return NULL;

    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else {
        // If duplicate exists, just decrement count
        if (root->count > 1) {
            root->count--;
            return root;
        }

        // Node with no child
        if (root->left == NULL && root->right == NULL) {
            delete root;
            return NULL;
        }
        // Node with one child
        else if (root->left == NULL) {
            Node* temp = root->right;
            delete root;
            return temp;
        }
        else if (root->right == NULL) {
            Node* temp = root->left;
            delete root;
            return temp;
        }
        // Node with two children
        else {
            Node* succ = findMin(root->right);
            root->key = succ->key;
            root->count = succ->count;
            root->right = deleteNode(root->right, succ->key);
        }
    }
    return root;
}

// Search for a value in BST
Node* searchNode(Node* root, int key) {
    if (root == NULL) return NULL;
    if (key == root->key) return root;
    if (key < root->key) return searchNode(root->left, key);
    return searchNode(root->right, key);
}

// Inorder traversal (LNR)
void inorder(Node* root) {
    if (root == NULL) return;
    inorder(root->left);
    cout << root->key;
    if (root->count > 1) cout << "(" << root->count << ")";
    cout << " ";
    inorder(root->right);
}

// Preorder traversal (NLR)
void preorder(Node* root) {
    if (root == NULL) return;
    cout << root->key;
    if (root->count > 1) cout << "(" << root->count << ")";
    cout << " ";
    preorder(root->left);
    preorder(root->right);
}

// Postorder traversal (LRN)
void postorder(Node* root) {
    if (root == NULL) return;
    postorder(root->left);
    postorder(root->right);
    cout << root->key;
    if (root->count > 1) cout << "(" << root->count << ")";
    cout << " ";
}

// Calculate height (depth) of the tree
int height(Node* root) {
    if (root == NULL) return 0;
    int lh = height(root->left);
    int rh = height(root->right);
    if (lh > rh)
        return lh + 1;
    else
        return rh + 1;
}

// Create a mirror copy of the tree
Node* mirrorCopy(Node* root) {
    if (root == NULL) return NULL;
    Node* n = createNode(root->key);
    n->count = root->count;
    n->left = mirrorCopy(root->right);
    n->right = mirrorCopy(root->left);
    return n;
}

// Create a deep copy of the tree
Node* copyTree(Node* root) {
    if (root == NULL) return NULL;
    Node* n = createNode(root->key);
    n->count = root->count;
    n->left = copyTree(root->left);
    n->right = copyTree(root->right);
    return n;
}

// Display parent nodes with their children
void displayParents(Node* root) {
    if (root == NULL) return;
    if (root->left != NULL || root->right != NULL) {
        cout << "Parent " << root->key << " -> ";
        if (root->left) cout << "L:" << root->left->key << " ";
        if (root->right) cout << "R:" << root->right->key << " ";
        cout << "\n";
    }
    displayParents(root->left);
    displayParents(root->right);
}

// Display all leaf nodes
void displayLeaves(Node* root) {
    if (root == NULL) return;
    if (root->left == NULL && root->right == NULL) {
        cout << root->key;
        if (root->count > 1) cout << "(" << root->count << ")";
        cout << " ";
    }
    displayLeaves(root->left);
    displayLeaves(root->right);
}

// Display tree level-wise using array queue
void levelOrder(Node* root) {
    if (root == NULL) {
        cout << "Tree empty.\n";
        return;
    }
    Node* q[200];
    int front = 0, rear = 0;
    q[rear++] = root;

    while (front < rear) {
        Node* cur = q[front++];
        cout << cur->key;
        if (cur->count > 1) cout << "(" << cur->count << ")";
        cout << " ";
        if (cur->left) q[rear++] = cur->left;
        if (cur->right) q[rear++] = cur->right;
    }
    cout << "\n";
}

// Free all nodes (to avoid memory leak)
void freeTree(Node* root) {
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    delete root;
}

int main() {
    Node* root = NULL;
    int choice, key;

    do {
        cout << "\n=== BINARY SEARCH TREE MENU ===\n";
        cout << "1. Insert\n";
        cout << "2. Delete\n";
        cout << "3. Search\n";
        cout << "4. Display Traversals\n";
        cout << "5. Display Depth (Height)\n";
        cout << "6. Display Mirror Image\n";
        cout << "7. Create a Copy\n";
        cout << "8. Display Parent -> Child Nodes\n";
        cout << "9. Display Leaf Nodes\n";
        cout << "10. Display Level Wise\n";
        cout << "11. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter key to insert: ";
                cin >> key;
                root = insertNode(root, key);
                cout << "Inserted " << key << ".\n";
                break;

            case 2:
                cout << "Enter key to delete: ";
                cin >> key;
                if (searchNode(root, key) == NULL)
                    cout << "Key not found.\n";
                else {
                    root = deleteNode(root, key);
                    cout << "Deleted (or decremented count) " << key << ".\n";
                }
                break;

            case 3:
                cout << "Enter key to search: ";
                cin >> key;
                if (searchNode(root, key))
                    cout << "Found " << key << ".\n";
                else
                    cout << "Not found.\n";
                break;

            case 4:
                cout << "Inorder: ";
                inorder(root);
                cout << "\nPreorder: ";
                preorder(root);
                cout << "\nPostorder: ";
                postorder(root);
                cout << "\n";
                break;

            case 5:
                cout << "Tree Depth: " << height(root) << "\n";
                break;

            case 6: {
                Node* mirror = mirrorCopy(root);
                cout << "Mirror (Inorder): ";
                inorder(mirror);
                cout << "\n";
                freeTree(mirror);
                break;
            }

            case 7: {
                Node* cp = copyTree(root);
                cout << "Copy (Inorder): ";
                inorder(cp);
                cout << "\n";
                freeTree(cp);
                break;
            }

            case 8:
                cout << "Parent -> Children:\n";
                displayParents(root);
                break;

            case 9:
                cout << "Leaf nodes: ";
                displayLeaves(root);
                cout << "\n";
                break;

            case 10:
                cout << "Level wise: ";
                levelOrder(root);
                break;

            case 11:
                cout << "Exiting...\n";
                break;

            default:
                cout << "Invalid choice.\n";
                break;
        }

    } while (choice != 11);

    freeTree(root);
    return 0;
}
