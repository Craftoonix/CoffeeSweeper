//file coffeeboard.cpp
#include <iostream>
#include "coffeeboard.h"

using namespace std;

//leest het karakter die de gebruiker geeft zonder enters
//char read()
//{
//    //de input van de gebruiker
//    char input;
//    //pakt het eerst volgende karakter
//    cin.get(input);
//    while (input == '\n')
//    {
//        cout << input;
//        //cin.get(input);
//    }//if
//    return input;
//}//read

//leest het karakter die de gebruiker geeft zonder enters
char readChar()
{
    //de input van de gebruiker
    char input;
    //pakt het eerst volgende karakter
    cin.get(input);
    if (input == '\n')
    {
        cin.get(input);
    }//if
    cin.ignore();
    return input;
}//read

int calculateInput(char input, int total)
{
    const int charZero = 48;
    const int factor10 = 10;

    return total * factor10 + (input - charZero);
}

//converteert de char nummers naar int nummers met maximale waarde
int readNumber(int maxi)
{
    //de input van de gebruiker
    char input;
    //pakt het eerstvolgende karakter
    cin.get(input);    
    //het cijfer dat ontstaat
    int number = 0;
    const int charZero = 48;
    const int charNine = 57;
    int total = 0;
    // input: abc123def1

    //functie eindigt bij de \n na de eerste \n
while (input != '\n')
    {
        total = calculateInput(input, number);
        if (input >= charZero && input <= charNine && total <= maxi)
        {
            number = total;
        }

        if (total > maxi)
        {
            number = maxi;
            break;
        }
        cin.get(input);
    }//while
    return number;
}//readNumber

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
        neighbor[i] = nullptr;
    }
    x = 0;
    y = 0;
}//boardbox::boardbox

coffeeboard::coffeeboard()
{
    w = 0;
    h = 0;
    perc = 0;
    exit = false;
}

void coffeeboard::print(boardbox* entrance)
{
    boardbox* helpX, * helpY;
    int i;
    helpX = entrance;
    helpY = entrance;
    cout << "\nDe totale hoeveelheid koffie is: " << coffeeAmount << endl;
    cout << "\n  |";
    for (i = 0; i < w; i++)
    {
        cout << " " << (i % 10);
    }
    cout << "\n--+";
    for (i = 0; i < (2 * w); i++)
    {
        cout << "-";
    }
    cout << "\n";
    while (helpY != nullptr)
    {
        cout << helpY->y << " |" << " ";
        while (helpX != nullptr)
        {
            if (helpX->amount >= 1 && helpX->openedVisible == true)
            {
                cout << helpX->amount << " ";
            }
            else if (helpX->marked == true)
            {
                cout << "# ";
            }
            else if (helpX->openedVisible == true)
            {
                cout << "+ ";
            }
            else
            {
                cout << ". ";
            }
            helpX = helpX->neighbor[2];
        }
        cout << "\n";
        helpY = helpY->neighbor[4];
        helpX = helpY;
    }
}

boardbox* find(int x, int y, boardbox* entrance)
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

void coffeeboard::init(int he, int wi, int pe, boardbox*& entrance)
{
    h = he;
    w = wi;
    perc = pe;
    createBoard(entrance);
    scatterCoffee(entrance);
}

void coffeeboard::createRow(int y, boardbox*& verticalPointer, boardbox*& entrance)
{
    boardbox box;
    int i;
    boardbox* boxPointer, * boxPointer2;
    boxPointer = new boardbox;
    int random = 0;
    boxPointer2 = boxPointer;
    verticalPointer = boxPointer;
    if (entrance == nullptr)
    {
        entrance = boxPointer;
    }
    for (i = 0; i < w; i++)
    {
        boxPointer->x = box.x;
        boxPointer->y = y;
        if (perc > 0)
        {
            srand(time(NULL) % rand());
            random = rand() % (100 / perc);
            if (random == 0)
            {
                boxPointer->isCoffee = true;
            }
        }
        box.x++;
        if (i < (w - 1))
        {
            boxPointer->neighbor[2] = new boardbox;
            boxPointer2 = boxPointer->neighbor[2];
            boxPointer2->neighbor[6] = boxPointer;
            boxPointer = boxPointer2;
        }
    }
}//coffeeboard::createRow

