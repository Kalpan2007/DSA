#include <iostream>
using namespace std;
class node{
public:
  int data ;
  node* next;
  node(int value){
      data = value;
      next = NULL;
  }
};
class linkedlist{
  private :
  node* head ;
  public :
  linkedlist(){
      head = NULL;
  }
  //insert at end 
  void insertatend(int value){
      node* newnode = new node(value);
      if(head==NULL){
          head = newnode;
          return;
      }
      node* temp = head;
      while(temp->next!=NULL){
          temp = temp-> next;
      }
      temp->next = newnode;
  }
  //inesert at start 
  void insertatstart(int value){
      node* newnode = new node(value);
      newnode->next = head ;
      head = newnode ;
  }
  //insert at any position 
  void insertatposition(int pos , int value){
      node* newnode = new node(value);
      if(pos==1){
          newnode->next = head;
          head = newnode ;
          return; 
      }
      node* temp = head;
      int count = 1;
      while(temp!=NULL && count < pos-1){
          temp = temp->next;
          count++;
      }
      newnode->next = temp->next;
      temp->next = newnode;
  }
  // delte by value
void deletebyvalue(int value){
    if(head == NULL) return;

    if(head->data == value){
        node* temp = head;
        head = temp->next;
        delete temp;
        return;
    }

    node* temp = head;
    while(temp->next != NULL && temp->next->data != value) {
        temp = temp->next;
    }

    if(temp->next == NULL) return; // Value not found

    node* todelete = temp->next;
    temp->next = todelete->next;
    delete todelete;
}
  // print 
  void print(){
      node* temp = head;
      while(temp!=NULL){
          cout << temp->data << " ";
          temp = temp->next;
      }
  }
};
int main() {
     linkedlist list;

    list.insertatend(10);
    list.insertatend(20);
    list.insertatstart(5);
    list.insertatposition(3,15);
    list.insertatposition(1, 1);

    cout << "Original List:\n";
    list.print();  // 1 -> 5 -> 10 -> 15 -> 20

    list.deletebyvalue(10); // Delete middle
    list.deletebyvalue(1);  // Delete head
    list.deletebyvalue(99); // Not found

    cout << "\nAfter Deletions:\n";
    list.print();  
}