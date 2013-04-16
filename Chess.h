#include <iostream>
#include <string>
#include <vector>
//#include <Utility>
using namespace std;

class Player
{
 private:
  string name;
  int score;
  string color;
 public:
  Player();
  Player(string s, string c);
  string getName();
  void setName(string s);
  int getScore();
  void setScore(int i);
  string getColor();
  void setColor(string c);
};
class chessBoard;
class chessPiece
{
 private:
  string type;
  string id;
  string symbol;
 public:
  chessPiece();
  chessPiece(string name);
  chessPiece& operator=(const chessPiece & other);
  string getType();
  void setType(string s);
  string getId();
  void setId(string s);
  string getSymbol();
  void setSymbol(string c);
  vector <pair <int, int> > validMoves(int x, int y, string playerColor, chessBoard A);
};
class chessSquare
{
 private:
  bool filled;
  chessPiece fill;
 public:
  char color;
  chessSquare(char c);
  chessSquare();
  void setFill(chessPiece temp);
  chessPiece getFill();
  void setFilled(bool fill);
  bool getFilled();
};
class chessBoard
{
 public:
  chessSquare board[8][8];
  chessBoard();
  void print();
  void bool_print();
  void move(int startX, int startY, int endX, int endY);
  void colorof(int x,int y);
  void placePiece(int x, int y, chessPiece temp, string info);
};

