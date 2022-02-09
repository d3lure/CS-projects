#include <iostream>
#include <string>
using namespace std;

class Node {
    public:
    int value;
    Node *next;
    Node *prev;
};

class FIFO {
    public:

    int listSize;
    Node *head;
    Node *tail;

    int queueSize;
    Node *front;
    Node *back;

    FIFO() {
        listSize = 0;
        queueSize = 0;
        head = NULL;
        tail = NULL;
        front = NULL;
        back = NULL;
    }

    ~FIFO() {
        delete[] head, tail, front, back;
    }

    void initList() {
        listSize = 0;
        head = NULL;
        tail = NULL;
    }

    void initQueue() {
        queueSize = 0;
        front = NULL;
        back = NULL;
    }

    void addBeg(int value) { 
        Node *new_node = new Node();
        new_node->value = value;
 
        if(listSize != 0) {
            if(checkIfHeadBetween()) {
                queueSize++;
            }
            new_node->prev = tail;
            new_node->next = head;
            head->prev = new_node;
            tail->next = new_node;
            head = new_node;
        }
        else {
            head = new_node;
            tail = new_node;
        }
        listSize++;
    }

    void addEnd(int value) {
        Node *new_node = new Node();
        new_node->value = value;

        if(listSize != 0) {
            if(checkIfHeadBetween()) {
                queueSize++;
            }
            new_node->next = head;
            new_node->prev = tail;
            head->prev = new_node;
            tail->next = new_node;
            tail = new_node;
        }
        else {
            head = new_node;
            tail = new_node;
        }
        listSize++;
    }

    void push(int value) {
        if(listSize == 0) {
            addBeg(value);
            front = head;
            back = head;
        }
        else if(listSize == queueSize) {
            if(checkIfHeadBetween()) {
                Node* new_node = new Node();
                new_node->value = value;
                new_node->next = back;
                new_node->prev = back->prev;

                back->prev->next = new_node;
                back->prev = new_node;
                back = new_node;
                listSize++;
            }
            else if(head==front && back==tail && listSize > 1) {
                //cout << "test124124" << endl;
                Node* new_node = new Node();
                new_node->value = value;

                new_node->next = back;
                new_node->prev = back->prev;

                back->prev->next = new_node;
                back->prev = new_node;

                back = new_node;
                listSize++;
            }   
            else {
                //cout << "|test1|" << endl;
                addBeg(value);
                back = head;
            }
        }
        else {
            if(queueSize != 0) {
                back = back->prev;
                back->value = value;
            }
            else {
                tail->value = value;
                front = tail;
                back = tail;
            }
        }
        queueSize++;
    }

    bool checkIfHeadBetween() {
        if(queueSize > 2) {
            Node *curr = front; 
            while(curr != back) {
                if(curr == head) return true;
                curr = curr->prev; 
            }
        }
        return false;
    }

    void pop() {
        if(queueSize > 1) {
            cout << front->value << endl;
            front = front->prev;
            queueSize--;
        }
        else if(queueSize == 1) {
            cout << front->value << endl;
            initQueue();
        }
        else {
            cout << "NULL" << endl;
        }
    }

    void printForward() {
        if(listSize > 1) {
            Node *curr = head;  
            while(curr != tail) { 
                cout << curr->value << " ";
                curr = curr->next; 
            }
            cout << tail->value;   
        } 
        else if(listSize == 1) cout << head->value;  
        else cout << "NULL";
    }

    void printBackward() {
        if(listSize > 1) {
            Node *curr = tail; 
            while(curr != head) {
                cout << curr->value << " ";
                curr = curr->prev; 
            }
            cout << head->value; 
        }
        else if(listSize == 1) cout << head->value;
        else cout << "NULL" << endl;
    }

