#include "Checkers.h"
#include <iostream>

using namespace std;

int main() {
    Checkers game;
    int r1, c1, r2, c2;

    cout << "歡迎來到 C++ 國際跳棋" << endl;
    cout << "提示：輸入 '-1' 可以隨時退出遊戲。" << endl;

    while (true) {
        game.display();
        cout << "輸入起始座標與目標 (r1 c1 r2 c2)，例如 '5 0 4 1': ";
        
        cin >> r1;
        if (r1 == -1) {
            cout << "遊戲結束，感謝遊玩！" << endl;
            break;
        }
        
        if (!(cin >> c1 >> r2 >> c2)) break;

        if (!game.makeMove(r1, c1, r2, c2)) {
            cout << ">>> 無效的移動，請再試一次！" << endl;
        }
    }
    return 0;
}