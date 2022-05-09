#include <graphics.h>
#include <conio.h>
#include <string>
#include <iostream>
#include "defData.h"
#include "struct.h"
using namespace std;
/************************
*函数声明
************************/
void gameControl(char direct, int flag[][COLUMN], int map[][COLUMN], int n, POS& man, IMAGE images[], int k);
void init_graphic(IMAGE images[], int k, IMAGE bg_image);
bool login(userinfo& user);
bool fetch_level_info(_levelinfo& level, int level_id);
bool transform_map_db2array(_levelinfo& level, int map[LINE][COLUMN]);
bool updata_user_level(userinfo& user, int next_level_id);
bool isGameOver(int map[][COLUMN], int n);
void gameOverScene(IMAGE* bg);
void gameNextScene(IMAGE* bg);

/************************
*地图定义
************************/
//地图背景变量
IMAGE bg_image;
//地图道具变量
IMAGE images[8];
//地图
int map[LINE][COLUMN] = { 0 };
//地图标记目的地的点
int flag[LINE][COLUMN] = { 0 };
//小人坐标
POS man;

int main()
{
    /************************
    *1.用户身份验证
    *
    ************************/
    userinfo user;  //当前未填的用户信息
    //判断是否成功登录
    if (login(user) == false) {
        cout << "登录失败，请重新登录！" << endl;
        ::system("pause");
        exit(-1);   //立即推出程序，类似return 0;
    }
    else {
        cout << "登录成功，用户id:" << user.id << endl << "你所在的关卡是：" << user.level_id << endl;
        ::system("pause");
    }

    /************************
    *2.游戏环节
    *
    ************************/
    //初始化游戏舞台
    init_graphic(images, 8, bg_image);

    //创建循环的判断条件
    bool quit = false;
    do {
        //根据用户所在的关卡id获取关卡数据
        _levelinfo level;
        if (!fetch_level_info(level, user.level_id)) {
            cout << "获取关卡数据失败，请重试";
            ::system("pause");
            exit(-1);   //立即推出程序，类似return 0;
        }
        else {
            cout << "获取关卡数据成功"<<endl;
            ::system("pause");
        }
        //把数据库中的地图数据转换到map中
        if (!transform_map_db2array(level, map)) {
            cout << "地图数据载入失败" << endl;
            ::system("pause");
            exit(-1);   //立即推出程序，类似return 0;w
        }
        else {
            cout << "地图数据载入成功" << endl;
            ::system("pause");
        }

        //将已加载图片的图变量(背景)放到舞台上
        putimage(0, 0, &bg_image);
        //显示每个位置的图标
        for (int i = 0; i < level.map_row; i++) {
            for (int j = 0; j < level.map_column; j++) {
                if (map[i][j] == MAN) {  //如果遍历到人，就记录人的坐标
                    man.y = i;
                    man.x = j;
                }
                if (map[i][j] == BOX_des) {  //如果遍历到目的地，则标记为1
                    flag[i][j] = 1;
                }
                putimage(START_X + j * Normalsize, START_Y + i * Normalsize, &images[map[i][j]]);
            }
        }

        //游戏环节:热键控制
        //给热键输入的循环条件
        do {
            //keyborder函数，如果有检测到热键，返回true
            if (_kbhit()) {
                char ch = _getch();  //获取热键字符
                switch (ch) {
                case KEY_UP:
                    gameControl(KEY_UP,flag,map, LINE,man,images,8);   //操控
                    break;
                case KEY_LEFT:
                    gameControl(KEY_LEFT, flag, map, LINE, man, images, 8);
                    break;
                case KEY_RIGHT:
                    gameControl(KEY_RIGHT, flag, map, LINE, man, images, 8);
                    break;
                case KEY_DOWN:
                    gameControl(KEY_DOWN, flag, map, LINE, man, images, 8);
                    break;
                case KEY_QUIT:
                    quit = true;  //遇到q键退出
                    break;
                }
                //判断是否游戏结束
                if (isGameOver(map, COLUMN)) {

                    //如果下一关的序号为0，认为通关，否则就跳到下一关
                    if (level.next_level < 1) {
                        gameOverScene(&images[END]);
                        quit = true;  //结束游戏环节
                        break;
                    }
                    gameNextScene(&bg_image);

                    //更新数据库用户的关卡信息（即users表的id关卡序号修改为next_level）
                    if (updata_user_level(user, level.next_level))
                        user.level_id = level.next_level;  //程序中该用户的关卡也要更新
                    break;  //热键控制结束，先退出内部循环，再跳出外部循环，然后再次载入地图


                }
            }
        } while (!quit);
    } while (!quit);

    ::system("pause");

    //游戏结束，释放资源
    closegraph();
    return 0;
}