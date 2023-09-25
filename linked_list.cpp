#include<iostream>


// Lista jednokierunkowa

using namespace std;

class Node
{   
    public:

    int val;
    Node* next;

    //Node(int x) : val(x), next(NULL) {};
};

void printList(Node* p)
{
    for(p; p != NULL; p = p->next)
    {
        cout << p->val << "  ";
    }
}

int listSize(Node* head)
{
    int counter = 0;

    while(head != NULL)
    {
        head = head->next;
        counter++;
    }

    return counter;
}

/*-----Dodawanie na początku listy--------*/
/* Funkcja przyjmuje dwa argumenty:
1. wskaźnik na węzęł (Node), aby
działać bezpośrednio na oryginale listy, a nie na kopi.
2. wartość która zostanie przypisana*/

void pushFront(Node** head, int value)                          
{
    Node* p = new Node();                               //Tworzymy nowy elementy typu Node

    p->val = value;                                     //przypisujemy mu wartość otrzymaną jako argument
    p->next = (*head);                                  //jako następny element przypisujemy głowę otrzymaną jako argument (głowa przysłana jako argument zostaje drugim elementem)
    *head = p;                                          //nadpisujemy head nowo utworzonym elementem (nowo utworzony element zostaje piewszym elementem)
}

/*-------Dodawanie na końcu listy----------*/
/* Funkcja przyjmuje dwa argumenty j.w
Należy rozpatrzyć dwa przypadi:
1. Gdy lista jest pusta (head = NULL).
Wtedy należy utworzyć nowy elementy i dodać do
niego wartości.
2. Gdy nie jest pusta, wtedy należy przejść po całej 
liście za pomocą dodatkowego wskaźnika, utworzyć nowy
element i dodać od niego wartości.
*/

void pushBack(Node** head, int value)
{
    if((*head) == NULL)                                                            //gdy head jest nullem
    {   
        (*head) = new Node();                                                      //utworzenie nowego elementu
        (*head)->val = value;                                                      //dodanie wartości
        (*head)->next = NULL;                                                      //dodanie wskaźnika next na NULL
    }
    else
    {

        Node* current = *head;                                                     //Utworzenie nowego pointera (ale nie elementu typu Node)

        while(current->next != NULL)                                               //Przejście po każdym elemencie listy do ostaniego elementu
        {                                                                          //należy zatrzymać się na ostatnim elemencie (dlatego pętla przechodzi po curren->next, a nie current)
            current = current->next;
        }

        current->next = new Node();                                                //Do wskaźnika next na ostatnim elemencie, dodanie nowego elementu
        current->next->val = value;                                                //Dodanie do niego wartości z funkcji
        current->next->next = NULL;                                                //Ustawienie wartości następnego na NULL
    }
}

/*-----Dodawanie elementu na wybranym indexie----*/
/*Należy rozpatrzeć trzy przypadki:
1. Gdy index jest równy 0,
2. Gdy index jest równy rozmiarowi listy,
3. Gdy index jest po środku.
*/

void pushByIndex(Node** head, int value, int index)
{
    if(index == 0)                                                                  //Jeśli podany index jest równy 0 to dodajemy element na początek listy
    {
        pushFront(head, value);
    }
    else if(index == listSize(*head))                                               //Jeśli index jest równy ilości elementów listy dodajemy element na koniec listy
    {
        pushBack(head, value);
    }
    else                                                                            //Jeśli jest w środku:
    {

        Node* current = *head;                                                      //Tworzymy wskaźnik do iteracji po liście
        int counter = 0;                                                            //Tworzymy zmienną licznikową
        
        while(current->next != NULL && counter != index-1 )                         //Iteracja po pętli. Dopóki następny nie będzie NULL (dodatkowe zabezpiczenie) i licznik nie będzie równy wybranemu indeksowi - 1
        {
            current = current->next;                                                //Iteracje
            counter++;
        }                                                                           //Zatrzymanie iteracji na wybranym indexie

        Node* nextElement = current->next;                                          //Zapisanie następnego elementu aby go nie stracić (i tym samym zapamiętanie dalszej części listy po nim)
        
        current->next = new Node();                                                 //Utworzenie nowego pustego elementu w current->next (czyli jeden dalej niż jesteśmy)
        current->next->val = value;                                                 //Dodanie do niego wartości z funkcji
        current->next->next = nextElement;                                          //Przypisanie dalszej części listy
    }
}

/*-----------Usuwanie pierwszego elementu------------*/
/*Prz usuwaniu należy wziąć pod uwagę przypadek gdy lista jest pusta*/

void popFront(Node** head)
{
    if(*head != NULL)                                                               //Sprawdzenie czy lista nie jest pusta
    {
        Node* tmp = (*head)->next;                                                  //Zapamiętanie następnego (drugiego) elementu na liście
        delete *head;                                                               //Usunięcie heada (dalsza część listy jest zapamiętana w temp)
        *head = tmp;                                                                //Przypisanie do head zmiennej temp czyli dalszej części listy bez pierwszego elementu
    }

}

/*---------Usuwanie ostatniego elementu---------------*/
/*Przy usuwaniu ostatniego elementu należy wziąć pod uwagę dwa przypadki:
1. Gdy lista jest jednoelementowa,
2. Gdy lista ma więcej niż jeden element.*/

void popBack(Node** head)
{

    if((*head)->next == NULL)                                                      //Gdy lista ma jeden element
    {
        *head = NULL;                                                              //Ustawienie głowy na NULL
    }
    else
    {
        Node* current = *head;                                                     //Dodatkowy wskaźnik do iteracji

        while(current->next->next != NULL)                                         //Pętla do przedostatniego elementu
        {
            current = current->next;
        }                                                                          //Zatrzymanie pętli na przedostatnim elemencie

        delete(current->next);                                                     //Usunięcie ostatniego elementu
        current->next = NULL;                                                      //Ustawienie wskaźnika next przedostatniego elementu (teraz już ostatniego) na NULL
    }
}

void popByIndex(Node** head, int index)
{
    if(index == 0)                                                                 //Gdy index jest równy 0
    {
        popFront(head);                                                            //Usuń pierwszy element
    }
    else
    {
        Node* current = *head;                                                     //Wskaźnik do iteracji
        int counter = 0;                                                           //Licznik do iteracji

        while(current->next != NULL && counter != index-1)                         //Przeskakuj elementy do elementu jeden przed indeksem
        {
            current = current->next;
            counter++;
        }                                                                          //Zatrzymanie pętli jeden przed indeksem

        Node* nextElement = current->next->next;                                   //Dodatkowy wskaźnik do zapisania elementu jeden po tym który będzie usunięty (i dalszej części listy za nim)
        
        delete(current->next);                                                     //Usunięcie elementu (następny po tym na którym zatrzymała się pętla)

        current->next = nextElement;                                                //Dodanie do następnika adresu dalszej części listy
    }

}

int main()
{
    Node* head = NULL;                                              //utworzenie listy

    //head = NULL;

    pushFront(&head, 12);                                   //Aby funkcja działała poprawnie należy wysłać do niej adres listy i wartość.
    pushFront(&head, 22);
    pushFront(&head, 33);
    pushFront(&head, 17);
    pushFront(&head, 19);
    pushBack(&head, 44);
    pushByIndex(&head, 27, 1);
    popFront(&head);
    popBack(&head);
    popByIndex(&head, 3);
    popByIndex(&head, 3);

    cout << "Lista: " << listSize(head) << endl;
    
    printList(head);


}
