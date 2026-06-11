#include "Checkers.h"
#include <iostream>
#include <cmath>

using namespace std;

Checkers::Checkers() {
    turn = 1; // 紅方先手
    resetBoard();
}

void Checkers::resetBoard() {
    for (int r = 0; r < 8; r++) {
        for (int c = 0; c < 8; c++) {
            board[r][c] = EMPTY;
            // 只在深色格放置棋子
            if ((r + c) % 2 != 0) {
                if (r < 3) board[r][c] = BLACK;
                else if (r > 4) board[r][c] = RED;
            }
        }
    }
}

void Checkers::display() {
    cout << "\n    0 1 2 3 4 5 6 7 (行)" << endl;
    cout << "  -------------------" << endl;
    for (int r = 0; r < 8; r++) {
        cout << r << " | ";
        for (int c = 0; c < 8; c++) {
            if (board[r][c] == EMPTY) cout << ". ";
            else if (board[r][c] == RED) cout << "R ";
            else if (board[r][c] == BLACK) cout << "B ";
            else if (board[r][c] == RED_KING) cout << "K "; // 紅王
            else if (board[r][c] == BLACK_KING) cout << "M "; // 黑王
        }
        cout << "|" << endl;
    }
    cout << "  -------------------" << endl;
    cout << "當前回合: " << (turn == 1 ? "紅方 (R/K)" : "黑方 (B/M)") << endl;
}

bool Checkers::isMyPiece(Piece p) {
    if (turn == 1 && (p == RED || p == RED_KING)) return true;
    if (turn == 2 && (p == BLACK || p == BLACK_KING)) return true;
    return false;
}

bool Checkers::isEnemyPiece(Piece p) {
    if (p == EMPTY) return false;
    if (turn == 1 && (p == BLACK || p == BLACK_KING)) return true;
    if (turn == 2 && (p == RED || p == RED_KING)) return true;
    return false;
}

bool Checkers::makeMove(int r1, int c1, int r2, int c2) {
    if (r1 < 0 || r1 > 7 || c1 < 0 || c1 > 7 || r2 < 0 || r2 > 7 || c2 < 0 || c2 > 7) return false;
    if (!isMyPiece(board[r1][c1])) return false;
    if (board[r2][c2] != EMPTY) return false;

    Piece currentPiece = board[r1][c1];
    int rowDiff = r2 - r1;
    int colDiff = abs(c2 - c1);

    if (abs(rowDiff) != colDiff) return false;

    bool isKing = (currentPiece == RED_KING || currentPiece == BLACK_KING);

    // 普通棋子邏輯
    if (!isKing) {
        if (currentPiece == RED && rowDiff > 0) return false;
        if (currentPiece == BLACK && rowDiff < 0) return false;

        if (abs(rowDiff) == 1) {
            executeMove(r1, c1, r2, c2);
            return true;
        }
        if (abs(rowDiff) == 2) {
            int midR = (r1 + r2) / 2;
            int midC = (c1 + c2) / 2;
            if (isEnemyPiece(board[midR][midC])) {
                board[midR][midC] = EMPTY;
                executeMove(r1, c1, r2, c2);
                return true;
            }
        }
        return false;
    }
    // 王棋/飛王邏輯
    else {
        int stepR = (rowDiff > 0) ? 1 : -1;
        int stepC = (c2 - c1 > 0) ? 1 : -1;

        int checkR = r1 + stepR;
        int checkC = c1 + stepC;

        int enemyCount = 0;
        int enemyR = -1, enemyC = -1;

        while (checkR != r2 && checkC != c2) {
            Piece p = board[checkR][checkC];
            if (isMyPiece(p)) return false;
            if (isEnemyPiece(p)) {
                enemyCount++;
                enemyR = checkR;
                enemyC = checkC;
            }
            checkR += stepR;
            checkC += stepC;
        }

        if (enemyCount == 0) {
            executeMove(r1, c1, r2, c2);
            return true;
        }
        else if (enemyCount == 1) {
            board[enemyR][enemyC] = EMPTY;
            executeMove(r1, c1, r2, c2);
            return true;
        }
        return false;
    }
}

void Checkers::executeMove(int r1, int c1, int r2, int c2) {
    board[r2][c2] = board[r1][c1];
    board[r1][c1] = EMPTY;

    if (board[r2][c2] == RED && r2 == 0) {
        board[r2][c2] = RED_KING;
        cout << ">>> 紅方棋子升變為飛王(K)！" << endl;
    }
    if (board[r2][c2] == BLACK && r2 == 7) {
        board[r2][c2] = BLACK_KING;
        cout << ">>> 黑方棋子升變為飛王(M)！" << endl;
    }

    turn = (turn == 1) ? 2 : 1;
}