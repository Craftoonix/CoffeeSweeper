// Opdracht 4.cpp : This file contains the 'main' function. Program execution begins and ends there.
// NOTES:
// - Double digits coords in zet
// - Wat gebeurt er als er letters worden ingetikt in Zet
// - Wat gebeurt er bij readChar als je een cijfer intikt
// - Board view double digits
// - titels voor computerspeler aantal wins and loses
// - coffeeteken bij loss ipvv neighbourcount

// EXTRA
// - Maak een file met constanten

#include <iostream>
#include <cstdlib>
#include "coffeeboard.h"

using namespace std;

void information()
{

}//information

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
        board.humanMove(entrance, board);
        board.print(entrance);
        break;
    case 'r': case 'R':
        board.randomMove(entrance, board);
        board.print(entrance);
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

void computerMenu(boardbox*& entrance, coffeeboard& board)
{
    cout << "Hoeveel games zal de computer spelen? ";
    board.games = readNumber(100000);
    board.computerMove(entrance, board);
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
        if (input == 'c' || input == 'C')
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
    else if (input == 'c' || input == 'C')
    {
        computerMenu(entrance, board);
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
