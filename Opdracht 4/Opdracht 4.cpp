// Opdracht 4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cstdlib>

using namespace std;

void information()
{

}//information

class element 
{
public:
    element* previous;
    int info;
    element* next;
};//element

class list 
{
private:
    element* entrance;
    element* exit;
public:
    list();
    void printFB();
    void printBF();
    void add(int n);
    void buildlist(int n);
};//list

//   +-----+      +-----+----+-----+        +-----+----+-----+      +-----+
//   |   --+----> | NULL| 10 |   --+------> |  |  | 20 | NULL| <----+--   |
//   +-----+      +-----+--+-+-----+        +-----+--+-+-----+      +-----+
//  L.ingang                    ^---------------                   L.uitgang
//       
// L.ingang (L van klasse lijst) wijst dus het eerste element uit een serie 
// elementen aan, waarbij ieder element informatie bevat (het info-veld), 
// en twee pointers: naar het vorige en volgende element;
// voor het voorbeeld hierboven zijn in totaal twee new's nodig. 

//constructor
list::list()
{
    entrance = nullptr;
    exit = nullptr;
}//list::list

//drukt lijst af van voor naar achter
void list::printFB() {
    element* help = entrance;
    cout << "VA afdrukken..." << endl;
    while (help != nullptr)
    {
        cout << help->info << endl;
        help = help->next;
    }
}//list::printFB

//drukt lijst af van achter naar voor
void list::printBF() {
    element* hulp = exit;
    cout << "AV afdrukken..." << endl;
    while (hulp != nullptr)
    {
        cout << hulp->info << endl;
        hulp = hulp->previous;
    }//while
    // TODO
}//list::printBF

void list::add(int n){
    element * p;
    p = new element;
    p->previous = nullptr;
    p->info = (10 * n);
    p->next = entrance;
    if (entrance != nullptr)
    {
        entrance->next = p;
    }//if
    else
    {
        exit = p;
    }//else
    entrance = p;
}//list::add

//maakt lijst met n elementen
void list::buildlist(int n) {
    int i;
    for (i = 1; i <= n; i++)
    {
        add(i);
    }//for
}//list::buildlist

//converteert de char nummers naar int nummers met maximale waarde
int readNumber(int maxi)
{
    //de input van de gebruiker
    char input;
    //pakt het eerstvolgende karakter
    cin.get(input);
    //het volgede karakter is \n dus pakken we het karakter erna
    cin.get(input);
    //het cijfer dat ontstaat
    int number = 0;
    //functie eindigt bij de \n na de eerste \n
    while (input != '\n')
    {
        if (input < '0' || input > '9' || (number * 10 + (input - 48)) > maxi)
        {
        }//if
        else
        {
            number = number * 10 + (input - 48);
        }//else
        input = cin.get();
    }//while

    //om delen door 0 te omzeilen
    if (number == 0)
    {
        return 1;
    }//if
    else
    {
        return number;
    }//else
}//readNumber

class boardbox
{
public:
    bool openedVisible;
    bool isCoffee;
    bool marked;
    int amount; //..8
    boardbox * neighbor[8];
    int x, y;
    boardbox();
    boardbox* find(int x, int y, boardbox* entrance);
};//class boardbox

//constructor
boardbox::boardbox()
{
    openedVisible = false;
    isCoffee = false;
    marked = false;
    amount = 0;
    int i;
    for (i = 0; i < 8; i++)
    {
        neighbor[i] = 0;
    }
    x = 0;
    y = 0;
}//boardbox::boardbox

class coffeeboard
{
private:
    int h, w;
    boardbox * entrance;
    //int coffeeAmount, moves;
    //void put();
    void createRow(int y, boardbox *&help);
    void createBoard();
    //int perc;
    //void repair();
    //void neighborzero();

public:
    coffeeboard();
    //~coffeeboard();

    //void humanMove();
    //void compMove();
    void init(int he, int wi, int pe);
    //void scatterCoffee();
};//class coffeeboard

coffeeboard::coffeeboard()
{
    entrance = nullptr;
    w = 30;
    h = 20;
}

boardbox * find(int x, int y, boardbox* entrance)
{
    boardbox* p = entrance;
    while (p != nullptr)
    {
        while (p->x != x)
        {
            p = p->neighbor[2];
        }
        while (p->y != y)
        {
            p = p->neighbor[4];
        }
        return p;
    }
    return nullptr;
}

void coffeeboard::init(int he, int wi, int pe)
{

    createBoard();
}

void coffeeboard::createRow(int y, boardbox *&help)
{
    boardbox box;
    int i;
    boardbox* boxPointer;
    boxPointer = new boardbox;
    int j;
    help = boxPointer;
    for (i = 0; i < w; i++)
    {
        for (j = 0; j < 8; j++)
        {
            boxPointer->neighbor[j] = nullptr;
        }
        boxPointer->x = box.x;
        boxPointer->y = y;
        box.x++;
        boxPointer->neighbor[2] = entrance;
        entrance->neighbor[6] = boxPointer;
        if (entrance != nullptr)
        {
            entrance->neighbor[2] = boxPointer;
        }//if
        entrance = boxPointer;
        cout << boxPointer->x << ":" << boxPointer->y << " ";
    }
}//coffeeboard::createRow

void coffeeboard::createBoard()
{
    boardbox * highPointer, * lowPointer, * verticalPointer;
    boardbox box;
    int i, j;
    verticalPointer = entrance;
    lowPointer = entrance;
    highPointer = entrance;

    for (i = 0; i < h; i++)
    {
        createRow(box.y, verticalPointer);
        if (i != 0)
        {
            lowPointer = verticalPointer;
            for (j = 0; j < w; j++)
            {
                highPointer->neighbor[4] = lowPointer;
                lowPointer->neighbor[0] = highPointer;
                if (highPointer->neighbor[2] != nullptr) 
                {
                    highPointer->neighbor[3] = lowPointer->neighbor[2];
                    lowPointer->neighbor[1] = highPointer->neighbor[2];
                }
                if (highPointer->neighbor[6] != nullptr)
                {
                    highPointer->neighbor[5] = lowPointer->neighbor[6];
                    lowPointer->neighbor[7] = highPointer->neighbor[6];
                }
                if (highPointer->neighbor[2] != nullptr)
                {
                    highPointer = highPointer->neighbor[2];
                    lowPointer = lowPointer->neighbor[2];
                }
            }
        }
        box.y++;
        cout << endl;
    }
}

int main() 
{
    coffeeboard board;
    board.init(1, 1, 1);
    return 0;
}//main


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
