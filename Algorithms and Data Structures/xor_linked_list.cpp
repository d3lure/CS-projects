#include <iostream>
#include <string>
using namespace std;

class Node {
    public:
    int value;
    Node *npx;
};

class List {
    public:
    int listSize;
    Node *head;
    Node *tail;
    Node *actual;
    Node *act_next;
    Node *act_prev;

    List() {
        listSize = 0;
        head = NULL;
        tail = NULL;
        actual = NULL;
        act_next = NULL;
        act_prev = NULL;
    }

    ~List() {
        delete[] head, tail, actual, act_next, act_prev;
    }

    void init() {
        listSize = 0;
        head = NULL;
        tail = NULL;
        actual = NULL;
        act_next = NULL;
        act_prev = NULL;
    }

    Node* addressXOR (Node *a, Node *b) { 
        return reinterpret_cast<Node *>(reinterpret_cast<uintptr_t>(a) ^ reinterpret_cast<uintptr_t>(b)); 
    }

    void addBeg(int value) { 
        Node *new_node = new Node;
        new_node->value = value; 
        new_node->npx = head; 
    
        if (head != NULL) { 
            head->npx = addressXOR(new_node, head->npx);
            head = new_node;

            //check if new added node is behind 'actual' pointer
            if(addressXOR(head->npx, NULL) == actual) {
                act_prev = head;
            }
        }
        else {
            head = new_node;
            tail = new_node;
            actual = new_node;
        }
        listSize += 1;
    }

    void addEnd(int value) { 
        Node *new_node = new Node;

        if(head == NULL) {
            addBeg(value);
        }
        else {
            
            Node* temp = addressXOR((tail)->npx, NULL);
            tail->npx = addressXOR(temp, new_node);
            new_node->npx = tail;
            new_node->value = value;

            tail = new_node;

            if(addressXOR(tail->npx, NULL) == actual) {
                act_next = tail;
            }
            listSize += 1;
        }
    }

    void printForward() {
        if(listSize == 0) {
            cout << "NULL" << endl;
        }
        else {
            Node *curr = head; 
            Node *prev = NULL; 
            Node *next; 
    
            while (curr != NULL) { 
            
                cout << curr->value << " "; 

                next = addressXOR(prev, curr->npx); 
                prev = curr; 
                curr = next; 
            }   
            delete[] curr, prev, next; 
        } 
    }

    void printBackward() {
        if(listSize == 0) {
            cout << "NULL" << endl;
        }
        else {
            Node *curr = tail; 
            Node *next = NULL; 
            Node *prev; 

            while(curr != NULL) {

                cout << curr->value << " ";

                prev = addressXOR(next, curr->npx);
                next = curr;
                curr = prev;
            }
            delete[] curr, prev, next;
        }
    }

    void deleteBeg() {
        if(listSize > 1) {
            Node *beg = head;

            if(beg == actual) {
                //new actual is tail and new prev will be prev of the tail, next = NULL
                head = addressXOR(NULL, beg->npx);
                actual = tail;
                act_next = NULL;
                act_prev = addressXOR(NULL, actual->npx);
                head->npx = addressXOR(NULL, addressXOR(beg, head->npx));
            }
            else if(beg == act_prev) {
                //actual will be head, prev is equal NULL
                head = actual;
                act_prev = NULL;
                head->npx = addressXOR(NULL, act_next);
            }
            else {
                head = addressXOR(NULL, beg->npx);
                head->npx = addressXOR(NULL, addressXOR(beg, head->npx));
            }

            listSize -= 1;
            delete[] beg;
        }
        else if(listSize == 1) {
            init();
        }
    }

    void deleteEnd() { 
        if (listSize > 1) { 
            Node *end = tail;

            if(end == actual) {
                tail = addressXOR(end->npx, NULL);
                actual = tail;
                act_next = NULL;
                act_prev = addressXOR(NULL, tail->npx);
                tail->npx = addressXOR(NULL, addressXOR(end, tail->npx));
            }
            else if(end == act_next) {
                tail = actual;
                act_next = NULL;
                tail->npx = addressXOR(NULL, act_prev);
            }
            else {
                tail = addressXOR(NULL, end->npx);
                tail->npx = addressXOR(NULL, addressXOR(end, tail->npx));
            }

            listSize -= 1;
            delete[] end;
        }
        else if(listSize == 1) {
            init();
        }
    } 

    void deleteActual() {
        if(listSize > 1) {
            Node* tmp = actual;

            if(actual == head) {
                actual = tail;
                head = act_next;
                head->npx = addressXOR(NULL, addressXOR(act_next->npx, tmp));
                act_next = NULL;
                act_prev = addressXOR(tail->npx, NULL);
            }
            else if(actual == tail) {
                actual = act_prev;
                tail = actual;
                act_next = NULL;
                act_prev = addressXOR(actual->npx, tmp);
                actual->npx = addressXOR(actual->npx, addressXOR(tmp, NULL));
            }
            else {
                actual = act_prev;
                act_prev = addressXOR(act_prev->npx, tmp);
                actual->npx = addressXOR(tmp, addressXOR(actual->npx, act_next));
                act_next->npx = addressXOR(tmp, addressXOR(act_next->npx, actual));
            }

            listSize -= 1;
            delete[] tmp;
        }
        else if(listSize == 1) {
            init();
        }
    }

