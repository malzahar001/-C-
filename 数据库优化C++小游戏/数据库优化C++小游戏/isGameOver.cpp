#include "struct.h"
#include "defData.h"
using namespace std;

/************************
*实现判断游戏结束
************************/
bool isGameOver(int map[][COLUMN],int n) {
    for (int i = 0; i < LINE; i++) {
        for (int j = 0; j < COLUMN; j++) {
            if (map[i][j] == BOX_des)
                return false;
        }
    }
    return true;
}
