// cards.cpp
// Authors: Collin Qian
// Implementation of the classes defined in cards.h

#include <iostream>
#include "cards.h"
using namespace std;

CardsBST::CardsBST() : root(nullptr) {}

CardsBST::~CardsBST()
{
    clear(root);
}

void CardsBST::clear(cardNode *root)
{
    if (root)
    {
        clear(root->left);
        clear(root->right);
        delete root;
    }
}

void CardsBST::insert(Cards c)
{
    if (!root)
    {
        root = new cardNode(c);
        return;
    }
    return insert(c, root);
}

void CardsBST::insert(Cards c, cardNode *p)
{
    if (p->card == c)
        return;
    if (c < p->card)
    {
        if (p->left)
            insert(c, p->left);
        else
        {
            cardNode *temp = new cardNode(c);
            p->left = temp;
            temp->parent = p;
            return;
        }
    }
    else
    {
        if (p->right)
            insert(c, p->right);
        else
        {
            cardNode *temp = new cardNode(c);
            p->right = temp;
            temp->parent = p;
            return;
        }
    }
}

void CardsBST::remove(Cards c)
{
    cardNode *p = findNode(c, this->root);
    if (!p)
        return;

    cardNode *parent = nullptr;
    if (p->parent)
        parent = p->parent;

    if (p->left == nullptr && p->right == nullptr)
    {
        // " << endl;
        if (p != root)
        {
            if (parent->right == p)
            {
                // cout << " p is right child " << endl;
                if (parent == root)
                {
                    root->right = nullptr;
                }
                parent->right = nullptr;
            }
            else
            {
                // cout << " p is left child " << endl;
                // parent->card.printCard();
                if (parent == root)
                {
                    root->left = nullptr;
                }
                parent->left = nullptr;
            }
        }
        else
        {
            root = nullptr;
        }

        delete p;
    }

    else if (p->left != nullptr && p->right != nullptr)
    {
        // cout << " two children " << endl;
        cardNode *succ = getSuccessorNode(p->card);
        Cards z = succ->card;
        remove(succ->card);
        p->card = z;
        return;
    }

    else
    {
        // cout << " one child " << endl;
        cardNode *replace;

        if (p->left == nullptr)
        {
            // cout << " one child is right child  " << endl;
            replace = p->right;
            cardNode *replaceparent = nullptr;
            while (replace->left)
            {
                replaceparent = replace;
                replace = replace->left;
            }
            if (replaceparent != nullptr)
            {
                Cards newCard = replace->card;
                remove(replace->card);
                p->card = newCard;
                return;
            }
            else
            {
                if (root == p)
                {
                    root = replace;
                    p->right = nullptr;
                    replace->parent = nullptr;
                    delete p;
                    return;
                }
            }
        }
        else
        {
            // " one child is left child  " << endl;
            replace = p->left;
            if (root == p)
            {
                root = replace;
                p->left = nullptr;
                replace->parent = nullptr;
                delete p;
                return;
            }
        }

        if (p == parent->left)
        {
            parent->left = replace;
        }
        else
        {
            parent->right = replace;
        }
        replace->parent = parent;
        delete p;
    }
    return;
}

bool CardsBST::contains(Cards c)
{
    if (this->findNode(c, this->root) == nullptr)
        return false;
    else
        return true;
}

void CardsBST::printInOrder()
{
    printInOrder(this->root);
}

void CardsBST::printInOrder(cardNode *root)
{
    if (root)
    {
        printInOrder(root->left);
        root->card.printCard();
        printInOrder(root->right);
    }
}

void CardsBST::printPreOrder()
{
    printPreOrder(this->root);
}

void CardsBST::printPreOrder(cardNode *root)
{
    if (root)
    {
        root->card.printCard();
        printPreOrder(root->left);
        printPreOrder(root->right);
    }
}

CardsBST::cardNode *CardsBST::getSuccessorNode(Cards c)
{
    // find node. check if it has a ->left. if not, find the last ->right.

    cardNode *p = this->findNode(c, this->root);
    if (!p)
    {
        // cout << "Node not found" << endl;
        return nullptr;
    }

    else
    {
        // cout << "Else" << endl;
        if (!p->parent && !p->right)
        {
            // cout << "case 1" << endl;
            return nullptr;
        }

        if (c == findMax())
        {
            return nullptr;
        }

        if (p->right)
        {
            // cout << "case 3" << endl;
            p = p->right;
            while (p->left)
            {
                p = p->left;
            }
            return p;
        }
        else if (p->parent->left == p)
        {
            // cout << "case 4" << endl;
            return p->parent;
        }
        else
        {
            // cout << "case 5" << endl;
            cardNode *n = p->parent;
            while (p->card > n->card)
            {
                n = n->parent;
            }
            return n;
        }
    }
}

Cards CardsBST::getSuccessor(Cards c)
{
    // cout << "getSuccessor progress" << endl;
    cardNode *p = getSuccessorNode(c);
    // cout << "getSuccessorNode Passed" << endl;
    Cards x;
    if (!p)
    {
        // cerr << "No Successor Found!" << endl;
        return x;
    }
    else
        return p->card;
}

CardsBST::cardNode *CardsBST::getPredecessorNode(Cards c)
{
    cardNode *p = this->findNode(c, this->root);
    if (!p)
    {
        return nullptr;
    }

    if (c == findMin())
        return nullptr;

    else
    {
        if (p->left)
        {
            p = p->left;
            while (p->right)
            {
                p = p->right;
            }
            return p;
        }
        // right child
        else if (p->parent->right == p)
        {
            return p->parent;
        }
        // left child
        else
        {
            cardNode *n = p->parent;
            while (p->card < n->card)
            {
                n = n->parent;
            }
            return n;
        }
    }
}

Cards CardsBST::getPredecessor(Cards c)
{
    cardNode *p = this->getPredecessorNode(c);
    Cards x;
    if (!p)
    {
        // cerr << "No Predecessor Found!" << endl;
        return x;
    }
    else
        return p->card;
}

// private functions
CardsBST::cardNode *CardsBST::findNode(Cards c, cardNode *p)
{
    while (p)
    {
        if (c == p->card)
        {
            return p;
        }
        else if (c > p->card)
        {
            p = p->right;
        }
        else if (c < p->card)
        {
            p = p->left;
        }
    }
    return nullptr;
}

CardsBST::cardNode *CardsBST::minNode()
{
    cardNode *p = this->root;
    while (p && p->left)
    {
        p = p->left;
    }
    return p;
}

Cards CardsBST::findMin()
{
    cardNode *p = minNode();
    return p->card;
}

CardsBST::cardNode *CardsBST::maxNode()
{
    cardNode *p = this->root;
    while (p && p->right)
    {
        p = p->right;
    }
    return p;
}
Cards CardsBST::findMax()
{
    cardNode *p = maxNode();
    return p->card;
}