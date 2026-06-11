#ifndef CHECKERS_H
#define CHECKERS_H

// 定義棋子類型
enum Piece { EMPTY = 0, RED = 1, BLACK = 2, RED_KING = 3, BLACK_KING = 4 };

class Checkers {
private:
    Piece board[8][8];
    int turn; // 1: 紅方(RED/RED_KING), 2: 黑方(BLACK/BLACK_KING)

    // 內部輔助函式
    bool isMyPiece(Piece p);
    bool isEnemyPiece(Piece p);
    void executeMove(int r1, int c1, int r2, int c2);

public:
    Checkers();
    void resetBoard();
    void display();
    bool makeMove(int r1, int c1, int r2, int c2);
};

#endif // CHECKERS_H