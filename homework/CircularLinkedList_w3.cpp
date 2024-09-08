#include <iostream>

using namespace std;

template <typename T>
struct Node {
    T data;
    Node* next;
    Node* prev;
};

template <typename T>
class List {
private:
    Node<T>* sentinel;
public:
    List() {
        sentinel = new Node<T>;
        sentinel->next = sentinel;
        sentinel->prev = sentinel;
    }

    void push_back(T value) {
        Node<T>* temp = new Node<T>;
        temp->data = value;

        
        temp->prev = sentinel->prev; 
        temp->next = sentinel;  
        sentinel->prev->next = temp;
        sentinel->prev = temp;  
    }

    void push_front(T value) {
        Node<T>* temp = new Node<T>;
        temp->data = value;

        temp->next = sentinel->next; 
        temp->prev = sentinel;  
        sentinel->next->prev = temp;
        sentinel->next = temp;  

    }

    void print() {
        Node<T>* temp = sentinel->next;

        cout << "[ ";
        
        while (temp != sentinel) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        
        cout << "]" << endl;
        
    }

    T front(){
        if (sentinel->next ==sentinel) {
            cout << "La lista está vacía" << endl;
            return T();
        }
        
        return sentinel->next->data;
    }

    T back(){
        if (sentinel->next ==sentinel) {
            cout << "La lista está vacía" << endl;
            return T();
        }
        
        return sentinel->prev->data;
        
        
    }

    T pop_front() {

        
        if (sentinel->next == sentinel) { 
            cout << "La lista está vacía" << endl;
            return T();
        }

        Node<T>* temp = sentinel->next;
        T value = temp -> data;        
        sentinel->next = temp-> next;
        temp->next->prev = sentinel;

        
        delete temp;

        
        return value;
    }

    T pop_back() {
        if (sentinel->prev == sentinel) {
            cout << "La lista está vacía." << endl;
            return T();
        }


        Node<T>* temp = sentinel -> prev;
        T value = temp->data; 

        
        sentinel ->prev = temp-> prev;
        temp->prev ->next = sentinel;

        delete temp; 

        return value;
    }

    void insert(T value, int position) {
        Node<T>* newNode = new Node<T>;
        newNode->data = value;

        Node<T>* current = sentinel->next;
        int current_position = 0;
        
        if (position == 0) {
            push_front(value);
            return;
        }


        while (current != sentinel && current_position < position) {
            current = current->next;
            current_position++;
            
        }

        if (current == sentinel) {
            push_back(value);
        } else {

            
            newNode->prev = current->prev;
            newNode->next = current;
            current->prev->next = newNode;
            current->prev = newNode;
            
        }
        
    }

    bool empty() {
        if(sentinel->next == sentinel){
            return true;
        }
        return false;
    }


    void remove(int position) {
        if (sentinel->next == sentinel) {
            cout << "La lista está vacía" << endl;
            return;
        }
        Node<T>* current = sentinel->next;
        int current_position = 0;
    
        while (current != sentinel && current_position < position) {
            current = current->next;
            current_position++;
            
        }

        
        if (current == sentinel) {
            current = sentinel->prev; 
        }
    
        current->prev->next = current->next;
        current->next->prev = current->prev;
    
        delete current; 

        
    }

    T operator[](int position) {
        if (empty()) {
            cout << "La lista está vacía" << endl;
            return T();
        }
        

        Node<T>* current = sentinel->next;
        int current_position = 0;

        while (current != sentinel && current_position < position) {
            current = current->next;
            current_position++;
            
        }

        if (current == sentinel) {
            return sentinel->prev->data;
            
        }

        return current->data;



        
    }

    int size() {
        int size = 0;
        Node<T>* current = sentinel->next;
        
        while (current != sentinel) {
            size++;
            current = current->next;
        }
        
        return size;
    }


    void clear() {
        
        Node<T>* current = sentinel->next;

        while (current != sentinel) {
            Node<T>* next;
            next = current->next;
            delete current;
            current = next;
        }

        sentinel->next = sentinel;
        sentinel->prev = sentinel;

        
    }


    void reverse() {
        Node<T>* current = sentinel->next;
        Node<T>* temp = nullptr;

        if (current == sentinel) {
            return;
        }

        
        while (current != sentinel) {
            temp = current->next;
            current->next = current->prev;
            current->prev = temp;
            current = temp;  
        }
        
        
        sentinel->next = sentinel->prev;
        sentinel->prev = sentinel->next;

    }
};

int main() {
    List<int> list;

    list.push_back(5);
    list.push_back(3);
    list.push_back(9);
    list.push_front(1);

    list.print();

    cout << "head: " << list.front()<< endl;
    cout << "tail: " <<list.back()<< endl <<endl;

    cout << "pop_front: " << list.pop_front() << endl;
    list.print();
    cout << "pop_back: " << list.pop_back() << endl;
    list.print();

    list.insert(1, 0);
    list.insert(9, 3);
    list.print();

    list.remove(2);
    list.print();

    cout << "enti? " << list.empty() << endl;
    cout << list.operator[](2) << endl;
    list.print();
    cout << "sais: " << list.size() << endl;

    list.reverse();
    list.print();
    
    list.clear();
    list.print();
}
