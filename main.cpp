#include <iostream>
#include <iomanip>
#include <cmath>
#include <random>

using namespace std;

#define VAR_NAME(var ,n) var ## n
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

    this -> ship[0] = 4;
    for (int i = 1; i < 3; i++) {
        this -> ship[i] = Ship(3);
      }
    for (int i = 3; i < 6; i++) {
        this -> ship[i] = Ship(2);
      }
    for (int i = 6; i < 10; i++) {
        this -> ship[i] = Ship(1);
      }
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

  bool checkShipSpace(int shipId, int startx, int starty, int endx, int endy) {
    int descCount = this -> getShip(shipId) -> GetDescCount();
    int descCheck = 0;

    if (starty == endy) {//Если корабль раположен горизонтально
        if (startx == 0 && starty == 0) {//Если координаты начала корабля упираются в угол 0 0
            for (int i = 0; i < descCount; i++) {
                char point0 = this -> getPoint((startx + i) + 0, starty + 0);
                char point1 = this -> getPoint((startx + i) + 0, starty + 1);
                char point2 = this -> getPoint((startx + i) + 1, starty + 1);
                char point3 = this -> getPoint((startx + i) + 1, starty + 0);

                if (point0 != SHIP && point1 != SHIP && point2 != SHIP && point3 != SHIP) {
                    descCheck++;
                  }
              }
          }
        else if (startx > 0 && starty == 0 && endx < 9) {//Если корабль прижат к верхней границе
            for (int i = 0; i < descCount; i++) {
                char point0 = this -> getPoint((startx + i) + 0, starty + 0);
                char point1 = this -> getPoint((startx + i) + 0, starty + 1);
                char point2 = this -> getPoint((startx + i) + 1, starty + 1);
                char point3 = this -> getPoint((startx + i) + 1, starty + 0);
                char point4 = this -> getPoint((startx + i) - 1, starty + 0);
                char point5 = this -> getPoint((startx + i) - 1, starty + 1);

                if (point0 != SHIP && point1 != SHIP && point2 != SHIP && point3 != SHIP && point4 != SHIP && point5 != SHIP) {
                    descCheck++;
                  }
              }
          }
        else if (endx == 9 && endy== 0) {//Если координаты конца корабля упираются в угол 9 0
            for (int i = 0; i < descCount; i++) {
                char point0 = this -> getPoint((startx + i) - 0, starty + 0);
                char point1 = this -> getPoint((startx + i) - 1, starty + 0);
                char point2 = this -> getPoint((startx + i) - 1, starty + 1);
                char point3 = this -> getPoint((startx + i) - 0, starty + 1);

                if (point0 != SHIP && point1 != SHIP && point2 != SHIP && point3 != SHIP) {
                    descCheck++;
                  }
              }
          }
        else if (startx == 0 && starty > 0 && starty < 9) {//Если корабль прижат к левой границе
            for (int i = 0; i < descCount; i++) {
                char point0 = this -> getPoint((startx + i) + 0, starty + 0);
                char point1 = this -> getPoint((startx + i) + 0, starty - 1);
                char point2 = this -> getPoint((startx + i) + 1, starty - 1);
                char point3 = this -> getPoint((startx + i) + 1, starty + 0);
                char point4 = this -> getPoint((startx + i) + 1, starty + 1);
                char point5 = this -> getPoint((startx + i) - 0, starty + 1);

                if (point0 != SHIP && point1 != SHIP && point2 != SHIP && point3 != SHIP && point4 != SHIP && point5 != SHIP) {
                    descCheck++;
                  }
              }
          }
        else if ((startx > 0 && endx < 9) && (starty > 0 && endy < 9)) {//Если корабль не касается границ поля
            for (int i = 0; i < descCount; i++) {//Проверить точки на соприкосновение
                char point0 = this -> getPoint((startx + i) - 0, (starty) - 1);
                char point1 = this -> getPoint((startx + i) - 1, (starty) - 1);
                char point2 = this -> getPoint((startx + i) - 1, (starty) - 0);
                char point3 = this -> getPoint((startx + i) - 1, (starty) + 1);
                char point4 = this -> getPoint((startx + i) - 0, (starty) + 1);
                char point5 = this -> getPoint((startx + i) + 1, (starty) + 1);
                char point6 = this -> getPoint((startx + i) + 1, (starty) + 0);
                char point7 = this -> getPoint((startx + i) + 1, (starty) - 1);
                char point8 = this -> getPoint((startx + i) - 0, (starty) - 0);
                //Если соприкосновения или занятых точек нету
                if (point0 != SHIP && point1 != SHIP &&  point2 != SHIP && point3 != SHIP && point4 != SHIP && point5 != SHIP && point6 != SHIP && point7 != SHIP && point8 != SHIP) {
                    descCheck++;//прибавить свободную клетку
                  }
              }
          }
        else if (endx == 9 && starty > 0 && endy < 9) {//если прижат к правой границе
            for (int i = 0; i < descCount; i++) {
                char point0 = this -> getPoint((startx + i) + 0, starty + 0);
                char point1 = this -> getPoint((startx + i) + 0, starty - 1);
                char point2 = this -> getPoint((startx + i) - 1, starty - 1);
                char point3 = this -> getPoint((startx + i) - 1, starty + 0);
                char point4 = this -> getPoint((startx + i) - 1, starty + 1);
                char point5 = this -> getPoint((startx + i) - 0, starty + 1);

                if (point0 != SHIP && point1 != SHIP && point2 != SHIP && point3 != SHIP && point4 != SHIP && point5 != SHIP) {
                    descCheck++;
                  }
              }
          }
        else if (startx == 0 && starty == 9) {//если начало в углу 0 9
            for (int i = 0; i < descCount; i++) {
                char point0 = this -> getPoint((startx + i) + 0, starty - 0);
                char point1 = this -> getPoint((startx + i) + 0, starty - 1);
                char point2 = this -> getPoint((startx + i) + 1, starty - 1);
                char point3 = this -> getPoint((startx + i) + 1, starty - 0);

                if (point0 != SHIP && point1 != SHIP && point2 != SHIP && point3 != SHIP) {
                    descCheck++;
                  }
              }
          }
        else if (startx == 9 && starty > 0 && endy < 9) {//если корабль прижат к нижней границе
            for (int i = 0; i < descCount; i++) {
                char point0 = this -> getPoint((startx + i) + 0, starty - 0);
                char point1 = this -> getPoint((startx + i) - 1, starty - 0);
                char point2 = this -> getPoint((startx + i) - 1, starty - 1);
                char point3 = this -> getPoint((startx + i) + 0, starty - 1);
                char point4 = this -> getPoint((startx + i) + 1, starty - 1);
                char point5 = this -> getPoint((startx + i) + 1, starty - 0);

                if (point0 != SHIP && point1 != SHIP && point2 != SHIP && point3 != SHIP && point4 != SHIP && point5 != SHIP) {
                    descCheck++;
                  }
              }
          }
        else if (endx == 9 && endy == 9) {//если корабль упирается в угол 9 9
            for (int i = 0; i < descCount; i++) {
                char point0 = this -> getPoint((startx + i) - 0, starty - 0);
                char point1 = this -> getPoint((startx + i) - 1, starty - 0);
                char point2 = this -> getPoint((startx + i) - 1, starty - 1);
                char point3 = this -> getPoint((startx + i) - 0, starty - 1);

                if (point0 != SHIP && point1 != SHIP && point2 != SHIP && point3 != SHIP) {
                    descCheck++;
                  }
              }
          }

        if (descCheck == descCount) {//Если количество доступных клеток равно размеру палубы
            return true;
          }
        else {
            return false;
          }
      }

    else if (startx == endx) {//Если корабль расположен вертикально
        if (startx == 0 && starty == 0) {//Если координаты начала корабля упираются в угол 0 0
            for (int i = 0; i < descCount; i++) {
                char point0 = this -> getPoint(startx + 0, (starty + i) + 0);
                char point1 = this -> getPoint(startx + 0, (starty + i) + 1);
                char point2 = this -> getPoint(startx + 1, (starty + i) + 1);
                char point3 = this -> getPoint(startx + 1, (starty + i) + 0);

                if (point0 != SHIP && point1 != SHIP && point2 != SHIP && point3 != SHIP) {
                    descCheck++;
                  }
              }
          }
        else if (startx > 0 && startx < 9 && starty == 0) {//Если корабль прилегает к верхней границе
            for (int i = 0; i < descCount; i++) {
                char point0 = this -> getPoint(startx + 0, (starty + i) + 0);
                char point1 = this -> getPoint(startx - 1, (starty + i) + 0);
                char point2 = this -> getPoint(startx - 1, (starty + i) + 1);
                char point3 = this -> getPoint(startx + 0, (starty + i) + 1);
                char point4 = this -> getPoint(startx + 1, (starty + i) + 1);
                char point5 = this -> getPoint(startx + 1, (starty + i) + 0);

                if (point0 != SHIP && point1 != SHIP && point2 != SHIP && point3 != SHIP && point4 != SHIP && point5 != SHIP) {
                    descCheck++;
                  }
              }
          }
        else if (startx == 9 && starty == 0) {//Если корабль упирается в угол 9 0
            for (int i = 0; i < descCount; i++) {
                char point0 = this -> getPoint(startx - 0, (starty + i) + 0);
                char point1 = this -> getPoint(startx - 1, (starty + i) + 0);
                char point2 = this -> getPoint(startx - 1, (starty + i) + 1);
                char point3 = this -> getPoint(startx - 0, (starty + i) + 1);

                if (point0 != SHIP && point1 != SHIP && point2 != SHIP && point3 != SHIP) {
                    descCheck++;
                  }
              }
          }
        else if (startx == 0 && starty > 0 && endy < 9) {//Если корабль прилегает к левой границе
            for (int i = 0; i < descCount; i++) {
                char point0 = this -> getPoint(startx + 0, (starty + i) + 0);
                char point1 = this -> getPoint(startx + 0, (starty + i) - 1);
                char point2 = this -> getPoint(startx + 1, (starty + i) - 1);
                char point3 = this -> getPoint(startx + 1, (starty + i) + 0);
                char point4 = this -> getPoint(startx + 1, (starty + i) + 1);
                char point5 = this -> getPoint(startx + 0, (starty + i) + 1);

                if (point0 != SHIP && point1 != SHIP && point2 != SHIP && point3 != SHIP && point4 != SHIP && point5 != SHIP) {
                    descCheck++;
                  }
              }
          }
        else if ((startx > 0 && starty < 9) && (endx > 0 && endy < 9)) {//Если корабль не прилегает к границам
            for (int i = 0; i < descCount; i++) {//Проверить точки на соприкосновение
                char point0 = this -> getPoint(startx - 0, (starty + i) - 1);
                char point1 = this -> getPoint(startx - 1, (starty + i) - 1);
                char point2 = this -> getPoint(startx - 1, (starty + i) - 0);
                char point3 = this -> getPoint(startx - 1, (starty + i) + 1);
                char point4 = this -> getPoint(startx - 0, (starty + i) + 1);
                char point5 = this -> getPoint(startx + 1, (starty + i) + 1);
                char point6 = this -> getPoint(startx + 1, (starty + i) + 0);
                char point7 = this -> getPoint(startx + 1, (starty + i) - 1);
                char point8 = this -> getPoint(startx - 0, (starty + i) - 0);
                //Если соприкосновения или занятых точек нету
                if (point0 != SHIP && point1 != SHIP &&  point2 != SHIP && point3 != SHIP && point4 != SHIP && point5 != SHIP && point6 != SHIP && point7 != SHIP && point8 != SHIP) {
                    descCheck++;//прибавить свободную клетку
                  }
              }

          }
        else if (startx == 9 && starty > 0 && endy < 9) {//Если корабль прилегает к правой границе
            for (int i = 0; i < descCount; i++) {
                char point0 = this -> getPoint(startx + 0, (starty + i) + 0);
                char point1 = this -> getPoint(startx + 0, (starty + i) - 1);
                char point2 = this -> getPoint(startx - 1, (starty + i) - 1);
                char point3 = this -> getPoint(startx - 1, (starty + i) + 0);
                char point4 = this -> getPoint(startx - 1, (starty + i) + 1);
                char point5 = this -> getPoint(startx - 0, (starty + i) + 1);

                if (point0 != SHIP && point1 != SHIP && point2 != SHIP && point3 != SHIP && point4 != SHIP && point5 != SHIP) {
                    descCheck++;
                  }
              }
          }
        else if (startx == 0 && endy == 9) {//Если корабль упирается в угол 0 9
            for (int i = 0; i < descCount; i++) {
                char point0 = this -> getPoint(startx + 0, (starty + i) - 0);
                char point1 = this -> getPoint(startx + 0, (starty + i) - 1);
                char point2 = this -> getPoint(startx + 1, (starty + i) - 1);
                char point3 = this -> getPoint(startx + 1, (starty + i) - 0);

                if (point0 != SHIP && point1 != SHIP && point2 != SHIP && point3 != SHIP) {
                    descCheck++;
                  }
              }

          }
        else if (startx > 0 && startx < 9 && endy == 9) {//Если корабль прилегает к нижней границе
            for (int i = 0; i < descCount; i++) {
                char point0 = this -> getPoint(startx + 0, (starty + i) - 0);
                char point1 = this -> getPoint(startx - 1, (starty + i) - 0);
                char point2 = this -> getPoint(startx - 1, (starty + i) - 1);
                char point3 = this -> getPoint(startx + 0, (starty + i) - 1);
                char point4 = this -> getPoint(startx + 1, (starty + i) - 1);
                char point5 = this -> getPoint(startx + 1, (starty + i) - 0);

                if (point0 != SHIP && point1 != SHIP && point2 != SHIP && point3 != SHIP && point4 != SHIP && point5 != SHIP) {
                    descCheck++;
                  }
              }
          }
        else if (endx == 9 && endy == 9) {//Если корабль упирается в угол 9 9
            for (int i = 0; i < descCount; i++) {
                char point0 = this -> getPoint(startx - 0, (starty + i) - 0);
                char point1 = this -> getPoint(startx - 1, (starty + i) - 0);
                char point2 = this -> getPoint(startx - 1, (starty + i) - 1);
                char point3 = this -> getPoint(startx - 0, (starty + i) - 1);

                if (point0 != SHIP && point1 != SHIP && point2 != SHIP && point3 != SHIP) {
                    descCheck++;
                  }
              }
          }

        if (descCheck == descCount) {//Если количество доступных клеток равно размеру палубы
            return true;
          }
        else {
            return false;
          }
      }
    return false;
  }

  bool setShip(int shipId, int startx, int starty, int endx, int endy) {
    int descCount = this -> getShip(shipId) -> GetDescCount();

    if (startx == endx || starty == endy) {//Если координаты находятся на одной прямой
        if ((abs(startx - endx) + 1) == descCount || (abs(starty - endy) + 1) == descCount){//Если длинна прямой равна длине палубы

            if (this->checkShipSpace(shipId, startx, starty, endx, endy)) {
                if (starty == endy) {//Если корабль раположен горизонтально
                    this -> getShip(shipId)->SetDescStartX(startx);
                    this -> getShip(shipId)->SetDescStartY(starty);
                    this -> getShip(shipId)->SetDescEndX(endx);
                    this -> getShip(shipId)->SetDescEndY(endy);

                    for (int i = 0; i < descCount; i++) {
                        this -> setPoint(startx + i, starty, SHIP);
                      }
                    return true;
                  }
                else if (startx == endx) {//Если корабль расположен вертикально
                    this -> getShip(shipId)->SetDescStartX(startx);
                    this -> getShip(shipId)->SetDescStartY(starty);
                    this -> getShip(shipId)->SetDescEndX(endx);
                    this -> getShip(shipId)->SetDescEndY(endy);

                    for (int i = 0; i < descCount; i++) {
                        this -> setPoint(startx , starty + i, SHIP);
                      }
                    return true;
                  }
                else {
                    return false;
                  }
              }
          }
      }
    else {
        return false;
      }
    return false;
  }

  int Shot(int x, int y, Field &field) {
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
  void printBoard(Field &fieldHuman, Field &fieldAiShow, string message) {
    system("clear");
    cout << message << endl;
    setiosflags(ios::right);
    cout << setw(5) << "" << "1 2 3 4 5 6 7 8 9 10";
    cout << setw(6) << "" << "1 2 3 4 5 6 7 8 9 10" << endl;
    for (int y = 0; y < fieldHuman.getSizeY(); y++) {
        cout << setw(4) << y+1 << "|";
        for (int x = 0; x < fieldHuman.getSizeX(); x++) {
            cout << fieldHuman.getPoint(x, y) << "|";
          }
        cout << setw(5) << y+1 << "|";
        for (int x = 0; x < fieldAiShow.getSizeX(); x++) {
            cout << fieldAiShow.getPoint(x, y) << "|";
          }
        cout << endl;
      }
  }

  int turnHuman(Field &fieldAiShow, Field &fieldAiHide) {
    int x = -1, y = -1;

    do {
        cout << "\nОрудия готовы для залпа. Укажите строку и столбец: ";
        cin >> y >> x;
        x--;
        y--;
      }
    while ((x < 0 || y < 0) || (x > 9 || y > 9) );

    return fieldAiShow.Shot(x, y, fieldAiHide);
  }

  bool setHumanShips(Field &field, Field &fieldHuman, Field &fieldAiShow) {
    int startx = -1, starty = -1, endx = -1, endy = -1;
    bool check;

    for(int i = 0; i < 10; i++) {//ОТЛАДОЧНОЕ УСЛОВИЕ (i < 2)
        do {
            this->printBoard(fieldHuman, fieldAiShow, "Расстановка кораблей");

            do {
                cout << "\nУкажите строку и столбец начала ";
                cout << field.getShip(i)->GetDescCount() << "-палубного корабля: ";
                cin >> starty >> startx;
                startx--;
                starty--;
              }
            while (((startx < 0 || starty < 0) || (startx > 9 || starty > 9)) || (field.getPoint(startx, starty) != EMPTY));
            do {
                cout << "Укажите строку и столбец конца ";
                cout << field.getShip(i)->GetDescCount() << "-палубного корабля: ";
                cin >> endy >> endx;
                endx--;
                endy--;
              }
            while (((endx < 0 || endy < 0) || (endx > 9 || endy > 9)) || (field.getPoint(startx, starty) != EMPTY) || (field.getPoint(endx, endy) != EMPTY) || (startx > endx || starty > endy));
            check = field.setShip(i, startx, starty, endx, endy);
          }
        while (!check);
      }
    return true;
  }

  bool setAiShips(Field &field, Field &fieldHuman, Field &fieldAiShow) {
    int direction, startx = 0, starty = 0, endx_v = 0, endy_v = 0, endx_h = 0, endy_h = 0;

    random_device rd;
    mt19937 mt(rd());
    uniform_real_distribution <double> distx(0, field.getSizeX());
    uniform_real_distribution <double> disty(0, field.getSizeY());
    uniform_real_distribution <double> distdir(0, 4);

    for (int i = 0; i < 10; i++) {
        do {
            this->printBoard(fieldHuman, fieldAiShow, "Расстановка кораблей");

            do {
                do {
                    startx = distx(mt);
                    starty = disty(mt);
                  }
                while (field.getPoint(startx, starty) != EMPTY);

                endx_v = startx;
                endy_v = starty + field.getShip(i) -> GetDescCount() - 1;

                endx_h = startx + field.getShip(i) -> GetDescCount() - 1;
                endy_h = starty;
              }
            while ((endx_h > 9 || endy_h > 9) || (endx_v > 9 || endy_v > 9) || (field.getPoint(startx, starty) != EMPTY || field.getPoint(endx_h, endy_h) != EMPTY) || (field.getPoint(endx_v, endy_v) != EMPTY));
          }
        while (!field.checkShipSpace(i, startx, starty, endx_h, endy_h) || !field.checkShipSpace(i, startx, starty, endx_v, endy_v));

        direction = distdir(mt);

        if (field.checkShipSpace(i, startx, starty, endx_h, endy_h) && direction > 2) {
            field.setShip(i, startx, starty, endx_h, endy_h);
          }
        else if (field.checkShipSpace(i, startx, starty, endx_v, endy_v) && direction < 3) {
            field.setShip(i, startx, starty, endx_v, endy_v);
          }
      }
    return true;
  }

  bool CheckWin() {

    return true;
  }
private:

};

int main() {
  Field fieldHuman, fieldAiShow, fieldAiHide;
  Board board;

  board.setAiShips(fieldAiHide, fieldHuman, fieldAiHide);

  while (true) {
      board.printBoard(fieldHuman, fieldAiHide, "\t Морской бой. \t Новая игра \n");
//      board.setHumanShips(fieldHuman, fieldHuman, fieldAiShow);
      board.turnHuman(fieldAiShow, fieldAiHide);
    }

  return 0;
}
