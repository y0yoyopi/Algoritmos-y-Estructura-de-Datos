#include <iostream>
#include <cmath>


using namespace std;

template <typename T>
struct Node {
    T data;
    Node<T>* next;
};

template <typename T>
class List {
private:
    Node<T>* head;

public:
    List() : head(nullptr) {}

    void push_back(T i){
        Node<T>* node = new Node<T>();
        node->data = i;
        node->next = nullptr;
        if(head == nullptr){
            head = node;
        }
        else{
            Node<T>* temp = head;
            while(temp->next != nullptr){
                temp = temp->next;
            }
            temp->next = node;
        }
    }

    void push_front(T i){
        Node<T>* node = new Node<T>();
        node->data = i;
        node->next = head;
        head = node;
    }


    T front(){
        if (head == nullptr) {
            cout << "La lista esta vacia" << endl;;
        }
        return head->data;
    }

    T back(){
        if (head == nullptr) {
            cout << "La lista esta vacia" << endl;;
        }
        Node<T>* temp = head;
        while(temp->next != nullptr){
            temp = temp->next;
        }
        return temp->data;
        
    }

    T popfront(){
        if (head == nullptr) {
            cout << "La lista esta vacia" << endl;;
        }
        Node<T>* temp = head; 
        T value = temp->data; 
        head = head->next;    
        delete temp;          

        return value;
        
    }

    /*
    T popback(){
        if (head == nullptr) {
            cout << "La lista esta vacia" << endl;;
        }

        if (head->next == nullptr) {
            T value = head->data;
            delete head;
            head = nullptr;
            return value;
        }

        Node<T>* temp = head; 
        while(temp->next->next != nullptr){
            temp = temp->next;
        }
        T value = temp->next->data; 
        delete temp->next;
        temp->next = nullptr;  

        return value;
    }*/
    
    T popback(){
        if (head == nullptr) {
            cout << "La lista esta vacia" << endl;;
        }
        
        if (head->next == nullptr) {
            T value = head->data;
            delete head;
            head = nullptr;
            return value;
        }

        Node<T>* temp = head;
            Node<T>* tprev = nullptr;
            while (temp->next != nullptr) {
                tprev = temp;
                temp = temp->next;
            }
            T value = temp->data;
            delete temp;
            tprev->next = nullptr;

            return value;
    }

    T operator[](int i){
        Node<T>* temp = head;
        int j = 0;
        while(temp != nullptr){
            
            if(j == i){
                return temp->data;
            }
            temp = temp->next;
            j++;
        }
        return -1; //fuera de rango
    }

    bool empty(){
        return head == nullptr;
    }

    int size(){
        Node<T>* temp = head;
        int size = 0;
        while(temp != nullptr){
            temp = temp->next;
            size++;
        }
        return size;
    }

    void clear() {
        Node<T>* current = head;
        while (current != nullptr) {
            Node<T>* next = current->next; 
            delete current;
            current = next; 
        }
        head = nullptr; 
    }

    void reverse(){
        Node<T>* prev = nullptr;
        Node<T>* current = head;
        Node<T>* next = nullptr;

        while (current != nullptr) {
            next = current->next;  
            current->next = prev;  
            prev = current;        
            current = next;        
        }

        head = prev;
    }

    int binary_to_decimal_it() {
        int size = 0;
        int sum = 0;
        auto current = head;

       while (current != nullptr) {
          size += 1;
          current = current->next;
      }

       current = head;

      while (current != nullptr) {
          sum += pow(2, size - 1) * current->data; 
           size--; 
           current = current->next;
      }

        return sum;
    }

    void print(){
        Node<T>* temp = head;
        while(temp != nullptr){
            cout << temp->data << " ";
            temp = temp->next;
        }
    }

// MERGE SORT----------------------------------------

    Node<T>* mergeSort(Node<T>* head) {
        if (head == nullptr || head->next == nullptr) {
            return head;
        }


        Node<T>* middle = getMiddle(head);
        Node<T>* nextOfMiddle = middle->next;

        middle->next = nullptr; 


        Node<T>* left = mergeSort(head);
        Node<T>* right = mergeSort(nextOfMiddle);


        Node<T>* sortedList = merge(left, right);

        return sortedList;
    }

    Node<T>* merge(Node<T>* left, Node<T>* right) {

        if (left == nullptr) return right;
        if (right == nullptr) return left;

        Node<T>* result = nullptr;


        if (left->data <= right->data) {
            result = left;
            result->next = merge(left->next, right);
        } else {
            result = right;
            result->next = merge(left, right->next);
        }

        return result;
    }

    Node<T>* getMiddle(Node<T>* head) {
        if (head == nullptr) return head;

        Node<T>* slow = head; 
        Node<T>* fast = head->next; 

        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
        }

        return slow;
    }

    void sort() {
      head = mergeSort(head);
    }

// -------------------------------------------------- 

};


int main() {
    List<int> list;
    list.push_back(1);
    list.push_back(14);
    list.push_back(29);
    list.push_back(1);
    list.push_back(2);
    list.push_back(18);
    list.push_back(33);
    list.push_front(0);
    
    list.print();
    cout << endl;
    list.reverse();    
    

    list.print();
    cout << endl;
    cout << list.popback() << endl;

    list.sort();

    list.print();
    
}