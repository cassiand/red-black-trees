// cassian
// 11/26/22
// week 12 assignment
// red black trees

#include <iostream>
#include <queue>

using namespace std;

enum Color { RED, BLACK };

struct Node
{
    int data;
    bool color;
    Node* left, * right, * parent;

    // Constructor
    Node(int data)
    {
        this->data = data;
        left = right = parent = NULL;
        this->color = RED;
    }
};

// red black tree class
class RedBlackTree
{
private:
    Node* root;
protected:
    void rotateLeft(Node*&, Node*&);
    void rotateRight(Node*&, Node*&);
    void fixViolation(Node*&, Node*&);
public:
    // Constructor
    RedBlackTree() { root = NULL; }
    void insert(const int& n);
    void inorder();
    void levelOrder();
};

// function for inorder traversal
void inorderHelper(Node* root)
{
    if (root == NULL)
        return;

    inorderHelper(root->left);
    cout << root->data << "  ";
    inorderHelper(root->right);
}

// function to insert a new node with given key
Node* BSTInsert(Node* root, Node* pt)
{
    // if tree is empty, return a new node
    if (root == NULL)
        return pt;

    // Otherwise, go down  tree
    if (pt->data < root->data)
    {
        root->left = BSTInsert(root->left, pt);
        root->left->parent = root;
    }
    else if (pt->data > root->data)
    {
        root->right = BSTInsert(root->right, pt);
        root->right->parent = root;
    }

    /* return the (unchanged) node pointer */
    return root;
}

// function for level order traversal
void levelOrderHelper(Node* root)
{
    if (root == NULL)
        return;

    queue<Node*> q;
    q.push(root);

    while (!q.empty())
    {
        Node* temp = q.front();
        cout << temp->data << "  ";
        q.pop();

        if (temp->left != NULL)
            q.push(temp->left);

        if (temp->right != NULL)
            q.push(temp->right);
    }
}

void RedBlackTree::rotateLeft(Node*& root, Node*& pt)
{
    Node* pt_right = pt->right;

    pt->right = pt_right->left;

    if (pt->right != NULL)
        pt->right->parent = pt;

    pt_right->parent = pt->parent;

    if (pt->parent == NULL)
        root = pt_right;

    else if (pt == pt->parent->left)
        pt->parent->left = pt_right;

    else
        pt->parent->right = pt_right;

    pt_right->left = pt;
    pt->parent = pt_right;
}

void RedBlackTree::rotateRight(Node*& root, Node*& pt)
{
    Node* pt_left = pt->left;

    pt->left = pt_left->right;

    if (pt->left != NULL)
        pt->left->parent = pt;

    pt_left->parent = pt->parent;

    if (pt->parent == NULL)
        root = pt_left;

    else if (pt == pt->parent->left)
        pt->parent->left = pt_left;

    else
        pt->parent->right = pt_left;

    pt_left->right = pt;
    pt->parent = pt_left;
}

// function to fix rule breaks after BST insertion
void RedBlackTree::fixViolation(Node*& root, Node*& pt)
{
    Node* parent_pt = NULL;
    Node* grand_parent_pt = NULL;

    while ((pt != root) && (pt->color != BLACK) &&
        (pt->parent->color == RED))
    {

        parent_pt = pt->parent;
        grand_parent_pt = pt->parent->parent;

        /*  Case : A
            Parent of pt is left child
            of Grand-parent of pt */
        if (parent_pt == grand_parent_pt->left)
        {

            Node* uncle_pt = grand_parent_pt->right;

            /* Case : 1
               The uncle of pt is also red
               Only Recoloring required */
            if (uncle_pt != NULL && uncle_pt->color ==
                RED)
            {
                grand_parent_pt->color = RED;
                parent_pt->color = BLACK;
                uncle_pt->color = BLACK;
                pt = grand_parent_pt;
            }

            else
            {
                /* Case : 2
                   pt is right child of its parent
                   Left-rotation required */
                if (pt == parent_pt->right)
                {
                    rotateLeft(root, parent_pt);
                    pt = parent_pt;
                    parent_pt = pt->parent;
                }

                /* Case : 3
                   pt is left child of its parent
                   Right-rotation required */
                rotateRight(root, grand_parent_pt);
                swap(parent_pt->color,
                    grand_parent_pt->color);
                pt = parent_pt;
            }
        }

        /* Case : B
           Parent of pt is right child
           of Grand-parent of pt */
        else
        {
            Node* uncle_pt = grand_parent_pt->left;

            /*  Case : 1
                The uncle of pt is also red
                Only Recoloring required */
            if ((uncle_pt != NULL) && (uncle_pt->color ==
                RED))
            {
                grand_parent_pt->color = RED;
                parent_pt->color = BLACK;
                uncle_pt->color = BLACK;
                pt = grand_parent_pt;
            }
            else
            {
                /* Case : 2
                   pt is left child of its parent
                   Right-rotation required */
                if (pt == parent_pt->left)
                {
                    rotateRight(root, parent_pt);
                    pt = parent_pt;
                    parent_pt = pt->parent;
                }

                /* Case : 3
                   pt is right child of its parent
                   Left-rotation required */
                rotateLeft(root, grand_parent_pt);
                swap(parent_pt->color,
                    grand_parent_pt->color);
                pt = parent_pt;
            }
        }
    }

    root->color = BLACK;
}

// Function to insert a new node with given data
void RedBlackTree::insert(const int& data)
{
    Node* pt = new Node(data);

    //  normal BST insert
    root = BSTInsert(root, pt);

    // fix Red Black Tree violations
    fixViolation(root, pt);
}

// function to do inorder and level order traversals
void RedBlackTree::inorder() { inorderHelper(root); }
void RedBlackTree::levelOrder() { levelOrderHelper(root); }

// Driver Code
int main()
{
    RedBlackTree tree;

    tree.insert(30);
    tree.insert(28);
    tree.insert(21);
    tree.insert(11);
    tree.insert(17);
    tree.insert(4);


    cout << "Inorder Traversal of Created Tree\n";
    tree.inorder();

    cout << "\n\nLevel Order Traversal of Created Tree\n";
    tree.levelOrder();

    return 0;
}