    void deleteValue(int value) {
        if(listSize > 1) {
            Node *curr = head; 
            Node *prev = NULL; 
            Node *next = NULL; 

            while (curr != NULL) {
                if(curr->value == value) {
                    if(curr == head) {
                        deleteBeg();
                        curr = head;
                        prev = NULL;
                        next = NULL;
                    }
                    else if(curr == tail) {
                        deleteEnd();
                        curr = head;
                        prev = NULL;
                        next = NULL;
                    }
                    else if(curr == actual) {
                        deleteActual();
                        curr = head;
                        prev = NULL;
                        next = NULL;
                    }
                    else {
                        Node* tmp = curr;
                        if(tmp == act_next) {
                            act_next = addressXOR(tmp->npx, actual);
                            actual->npx = addressXOR(actual->npx, addressXOR(tmp, act_next));
                            act_next->npx = addressXOR(act_next->npx, addressXOR(tmp, actual));
                            delete[] tmp;
                        }
                        else if(tmp == act_prev) {
                            act_prev = addressXOR(tmp->npx, actual);
                            actual->npx = addressXOR(actual->npx, addressXOR(tmp, act_prev));
                            act_prev->npx = addressXOR(act_prev->npx, addressXOR(tmp, actual));
                            delete[] tmp;
                        }
                        else {
                            next = addressXOR(prev, curr->npx);
                            prev->npx = addressXOR(prev->npx, addressXOR(curr, next));
                            next->npx = addressXOR(next->npx, addressXOR(curr, prev));
                        }
                        curr = head;
                        prev = NULL;
                        next = NULL; 
                    }
                } 
                else {
                    next = addressXOR(prev, curr->npx); 
                    prev = curr; 
                    curr = next; 
                }
            }
            delete[] curr, prev, next;
        }
        else if(listSize == 1 && head->value == value) {
            init();
        }
    }

    void next() {
        //If list has less than two nodes 'next' method does nothing
        //else check if next node will be NULL, if it will, 'next' method points to the head of list
        if(listSize > 1) {

            if(addressXOR(actual->npx, act_prev) != NULL) {
            cout << act_next->value << endl;

            act_prev = actual;
            actual = act_next;
            act_next = addressXOR(act_next->npx, act_prev);
        }
            else {
                cout << head->value << endl;

                act_prev = NULL;
                actual = head;
                act_next = addressXOR(NULL, head->npx);
            }
        }
        else if(listSize == 1) cout << actual->value << endl;
        else cout << "NULL" << endl;
    }

    void prev() {
        //If list has less than two nodes 'prev' method does nothing
        //Else check if previous node will be NULL, if it will, 'prev' method will point to tail 
        if(listSize > 1) {
            if(addressXOR(actual->npx, act_next) != NULL) {
                cout << act_prev->value << endl;
                act_next = actual;
                actual = act_prev;
                act_prev = addressXOR(actual->npx, act_next);
            }
            else {
                cout << tail->value << endl;
                act_next = NULL;
                actual = tail;
                act_prev = addressXOR(NULL, tail->npx);
            }
        }
        else if(listSize == 1) cout << actual->value << endl;
        else cout << "NULL" << endl;
    }

    void addActual(int value) {
        Node* new_node = new Node;
        new_node->value = value;

        if(actual != head) {
            new_node->npx = addressXOR(act_prev, actual);
            actual->npx = addressXOR(actual->npx, addressXOR(act_prev, new_node));
            act_prev->npx = addressXOR(act_prev->npx, addressXOR(actual, new_node));
            act_prev = new_node;
        }
        else {
            new_node->npx = addressXOR(NULL, actual);
            actual->npx = addressXOR(actual->npx, addressXOR(NULL, new_node));
            act_prev = new_node;
            head = new_node;
        }
    } 

    void printActual() {
        if(actual != NULL) cout << actual->value << endl;
        else cout << "NULL" << endl;
    }

};

int main() {    

    List* list = new List();
    string command;

    while(cin >> command) {
        int value;

        if(command == "ADD_BEG") {
            cin >> value;
            list->addBeg(value);
        }

        else if(command == "PRINT_FORWARD") {
            list->printForward();
            putchar('\n');
        }
        
        else if(command == "ADD_END") {
            cin >> value;
            list->addEnd(value);
        }

        else if(command == "PRINT_BACKWARD") {
            list->printBackward();
            putchar('\n');
        }

        else if(command == "DEL_BEG") {
            list->deleteBeg();
        }

        else if(command == "DEL_END") {
            list->deleteEnd();
        }

        else if(command == "DEL_ACT") {
            list->deleteActual();
        }

        else if(command == "ACTUAL") {
            list->printActual();
        }

        else if(command == "NEXT") {
            list->next();
        }

        else if(command == "PREV") {
            list->prev();
        }

        else if(command == "ADD_ACT") {
            cin >> value;
            list->addActual(value);
        }

        else if(command == "DEL_VAL") {
            cin >> value;
            list->deleteValue(value);
        }
    }
    return 0;
}
