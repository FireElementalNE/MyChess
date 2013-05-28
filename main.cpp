#include <iostream>
#include <string>
#include <vector>
#include "Chess.h"
using namespace std;
string whoseTurn(int turnNum);
void init(chessBoard &A, bool testing, string test);
string fixMe(string &s);
string turnText(int i, string bName, string wName);
void addMove(vector < pair <string,pair <int, int > > > &movesList, pair <int,int> space, string name);
bool hasMoved2(vector < pair <string,pair <int,int> > > moves, string s);
bool inCheck(string playerColor, chessBoard A, vector < pair <string,pair <int, int > > > movesList);
pair <int,int> findKing(chessBoard A, string playerColor);
bool isKing(chessBoard A, string playerColor);
int main()
{
  vector < pair <string,pair <int, int > > > movesList;
  chessBoard A;
  init(A,true,"Castle");
  int wQCount = 1, bQCount = 1;
  int wKCount = 2, bKCount = 2;
  int wRCount = 2, bRCount = 2;
  int wBCount = 2, bBCount = 2;
  //cout << "Player Setup----------------------->" << endl;
  string name1 = "A";
  string name2 = "b";
  //cout << "Name of white player:";
  //cin >> name1;
  //cout << "Name of black player:";
  //cin >> name2;
  Player whitePlayer = Player(name1, "W");
  Player blackPlayer = Player(name2, "B");
  int turnNum = 1;
  cout << turnText(turnNum, blackPlayer.getName(), whitePlayer.getName()) << endl;
  bool sureCheck = false;
  string selection = "";
  while(fixMe(selection) != "exit") {
    A.print();
    int x;
    int y;
    chessPiece temp;
    sureCheck = false;
    bool brokenLoop = false;
    bool isInCheck = false;
    if(!isKing(A,whoseTurn(turnNum))) {
      cout << "Game Over " << whoseTurn(turnNum) << " Wins." << endl;
      brokenLoop = true;
      break;
    }
    if(inCheck(whoseTurn(turnNum),A,movesList)) {
      cout << "You are in Check..." << endl;
      isInCheck = true;
    }
    while(!sureCheck) {
      cout << "Coordinates of Piece to move(no spaces): ";
      cin >> selection;
      cout << "You input " << selection << "." << endl;
      if(fixMe(selection) == "exit") {
	break;
      }
      x = selection[0] - 97;
      y = 56 - selection[1];
      //cout << x << " " << x << endl;
      if(x < 8 && y < 8 && x >=0 && y >=0 ) {
	temp = A.board[y][x].getFill();
	//cout << whoseTurn(turnNum)[0] << " " << temp.getId()[0] << " " << temp.getId() << endl;
	if(whoseTurn(turnNum)[0] == temp.getId()[0] && temp.getId() != "") {
	  cout << "The piece at x=" << x << " and y=" << y << " is a " << temp.getType() << " with ID=" << temp.getId() << " and with color=" << temp.getId()[0] << endl;
	  string t9;
	  cout << "Are You sure? (y/n):";
	  cin >> t9;
	  if(fixMe(t9) == "y" || fixMe(t9) == "yes") {
	    sureCheck = true;
	    break;
	  }
	  else 
	    break;
	}
	else {
	  if(x < 8 && x >= 0 && y < 8 && x >= 0 && temp.getId() != "+++" && temp.getId() != "   ") {
	    cout << "That piece is either not yours or the Chess Square is empty." << endl;
	    continue;
	  }
	  else {
	    cout << "Fatal Error" << endl;
	    brokenLoop = true;
	    break;
	  }
	}
      }
    }
    if(brokenLoop) {
      break;
    }
    vector <pair <int,int> > moves;
    if(turnNum % 2 == 0) {
      moves = temp.validMoves(x,y,blackPlayer.getColor(),A, movesList);
    }
    else {
      moves = temp.validMoves(x,y,whitePlayer.getColor(),A, movesList);
    }
    if(moves.size() != 0) {
      cout << "You have " << moves.size() << " valid moves." << endl;
      for(int i = 0; i < moves.size(); i++) {
	char c1 = moves[i].first + 97;
	char c2 = -moves[i].second + 56;
	cout << "[" << i << "]" <<" VALID MOVE @: " << c1 << " " << c2 << endl;
      }
      int choice;
      cout << ">";
      cin >> choice;
      if(choice >= moves.size()) {
	cout <<"ERROR: INVALID CHOICE NEXT TURN" << endl;
	continue;
      }
      else {
	int newX = moves[choice].first;
	int newY = moves[choice].second;
	if(turnNum % 2 == 1 && x == 3 && y == 0 && newX == 2 && newY == 0) {
	  A.move(x,y,newX,newY);
	  A.move(0,0,3,0);
	  addMove( movesList, make_pair(newX, newY) , A.board[newY][newX].getFill().getId());
	  addMove( movesList, make_pair(x,y) , "WR1" );
	}
	else if (turnNum % 2 == 1 && x == 3 && y == 0 && newX == 6 && newY == 0) {
	  A.move(x,y,newX,newY);
	  A.move(7,0,5,0);
	  addMove( movesList, make_pair(newX, newY) , A.board[newY][newX].getFill().getId());
	  addMove( movesList, make_pair(x,y) , "WR2" );
	}
	else if(turnNum % 2 == 0 && x == 3 && y == 7 && newX == 2 && newY == 7) {
	  A.move(x,y,newX,newY);
	  A.move(0,7,3,7);
	  addMove( movesList, make_pair(newX, newY) , A.board[newY][newX].getFill().getId());
	  addMove( movesList, make_pair(x,y) , "BR1" );
	}
	else if (turnNum % 2 == 0 && x == 3 && y == 7 && newX == 6 && newY == 7) {
	  A.move(x,y,newX,newY);
	  A.move(7,7,5,7);
	  addMove( movesList, make_pair(newX, newY) , A.board[newY][newX].getFill().getId());
	  addMove( movesList, make_pair(x,y) , "BR2" );
	}
	else {
	  if(turnNum % 2 == 1 && A.board[y][x].getFill().getType() == "Pawn" && newY == 7) {
	    int t0;
	    cout << "What would you like to turn this piece into? (number only)" << endl;
	    cout << "[0] Knight" << endl;
	    cout << "[1] Bishop" << endl;
	    cout << "[2] Rook" << endl;
	    cout << "[3] Queen" << endl;
	    cout << ">";
	    cin >> t0;
	    A.move(x,y,newX,newY);
	    chessPiece pawn = chessPiece("Pawn");
	    chessPiece knight = chessPiece("Knight");
	    chessPiece bishop = chessPiece("Bishop");
	    chessPiece rook = chessPiece("Rook");
	    chessPiece queen = chessPiece("Queen");
	    if (t0 == 0 ) {
	      wKCount++;
	      A.placePiece(newX,newY,knight,"WK"+to_string(wKCount));
	    }
	    else if (t0 == 1 ) {
	      wBCount++;
	      A.placePiece(newX,newY,bishop,"WB"+to_string(wBCount));
	    }
	    else if (t0 == 2 ) {
	      wRCount++;
	      A.placePiece(newX,newY,rook,"WR"+to_string(wRCount));
	    }
	    else if (t0 == 3 ) {
	      wQCount++;
	      A.placePiece(newX,newY,queen,"WQ"+to_string(wQCount));
	    }
	    addMove( movesList, make_pair(newY, newX) , A.board[newY][newX].getFill().getId());
	  }
	  else if(turnNum % 2 == 0 && A.board[y][x].getFill().getType() == "Pawn" && newY == 0) {
	    int t0;
	    cout << "What would you like to turn this piece into? (number only)" << endl;
	    cout << "[0] Knight" << endl;
	    cout << "[1] Bishop" << endl;
	    cout << "[2] Rook" << endl;
	    cout << "[3] Queen" << endl;
	    cout << ">";
	    cin >> t0;
	    A.move(x,y,newX,newY);
	    chessPiece pawn = chessPiece("Pawn");
	    chessPiece knight = chessPiece("Knight");
	    chessPiece bishop = chessPiece("Bishop");
	    chessPiece rook = chessPiece("Rook");
	    chessPiece queen = chessPiece("Queen");
	    if (t0 == 0 ) {
	      bKCount++;
	      A.placePiece(newX,newY,knight,"BK"+to_string(bKCount));
	    }
	    else if (t0 == 1 ) {
	      bBCount++;
	      A.placePiece(newX,newY,bishop,"BB"+to_string(bBCount));
	    }
	    else if (t0 == 2 ) {
	      bRCount++;
	      A.placePiece(newX,newY,rook,"BR"+to_string(bRCount));
	    }
	    else if (t0 == 3 ) {
	      bQCount++;
	      A.placePiece(newX,newY,queen,"BQ"+to_string(bQCount));
	    }
	    addMove( movesList, make_pair(newY, newX) , A.board[newY][newX].getFill().getId());
	  }
	  else {
	    A.move(x,y,newX,newY);
	    addMove( movesList, make_pair(newY, newX) , A.board[newY][newX].getFill().getId());
	  }
	}
      }
      if(!brokenLoop) {
	cout << "TURN SWITCH" << endl;
	turnNum++;
	cout << turnText(turnNum, blackPlayer.getName(), whitePlayer.getName()) << endl;
      }
    }
    else {
      cout << "WRONG PIECE" << endl;
      cout << "TURN SWITCH" << endl;
      turnNum++;
      cout << turnText(turnNum, blackPlayer.getName(), whitePlayer.getName()) << endl;
    }
  }
  cout << "Goodbye!" << endl;
  //system("pause");
  return 0;
}
bool isKing(chessBoard A, string playerColor){ 
  for(int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      if( A.board[i][j].getFill().getId()[0] == playerColor[0] && A.board[i][j].getFill().getType() == "King") {
	return true;
      }
    }
  }
  return false;
}
pair <int,int> findKing(chessBoard A, string playerColor) {
 for(int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      if( A.board[i][j].getFill().getId()[0] == playerColor[0] && A.board[i][j].getFill().getType() == "King") {
	return make_pair(j,i);
      }
    }
  }
}
bool inCheck(string playerColor, chessBoard A, vector < pair <string,pair <int, int > > > movesList ) {
  vector <pair < chessPiece, pair < int,int > > > list;
  vector <pair < chessPiece, pair <int,int> > > potentialMoves;
  pair <int,int> kingPlace;
  string playerKing = "";
  playerKing += playerColor[0];
  playerKing += 'K'; 
  playerKing += '0';
  for(int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      if( A.board[i][j].getFilled() && A.board[i][j].getFill().getId()[0] != playerKing[0] ) {
	pair <int,int> t0 = make_pair(i,j);
	list.push_back(make_pair(A.board[i][j].getFill(),t0));
      }
      else if(A.board[i][j].getFill().getId() == playerKing) {
	kingPlace = make_pair(j,i);
      }
    }
  }
  cout << kingPlace.first << " " << kingPlace.second << endl;
  for( int i = 0; i < list.size(); i++ ) {
    vector < pair <int,int> > t2;
    if(list[i].first.getId()[0] == 'B' )
      t2 = list[i].first.validMoves(list[i].second.second,list[i].second.first,"Black",A,movesList);
    else
      t2 = list[i].first.validMoves(list[i].second.second,list[i].second.first,"White",A,movesList);
    for(int j = 0; j < t2.size(); j++) {
      potentialMoves.push_back(make_pair(list[i].first,t2[j]));
    }
  }
  for(int i = 0; i < potentialMoves.size(); i++ ) {
    if(potentialMoves[i].second.first == kingPlace.first && potentialMoves[i].second.second == kingPlace.second) {      
      cout << potentialMoves[i].first.getId() << endl;
      return true;
    }
  }
  return false;
}
string fixMe(string &s) {
  for(int i = 0; i < s.length(); i++) {
    char temp = tolower(s[i]);
    s[i] = temp;
  }
  return s;
}
bool hasMoved2(vector < pair <string,pair <int,int> > > moves, string s) {
  for( int i = 0; i < moves.size(); i++ ) {
    if( s == moves[i].first ) {
      return true;
    }
  }
  return false;
}
string turnText(int i, string bName, string wName) {
  if(i % 2 == 0) 
    return bName + "'s Turn---------------------->";
  return wName + "'s Turn---------------------->";
}
string whoseTurn(int i) {
  if(i % 2 == 0)
    return "Black";
  return "White";
}
void addMove(vector < pair <string,pair <int, int > > > &movesList, pair <int,int> space, string name) {
  movesList.push_back(make_pair(name,space));
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
    A.placePiece(4,0,queen,"WQ0");
    A.placePiece(3,0,king,"WK0");
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
      A.placePiece(4,0,queen,"WQ0");
    }
    else if (test == "King") {
      A.placePiece(3,0,king,"WK0");
      A.placePiece(3,7,king,"BK0");
    }
    else if (test == "Castle") {
      A.placePiece(7,7,rook,"BR2");
      A.placePiece(0,7,rook,"BR1");
      A.placePiece(7,0,rook,"WR2");
      A.placePiece(0,0,rook,"WR1");
      A.placePiece(3,0,king,"WK0");
      A.placePiece(3,7,king,"BK0");
    }
    else if (test == "special" ) {
      A.placePiece(6,6,pawn,"WP1");
      A.placePiece(6,1,pawn,"BP1");
      A.placePiece(3,0,king,"WK0");
      A.placePiece(3,7,king,"BK0");
    }
  }
}
