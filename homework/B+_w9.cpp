#include <iostream>

using namespace std;

const int MAX_KEYS = 3;

struct BPlusNode {
    int keys[MAX_KEYS];
    BPlusNode* children[MAX_KEYS + 1];
    int keyCount;
    bool isLeaf;

    BPlusNode(bool leaf) {
        isLeaf = leaf;
        keyCount = 0;
        for (int i = 0; i <= MAX_KEYS; i++) {
            children[i] = nullptr;
        }
    }
};

class BPlusTree {
    BPlusNode* root;

public:
    BPlusTree() {
        root = new BPlusNode(true);
    }

    bool search(int key) {
        BPlusNode* cursor = root;
        while (cursor != nullptr) {
            int i = 0;
            while (i < cursor->keyCount && key > cursor->keys[i]) {
                i++;
            }
            if (i < cursor->keyCount && cursor->keys[i] == key) {
                return true;
            }
            cursor = cursor->isLeaf ? nullptr : cursor->children[i];
        }
        return false;
    }

    void insert(int key) {
        if (root->keyCount == MAX_KEYS) {
            BPlusNode* newRoot = new BPlusNode(false);
            newRoot->children[0] = root;
            splitChild(newRoot, 0, root);
            root = newRoot;
        }
        insertNonFull(root, key);
    }

    void remove(int key) {
        removeInternal(root, key);
        if (root->keyCount == 0 && !root->isLeaf) {
            BPlusNode* oldRoot = root;
            root = root->children[0];
            delete oldRoot;
        }
    }

private:
    void insertNonFull(BPlusNode* node, int key) {
        int i = node->keyCount - 1;
        
        if (node->isLeaf) {
            while (i >= 0 && key < node->keys[i]) {
                node->keys[i + 1] = node->keys[i];
                i--;
            }
            node->keys[i + 1] = key;
            node->keyCount++;
        } else {
            while (i >= 0 && key < node->keys[i]) {
                i--;
            }
            i++;
            
            if (node->children[i]->keyCount == MAX_KEYS) {
                splitChild(node, i, node->children[i]);
                if (key > node->keys[i]) {
                    i++;
                }
            }
            insertNonFull(node->children[i], key);
        }
    }


    void splitChild(BPlusNode* parent, int index, BPlusNode* child) {
        BPlusNode* newChild = new BPlusNode(child->isLeaf);
        newChild->keyCount = MAX_KEYS / 2;

        for (int j = 0; j < MAX_KEYS / 2; j++) {
            newChild->keys[j] = child->keys[j + (MAX_KEYS / 2) + 1];
        }
        
        if (!child->isLeaf) {
            for (int j = 0; j <= MAX_KEYS / 2; j++) {
                newChild->children[j] = child->children[j + (MAX_KEYS / 2) + 1];
            }
        }
        
        child->keyCount = MAX_KEYS / 2;
        
        for (int j = parent->keyCount; j > index; j--) {
            parent->children[j + 1] = parent->children[j];
        }
        parent->children[index + 1] = newChild;
        
        for (int j = parent->keyCount - 1; j >= index; j--) {
            parent->keys[j + 1] = parent->keys[j];
        }
        parent->keys[index] = child->keys[MAX_KEYS / 2];
        parent->keyCount++;
    }

    void removeInternal(BPlusNode* node, int key) {
        int index = 0;
        while (index < node->keyCount && node->keys[index] < key) {
            index++;
        }

        if (node->isLeaf) {
            if (index < node->keyCount && node->keys[index] == key) {
                for (int i = index; i < node->keyCount - 1; i++) {
                    node->keys[i] = node->keys[i + 1];
                }
                node->keyCount--;
            }
        } 
        else {
            if (index < node->keyCount && node->keys[index] == key) {
                if (node->children[index]->keyCount >= (MAX_KEYS + 1) / 2) {
                    int predKey = maxKey(node->children[index]);
                    node->keys[index] = predKey;
                    removeInternal(node->children[index], predKey);
                } else if (node->children[index + 1]->keyCount >= (MAX_KEYS + 1) / 2) {
                    int sucKey = minKey(node->children[index + 1]);
                    node->keys[index] = sucKey;
                    removeInternal(node->children[index + 1], sucKey);
                } else {
                    mergeChildren(node, index);
                    removeInternal(node->children[index], key);
                }
            } else {
                if (node->children[index]->keyCount < (MAX_KEYS + 1) / 2) {
                    if (index > 0 && node->children[index - 1]->keyCount >= (MAX_KEYS + 1) / 2) {
                        borrowFromLeft(node, index);
                    } else if (index < node->keyCount && node->children[index + 1]->keyCount >= (MAX_KEYS + 1) / 2) {
                        borrowFromRight(node, index);
                    } else {
                        if (index < node->keyCount) {
                            mergeChildren(node, index);
                        } else {
                            mergeChildren(node, index - 1);
                            index--;
                        }
                    }
                }
                removeInternal(node->children[index], key);
            }}
    }

