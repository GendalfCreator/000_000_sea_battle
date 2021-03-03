#include <iostream>
#include <iomanip>

using namespace std;

//#define FIELD_NAME(n) field ## n
#define POINT_ITEM(a, x, y) (*((*(a + (y))) + (x)))

//enum SHIPS {EMPTY = '_', singledeck = '1', doubledeck = '2', trippledeck = '3', fourdeck = '4'};
//enum TURNS {SHIP = '#', DAMAGE = 'X', MISS = 'o'};

class Ship {
public:
  Ship() {
    this -> descCount = 0;
  }

  Ship(int descCount) {
    this -> descCount = descCount;
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

private:
  enum shipStatus {WHOLE = '#', DAMAGED = 'X'};
  int descCount;
  int descStartX;
  int descStartY;
  int descEndX;
  int descEndY;
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
            *(*(this -> map + y) + x) = EMPTY;
          }
      }

    this -> ship[0].SetDescCount(4);

    for (int i = 1; i < 3; i++) {
        this -> ship[i].SetDescCount(3);
      }
    for (int i = 3; i < 6; i++) {
        this -> ship[i].SetDescCount(2);
      }
    for (int i = 6; i < 10; i++) {
        this -> ship[i].SetDescCount(1);
      }
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

  void setPoint(int x, int y) {

  }

  void Shot(int x, int y) {

  }

  Ship* getShip(int i) {
    return &ship[i];
  }
private:
  int sizeX;
  int sizeY;
  enum pointStatus {EMPTY = '_', MISS = 'o', WHOLE = '#', DAMAGED = 'X'};
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

private:

};



//typedef struct {
//  int sizeX;
//  int sizeY;
//  int singledeckcount;
//  int doubledeckcount;
//  int trippledeckcount;
//  int fourdeckcount;
//  SHIPS** map;
//  TURNS showturn;
//} Field;

//char getValue(SHIPS** array, const int x, const int y) {
//  return POINT_ITEM(array, x, y);
//}

//void setValue(SHIPS** array, const int x, const int y, SHIPS value) {
//  POINT_ITEM(array, x, y) = value;
//}

//int checkShip(Field &field, int x, int y) {
//  if (getValue(field.map, x - 1, y) == SHIP) {

//    }
//}

//void initField(Field &field) {
//    field.sizeX = 10;
//    field.sizeY = 10;
//    field.map = new SHIPS* [field.sizeY];

//    for (int y = 0; y < field.sizeY; y++) {
//        *(field.map + y) = new SHIPS [field.sizeX];
//      for (int x = 0; x < field.sizeX; x++){
//          setValue(field.map, x, y, EMPTY);
//        }
//      }
//}

//void printDesc(Field &fieldhuman, Field &fieldai) {
//  system("clear");
//  cout << "Морской бой. Новая игра \n" << endl;
//  cout << setiosflags(ios::right);
//  cout << setw(4) << "" << "1 2 3 4 5 6 7 8 9 10";
//  cout << "\t" << "1 2 3 4 5 6 7 8 9 10" << endl;

//  for (int y = 0; y < fieldhuman.sizeY; y++) {
//      cout << setw(3) << y + 1 << "|";
//      for (int x = 0; x < fieldhuman.sizeX; x++) {
//          cout << (char)((getValue(fieldhuman.map, x, y) != EMPTY) ? SHIP : EMPTY) << "|";
//        }
//      cout << setw(4)<< "" << setw(3) << y + 1 << "|";
//      for (int x = 0; x < fieldai.sizeX; x++) {
//          cout << (char)((getValue(fieldai.map, x, y) != EMPTY) ? SHIP : EMPTY) << "|";
//        }
//      cout << endl;
//      }
//  cout << endl;
//}

//void turnHuman(Field field) {
//  int x, y;
//  cout << "Укажите, куда поставить корабль (x y): ";
//  cin >> x >> y;
//  x--;
//  y--;
//  setValue(field.map, x, y, singledeck);
//}

int main() {

  Field field0, field1;
  Board board;

  field0.getShip(1)->GetDescCount();


  board.printBoard(field0, field1, "\t Морской бой. \t Новая игра \n");

  return 0;
}
