#include <iostream>
using namespace std;

template <typename T>
class LinkedList{
    struct Node{
        T data;
        Node * next;
    };
    Node * head, * tail;
    int count;

public:
    LinkedList(){
        //set up empty list
        head=tail=NULL;
        count=0;
    }

    void insertAtHead(const T & obj){
        if(count==0){
            head=tail=new Node;
            tail->next=NULL;
            tail->data=obj;
        }else{
            Node * temp = new Node;
            temp -> next = head;
            head=temp;
            temp->data=obj;
        }
        count++;
    }

    void eraseAtHead(){
        if(count>0){
                if(count==1){
                    delete head;
                    head=tail=NULL;
                }else{
                    Node * temp = head -> next;
                    delete head;
                    head = temp;
                }
                count--;
        }
    }

    void insertAtTail(const T & obj){
        /*Add your code here*/
    }

    void eraseAtTail(){
        /*Add your code here*/
    }

    int size(){
        return count;
    }

    void print(){
        /*this is a temporary method for testing
        purposes only. It will be removed from the class.*/
        Node * curr = head;
        while(curr!=NULL){
            cout<<(curr->data)<<" ";
            curr = curr -> next;
        }cout<<endl;
    }
};










int main()
{
    LinkedList<int> l;
    for(int i=0; i<10; i++){
            l.insertAtHead(i);
    }

    for(int i=0; i<5; i++){
            l.eraseAtHead();
    }

    l.print();


    return 0;
}