    int maxKey(BPlusNode* node) {
        while (!node->isLeaf) {
            node = node->children[node->keyCount];}
        return node->keys[node->keyCount - 1];
    }

    int minKey(BPlusNode* node) {
        while (!node->isLeaf) {
            node = node->children[0];}
        return node->keys[0];
    }

    void mergeChildren(BPlusNode* parent, int index) {
        BPlusNode* left = parent->children[index];
        BPlusNode* right = parent->children[index + 1];

        left->keys[left->keyCount] = parent->keys[index];
        for (int i = 0; i < right->keyCount; i++) {
            left->keys[left->keyCount + 1 + i] = right->keys[i];}

        if (!left->isLeaf) {
            for (int i = 0; i <= right->keyCount; i++) {
                left->children[left->keyCount + 1 + i] = right->children[i];
            }
        }

        left->keyCount += right->keyCount + 1;


        for (int i = index; i < parent->keyCount - 1; i++) {
            parent->keys[i] = parent->keys[i + 1];
            parent->children[i + 1] = parent->children[i + 2];
        }
        parent->keyCount--;

        delete right;
    }

    void borrowFromLeft(BPlusNode* parent, int index) {
        BPlusNode* child = parent->children[index];
        BPlusNode* leftSibling = parent->children[index - 1];
        
        for (int i = child->keyCount; i > 0; i--) {
            child->keys[i] = child->keys[i - 1];
        }
        child->keys[0] = parent->keys[index - 1];
        
        if (!leftSibling->isLeaf) {
            for (int i = child->keyCount + 1; i > 0; i--) {
                child->children[i] = child->children[i - 1];
            }
            child->children[0] = leftSibling->children[leftSibling->keyCount];
        }
        parent->keys[index - 1] = leftSibling->keys[leftSibling->keyCount - 1];
        child->keyCount++;
        leftSibling->keyCount--;
    }

    void borrowFromRight(BPlusNode* parent, int index) {
        BPlusNode* child = parent->children[index];
        BPlusNode* rightSibling = parent->children[index + 1];
        
        child->keys[child->keyCount] = parent->keys[index];
        if (!rightSibling->isLeaf) {
            child->children[child->keyCount + 1] = rightSibling->children[0];
        }
        parent->keys[index] = rightSibling->keys[0];
        
        for (int i = 0; i < rightSibling->keyCount - 1; i++) {
            rightSibling->keys[i] = rightSibling->keys[i + 1];
        }
        
        if (!rightSibling->isLeaf) {
            for (int i = 0; i < rightSibling->keyCount; i++) {
                rightSibling->children[i] = rightSibling->children[i + 1];
            }
        }
        
        child->keyCount++;
        rightSibling->keyCount--;
    }
};

int main() {
    BPlusTree tree;

    //Insercion
    tree.insert(10);
    tree.insert(20);
    tree.insert(5);
    tree.insert(6);
    tree.insert(12);
    tree.insert(30);
    tree.insert(7);
    tree.insert(17);
    tree.insert(19);

    //Busqueda
    cout << "Buscando 15 en el árbol: " << (tree.search(15) ? "Encontrado" : "No encontrado") << endl;
    cout << "Buscando 10 en el árbol: " << (tree.search(10) ? "Encontrado" : "No encontrado") << endl;
    cout << "Buscando 6 en el árbol: " << (tree.search(6) ? "Encontrado" : "No encontrado") << endl << endl;


    //Eliminar
    cout << "Eliminar 10" << endl;
    tree.remove(10);
    cout << "Buscando 10 en el árbol: " << (tree.search(10) ? "Encontrado" : "No encontrado") << endl;

    cout << "Eliminar 12" << endl;
    tree.remove(12);
    cout << "Buscando 12 en el árbol: " << (tree.search(12) ? "Encontrado" : "No encontrado") << endl;

    cout << "Eliminar 6" << endl;
    tree.remove(6);
    cout << "Buscando 6 en el árbol: " << (tree.search(6) ? "Encontrado" : "No encontrado") << endl;

    cout << "Eliminar 19" << endl;
    tree.remove(19);
    cout << "Buscando 19 en el árbol: " << (tree.search(19) ? "Encontrado" : "No encontrado") << endl;

    return 0;
}
