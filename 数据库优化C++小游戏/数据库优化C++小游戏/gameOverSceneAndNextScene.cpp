#include "struct.h"
#include "defData.h"
using namespace std;

/************************
*实现游戏结束和跳转下一关
* 输入：背景图变量
* 输出：背景图变量与祝贺话语。
************************/
void gameOverScene(IMAGE* bg) {
    putimage(0, 0, bg);
    settextcolor(WHITE); //字体颜色
    RECT rec = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
    settextstyle(20, 0, _T("宋体"));  //字体样式
    drawtext(_T("恭喜您，通关了！"),
        &rec, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    //::system("pause");游戏结束不需要暂停
    //DT_SINGLELINE :单行显示。DT_CENTER:居中显示。DT_VCENTER : 垂直居中显示
}
void gameNextScene(IMAGE* bg) {
    putimage(0, 0, bg);
    settextcolor(WHITE); //字体颜色
    RECT rec = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
    settextstyle(20, 0, _T("宋体"));  //字体样式
    drawtext(_T("恭喜您，此关挑战成功，任意键跳转到下一关！"),
        &rec, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    //DT_SINGLELINE :单行显示。DT_CENTER:居中显示。DT_VCENTER : 垂直居中显示
    ::system("pause");
    cleardevice();    //如果要跳转到下一关，最后要清屏，去掉文字

}