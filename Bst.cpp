//implemntation of binary tree
#include <iostream>
#include <queue>
#include <climits>

class BstNode
{
public:
    int data;
    BstNode *left;
    BstNode *right;
    BstNode(int data)
    {
        this->data = data;
        this->left = NULL;
        this->right = NULL;
    }
};

BstNode *push(BstNode *root, int data)
{
    if (root == NULL)
    {
        root = new BstNode(data);
    }
    else if (data <= root->data)
    {
        root->left = push(root->left, data);
    }
    else
    {
        root->right = push(root->right, data);
    }
    return root;
}

bool Search(BstNode *root, int data)
{
    if (root == NULL)
    {
        return false;
    }
    else if (root->data == data)
    {
        return true;
    }
    else if (data <= root->data)
    {
        return Search(root->left, data);
    }
    else
    {
        return Search(root->right, data);
    }
}

void levelOrder(BstNode *root)
{
    if (root == NULL)
        return;

    std::queue<BstNode *> Q;
    Q.push(root);
    while (!Q.empty())
    {
        std::cout << Q.front()->data << " ";
        if (Q.front()->left != NULL)
            Q.push(Q.front()->left);
        if (Q.front()->right != NULL)
            Q.push(Q.front()->right);
        Q.pop();
    }
}

void preOrder(BstNode *root)
{
    if (root == NULL)
        return;
    std::cout << root->data << " ";
    preOrder(root->left);
    preOrder(root->right);
}

void inOrder(BstNode *root)
{
    if (root == NULL)
        return;
    inOrder(root->left);
    std::cout << root->data << " ";
    inOrder(root->right);
}

void postOrder(BstNode *root)
{
    if (root == NULL)
        return;
    postOrder(root->left);
    postOrder(root->right);
    std::cout << root->data << " ";
}

bool isBinarySearchTree(BstNode *root, int min = INT_MIN, int max = INT_MAX)
{
    if (root == NULL)
        return true;

    if (root->data >= min && root->data < max &&
        isBinarySearchTree(root->left, min, root->data) &&
        isBinarySearchTree(root->right, root->data + 1, max))
        return true;
    else
        return false;
}

BstNode *findMin(BstNode *root)
{
    if (root == NULL || root->left == NULL)
        return root;
    findMin(root->left);
}

BstNode *deleteNode(BstNode *root, int data)
{
    if (root == NULL)
        return root;
    else if (data < root->data)
        root->left = deleteNode(root->left, data);
    else if (data > root->data)
        root->right = deleteNode(root->right, data);
    else
    {
        if (root->left == NULL && root->right == NULL)
        {
            BstNode *temp = root;
            delete temp;
            root = NULL;
        }
        else if (root->left == NULL)
        {
            BstNode *temp = root;
            root = root->right;
            delete temp;
        }
        else if (root->right == NULL)
        {
            BstNode *temp = root;
            root = root->left;
            delete temp;
        }
        else
        {
            BstNode *temp = findMin(root->right);
            root->data = temp->data;
            root->right = deleteNode(root->right, temp->data);
        }
    }

    return root;
}

BstNode *deleteTree(BstNode *root)
{
    if (root == NULL)
        return root;

    root->left = deleteTree(root->left);
    root->right = deleteTree(root->right);
    BstNode *temp = root;
    delete temp;
    root = NULL;

    return root;
}

BstNode *findNode(BstNode *root, int data)
{
    if (root == NULL)
        return NULL;
    else if (data == root->data)
        return root;
    else if (data > root->data)
        return findNode(root->right, data);
    else
        return findNode(root->left, data);
}

BstNode *findSuccessor(BstNode *root, int data)
{
    BstNode *current = findNode(root, data);
    if (current == NULL)
        return NULL;
    else if (current->right != NULL)
    {
        return findMin(current->right);
    }
    else
    {
        BstNode *ancestor = root;
        BstNode *successor = NULL;
        while (current != ancestor)
        {
            if (current->data <= ancestor->data)
            {
                successor = ancestor;
                ancestor = ancestor->left;
            }
            else
                ancestor = ancestor->right;
        }
        return successor;
    }
}

int main()
{
    BstNode *root = NULL;
    root = push(root, 15);
    root = push(root, 20);
    root = push(root, 10);
    root = push(root, 5);
    root = push(root, 12);

    std::cout << std::boolalpha << Search(root, 10);
    std::cout << "\n";
    std::cout << std::boolalpha << Search(root, 130);
    std::cout << "\n";

    std::cout << "Level Order: ";
    levelOrder(root);
    std::cout << "\n";
    std::cout << "Pre Order:   ";
    preOrder(root);
    std::cout << "\n";
    std::cout << "In Order:    ";
    inOrder(root);
    std::cout << "\n";
    std::cout << "Post Order:  ";
    postOrder(root);
    std::cout << "\n";

    std::cout << std::boolalpha << isBinarySearchTree(root);
    std::cout << "\n";

    std::cout << "Successor of 5: " << findSuccessor(root, 5)->data;
    std::cout << "\n";

    std::cout << "Successor of 12: " << findSuccessor(root, 12)->data;
    std::cout << "\n";

    std::cout << "Level Order(before deletion): ";
    levelOrder(root);
    std::cout << "\n";

    deleteNode(root, 10);

    std::cout << "Level Order(after deletion): ";
    levelOrder(root);
    std::cout << "\n";

    root->left = deleteTree(root->left);

    std::cout << "Level Order(after left sub-tree deletion): ";
    levelOrder(root);
    std::cout << "\n";

    return 0;
}
