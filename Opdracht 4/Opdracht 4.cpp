// Opdracht 4.cpp : This file contains the 'main' function. Program execution begins and ends there.
// NOTES:
// - Double digits coords in zet
// - Wat gebeurt er als er letters worden ingetikt in Zet
// - Wat gebeurt er bij readChar als je een cijfer intikt
// - computerzet
// - percentage coffe in de min (wat is default?)
// - Board view double digits
// - 1e zet NOOIT koffie!!!

// EXTRA
// - Maak een file met constanten

#include <iostream>
#include <cstdlib>
#include "coffeeboard.h"

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

void menu(char & input)
{
    cout << "Wie speelt het spel? (M)ens of (C)omputer? ";
    input = readChar();
    switch (input)
    {
    case 'm': case 'M':
        cout << "\nMens" << endl;
        break;
    case 'c': case 'C':
        cout << "\nIk speel voor jou noob! " << endl;
        break;
    default:
        break;
    }
}

void submenu(char & input, coffeeboard & board, boardbox* entrance)
{
    cout << "Kies uit: (Z)et, (R)andom, (M)arkeer, (T)erug, (S)top  ";
    input = readChar();
    switch (input)
    {
    case 'z': case 'Z':
        cout << "\nZet " << endl;
        board.humanMove(entrance, board);
        board.print(entrance);
        break;
    case 'r': case 'R':
        cout << "\nRandom " << endl;
        break;
    case 'm': case 'M':
        board.mark(entrance);
        board.print(entrance);
        break;
    case 't': case 'T':
        cout << "\nTerug " << endl;
        break;
    case 's': case 'S':
        board.exit = true;
        cout << "\nStop " << endl;
        break;
    }
}

int main() 
{
    coffeeboard board;
    boardbox* entrance = nullptr;
    int h, w, p;
    char input = 'a';

    cout << "Hoe hoog moet het bord zijn (max 50)? ";
    h = readNumber(50);
    cout << "Hoe breed moet het bord zijn (max 100)? ";
    w = readNumber(100);
    cout << "Wat is de percentage voor de hoeveelheid koffie (max 100)? ";
    p = readNumber(100);
    board.init(h, w, p, entrance);
    while (input <= 'b' || (input >= 'd' && input <= 'l') || (input >= 'n'
    && input <= 'B') || (input >= 'D' && input <= 'L') || input >= 'N')
    {
        menu(input);
        if (input == 'm' || input == 'M')
        {
            break;
        }
    }

    if (input == 'm' || input == 'M')
    {   
        board.print(entrance);
        while (board.exit == false)
        {
            submenu(input, board, entrance);
            
        }
    }
    return 0;
}//main

//input <= 'r' || (input >= 't' && input <= 'R') || input >= 'T'
//if (board.exit == true)
//            {
//                break;
//            }
            
//char leesOptie() {
//	char invoer2[3];
//	cin.get(invoer2, 3);
//	cin.ignore();
//	return invoer2[0];
//}//leesOptie

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
