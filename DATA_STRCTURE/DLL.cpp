#include <iostream>
using namespace std;
class node{
  public :
  int data;
  node* next;
  node* prev;
  node(int value){
      data = value;
      next = NULL;
      prev = NULL;
  }
};
class DLL{
    private :
    node* head;
    public :
    DLL(){
        head = NULL;
    }
    //inser at start 
    void insertatstart(int value){
        node* newnode = new node(value);
        if(head!=NULL){
             head->prev = newnode ;
        }
        newnode->next = head;
        head = newnode;
    }
    // inser at end
    void insertatend(int value){
        node* newnode = new node(value){
            if(head==NULL){
                head = newnode;
                return ;
            }
            node* temp = head;
            while(temp->next!=NULL){
                temp = temp->next;
            }
            temp->next = newnode;
            newnode->prev = temp;
        }
    }
    // insert at position 
    void insertatposition(int pos , int value){
        node* newnode = new node(value);
        if(pos==1){
            if(head!=NULL){
             head->prev = newnode ;
        }
        newnode->next = head;
        head = newnode;
        return;
        }
        node* temp = head;
        int count = 1;
        while(temp!=NULL && count < pos-1){
            temp = temp->next;
            count++;
        }
        if (temp == NULL) {
            cout << "Position out of bounds!" << endl;
            delete newNode;
            return;
        }
        newnode->next = temp->next;
        newnode->prev = temp;
         if (temp->next != NULL) {
            temp->next->prev = newNode;
        }
        temp->next = newnode;
    }
    // delete by value
    void deletebyvalue(int value){
        if(head->data==value){
            node* todelete = head;
            head = head->next;
            head->prev = NULL;
            delete todelete;
            return;
        }
        node* temp = head;
        while(temp->next!=NULL && temp->data!=value){
            temp = temp->next;
        }
        if(temp==NULL) return ;
        temp->prev->next = temp->next;
        if(temp->next!=NULL) temp->next->prev = temp->prev;
        delete temp;
    }
    // print as well as linkedlist 
    // you can also reverse print by going to last node and after that travel to first !!
};
int main() {
    DLL dll;
    dll.insertatstart(10);
    dll.insertatend(20);
    dll.insertatposition(2, 15);
    dll.deletebyvalue(15);
    dll.insertatstart(5);
    dll.insertatend(25);
    dll.insertatposition(3, 12);
    dll.deletebyvalue(10);
    dll.insertatend(30);
    dll.insertatstart(1);
    dll.insertatposition(4, 18);
    dll.deletebyvalue(20);
    dll.insertatstart(0);   
    dll.insertatend(35);
    dll.insertatposition(5, 22);
    dll.deletebyvalue(25);
    dll.insertatstart(-5);
    return 0;
}