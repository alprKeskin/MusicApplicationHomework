#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>

#include "Node.h"

template<class T>
class LinkedList {
public: // DO NOT CHANGE THIS PART.
    LinkedList();
    LinkedList(const LinkedList<T> &obj);

    ~LinkedList();

    int getSize() const;
    bool isEmpty() const;
    bool contains(Node<T> *node) const;

    Node<T> *getFirstNode() const;
    Node<T> *getLastNode() const;
    Node<T> *getNode(const T &data) const;
    Node<T> *getNodeAtIndex(int index) const;

    void insertAtTheFront(const T &data);
    void insertAtTheEnd(const T &data);
    void insertAfterNode(const T &data, Node<T> *node);
    void insertAsEveryKthNode(const T &data, int k);

    void removeNode(Node<T> *node);
    void removeNode(const T &data);
    void removeAllNodes();
    void removeEveryKthNode(int k);

    void swap(Node<T> *node1, Node<T> *node2);
    void shuffle(int seed);

    void print(bool reverse=false) const;

    LinkedList<T> &operator=(const LinkedList<T> &rhs);

private: // YOU MAY ADD YOUR OWN UTILITY MEMBER FUNCTIONS HERE.

private: // DO NOT CHANGE THIS PART.
    Node<T> *head;

    int size;
};

template<class T>
LinkedList<T>::LinkedList() {
    // TODO
    head = NULL;
    size = 0;
}

template<class T>
LinkedList<T>::LinkedList(const LinkedList<T> &obj) {
    // TODO

    // Generate a node pointer and make it point to the first node of the object
    Node<T> *objcurr = obj.head;
    // Generate node pointers to build our list
    Node<T> *current = NULL;
    Node<T> *previous = NULL;

    // If obj is an empty list
    if (obj.head == NULL) {
        // Then, our list will be an empty list also
        head = NULL;
        size = 0;
    }

    // If obj has only one node
    else if (((obj.head)->next == obj.head) && ((obj.head)->prev == obj.head)) {
        // Initialize our linked list as an empty list
        head = NULL;
        size = 0;

        // Build our single node
        head = new Node<T>((obj.head)->data);

        // Make the connections properly
        // next should look at head
        head->next = head;
        // prev should look at head
        head->prev = head;

        // Finally, set size
        size = 1;
    }

    // If obj has more than one node
    else {
        // Initialize our linked list as an empty list
        head = NULL;
        size = 0;

        // Start building our list
        // Build our first node
        head = new Node<T>((obj.head)->data);

        // Make previous to point our first node
        previous = head;

        // This will traverse both lists
        // The condition here might be while(true) also
        do {

            // If objcurr is looking at the last node in the obj list
            // At this point, previous is looking at the last node of our list, current is NULL
            if (objcurr == (obj.head)->prev) {
                // Make your last connection
                // Connect the last node to the first node
                previous->next = head;
                // Connect the first node to the last node
                head->prev = previous;

                // We finished our mission, so don't continue looping
                break;
            }

            else {
                // Pass objcurr to the next node
                objcurr = objcurr->next;

                // Build a new node at which current is looking, and put the data inside the node pointed by objcurr to this new node
                current = new Node<T>(objcurr->data);

                // Connect the previous node to current node
                previous->next = current;
                // Connect the current node to previouse node
                current->prev = previous;

                // Take a step such that current is NULL and previous is looking at the last generated node
                previous = current;
                current = NULL;
            }
        } while(objcurr != obj.head);

        // Set our size correctly
        size = obj.size;
    }
}

template<class T>
LinkedList<T>::~LinkedList() {
    // TODO
    Node<T> *current = head;
    Node<T> *last;

    // If the list is empty
    if (head == NULL) {
        // Do nothing
        size = 0;
    }
    
    // If the list is not empty (includes one node sized list)
    else {
        // last looks at the last node
        last = head->prev;

        // Make head NULL
        head = NULL;
        size = 0;

        // While current is not equal to last
        while (current != last) {
            // Take a step
            current = current->next;
            // Delete the previous node of the current node
            delete current->prev;
        }

        // At this point current is looking at the last node
        // Delete the last node
        current = NULL;
        delete last;
        last = NULL;
    }
}

template<class T>
int LinkedList<T>::getSize() const {
    // TODO
    return size;
}

template<class T>
bool LinkedList<T>::isEmpty() const {
    // TODO
    return (size == 0);
}

