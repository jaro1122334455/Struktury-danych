#include<iostream>

// Lista dwukierunkowa

using namespace std;

class Node
{
    public:

    int val;
    Node* next;
    Node* prev;
};

void printList(Node* head)
{
    while(head != NULL)                                       //Pętla do wyświetlania wartości
    {
        cout << head->val << " ";
        head = head->next;
    }
}

void printListReverse(Node* head)
{
    while(head->next != NULL)                                 //Pierwotne przejście listy do ostatniego elementu
    {
        head = head->next;
    }
    while(head != NULL)                                       //Pętla do wyświeltania wartości
    {
        cout << head->val << " ";
        head = head->prev;
    }
}

void pushFront(Node** head, int value)
{
    if(*head == NULL)                                           //Gdy lista jest pusta
    {
        (*head) = new Node();                                   //Utworzenie nowego elementu w head
        (*head)->val = value;                                   //Przypisanie wartości
        (*head)->next = NULL;                                   //Ustawienie next i prev na NULL (bo to pierwszy element)
        (*head)->prev = NULL;
    }
    else                                                         //Gdy nie jest pusta
    {
        Node* current = new Node();                              //Utworzenie nowego elementu
        current->val = value;                                    //Przypisanie wartości

        current->prev = NULL;                                    //Ustawienie poprzednika current na NULL
        current->next = *head;                                   //Ustawienie następnika current na obecną głowę (tak aby current był przed head)
        (*head)->prev = current;                                 //Ustawienie poprzednika obecnego head na nowy element (current)
        *head = current;                                         //Zmiana head na nowy element
    }
}

void pushBack(Node** head, int value)
{
    if(*head == NULL)
    {
        *head = new Node();                                        //Gdy lista pusta działanie jest takie samo jak w przypadku dodania elementu na początek listy
        (*head)->val = value;
        (*head)->next = NULL;
        (*head)->prev = NULL;
    }
    else
    {
        Node* current = *head;                                      //Wskaźnik current na head
        
        while(current->next != NULL)                                //Pętla do ostatniego elementu
        {
            current = current->next;
        }                                                           //Zatrzymanie na ostatnim elemencie

        current->next = new Node();                                 //Na następniku ostatniego elementu utworzenie nowego elementu
        current->next->val = value;                                 //Dodanie do niego wartości
        current->next->prev = current;                              //Poprzednik nowo utworzonego elementu usrawiony na obecny element
        current->next->next = NULL;                                 //Następnik nowego elementu na NULL

        //cout << current->val << endl;

    }
}

void pushByIndex(Node** head, int value, int index)
{
    if(index == 0)                                                        //Jeśli index 0 dodaj na poczatek listy
    {
        pushFront(head, value);
    }
    else                                                                  //Jeśli nie to:
    {   
        Node* current = *head;                                            //Wskaźnik na head
        int counter = 0;
        
        while(current->next != NULL && counter != index-1)                //Pętla do wskazanego elementu
        {
            current = current->next;
            counter++;
        }
        
        Node* nextElement = current->next;                                 //Zapisanie następnego elementu aby go nie zgubić
        current->next = new Node();                                        //Utworzenie nowego elementu
        current->next->prev = current;                                     //Ustawienie poprzednika nowego elementu na obecny element
        current->next->val = value;                                        //Przypisanie wartości do nowego elemntu
        current->next->next = nextElement;                                 //Ustawienie następnika nowego elementu na wskaźnik gdzie zapisany był stary następnik i dalsza część listy 
        nextElement->prev = current->next;                                 //Zamknięcie łańcucha listy

    }
}

int main()
{
    Node* head = NULL;
    Node* tail;

    pushFront(&head, 2);
    pushFront(&head, 5);
    pushFront(&head, 7);
    pushBack(&head, 8);

    pushByIndex(&head, 12, 2);
    
    
    printList(head);
    cout << endl;
    printListReverse(head);


    //pushFront(&head, 7);

    //printList(head);

    //printListReverse(tail);

}