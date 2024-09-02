#include <iostream>

using namespace std;


struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};


ListNode* mergeSortedLists(ListNode* list1, ListNode* list2) {
    if (list1 == nullptr) return list2;
    if (list2 == nullptr) return list1;

    ListNode* head = nullptr;
    ListNode* tail = nullptr;

    if (list1->val <= list2->val) {
        head = list1;
        list1 = list1->next;
    } else {
        head = list2;
        list2 = list2->next;
    }

    tail = head;

    while (list1 != nullptr && list2 != nullptr) {
        if (list1->val <= list2->val) {
            tail->next = list1;
            list1 = list1->next;
        } else {
            tail->next = list2;
            list2 = list2->next;
        }
        tail = tail->next;
    }

    if (list1 != nullptr) {
        tail->next = list1;
    } else {
        tail->next = list2;
    }

    return head;
}

ListNode* reverse(ListNode* head) {
    ListNode* prev = nullptr;      
    ListNode* current = head;    
    ListNode* next = nullptr;   

    while (current != nullptr) { 
        next = current->next;  
        current->next = prev;     
        prev = current;         
        current = next;          
    }

    return prev;              
}

void print(ListNode* node) {
    while (node != nullptr) {
        cout << node->val << " ";
        node = node->next;
    }
    cout << endl;
}

ListNode* intersectionOfSortedLists(ListNode* list1, ListNode* list2) {
    ListNode* p1 = list1;
    ListNode* p2 = list2;
    ListNode* intersectionHead = nullptr;
    ListNode* intersectionTail = nullptr;

    while (p1 != nullptr && p2 != nullptr) {
        if (p1->val == p2->val) {
            
            ListNode* newNode = new ListNode(p1->val);
            if (intersectionHead == nullptr) {
                intersectionHead = newNode;
                intersectionTail = newNode; 
            } else {
                intersectionTail->next = newNode; 
                intersectionTail = intersectionTail->next;
            }
            p1 = p1->next;
            p2 = p2->next;
        } else if (p1->val < p2->val) {
            p1 = p1->next;  
        } else {
            p2 = p2->next; 
        }
    }

    return intersectionHead;
}

ListNode* insertionSort(ListNode* head) {
    if (head == nullptr) return nullptr; 

    ListNode* sortedHead = nullptr;

    while (head != nullptr) {
        ListNode* current = head;
        head = head->next; 


        if (sortedHead == nullptr || sortedHead->val >= current->val) {
            current->next = sortedHead; 
            sortedHead = current; 
        } else {
            ListNode* sortedCurrent = sortedHead; 
            while (sortedCurrent->next != nullptr && sortedCurrent->next->val < current->val) {
                sortedCurrent = sortedCurrent->next;
            }
            current->next = sortedCurrent->next;
            sortedCurrent->next = current;
        }
    }

    return sortedHead; 
}

int main() {
    ListNode* list1 = new ListNode(1);
    list1->next = new ListNode(1);
    list1->next->next = new ListNode(2);
    list1->next->next->next = new ListNode(6);

    ListNode* list2 = new ListNode(2);
    list2->next = new ListNode(4);
    list2->next->next = new ListNode(5);
    list2->next->next->next = new ListNode(6);


    cout << "Lista 1: ";
    print(list1);
    cout << "Lista 2: ";
    print(list2);

    cout << "Intersección de listas: ";
    ListNode* intersection = intersectionOfSortedLists(list1, list2);
    print(intersection);

    ListNode* mergedList = mergeSortedLists(list1, list2);

    cout << "Lista fusionada: ";
    print(mergedList);

    cout << "Lista fusionada invertida: ";
    mergedList = reverse(mergedList);
    print(mergedList);

    ListNode* list3 = new ListNode(54);
    list3->next = new ListNode(95);
    list3->next->next = new ListNode(2);
    list3->next->next->next = new ListNode(96);

    cout << "Insertion Sort: ";
    ListNode* sortedList = insertionSort(list3);
    print(sortedList);
    return 0;
}
