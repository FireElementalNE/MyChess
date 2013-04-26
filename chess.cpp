#include <iostream>
#include <string>
#include <vector>
//#include <Utility>
#include "Chess.h"
using namespace std;
bool moveCheck(int x, int y) {
  if(x >= 8 || x < 0)
    return false;
  else if(y >= 8 || y < 0)
    return false;
  return true;
}
Player::Player() { }
Player::Player(string s, string c) {
  name = s;
  color = c;
  score = 0;
}
void Player::setColor(string c) {
  color = c;
}
string Player::getColor() {
  return color;
}
void Player::setName(string s) {
  name = s;
}
string Player::getName() {
  return name;
}
void Player::setScore(int i) {
  score = i;
}
int Player::getScore() {
  return score;
}
chessPiece::chessPiece() { }
chessPiece::chessPiece(string name) {
  type = name;
  symbol = name[0];
}
string chessPiece::getSymbol() {
  return symbol;
}
void chessPiece::setSymbol(string c) {
  symbol = c;
}
string chessPiece::getType() {
  return type;
}
void chessPiece::setType(string s) {
  type = s;
}
string chessPiece::getId() {
  return id;
}
void chessPiece::setId(string s) {
  id = s;
}
chessSquare::chessSquare(char c) {
  filled = false;
  if(c == 'w') {
    color = 'w';
  }
  else if(c == 'b') {
    color = 'b';
  }
}
chessSquare::chessSquare() { 
}
void chessSquare::setFill(chessPiece temp) {
  fill = temp;
}
chessPiece chessSquare::getFill() {
  return fill;
}
void chessSquare::setFilled(bool temp) {
  filled = temp;
}
bool chessSquare::getFilled() {
  return 	filled;
}
chessBoard::chessBoard() {
  for(int y = 0; y < 8; y++) {
    for(int x = 0; x < 8; x++) {
      if(((x+y)%2) == 0) {
	board[y][x] = chessSquare('w');
      }
      else {
	board[y][x] = chessSquare('b');
      }
    }
  }
}
vector <pair <int, int> > chessPiece::validMoves(int x, int y, string playerColor, chessBoard A) {
  vector <pair <int,int> > list;
  //id comes from chessPiece Class
  if(type == "Pawn" && id[0] == playerColor[0]) {
    pair <int,int> t0;
    pair <int,int> t1;
    if(playerColor[0] == 'W') {
      if(!A.board[y+1][x].getFilled()) {
	t0 = make_pair(x,y+1);
	list.push_back(t0);
      }
      if(!A.board[y+2][x].getFilled() && y == 1) {
	t1 = make_pair(x,y+2);
	list.push_back(t1);
      }
    }
    else {
      if(!A.board[y-1][x].getFilled()) {
	t0 = make_pair(x,y-1);
	list.push_back(t0);
      }
      if(!A.board[y-2][x].getFilled() && y == 6) {
	t1 = make_pair(x,y-2);
	list.push_back(t1);
      }
    }
  }
  else if(type == "Rook" && id[0] == playerColor[0]) {
    for(int i = y+1; i < 8; i++) {
      //cout << i << endl;
      if(!A.board[i][x].getFilled()) {
	list.push_back(make_pair(x,i));
      }
      else {
	break;
      }
    }
    for(int i = y-1; i > 0; i--) {
      //cout << i << endl;
      if(!A.board[i][x].getFilled()) {
	list.push_back(make_pair(x,i));
      }
      else {
	break;
      }
    }
    for(int i = x+1; i < 8; i++) {
      //cout << i << endl;
      if(!A.board[y][i].getFilled()) {
	list.push_back(make_pair(i,y));
      }
      else {
	break;
      }
    }
    for(int i = x-1; i > 0; i--) {
      //cout << i << endl;
      if(!A.board[y][i].getFilled()) {
	list.push_back(make_pair(i,y));
      }
      else {
	break;
      }
    }
  }
  else if(type == "Knight" && id[0] == playerColor[0]) {
    vector < pair <int,int> > knightMoves;
    knightMoves.push_back(make_pair(x+1,y+2));
    knightMoves.push_back(make_pair(x+2,y+1));
    knightMoves.push_back(make_pair(x+2,y-1));
    knightMoves.push_back(make_pair(x+1,y-2));
    knightMoves.push_back(make_pair(x-1,y-2));
    knightMoves.push_back(make_pair(x-2,y-1));
    knightMoves.push_back(make_pair(x-2,y+1));
    knightMoves.push_back(make_pair(x-1,y+2));
    for(int i = 0; i < knightMoves.size(); i++) {
      if(moveCheck(knightMoves[i].first,knightMoves[i].second) && !A.board[knightMoves[i].second][knightMoves[i].first].getFilled())
	list.push_back(knightMoves[i]);
    }
  }
  return list;
}
chessPiece& chessPiece::operator=(const chessPiece& other) {
  type = other.type;
  symbol = other.symbol;
  id = other.id;
  return *this;
}
void chessBoard::print() {
  cout << "  ";
  for(int i = 0; i < 8; i++) {
    cout << "   " << i << "   ";
  }
  cout << endl << endl << endl;
  for(int y = 0; y < 8; y++) {
    cout << y << " ";
    for(int x = 0; x < 8; x++) {
      if(board[y][x].color == 'w' && !board[y][x].getFilled()) {
	cout << " [   ] ";
      }
      else if(board[y][x].color == 'b' && !board[y][x].getFilled()) {
	cout << " [+++] ";
      }
      else {
	cout << " [" <<  board[y][x].getFill().getId() << "] ";
      }
    }
    cout << endl << endl << endl;
  }
  
}

void chessBoard::move(int startX, int startY, int endX, int endY) {
  chessPiece temp = board[startY][startX].getFill();
  chessPiece BLANK = chessPiece("NONE");
  int desc = startX+startY;
  if(desc % 2 == 0) {
    placePiece(startX,startY,BLANK,"   ");
  }
  else {
    placePiece(startX,startY,BLANK,"+++");
  }
  board[endY][endX].setFill(temp);
  board[endY][endX].setFilled(true);
  board[startY][startX].setFilled(false);
}
void chessBoard::bool_print() {
  for(int i = 0; i < 8; i++) {
    for(int j = 0; j < 8; j++)
      cout << board[i][j].getFilled();
    cout << endl;
  }
}
void chessBoard::colorof(int x, int y) {
  char c = board[y][x].color;
  if(c == 'b') {
    cout << "Square (" << y << "," << x << ") is Black" << endl;
  }
  if(c == 'w') {
		cout << "Square (" << y << "," << x << ") is White" << endl;
  }
}
void chessBoard::placePiece(int x, int y, chessPiece temp, string info) {
  temp.setId(info);
  board[y][x].setFilled(true);
  board[y][x].setFill(temp);
}
