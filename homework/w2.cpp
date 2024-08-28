#include <iostream>
#include <cmath>


using namespace std;

template <typename T>
struct Node {
    T data;
    Node* next;
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


};


int main() {
    List<int> list;
    list.push_back(1);
    list.push_back(1);
    list.push_back(2);
    list.push_front(0);
    list.popfront();    


    list.print();

}