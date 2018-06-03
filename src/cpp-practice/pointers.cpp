#include <iostream>

using std::cout;
using std::endl;

template <class T>
class Node {
public:
    Node() { }
    explicit Node(T x) : item(x) { }
    T item;
    Node * next = nullptr;
};

template <class T>
Node<T> *search_list(Node<T> *node, T x) {
    if (node == nullptr) return nullptr;

    if (node->item == x) {
        return node;
    } else {
        return search_list(node->next, x);
    }
}

template <class T>
void push_front(Node<T> **head, T x) {
    Node<T> *n = new Node<T>(x);
    n->next = *head;
    *head = n;
}

template <class T>
void print_list(Node<T> *list) {
    if (list == nullptr) {
        cout << endl;
        return;
    } else {
        cout << list->item << ", ";
        return print_list(list->next);
    }
}


template <class T>
Node<T> * find_previous(Node<T> *list, Node<T> *node) {
    Node<T> * p = list;
    while (p->next != nullptr) {
        if (p->next == node) {
            return p;
        }
        p = p->next;
    }
    return nullptr;
}

template <class T>
void delete_from_list(Node<T> **head, T x) {
    Node<T> *result = search_list<T>(*head, x);
    if (result == nullptr) return;

    if (*head == result) {
        // Handle case when node to be deleted is the head
        *head = (*head)->next;
    } else {
        Node<T> *prev = find_previous<T>(*head, result);
        prev->next = result->next;
    }
    delete result;
}

int main(int argc, char *argv[]) {
    Node<int> *list = new Node<int>(0);

    push_front<int>(&list, 1);
    push_front<int>(&list, 2);
    push_front<int>(&list, 3);

    print_list<int>(list);

    Node<int> *result = search_list<int>(list, 2);
    if (result != nullptr) {
        cout << "Found node: " << result->item << endl;
    } else {
        cout << "Couldn't find node" << endl;
    }

    delete_from_list<int>(&list, 1);
    print_list<int>(list);
    delete_from_list<int>(&list, 3);
    delete_from_list<int>(&list, 5);
    delete_from_list<int>(&list, 0);
    print_list<int>(list);

    return 0;
}