template<class T>
bool LinkedList<T>::contains(Node<T> *node) const {
    // TODO
    Node<T> *current = head;

    // if the list is empty
    if (head == NULL) {
        // It cannot contain any node
        return false;
    }

    // If the list is not empty (includes one node sized list)
    else {
        // Traverse the list
        do {
            // If you find the node
            if (current == node) {
                return true;
            }
            // If it is not the node that we are looking for
            else {
                // Take a step
                current = current->next;
            }
        } while (current != head);

        return false;
    }

}

template<class T>
Node<T> *LinkedList<T>::getFirstNode() const {
    // TODO
    // This also handles the case when the list is empty
    return head;
}

template<class T>
Node<T> *LinkedList<T>::getLastNode() const {
    // TODO
    // If the list is empty
    if (head == NULL) {
        return NULL;
    }
    // If the list is not empty (does not include one node sized list)
    else {
        return head->prev;
    }
}

template<class T>
Node<T> *LinkedList<T>::getNode(const T &data) const {
    // TODO
    Node<T> *current = head;

    // If the list is empty
    if (head == NULL) {
        return NULL;
    }

    // If the list is not empty (includes one node sized list)
    else {
        // Traverse the list
        do {
            // If you find the data that you are looking for
            if (current->data == data) {
                return current;
            }
            // If it is not the data that your are looking for
            else {
                // Take a step
                current = current->next;
            }
        } while (current != head);

        // We could not find the data
        return NULL;
    }
}

template<class T>
Node<T> *LinkedList<T>::getNodeAtIndex(int index) const {
    // TODO
    Node<T> *current = head;
    int counter = 0;

    // If the list is empty
    if (head == NULL) {
        return NULL;
    }

    // If the list is not empty (includes one node sized list)
    else {
        do {
            // If you find the node indexed by index
            if (counter == index) {
                // return this node
                return current;
            }

            // If it is not the node that we are looking for
            else {
                // Take a step
                current = current->next;
                counter++;
            }
        } while (current != head);

        // At this point we could not find the node
        return NULL;
    }
}

template<class T>
void LinkedList<T>::insertAtTheFront(const T &data) {
    // TODO
    Node<T> *current;

    // increase size
    size++;

    // Build a new node with the given data
    current = new Node<T>(data);

    // If the list is empty
    if (head == NULL) {
        head = current;
        current->next = current;
        current->prev = current;
    }

    // If the list is not empty (includes one node sized list)
    else {
        // currents next should point to the old first node
        current->next = head;
        // currents prev should point to the last node 
        current->prev = head->prev;
        // last nodes next should point to the current node
        head->prev->next = current;
        // old first nodes prev should point to the current node
        head->prev = current;
        // head should point to the current node
        head = current;
    }
}

template<class T>
void LinkedList<T>::insertAtTheEnd(const T &data) {
    // TODO

    // Insert a node with the given data at the front
    insertAtTheFront(data);

    // make head to point to the second node now
    head = head->next;
}

template<class T>
void LinkedList<T>::insertAfterNode(const T &data, Node<T> *node) {
    // TODO
    Node<T> *current;

    // If the node is not contained in the list
    if (contains(node) == false) {
        // Do nothing
        ;
    }

    // If the node is contained in the list (includes one node sized list)
    else {
        // create a new node with the given data
        current = new Node<T>(data);

        // connect currents next
        current->next = node->next;
        //connect currents prev
        current->prev = node;

        // connect the node to the current node
        node->next = current;
        // one more connection
        current->next->prev = current;

        // increase the size
        size++;
    }
}

template<class T>
void LinkedList<T>::insertAsEveryKthNode(const T &data, int k) {
    // TODO
    Node<T> *current = head;
    int counter = 1;

    // if k is less than 2
    if (k < 2) {
        // do nothing
        ;
    }

    // if k is greater than 2
    else {
        do {
            // if you are pointing a node which you should insert a new node back of it
            if (counter % k == 0) {
                // insert a new node with the given data behind the current node
                // since insertAfterNode function increases the size, do not increase the size again
                insertAfterNode(data, current->prev);
                // since you have just inserted a new node, increase counter by 1
                counter++;
                // Take a step
                current = current->next;
                counter++;
            }
            // if it is an ordinary node
            else {
                // take a step
                current = current->next;
                counter++;
            }

        } while (current != head);
        
        // In case you need to insert a node as a last node
        if (counter % k == 0) {
            // insert a new node with the given data behind the current node
            // since insertAfterNode function increases the size, do not increase the size again
            insertAfterNode(data, current->prev);
        }
    }
}