    void printQueue() {
        if(queueSize > 1) {
            Node *curr = front; 
            while(curr != back) {
                cout << curr->value << " ";
                curr = curr->prev; 
            }
            cout << back->value;
        }
        else if(queueSize == 1) cout << front->value;
        else cout << "NULL";
    }

    void deleteBeg() {
        if(listSize > 1) {
            if(head == front) {
                front = front->next;
                queueSize--; 
            }
            else if(head == back) {
                back = back->next;
                queueSize--; 
            }
            if(checkIfHeadBetween()) {
                queueSize--;
            }
            head = head->next;
            head->prev = tail;
            tail->next = head;
            listSize--;
        }
        else if(listSize == 1) {
            initList();
            initQueue();
        }
    }

    void deleteEnd() { 
        if(listSize > 1) {
            if(tail == front) {
                front = front->next;
                queueSize--;    
            }
            else if(tail == back) {
                back = back->next;
                queueSize--;
            }
            if(checkIfHeadBetween()) {
                queueSize--;
            }
            tail = tail->prev;
            tail->next = head;
            head->prev = tail;
            listSize--;
        }
        else if(listSize == 1) {
            initList();
            initQueue();
        }
    }

    void garbageSoft() {
        if(listSize > 1 && front != NULL) {
            Node *curr = front->next;  
            while(curr != back) { 
                curr->value = 0;
                curr = curr->next; 
            }   
        }
        else if(listSize == 1 && front != NULL) {
            if(front != head) head->value = 0;
        }
        else {
            Node *curr = head;  
            while(curr != tail) { 
                curr->value = 0;
                curr = curr->prev; 
            }
            tail->value = 0;
        }  
    }

    void deleteNode(Node* node) {
        if(node != front || node != back) {
            if(node == head) {
                deleteBeg();
            }
            else if(node == tail) {
                deleteEnd();
            }
            else {
                node->prev->next = node->next;
                node->next->prev = node->prev;
                listSize--;
            }
        }
    }

    void garbageHard() {
        if(listSize > 1 && front != NULL) {
            Node *curr = front->next;  
            while(curr != back) { 
                deleteNode(curr);
                curr = curr->next; 
            }   
        }
        else if(listSize == 1 && front != NULL) {
            if(front != head) head->value = 0;
        }
        else {
            initList();
        }
    }

};

int main() {    

    FIFO* fifo = new FIFO();
    string command;

    while(cin >> command) {
        int value;

        if(command == "ADD_BEG") {
            cin >> value;
            fifo->addBeg(value);
        }

        else if(command == "ADD_END") {
            cin >> value;
            fifo->addEnd(value);
        }

        else if(command == "PRINT_FORWARD") {
            fifo->printForward();
            putchar('\n');
        }
        
        else if(command == "PRINT_BACKWARD") {
            fifo->printBackward();
            putchar('\n');
        }

        else if(command == "DEL_BEG") {
            fifo->deleteBeg();
        }

        else if(command == "DEL_END") {
            fifo->deleteEnd();
        }

        else if(command == "SIZE") {
            cout << fifo->listSize << endl;
        }

        else if(command == "COUNT") {
            cout << fifo->queueSize << endl;
        }

        else if(command == "PRINT_QUEUE") {
            fifo->printQueue();
            putchar('\n');
        }
        
        else if(command == "PUSH") {
            cin >> value;
            fifo->push(value);
        }
        
        else if(command == "POP") {
            fifo->pop();
        }

        else if(command == "GARBAGE_SOFT") {
            fifo->garbageSoft();
        }
    
        else if(command == "GARBAGE_HARD") {
            fifo->garbageHard();
        }


        else if(command == "FRONT") {
            cout << fifo->front->value << endl;
        }
        
        else if(command == "BACK") {
            cout << fifo->back->value << endl;
        }
        
        else if(command == "HEAD") {
            cout << fifo->head->value << endl;
        }
        
        else if(command == "TAIL") {
            cout << fifo->tail->value << endl;
        }

    }
    
    return 0;
}