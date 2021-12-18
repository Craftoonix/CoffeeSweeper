//file coffeeboard.h

int readNumber(int maxi);
char readChar();
char read();

class boardbox
{
public:
    bool openedVisible;
    bool isCoffee;
    bool marked;
    int amount; //..8
    boardbox* neighbor[8];
    int x, y;
    boardbox(); //constructor
    boardbox* find(int x, int y, boardbox* entrance);
};//class boardbox

class coffeeboard
{
private:
    int h, w;
    int coffeeAmount = 0;
    int nocoffeeAmount = 0;
    int visibleAmount = 0;
    //moves;
    //void put();
    void createRow(int y, boardbox*& verticalPointer, boardbox*& entrance);
    void createBoard(boardbox*& entrance);
    int perc;
    
    //void repair();
    //void neighborzero();

public:
    coffeeboard();
    //~coffeeboard();
    void print(boardbox* entrance);
    bool exit;
    void humanMove(boardbox * entrance, coffeeboard & board);
    void mark(boardbox* entrance);
    void computerMove(boardbox * entrance);
    void init(int he, int wi, int pe, boardbox*& entrance);
    void scatterCoffee(boardbox * entrance);
};//class coffeeboard

