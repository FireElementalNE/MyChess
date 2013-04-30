#include <iostream>
#include <string>
#include <vector>
#include "Chess.h"
using namespace std;
void init(chessBoard &A, bool testing, string test);
string fixMe(string &s);
string turnText(int i);
int main()
{
  chessBoard A;
  init(A,false,"none");
  A.print();
  cout << "Player Setup----------------------->" << endl;
  string name1 = "A";
  string name2= "b";
  cout << "Name of white player:";
  //cin >> name1;
  cout << "Name of black player:";
  //cin >> name2;
  Player whitePlayer = Player(name1, "W");
  Player blackPlayer = Player(name2, "B");
  int turnNum = 1;
  cout << turnText(turnNum) << endl;
  string selection;
  cout << "Coordinates of Piece to move(no spaces)";
  cin >> selection;
  while(fixMe(selection) != "exit") {
    int x = selection[0] - 48;
    int y = selection[1] - 48;
    chessPiece temp = A.board[y][x].getFill();
    cout << x << " " << y << endl;
    cout << "The piece at x=" << x << " and y=" << y << " is a " << temp.getType() << " with ID=" << temp.getId() << endl;
    vector <pair <int,int> > moves;
    if(turnNum % 2 == 0) {
      moves = temp.validMoves(x,y,blackPlayer.getColor(),A);
    }
    else {
      moves = temp.validMoves(x,y,whitePlayer.getColor(),A);
    }
    if(moves.size() != 0) {
      for(int i = 0; i < moves.size(); i++) {
	cout << "[" << i << "]" <<" VALID MOVE @: x=" << moves[i].first << " y=" << moves[i].second << endl;
      }
      int choice;
      cout << ">";
      cin >> choice;
      if(choice >= moves.size()) {
	cout <<"ERROR: INVALID CHOICE NEXT TURN" << endl;
	continue;
      }
      else {
	A.move(x,y,moves[choice].first,moves[choice].second);
      }
      cout << "TURN SWITCH" << endl;
      turnNum++;
      cout << turnText(turnNum) << endl;
      cout << "Coordinates of Piece to move(no spaces)";
      cin >> selection;
    }
    else {
      cout << "WRONG PIECE" << endl;
      cout << "TURN SWITCH" << endl;
      turnNum++;
      cout << turnText(turnNum) << endl;
      cout << "Coordinates of Piece to move(no spaces)";
      cin >> selection;
    }
    A.print();
  }
  //system("pause");
  return 0;
}
string fixMe(string &s) {
  for(int i = 0; i < s.length(); i++) {
    char temp = tolower(s[i]);
    s[i] = temp;
  }
  return s;
}
string turnText(int i) {
  if(i % 2 == 0) {
    return "Black Player's Turn---------------------->";
  }
  else {
    return "White Player's Turn---------------------->";
  }
}
void init(chessBoard &A, bool testing, string test) {
  vector <string> pieces;
  pieces.push_back("Pawn");
  pieces.push_back("Knight");
  pieces.push_back("Bishop");
  pieces.push_back("Rook");
  pieces.push_back("Queen");
  pieces.push_back("King");
  chessPiece pawn = chessPiece(pieces[0]);
  chessPiece knight = chessPiece(pieces[1]);
  chessPiece bishop = chessPiece(pieces[2]);
  chessPiece rook = chessPiece(pieces[3]);
  chessPiece queen = chessPiece(pieces[4]);
  chessPiece king = chessPiece(pieces[5]);
  if(!testing) {
    A.placePiece(0,0,rook,"WR1");
    A.placePiece(1,0,knight,"WK1");
    A.placePiece(2,0,bishop,"WB1");
    A.placePiece(3,0,queen,"WQ0");
    A.placePiece(4,0,king,"WK0");
    A.placePiece(5,0,bishop,"WB2");
    A.placePiece(6,0,knight,"WK2");
    A.placePiece(7,0,rook,"WR2");
    A.placePiece(0,1,pawn,"WP1");
    A.placePiece(1,1,pawn,"WP2");
    A.placePiece(2,1,pawn,"WP3");
    A.placePiece(3,1,pawn,"WP4");
    A.placePiece(4,1,pawn,"WP5");
    A.placePiece(5,1,pawn,"WP6");
    A.placePiece(6,1,pawn,"WP7");
    A.placePiece(7,1,pawn,"WP8");
    A.placePiece(0,7,rook,"BR1");
    A.placePiece(1,7,knight,"BK1");
    A.placePiece(2,7,bishop,"BB1");
    A.placePiece(3,7,king,"BK0");
    A.placePiece(4,7,queen,"BQ0");
    A.placePiece(5,7,bishop,"BB2");
    A.placePiece(6,7,knight,"BK2");
    A.placePiece(7,7,rook,"BR2");
    A.placePiece(0,6,pawn,"BP1");
    A.placePiece(1,6,pawn,"BP2");
    A.placePiece(2,6,pawn,"BP3");
    A.placePiece(3,6,pawn,"BP4");
    A.placePiece(4,6,pawn,"BP5");
    A.placePiece(5,6,pawn,"BP6");
    A.placePiece(6,6,pawn,"BP7");
    A.placePiece(7,6,pawn,"BP8");
  }
  else {
    if(test == "Pawn") {
      A.placePiece(0,1,pawn,"WP1");
      A.placePiece(1,1,pawn,"WP2");
      A.placePiece(2,1,pawn,"WP3");
      A.placePiece(3,1,pawn,"WP4");
      A.placePiece(4,1,pawn,"WP5");
      A.placePiece(5,1,pawn,"WP6");
      A.placePiece(6,1,pawn,"WP7");
      A.placePiece(7,1,pawn,"WP8");
      A.placePiece(0,6,pawn,"BP1");
      A.placePiece(1,6,pawn,"BP2");
      A.placePiece(2,6,pawn,"BP3");
      A.placePiece(3,6,pawn,"BP4");
      A.placePiece(4,6,pawn,"BP5");
      A.placePiece(5,6,pawn,"BP6");
      A.placePiece(6,6,pawn,"BP7");
      A.placePiece(7,6,pawn,"BP8");
    }
    else if(test == "Rook") {
      A.placePiece(7,7,rook,"BR2");
      A.placePiece(0,7,rook,"BR1");
      A.placePiece(7,0,rook,"WR2");
      A.placePiece(0,0,rook,"WR1");
    }
    else if(test == "Knight") {
      A.placePiece(1,7,knight,"BK1");
      A.placePiece(6,7,knight,"BK2");
      A.placePiece(1,0,knight,"WK1");
      A.placePiece(6,0,knight,"WK2");
    }
    else if(test == "Bishop") { 
      A.placePiece(2,7,bishop,"BB1");
      A.placePiece(5,7,bishop,"BB2"); 
      A.placePiece(2,0,bishop,"WB1");
      A.placePiece(5,0,bishop,"WB2");
    }
    else if(test == "Queen") {
      A.placePiece(4,7,queen,"BQ0");
      A.placePiece(3,0,queen,"WQ0");
    }
    else {
      A.placePiece(4,0,king,"WK0");
      A.placePiece(3,7,king,"BK0");
    }
  }
}
