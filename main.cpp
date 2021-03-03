#include <iostream>
#include <iomanip>

using namespace std;

//#define FIELD_NAME(n) field ## n
#define POINT_ITEM(a, x, y) (*((*(a + (y))) + (x)))

enum pointStatus {EMPTY = '_', MISS = 'o', SHIP = '#', DAMAGED = 'X'};

class Ship {
public:
  Ship() {
    this -> descCount = 0;
    this ->shipStatus = false;
  }

  Ship(int descCount) {
    this -> descCount = descCount;
    this -> shipStatus = true;
  }

  int GetDescCount() {
    return descCount;
  }

  void SetDescCount(int value) {
    descCount = value;
  }

  int GetDescStartX() {
    return descStartX;
  }

  void SetDescStartX(int value) {
    descStartX = value;
  }

  int GetDescStartY(){
    return descStartY;
  }

  void SetDescStartY(int value) {
    descStartY = value;
  }

  int GetDescEndX(){
    return descEndX;
  }

  void SetDescEndX(int value) {
    descEndX = value;
  }

  int GetDescEndY(){
    return descEndY;
  }

  void SetDescEndY(int value) {
    descEndY = value;
  }

  bool GetShipStatus() {
    return shipStatus;
  }
  ~Ship() {

  }

private:
  enum point{WHOLE = '#', DAMAGED = 'X'};
  int descCount;
  int descStartX;
  int descStartY;
  int descEndX;
  int descEndY;
  bool shipStatus;
};

class Field {
public:
  Field() {
    sizeX = 10;
    sizeY = 10;

    this -> map = new pointStatus*[this -> sizeY];
    for (int y = 0; y < (this -> sizeY); y++) {
        *(this -> map + y) = new pointStatus[this -> sizeX];
        for (int x = 0; x < (this -> sizeX); x++) {
            setPoint(x, y, EMPTY);
          }
      }

    for (int i = 1; i < 3; i++) {
        this -> ship[i] = Ship(3);
      }
    for (int i = 3; i < 6; i++) {
        this -> ship[i] = Ship(2);
      }
    for (int i = 6; i < 10; i++) {
        this -> ship[i] = Ship(1);
      }
    this -> ship[0] = 4;
  }

  Ship* getShip(int i) {
    return &ship[i];
  }

  int getSizeX() {
    return sizeX;
  }

  int getSizeY() {
    return sizeY;
  }

  char getPoint(int x, int y) {
    return *(*(this->map + y) + x);
  }

  void setPoint(int x, int y, pointStatus status) {
    *(*(this -> map + y) + x) = status;
  }

  int Shot(int x, int y, Field &field) {
    x--;
    y--;
    if (field.getPoint(x, y) == EMPTY) {
        setPoint(x, y, MISS);
        return 0;
      }
    else if (field.getPoint(x, y) == SHIP){
        setPoint(x, y, DAMAGED);
        return 1;
      }
    else {
        return -1;
      }
  }

  ~Field() {

  }

private:
  int sizeX;
  int sizeY;
  pointStatus** map;
  Ship ship[10];
};


class Board {
public:
  void printBoard(Field &field0, Field &field1, string message) {
    system("clear");
    cout << message << endl;
    setiosflags(ios::right);
    cout << setw(5) << "" << "1 2 3 4 5 6 7 8 9 10";
    cout << setw(6) << "" << "1 2 3 4 5 6 7 8 9 10" << endl;
    for (int y = 0; y < field0.getSizeY(); y++) {
        cout << setw(4) << y+1 << "|";
        for (int x = 0; x < field0.getSizeX(); x++) {
            cout << field0.getPoint(x, y) << "|";
          }
        cout << setw(5) << y+1 << "|";
        for (int x = 0; x < field1.getSizeX(); x++) {
            cout << field1.getPoint(x, y) << "|";
          }
        cout << endl;
      }
  }

  bool turnHuman(Field &field1, Field &field10) {
    int x = -1, y = -1;

    cout << "\n\tУкажите строку и столбец: ";

    cin >> y >> x;
    field1.Shot(x, y, field10);
    return true;
  }

  bool CheckWin() {

  }
private:

};

int main() {
  Field field0, field1, field10;
  Board board;

  field10.setPoint(7, 4, SHIP);

  while (true) {
      board.printBoard(field0, field1, "\t Морской бой. \t Новая игра \n");
      board.turnHuman(field1, field10);
    }


  return 0;
}
