/**
*  Course: CMPS 2143 - OOP
*  Assignment: A02
*  Purpose: Create two lists and combine them together and
*  find an int value in a list and return it as if the list
*  were an array
* 
*  @author Terry Griffin (comments by Tyler Roop)
*  @version 1.1
*/

#include <iostream>

using namespace std;

int A[100];

struct Node
{
    int x;
    Node *next;
    Node()
    {
        x = -1;
        next = NULL;
    }
    Node(int n)
    {
        x = n;
        next = NULL;
    }
};

class List
{
  private:
    Node *Head;
    Node *Tail;
    int Size;

  public:
    List()
    {
        Head = Tail = NULL;
        Size = 0;
    }
    
    /**
    *   Adds a new node onto the end of a list
    *
    *   @param {int} val : Value to be entered as
    *                      node's int
    *   @return {void}
    */
    void Push(int val)
    {
        // allocate new memory and init node
        Node *Temp = new Node(val);

        if (!Head && !Tail)
        {
            Head = Tail = Temp;
        }
        else
        {
            Tail->next = Temp;
            Tail = Temp;
        }
        Size++;
    }

    /**
    *   Adds a new node onto the start of a list
    *
    *   @param {int} val : Value to be entered as
    *                      node's int
    *   @return {void}
    */
    void Insert(int val)
    {
        // allocate new memory and init node
        Node *Temp = new Node(val);

        // figure out where it goes in the list

        Temp->next = Head;
        Head = Temp;
        if (!Tail)
        {
            Tail = Head;
        }
        Size++;
    }
    
    /**
    *   Prints the last item in a list
    *
    *   @return {void}
    */
    void PrintTail()
    {
        cout << Tail->x << endl;
    }
    
    /**
    *   Prints a list
    *
    *   @return {void}
    */
    string Print()
    {
        Node *Temp = Head;
        string list;

        while (Temp != NULL)
        {
            list += to_string(Temp->x) + "->";
            Temp = Temp->next;
        }

        return list;
    }

    // not implemented 
    int Pop()
    {
        Size--;
        return 0; //
    }

    /**
    *   concatenates two lists
    *
    *   @param {const List &} Rhs : List on right hand side of
    *                               addition sign to be concatenated
    *
    *   @return {List} : A list containing both of the concatenated lists
    */
    List operator+(const List &Rhs)
    {
        // Create a new list that will contain both when done
        List NewList;

        // Get a reference to beginning of local list
        Node *Temp = Head;

        // Loop through local list and Push values onto new list
        while (Temp != NULL)
        {
            NewList.Push(Temp->x);
            Temp = Temp->next;
        }

        // Get a reference to head of Rhs
        Temp = Rhs.Head;

        // Same as above, loop and push
        while (Temp != NULL)
        {
            NewList.Push(Temp->x);
            Temp = Temp->next;
        }

        // Return new concatenated version of lists
        return NewList;
    }
    
    /**
    *   Implementation of [] operator.  This function returns an
    *   int value as if the list were an array.
    *   
    *   @param {int} index : Place in list that desired value is located
    *
    *   @return {int} : desired value
    */
    int operator[](int index)
    {
        Node *Temp = Head;

        if (index >= Size)
        {
            cout << "Index out of bounds, exiting";
            exit(0);
        }
        else
        {

            for (int i = 0; i < index; i++)
            {
                Temp = Temp->next;
            }
            return Temp->x;
        }
    }

    /**
    *   Implementation of cout to be able to print lists
    *   
    *   @param {ostream &} os : outstream that prints with cout
    *   @param {List} L: List to be printed
    *
    *   @return {ostream &} : returns address of ostream to be printed with cout
    */
    friend ostream &operator<<(ostream &os, List L)
    {
        os << L.Print();
        return os;
    }
};

int main(int argc, char **argv)
{
    List L1;
    List L2;

    for (int i = 0; i < 25; i++)
    {
        // Fills L1 with values from 0 to 24 in ascending order
        L1.Push(i);
    }

    for (int i = 50; i < 100; i++)
    {
        // Fills L2 with values from 50 to 99 in ascending order
        L2.Push(i);
    }

    //cout << L1 << endl;
    
    // Prints the last value in both lists
    L1.PrintTail();
    L2.PrintTail();

    // concatenates L1 and L2 into L3
    List L3 = L1 + L2;
    // prints L3
    cout << L3 << endl;

    // prints the fifth value in L3
    cout << L3[5] << endl;
    return 0;
}
