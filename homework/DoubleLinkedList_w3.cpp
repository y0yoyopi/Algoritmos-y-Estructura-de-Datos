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
    Node<T>* head;
    Node<T>* tail;
public:
    List() : head(nullptr), tail(nullptr) {};

    void push_back(T value){
        Node<T>* temp = new Node<T>;
        temp->data = value;
        temp->next = nullptr;
        temp->prev = tail;

        if (tail == nullptr) {
            head = temp;  
        } else {
            tail->next = temp; 
        }

        tail = temp;  
    };

    void push_front(T value){
        Node<T>* temp = new Node<T>;
        temp->data = value;
        temp->next = head;
        temp->prev = nullptr;

        if (head == nullptr) {
            tail = temp;  
        } else {
            head->prev = temp; 
        }

        head = temp;  
    };

    void print(){
        Node<T>* temp = head;
        cout << "[ ";
        while(temp != nullptr){
            cout << temp->data << " ";
            temp = temp-> next;
        }
        cout << "]"<< endl;
    }

    T front(){
        if(head == nullptr){
            cout << "la lista esta vacía"<< endl;
            return T();
        }
        return head->data;
    }

    T back(){
        if(tail == nullptr){
            cout << "la lista esta vacía" << endl;
            return T();
        }
        return tail->data;
    }

    T pop_front(){
        if(head == nullptr){
            cout << "la lista esta vacía" << endl;
            return T();
        }
        
        Node<T>* temp = head;
        T value = temp->data;
        
        if(head == tail){
            head = nullptr;
            tail = nullptr;
        }
        else{
            head = head->next;
            head->prev = nullptr;
        }
        delete temp;
        
        return value;
    }

    T pop_back(){
        if(head == nullptr){
            cout << "la lista esta vacía" << endl;
            return T();
        }

        Node<T>* temp = tail;
        T value = temp->data;
        
        if(head == tail){
            head = nullptr;
            tail = nullptr;
        }
        else{
            tail = temp->prev;
            tail->next = nullptr;
        }
        delete temp;

        return value;
    }

    void insert(T value, int position) {
        if (position == 0) {
            push_front(value);
            return;
        }
    
        if (head == nullptr) {
            push_back(value);
            return;
        }
    
        Node<T>* temp = head;
        int current = 0;
    
        while (temp != nullptr && current < position - 1) {
            temp = temp->next;
            current++;
        }
    
        if (temp == nullptr || temp->next == nullptr) { 
            push_back(value);
        } else { 
            Node<T>* newnode = new Node<T>;
            newnode->data = value;
            newnode->next = temp->next;
            newnode->prev = temp;
            temp->next->prev = newnode;
            temp->next = newnode;
        }
    }

    void remove(int position){
        if (head == nullptr) {
            cout << "La lista está vacía." << endl;
            return;
        }
        
        Node<T>* current = new Node<T>;
        
        if (position == 0) {
            if (head == tail){
                delete head;
                head = nullptr;
                tail = nullptr;
            }
            else{
                current = head;
                head = head->next;
                head->prev = nullptr;
                delete current;
                }
            return;
        }

        current = head;
        int currentNum = 0;


        while (current != nullptr && currentNum < position) {
            current = current->next;
            currentNum++;
        }

        if (current == nullptr || current == tail) {
            pop_back();
            return;
            
        } 
        current->prev->next = current->next;
        current->next->prev = current->prev;
        
        delete current;
    }

    T operator[](int position){
        if (head == nullptr) {
            cout << "La lista está vacía." << endl;
            return T();
        }
        Node<T>* current = head;
        int currentNum = 0;

        while (current != nullptr && currentNum < position) {
            current = current->next;
            currentNum++;
        }
        if (current == nullptr){
            return tail->data;
        }
        return current->data;
        
    }

    bool empty(){
        if(head==nullptr){
            return true;
        }
        return false;
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

    void clear(){
        Node<T>* current = head;
        while(current != nullptr){
            Node<T>* temp = new Node<T>;
            delete temp;
            current = current->next;
        }
        head = nullptr;
        tail = head;
    }

    void reverse() {
        if (head == nullptr) return;
    
        Node<T>* current = head;
        Node<T>* temp = nullptr;
    
        while (current != nullptr) {
            temp = current->prev;
            current->prev = current->next;
            current->next = temp;
            current = current->prev; 
        }
    
        temp = head;
        head = tail;
        tail = temp;
    }
};


int main() {
    List<int> list;
    list.push_back(1);
    list.push_back(9);
    list.push_back(6);
    list.push_front(6);

    list.print();
    cout << list.front()<<endl;
    cout << list.back()<<endl;

    cout << list.pop_front()<<endl;
    list.print();

    cout << "pop back: " << list.pop_back()<<endl;
    list.print();
    
    list.insert(6, 1);
    list.print();

    cout << "remove: ";
    list.remove(2);
    list.print(); 

    cout << list.operator[](1)<<endl;

    cout << "empty? " << list.empty() << endl;
    cout << "size = " << list.size()<< endl;

    cout << "reverse: ";
    list.reverse();
    list.print();

    list.clear();
    cout << "clear list: ";
    list.print();
}
//300