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
    int coffeeAmount, nocoffeeAmount;
    int visibleAmount, moves;
    //void put();
    void createRow(int y, boardbox*& verticalPointer, boardbox*& entrance);
    void createBoard(boardbox*& entrance);
    int perc;
    void neighborzero(boardbox * neighbor, coffeeboard & board);
    void clean(boardbox* entrance, coffeeboard board);
    void rescatterCoffee(boardbox* entrance);

public:
    coffeeboard();
    //~coffeeboard();
    void print(boardbox* entrance);
    bool exit;
    bool win;
    int games;
    void humanMove(boardbox * entrance, coffeeboard & board);
    void mark(boardbox* entrance);
    void randomMove(boardbox * entrance, coffeeboard& board);
    void generalMove(boardbox* boxpointer, coffeeboard& board);
    void computerMove(boardbox * entrance, coffeeboard& board);
    void init(int he, int wi, int pe, boardbox*& entrance);
    void checkCoffee(boardbox * entrance);
};//class coffeeboard

