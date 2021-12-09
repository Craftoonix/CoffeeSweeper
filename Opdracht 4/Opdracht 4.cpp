// Opdracht 4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cstdlib>

using namespace std;


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
        boardbox* neighbor[8];
        int x, y;
        boardbox();

};

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
}

class coffeeboard
{
private:
    int h, w;
    coffeeboard* entrance;
    int coffeeAmount, moves;
    //boardbox* goto(int i, int j);
    void put();
    void createRow();
    void createBoard();
    int perc;
    void repair();
    void neighborzero();



public:
    coffeeboard();
    ~coffeeboard();

    void humanMove();
    void compMove();
    void init(int he, int wi, int pe);
    void scatterCoffee();
};




int main()
{
    std::cout << "Hello World!\n";
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
