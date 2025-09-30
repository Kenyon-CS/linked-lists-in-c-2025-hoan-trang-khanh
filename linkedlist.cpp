#include <iostream>

template <typename T>
class node {
  public:
    T data;           // Data of generic type T
    node* next;       // Pointer to the next node in the list

    node(T val) : data(val), next(nullptr) {}
};

template <typename T>
class LinkedList {
  private:
    node<T>* head;  // Pointer to the first node of the list

  public:
    LinkedList() : head(nullptr) {}

    // Insert at the end
    void append(T value) {
        node<T>* newNode = new node<T>(value);
        if (head == nullptr) {
            head = newNode;
        } else {
            node<T>* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }

    // Insert at the beginning
    void prepend(T value) {
        node<T>* newNode = new node<T>(value);
        newNode->next = head;
        head = newNode;
    }

    // Remove first occurrence of value
    void remove(T value) {
        if (head == nullptr) return;

        if (head->data == value) {
            node<T>* temp = head;
            head = head->next;
            delete temp;
            return;
        }

        node<T>* temp = head;
        while (temp->next != nullptr && temp->next->data != value) {
            temp = temp->next;
        }

        if (temp->next == nullptr) return;

        node<T>* nodeToRemove = temp->next;
        temp->next = temp->next->next;
        delete nodeToRemove;
    }

    // Print the list
    void print() {
        node<T>* temp = head;
        while (temp != nullptr) {
            std::cout << temp->data << " -> ";
            temp = temp->next;
        }
        std::cout << "nullptr" << std::endl;
    }

    // Destructor to clean up memory
    ~LinkedList() {
        while (head != nullptr) {
            node<T>* temp = head;
            head = head->next;
            delete temp;
        }
    }

    // Function to get the first element and remove it from the list
    void lfirst () {
        if (head == nullptr) {
            std::cout << "List is empty." << std::endl;
            return;
        }
        node<T>* temp = head;
        head = head->next;
        std::cout << "First element: " << temp->data << std::endl;
        delete temp;
    }

    // Function to get the last element and remove it from the list
    void last () {
        if (head == nullptr) {
            std::cout << "List is empty." << std::endl;
            return;
        }
        if (head->next == nullptr) {
            std::cout << "Last element: " << head->data << std::endl;
            delete head;
            head = nullptr;
            return;
        }
        node<T>* temp = head;
        while (temp->next->next != nullptr) {
            temp = temp->next;
        }
        std::cout << "Last element: " << temp->next->data << std::endl;
        delete temp->next;
        temp->next = nullptr;
    }

    // Insert in sorted order (ascending)
    void addOrder(T value) {
        node<T>* newNode = new node<T>(value);

        // Case 1: empty list OR new node goes before head
        if (head == nullptr || value < head->data) {
            newNode->next = head;
            head = newNode;
            return;
        }

        // Case 2: find position in middle or end
        node<T>* temp = head;
        while (temp->next != nullptr && temp->next->data < value) {
            temp = temp->next;
        }

        // Insert newNode between temp and temp->next
        newNode->next = temp->next;
        temp->next = newNode;
    }
};

int main() {
    LinkedList<int> list;

    list.addOrder(6);
    list.addOrder(1);
    list.addOrder(7);
    list.addOrder(3);
    list.addOrder(4);

    std::cout << "Linked List (sorted insertion): ";
    list.print();

    list.lfirst();
    std::cout << "After lfirst: ";
    list.print();

    list.last();
    std::cout << "After last: ";
    list.print();

    list.addOrder(5);
    std::cout << "After adding 5 in order: ";
    list.print();

    return 0;
}
