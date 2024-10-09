#include <iostream>
using namespace std;

// Define Stack class
class Stack {
private:
    // Index of the top element in the stack
    int top;
    // Array to store stack elements, with a capacity of 100
    // elements
    int arr[100];

public:
    // Constructor to initialize an empty stack
    Stack() { top = -1; }

    // Function to add an element x to the top of the stack
    void push(int x)
    {
        // If the stack is full, print "Stack overflow" and
        // return
        if (top >= 99) {
            cout << "Stack overflow" << endl;
            return;
        }
        // Add element to the top of the stack and increment
        // top
        arr[++top] = x;
        cout << "Pushed " << x << " to stack\n";
    }

    // Function to remove the top element from the stack
    int pop()
    {
        // If the stack is empty, print "Stack underflow"
        // and return 0
        if (top < 0) {
            cout << "Stack underflow" << endl;
            return 0;
        }
        // Remove the top element from the stack and
        // decrement top
        return arr[top--];
    }

    // Function to return the top element of the stack
    int peek()
    {
        // If the stack is empty, print "Stack is empty" and
        // return 0
        if (top < 0) {
            cout << "Stack is empty" << endl;
            return 0;
        }
        // Return the top element of the stack
        return arr[top];
    }

    // Function to check if the stack is empty
    bool isEmpty()
    {
        // Return true if the stack is empty (i.e., top is
        // -1)
        return (top < 0);
    }
};

// Main function
int main()
{
    // Create a stack
    Stack s;
    // Push elements into the stack
    s.push(10);
    s.push(20);
    s.push(30);
    // Print the top element of the stack
    cout << "Top element is: " << s.peek() << endl;
    // Print all elements in the stack
    cout << "Elements present in stack : ";
    // While the stack is not empty
    while (!s.isEmpty()) {
        // Pop the top element from the stack and print it
        cout << s.pop() << " ";
    }
    return 0;
}
