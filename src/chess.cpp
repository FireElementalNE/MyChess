#include <iostream>
#include <string>
#include <vector>
//#include <Utility>
#include "Chess.h"
using namespace std;
bool canCastle(vector < pair <string,pair <int, int > > > movesList,char pcolor,chessBoard A) {
  if (pcolor == 'W') {
    bool sawWR1 = false;
    bool sawWR2 = false;
    for(unsigned int i = 0; i < movesList.size(); i++) {
      if(movesList[i].first == "WK0")
	return false;
      else if(movesList[i].first == "WR1")
	sawWR1 = true;
      if(movesList[i].first == "WR2")
	sawWR2 = true;
    }
    if(sawWR1 && sawWR2)
      return false;
    if(A.board[0][3].getFill().getId() != "WK0")
      return false;
    if(A.board[0][0].getFill().getId() != "WR1")
      return false;
    if(A.board[0][7].getFill().getId() != "WR2")
      return false;
    return true;
  }
  else {
    bool sawBR1 = false;
    bool sawBR2 = false;
    for(unsigned int i = 0; i < movesList.size(); i++) {
      if(movesList[i].first == "BK0")
	return false;
      else if(movesList[i].first == "BR1")
	sawBR1 = true;
      if(movesList[i].first == "BR2")
	sawBR2 = true;
    }
    if(sawBR1 && sawBR2)
      return false;
    if(A.board[7][3].getFill().getId() != "BK0")
      return false;
    if(A.board[7][0].getFill().getId() != "BR1")
      return false;
    if(A.board[7][7].getFill().getId() != "BR2")
      return false;
    return true;
  }
}
bool hasMoved(vector < pair <string,pair <int,int> > > moves, string s) {
  for(unsigned int i = 0; i < moves.size(); i++ ) {
    if( s == moves[i].first ) {
      return true;
    }
  }
  return false;
}
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
  return filled;
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
vector <pair <int, int> > chessPiece::validMoves(int x, int y, string playerColor, chessBoard A, vector < pair <string,pair <int, int > > > movesList) {
  vector <pair <int,int> > list;
  //id comes from chessPiece Class
  if(type == "Pawn" && id[0] == playerColor[0]) {
    if(playerColor[0] == 'W') {
      if(!A.board[y+1][x].getFilled()) 
	list.push_back(make_pair(x,y+1));
      if(!A.board[y+2][x].getFilled() && y == 1)
	list.push_back(make_pair(x,y+2));
      if(A.board[y+1][x+1].getFilled() && A.board[y+1][x+1].getFill().getId()[0] != id[0])
	list.push_back(make_pair(x+1,y+1));
      if(A.board[y+1][x-1].getFilled() && A.board[y+1][x-1].getFill().getId()[0] != id[0])
	list.push_back(make_pair(x-1,y+1));
    }
    else {
      if(!A.board[y-1][x].getFilled())
	list.push_back(make_pair(x,y-1));
      if(!A.board[y-2][x].getFilled() && y == 6)
	list.push_back(make_pair(x,y-2));
      if(A.board[y-1][x+1].getFilled() && A.board[y-1][x+1].getFill().getId()[0] != id[0])
	list.push_back(make_pair(x+1,y-1));
      if(A.board[y-1][x-1].getFilled() && A.board[y-1][x-1].getFill().getId()[0] != id[0])
	list.push_back(make_pair(x-1,y-1));
    }
  }
  else if(type == "Rook" && id[0] == playerColor[0]) {
    //cout <<"its a rook" << endl;
    for(int i = y+1; i < 8; i++) {
      //cout << i << endl;
      if(!A.board[i][x].getFilled()) {
	list.push_back(make_pair(x,i));
      }
      else if(A.board[i][x].getFill().getId()[0] != id[0]) {
	list.push_back(make_pair(x,i));
	break;
      }
      else {
	break;
      }
    }
    for(int i = y-1; i >= 0; i--) {
      //cout << i << endl;
      if(!A.board[i][x].getFilled()) {
	list.push_back(make_pair(x,i));
      }
      else if(A.board[i][x].getFill().getId()[0] != id[0]) {
	list.push_back(make_pair(x,i));
	break;
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
      else if(A.board[y][i].getFill().getId()[0] != id[0]) {
	list.push_back(make_pair(i,y));
	break;
      }
      else {
	break;
      }
    }
    for(int i = x-1; i >= 0; i--) {
      //cout << i << endl;
      if(!A.board[y][i].getFilled()) {
	list.push_back(make_pair(i,y));
      }
      else if(A.board[y][i].getFill().getId()[0] != id[0]) {
	list.push_back(make_pair(i,y));
	break;
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
    for(unsigned int i = 0; i < knightMoves.size(); i++) {
      if(moveCheck(knightMoves[i].first,knightMoves[i].second) && !A.board[knightMoves[i].second][knightMoves[i].first].getFilled())
	list.push_back(knightMoves[i]);
      else if(moveCheck(knightMoves[i].first,knightMoves[i].second) && A.board[knightMoves[i].second][knightMoves[i].first].getFill().getId()[0] != id[0])
	list.push_back(knightMoves[i]);
    }
  }
  else if(type == "Bishop" && id[0] == playerColor[0]) {
    int xBishop = x+1;
    int yBishop = y+1;
    while(xBishop < 8 && yBishop < 8 && xBishop >= 0 && yBishop >= 0) {
      if(!A.board[yBishop][xBishop].getFilled()) {
	list.push_back(make_pair(xBishop,yBishop));
	xBishop++;
	yBishop++;
      }
      else if(A.board[yBishop][xBishop].getFill().getId()[0] != id[0]) {
	list.push_back(make_pair(xBishop,yBishop));
	break;
      }
      else {
	break;
      }
    }
    xBishop = x-1;
    yBishop = y-1;
    while(xBishop < 8 && yBishop < 8 && xBishop >= 0 && yBishop >= 0) {
      if(!A.board[yBishop][xBishop].getFilled()) {
	list.push_back(make_pair(xBishop,yBishop));
	xBishop--;
	yBishop--;
      }
      else if(A.board[yBishop][xBishop].getFill().getId()[0] != id[0]) {
	list.push_back(make_pair(xBishop,yBishop));
	break;
      }
      else {
	break;
      }
    }
    xBishop = x-1;
    yBishop = y+1;
    while(xBishop < 8 && yBishop < 8 && xBishop >= 0 && yBishop >= 0) {
      if(!A.board[yBishop][xBishop].getFilled()) {
	list.push_back(make_pair(xBishop,yBishop));
	xBishop--;
	yBishop++;
      }
      else if(A.board[yBishop][xBishop].getFill().getId()[0] != id[0]) {
	list.push_back(make_pair(xBishop,yBishop));
	break;
      }
      else {
	break;
      }
    }
    xBishop = x+1;
    yBishop = y-1;
    while(xBishop < 8 && yBishop < 8 && xBishop >= 0 && yBishop >= 0) {
      if(!A.board[yBishop][xBishop].getFilled()) {
	list.push_back(make_pair(xBishop,yBishop));
	xBishop++;
	yBishop--;
      }
      else if(A.board[yBishop][xBishop].getFill().getId()[0] != id[0]) {
	list.push_back(make_pair(xBishop,yBishop));
	break;
      }
      else {
	break;
      }
    }
  }
  else if(type == "Queen" && id[0] == playerColor[0]) {
    for(int i = y+1; i < 8; i++) {
      //cout << i << endl;
      if(!A.board[i][x].getFilled()) {
	list.push_back(make_pair(x,i));
      }
      else if(A.board[i][x].getFill().getId()[0] != id[0]) {
	list.push_back(make_pair(x,i));
	break;
      }
      else {
	break;
      }
    }
    for(int i = y-1; i >= 0; i--) {
      //cout << i << endl;
      if(!A.board[i][x].getFilled()) {
	list.push_back(make_pair(x,i));
      }
      else if(A.board[i][x].getFill().getId()[0] != id[0]) {
	list.push_back(make_pair(x,i));
	break;
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
      else if(A.board[y][i].getFill().getId()[0] != id[0]) {
	list.push_back(make_pair(i,y));
	break;
      }
      else {
	break;
      }
    }
    for(int i = x-1; i >= 0; i--) {
      //cout << i << endl;
      if(!A.board[y][i].getFilled()) {
	list.push_back(make_pair(i,y));
      }
      else if(A.board[i][x].getFill().getId()[0] != id[0]) {
	list.push_back(make_pair(i,y));
	break;
      }
      else {
	break;
      }
    }
    int xBishop = x+1;
    int yBishop = y+1;
    while(xBishop < 8 && yBishop < 8 && xBishop >= 0 && yBishop >= 0) {
      if(!A.board[yBishop][xBishop].getFilled()) {
	list.push_back(make_pair(xBishop,yBishop));
	xBishop++;
	yBishop++;
      }
      else if(A.board[yBishop][xBishop].getFill().getId()[0] != id[0]) {
	list.push_back(make_pair(xBishop,yBishop));
	break;
      }
      else {
	break;
      }
    }
    xBishop = x-1;
    yBishop = y-1;
    while(xBishop < 8 && yBishop < 8 && xBishop >= 0 && yBishop >= 0) {
      if(!A.board[yBishop][xBishop].getFilled()) {
	list.push_back(make_pair(xBishop,yBishop));
	xBishop--;
	yBishop--;
      }
      else if(A.board[yBishop][xBishop].getFill().getId()[0] != id[0]) {
	list.push_back(make_pair(xBishop,yBishop));
	break;
      }
      else {
	break;
      }
    }
    xBishop = x-1;
    yBishop = y+1;
    while(xBishop < 8 && yBishop < 8 && xBishop >= 0 && yBishop >= 0) {
      if(!A.board[yBishop][xBishop].getFilled()) {
	list.push_back(make_pair(xBishop,yBishop));
	xBishop--;
	yBishop++;
      }
      else if(A.board[yBishop][xBishop].getFill().getId()[0] != id[0]) {
	list.push_back(make_pair(xBishop,yBishop));
	break;
      }
      else {
	break;
      }
    }
    xBishop = x+1;
    yBishop = y-1;
    while(xBishop < 8 && yBishop < 8 && xBishop >= 0 && yBishop >= 0) {
      if(!A.board[yBishop][xBishop].getFilled()) {
	list.push_back(make_pair(xBishop,yBishop));
	xBishop++;
	yBishop--;
      }
      else if(A.board[yBishop][xBishop].getFill().getId()[0] != id[0]) {
	list.push_back(make_pair(xBishop,yBishop));
	break;
      }
      else {
	break;
      }
    }
  }
  else if(type == "King" && id[0] == playerColor[0]) {
  vector < pair <int,int> > kingMoves;
    kingMoves.push_back(make_pair(x,y-1));
    kingMoves.push_back(make_pair(x,y+1));
    kingMoves.push_back(make_pair(x+1,y));
    kingMoves.push_back(make_pair(x-1,y));
    kingMoves.push_back(make_pair(x-1,y-1));
    kingMoves.push_back(make_pair(x+1,y+1));
    kingMoves.push_back(make_pair(x-1,y+1));
    kingMoves.push_back(make_pair(x+1,y-1));
    for(unsigned int i = 0; i < kingMoves.size(); i++) {
      if(moveCheck(kingMoves[i].first,kingMoves[i].second) && !A.board[kingMoves[i].second][kingMoves[i].first].getFilled())
	list.push_back(kingMoves[i]);
      else if(moveCheck(kingMoves[i].first,kingMoves[i].second) && A.board[kingMoves[i].second][kingMoves[i].first].getFill().getId()[0] != id[0])
	list.push_back(kingMoves[i]);
    }
    //Castle check
    //bool canCastle(vector < pair <string,pair <int, int > > > movesList,char pcolor,chessBoard A) {
    if(playerColor[0] == 'W') {
      if(!hasMoved(movesList,id) && !hasMoved(movesList,"WR2") && !A.board[5][0].getFilled() && !A.board[6][0].getFilled() && canCastle(movesList,playerColor[0],A)) 
	list.push_back(make_pair(6,0));
      if(!hasMoved(movesList,id) && !hasMoved(movesList,"WR1") && !A.board[1][0].getFilled() && !A.board[2][0].getFilled() && !A.board[3][0].getFilled() && canCastle(movesList,playerColor[0],A)) 
	list.push_back(make_pair(2,0));
    }
    else {
      if(!hasMoved(movesList,id) && !hasMoved(movesList,"BR2") && !A.board[5][7].getFilled() && !A.board[6][7].getFilled() && canCastle(movesList,playerColor[0],A)) 
	list.push_back(make_pair(6,7));
      if(!hasMoved(movesList,id) && !hasMoved(movesList,"BR1") && !A.board[1][7].getFilled() && !A.board[2][7].getFilled() && !A.board[3][7].getFilled() && canCastle(movesList,playerColor[0],A)) 
	list.push_back(make_pair(2,7));
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
  // cout << "  ";
  
  cout << endl << endl;
  for(int y = 0; y < 8; y++) {
    cout << -1*(y-8) << " ";
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
    cout << endl << endl;
  }
  cout << "  ";
  for(int i = 0; i < 8; i++) {
    char c = 48+i+49;
    cout << "   " << c << "   ";
  }
  cout << endl << endl;
  
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
  //cout << temp.getHasMoved() << endl;
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
  cout << board[x][y].getFill().getId() << endl;
}