void coffeeboard::scatterCoffee(boardbox* entrance)
{
    boardbox* boxPointer = entrance;
    int neighborCounter, xCoord, yCoord;
    int yCounter = 0;
    int i;

    for (yCoord = 0; yCoord < h; yCoord++) //omlaag gaan
    {
        for (i = 0; i < yCounter; i++)
        {
            if (boxPointer->neighbor[4] != nullptr)
            {
                boxPointer = boxPointer->neighbor[4];
            }
        }
        for (xCoord = 0; xCoord < w; xCoord++) //naar rechts gaan
        {
            for (neighborCounter = 0; neighborCounter < 8; neighborCounter++) //buren tellen
            {
                if (boxPointer->neighbor[neighborCounter] != nullptr) //*boxpointer.neighbor[k]
                {
                    if ((boxPointer->neighbor[neighborCounter])->isCoffee == true) //*(boxpointer.neighbor[k]).isCoffee
                    {
                        boxPointer->amount++;
                    }
                }
            }
            if (boxPointer->isCoffee == true)
            {
                coffeeAmount++;
            }
            if (boxPointer->neighbor[2] != nullptr)
            {
                boxPointer = boxPointer->neighbor[2];
            }
        }
        yCounter++;
        boxPointer = entrance;
    }
    nocoffeeAmount = (w * h) - coffeeAmount;
}//coffeeboard::scatterCoffee

void coffeeboard::createBoard(boardbox*& entrance)
{
    boardbox* highPointer, * lowPointer, * verticalPointer;
    boardbox box;
    int yCoord, xCoord, yCoordHP; //before: i, j, k
    verticalPointer = nullptr;
    lowPointer = nullptr;
    highPointer = nullptr;
    for (yCoord = 0; yCoord < h; yCoord++)
    {
        createRow(box.y, verticalPointer, entrance);
        if (yCoord != 0)
        {
            lowPointer = verticalPointer;

            highPointer = entrance;
            for (yCoordHP = 0; yCoordHP < (yCoord - 1); yCoordHP++)
            {
                highPointer = highPointer->neighbor[4];
            }

            for (xCoord = 0; xCoord < w; xCoord++)
            {
                highPointer->neighbor[4] = lowPointer;
                lowPointer->neighbor[0] = highPointer;
                if (highPointer->neighbor[6] != nullptr)
                {
                    highPointer->neighbor[5] = lowPointer->neighbor[6];
                    lowPointer->neighbor[7] = highPointer->neighbor[6];
                }
                if (highPointer->neighbor[2] != nullptr)
                {
                    highPointer->neighbor[3] = lowPointer->neighbor[2];
                    lowPointer->neighbor[1] = highPointer->neighbor[2];
                    highPointer = highPointer->neighbor[2];
                    lowPointer = lowPointer->neighbor[2];
                }
            }
        }
        box.y++;
    }
}

void coffeeboard::humanMove(boardbox * entrance, coffeeboard & board)
{
    int inputX, inputY;
    cout << "Wat is de x-coordinaat van uw zet? ";
    inputX = readNumber(w - 1);
    cout << "Wat is de y-coordinaat van uw zet? ";
    inputY = readNumber(h - 1);
    find(inputX, inputY, entrance)->openedVisible = true;
    if (find(inputX, inputY, entrance)->isCoffee)
    {
        cout << "die pls\n"
            << "computer: ok\n";
        board.exit = true;
    }
    if (find(inputX, inputY, entrance)->isCoffee == false)
    {
        visibleAmount++;
    }
    if (visibleAmount == nocoffeeAmount)
    {
        cout << "\nYou got lucky..." << endl;
        board.exit = true;
    }
}

void coffeeboard::computerMove(boardbox* entrance)
{ 
    int inputX, inputY;
    inputX = rand();
    inputY = rand();
    find(inputX, inputY, entrance);
}

void coffeeboard::mark(boardbox* entrance)
{
    int inputX, inputY;
    cout << "Wat is de x-coordinaat van uw marker? ";
    inputX = readNumber(w - 1);
    cout << "Wat is de y-coordinaat van uw marker? ";
    inputY = readNumber(h - 1);
    find(inputX, inputY, entrance)->marked = !find(inputX, inputY, entrance)->marked;
}