template<class T>
void LinkedList<T>::removeNode(Node<T> *node) {
    // TODO

    // if the node is not contained by list
    if (contains(node) == false) {
        // do nothing
        ;
    }

    // if there is only one node in the list, and we will remove it
    else if ( (node == head) && (head->next == head) && (head->prev == head) ) {
        // delete that node
        delete head;
        // make the list empty
        head = NULL;
        size--;
    }

    // if there are more than one node in the list, and we will remove the first node
    else if (node == head) {
        // the second node will be the first node
        head = node->next;
        
        // connect previous nodes next to the next node
        node->prev->next = node->next;
        // connect the next nodes prev to the previous node
        node->next->prev = node->prev;

        // delete the node
        delete node;
        // decrease the size
        size--;
    }

    // if the node we will remove is not the first node
    else {
        // connect previous nodes next to the next node
        node->prev->next = node->next;
        // connect the next nodes prev to the previous node
        node->next->prev = node->prev;

        // delete the node
        delete node;
        // decrease the size
        size--;
    }
}

template<class T>
void LinkedList<T>::removeNode(const T &data) {
    // TODO
    Node<T> *current = head;
    int counter = 1;

    // if the list is empty
    if (head == NULL) {
        // do nothing
        ;
    }

    // if the list is not empty (includes on node sized list)
    else {
        do {
            // if you find the node with the given data
            if (current->data == data) {
                // take a step
                current = current->next;
                counter++;
                // remove that node (this will, also, handle the first node and size so do not decrease the size again)
                removeNode(current->prev);
            }

            // if it is not the node with the given data
            else {
                // take a step
                current = current->next;
                counter++;
            }
        } while (counter <= size);
    }
}

template<class T>
void LinkedList<T>::removeAllNodes() {
    // TODO
    Node<T> *current;

    // if the list is empty
    if (head == NULL) {
        // do nothing
        ;
    }

    // if the list has only one node
    else if ( (head->next == head) && (head->prev == head) ) {
        removeNode(head);
    }

    // if the list has more than one node (includes two node sized list)
    else {
        // current should point to the second node
        current = head->next;
        do {
            // take a step
            current = current->next;
            // remove that node (it will, also, decrease the size by 1)
            removeNode(current->prev);
        } while (current != head);

        // remove the first node lastly (it will make head NULL)
        removeNode(current);
    }
}

template<class T>
void LinkedList<T>::removeEveryKthNode(int k) {
    // TODO
    Node<T> *current = head;
    int counter = 1;

    // if k is less than 2
    if (k < 2) {
        // do nothing
        ;
    }

    // if k is greater than
    else {
        do {
            // if you are pointing a node which you should remove
            if (counter % k == 0) {
                // Take a step
                current = current->next;
                counter++;
                // since removeNode function decreases the size, do not decrease the size again
                removeNode(current->prev);
            }
            // if it is an ordinary node
            else {
                // take a step
                current = current->next;
                counter++;
            }
        } while (current != head);
    }
}

template<class T>
void LinkedList<T>::swap(Node<T> *node1, Node<T> *node2) {
    // TODO
    Node<T> *node1sprev;
    Node<T> *node1snext;

    // if either of the given nodes is not in the list
    if ( (contains(node1) == false) || (contains(node2) == false) ) {
        // do nothing
        ;
    }

    // if there are only two nodes in the list
    else if (size == 2) {
        // modeify head
        if ( (head == node1) || (head == node2) ) {
            // if node1 is the first node
            if (head == node1) {
                // make head node2
                head = node2;
            }
            // if node2 is the first node
            else if (head == node2) {
                // make head node1
                head = node1;
            }
        }
    }

    // if both nodes are in the list and the list has more than two nodes
    else {

        // if one of the nodes is the first node, make a necessary head arrangement
        if ( (head == node1) || (head == node2) ) {
            // if node1 is the first node
            if (head == node1) {
                // make head node2
                head = node2;
            }
            // if node2 is the first node
            else if (head == node2) {
                // make head node1
                head = node1;
            }
        }

        // if node2 is the next node of the node1
        if ( (node1->next == node2) && (node2->prev == node1) ) {
            node1->prev->next = node2;
            node2->next->prev = node1;
            node1->next = node2->next;
            node2->prev = node1->prev;
            node2->next = node1;
            node1->prev = node2;

        }

        // if node1 is the next node of the node2
        else if ( (node2->next == node1) && (node1->prev == node2) ) {
            node2->prev->next = node1;
            node1->next->prev = node2;
            node2->next = node1->next;
            node1->prev = node2->prev;
            node1->next = node2;
            node2->prev = node1;
        }

        // if they are not successive
        else {
            // connect node1s next and previous nodes to node2
            // connect node1s previous node to node2
            node1->prev->next = node2;
            // connect node1s next node to node2
            node1->next->prev = node2;

            // connect node2s next and previous nodes to node1
            // connect node2s previous node to node1
            node2->prev->next = node1;
            // connect node2s next node to node1
            node2->next->prev = node1;

            // connect node1s next and prev pointers to node2s next and previous nodes

            // to not to lose node1s prev and next pointers, save them
            node1sprev = node1->prev;
            node1snext = node1->next;

            // node1s prev will point to node2s previous node
            node1->prev = node2->prev;
            // node1s next will point to node2s next node
            node1->next = node2->next;

            // connect node2s next and prev pointers to node1s next and previous nodes
            // node2s prev will point to node1s previous node
            node2->prev = node1sprev;
            // node2s next will point to node1s next node
            node2->next = node1snext;
        }
    }
}

