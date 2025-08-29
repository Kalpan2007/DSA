 #include <iostream>
using namespace std;
class node{
    public :
    int data;
    node* next;
    node(int value){
        data = value;
        next = NULL;
    };
    void insertatend(int value){
        node* newnode = new node(value);
        if(tail==NULL){
            tail = newnode;
            tail->next = tail;
        }else{
            newnode->next = tail->next;
            tail->next = newnode;
            tail = newnode ;
        }
    }
    void insertatstart(int value){
        if(tail==NULL){
            tail = newnode;
            tail->next = newnode;
        }else{
            newnode->next = tail->next;
            tail->next = newnode;
        }
    }
    void display(){
        if(tail==NULL) return ;
        node* temp = tail->next;
        do{
            cout << temp->data;
            temp = temp->next;
        }while(temp!=tail->next)
    }
    void deletebyvalue(int value){
        if(tail==NULL) return ;
        node* curr = tail->next;
        ndoe* prev = tail;
        do{
            if(curr->data==value){
            // only if in list one node 
            if(curr==tail && curr==tail->next){
                delete curr;
                tail = NULL;
            }
            else{
                prev->next = curr->next;
                if(curr==tail){
                    tail = prev;
                }
                delete curr;
            }
            return ;
        }
        prev = curr;
        curr = curr->next;
            
        }while(curr != tail->next)
    }

int main() {
    // Write C++ code here
    std::cout << "Try programiz.pro";

    return 0;
}