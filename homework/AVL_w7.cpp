#include <iostream>
using namespace std;


struct TreeNode {
    int Entry;
    int count;
    int bal; 
    TreeNode* LeftNode;
    TreeNode* RightNode;

    TreeNode(int x) : Entry(x), count(1), bal(0), LeftNode(NULL), RightNode(NULL) {}
};

typedef TreeNode* TreePointer;

class AVLTree {
private:

    void rotateLL(TreePointer &pA) {
        TreePointer pB = pA->LeftNode;
        pA->LeftNode = pB->RightNode;
        pB->RightNode = pA;
        pA->bal = 0;
        pA = pB;
    }

    void rotateRR(TreePointer &pA) {
        TreePointer pB = pA->RightNode;
        pA->RightNode = pB->LeftNode;
        pB->LeftNode = pA;
        pA->bal = 0;
        pA = pB;
    }

    void rotateLR(TreePointer &pA) {
        TreePointer pB = pA->LeftNode;
        TreePointer pC = pB->RightNode;
        pB->RightNode = pC->LeftNode;
        pC->LeftNode = pB;
        pA->LeftNode = pC->RightNode;
        pC->RightNode = pA;
        if (pC->bal == 1)
            pA->bal = -1;
        else
            pA->bal = 0;
        if (pC->bal == -1)
            pB->bal = 1;
        else
            pB->bal = 0;
        pA = pC;
        pA->bal = 0;
    }

    void rotateRL(TreePointer &pA) {
        TreePointer pB = pA->RightNode;
        TreePointer pC = pB->LeftNode;
        pB->LeftNode = pC->RightNode;
        pC->RightNode = pB;
        pA->RightNode = pC->LeftNode;
        pC->LeftNode = pA;
        if (pC->bal == -1)
            pA->bal = 1;
        else
            pA->bal = 0;
        if (pC->bal == 1)
            pB->bal = -1;
        else
            pB->bal = 0;
        pA = pC;
        pA->bal = 0;
    }


    void SearchInsert(int x, TreePointer &pA, bool &h) {
        if (pA == NULL) {
            pA = new TreeNode(x);
            h = true;
        } else if (x < pA->Entry) {
            SearchInsert(x, pA->LeftNode, h);
            if (h) {
                switch (pA->bal) {
                    case -1: pA->bal = 0; h = false; break;
                    case 0:  pA->bal = 1; break;
                    case 1:  rotateLL(pA); h = false; break;
                }
            }
        } else if (x > pA->Entry) {
            SearchInsert(x, pA->RightNode, h);
            if (h) {
                switch (pA->bal) {
                    case 1:  pA->bal = 0; h = false; break;
                    case 0:  pA->bal = -1; break;
                    case -1: rotateRR(pA); h = false; break;
                }
            }
        } else {
            pA->count++; 
        }
    }

    


    void Delete(int x, TreePointer &pA, bool &h) {
        if (pA == NULL) {
            cout << "Element not found!" << endl;
            return;
        }
        if (x < pA->Entry) {
            Delete(x, pA->LeftNode, h);
            if (h) balanceL(pA, h);
        } else if (x > pA->Entry) {
            Delete(x, pA->RightNode, h);
            if (h) balanceR(pA, h);
        } else {
            TreePointer q = pA;
            if (pA->RightNode == NULL) {
                pA = pA->LeftNode;
                h = true;
            } else if (pA->LeftNode == NULL) {
                pA = pA->RightNode;
                h = true;
            } else {
                DelMin(q, pA->RightNode, h);
                if (h) balanceR(pA, h);
            }
            delete q;
        }
    }


    void DelMin(TreePointer &q, TreePointer &r, bool &h) {
        if (r->LeftNode != NULL) {
            DelMin(q, r->LeftNode, h);
            if (h) balanceL(r, h);
        } else {
            q->Entry = r->Entry;
            q = r;
            r = r->RightNode;
            h = true;
        }
    }

    


    void balanceL(TreePointer &pA, bool &h) {
        if (pA->bal == 1) {
            pA->bal = 0;
        } else if (pA->bal == 0) {
            pA->bal = -1;
            h = false;
        } else {
            TreePointer pB = pA->RightNode;
            if (pB->bal <= 0) {
                rotateRR(pA);
                h = pB->bal == 0 ? false : true;
            } else {
                rotateRL(pA);
                h = true;
            }
        }
    }

    void balanceR(TreePointer &pA, bool &h) {
        if (pA->bal == -1) {
            pA->bal = 0;
        } else if (pA->bal == 0) {
            pA->bal = 1;
            h = false;
        } else {
            TreePointer pB = pA->LeftNode;
            if (pB->bal >= 0) {
                rotateLL(pA);
                h = pB->bal == 0 ? false : true;
            } else {
                rotateLR(pA);
                h = true;
            }
        }
    }

    
    


public:
    TreePointer root;

    AVLTree() : root(NULL) {}

    void insert(int x) {
        bool h = false;
        SearchInsert(x, root, h);
    }

    void remove(int x) {
        bool h = false;
        Delete(x, root, h);
    }
    
    bool Search(int x, TreePointer pA) {
        if (pA == NULL) {
            return false;  
        } 
        else if (x < pA->Entry) {
            return Search(x, pA->LeftNode);  
        } 
        else if (x > pA->Entry) {
            return Search(x, pA->RightNode); 
        } 
        else {
            return true; 
        }
    }

    void Display(TreePointer root, int space = 0, int indent = 4) {
    if (root == NULL)
        return;

    // Increase distance between levels
    space += indent;

    // Process right child first
    Display(root->RightNode, space);

    // Print current node after space count
    cout << endl;
    for (int i = indent; i < space; i++) {
        cout << " ";
    }
    cout << root->Entry << "(" << root->bal << ")";  // Print key and balance factor

    // Process left child
    Display(root->LeftNode, space);
    }

};

int main(){
    AVLTree tree;
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.remove(20);

    int x = 20;//queremos encontrar 20
    bool found = tree.Search(x, tree.root);

    cout << "found?" << found <<endl;

    tree.Display(tree.root);
    return 0;
}