template<class T>
void LinkedList<T>::shuffle(int seed) {
    // TODO
    Node<T> *node1;
    Node<T> *node2;

    for (int i = 0; i < size; i++) {
        node1 = getNodeAtIndex(i);
        node2 = getNodeAtIndex( (i * i + seed) % size );
        swap(node1, node2);
    }
}

template<class T>
void LinkedList<T>::print(bool reverse) const {
    if (this->isEmpty()) {
        std::cout << "The list is empty." << std::endl;
        return;
    }

    if (reverse) {
        // traverse in reverse order (last node to first node).

        Node<T> *node = this->getLastNode();

        do {
            std::cout << *node << std::endl;
            node = node->prev;
        }
        while (node != this->getLastNode());
    } else {
        // traverse in normal order (first node to last node).

        Node<T> *node = this->getFirstNode();

        do {
            std::cout << *node << std::endl;
            node = node->next;
        }
        while (node != this->getFirstNode());
    }
}

template<class T>
LinkedList<T> &LinkedList<T>::operator=(const LinkedList<T> &rhs) {
    // TODO
    // Generate a node pointer and make it point to the first node of the object
    Node<T> *objcurr = rhs.head;
    // Generate node pointers to build our list
    Node<T> *current = NULL;
    Node<T> *previous = NULL;

    // remove all nodes
    removeAllNodes();

    // If rhs is an empty list
    if (rhs.head == NULL) {
        // Then, our list will be an empty list also
        head = NULL;
        size = 0;
    }

    // If rhs has only one node
    else if (((rhs.head)->next == rhs.head) && ((rhs.head)->prev == rhs.head)) {
        // Initialize our linked list as an empty list
        head = NULL;
        size = 0;

        // Build our single node
        head = new Node<T>((rhs.head)->data);

        // Make the connections properly
        // next should look at head
        head->next = head;
        // prev should look at head
        head->prev = head;

        // Finally, set size
        size = 1;
    }

    // If rhs has more than one node
    else {
        // Initialize our linked list as an empty list
        head = NULL;
        size = 0;

        // Start building our list
        // Build our first node
        head = new Node<T>((rhs.head)->data);

        // Make previous to point our first node
        previous = head;

        // This will traverse both lists
        // The condition here might be while(true) also
        do {

            // If objcurr is looking at the last node in the rhs list
            // At this point, previous is looking at the last node of our list, current is NULL
            if (objcurr == (rhs.head)->prev) {
                // Make your last connection
                // Connect the last node to the first node
                previous->next = head;
                // Connect the first node to the last node
                head->prev = previous;

                // We finished our mission, so don't continue looping
                break;
            }

            else {
                // Pass objcurr to the next node
                objcurr = objcurr->next;

                // Build a new node at which current is looking, and put the data inside the node pointed by objcurr to this new node
                current = new Node<T>(objcurr->data);

                // Connect the previous node to current node
                previous->next = current;
                // Connect the current node to previouse node
                current->prev = previous;

                // Take a step such that current is NULL and previous is looking at the last generated node
                previous = current;
                current = NULL;
            }
        } while(objcurr != rhs.head);

        // Set our size correctly
        size = rhs.size;
    }
    return *this;
}

#endif //LINKEDLIST_H