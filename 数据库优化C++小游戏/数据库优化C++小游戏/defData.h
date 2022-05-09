#pragma once
#include <graphics.h>
#include <conio.h>
#include <string>
#include <iostream>
#include <mysql.h>
using namespace std;
/************************
*宏定义
************************/
#define LINE 48  //地图最大行数
#define COLUMN 48  //地图最大列数

#define SCREEN_WIDTH 780  //舞台宽度
#define SCREEN_HEIGHT 585  //舞台高度

#define Normalsize 65  //道具一般尺寸，也是每个位置的偏移量

#define START_X  0    //地图的起始坐标
#define START_Y  0    //地图的起始坐标

//热键
#define KEY_UP  'w'    //char 'w'
#define KEY_LEFT  'a'    //char 'a'
#define KEY_RIGHT  'd'    //char 'd'
#define KEY_DOWN  's'    //char 's'
#define KEY_QUIT  'q'    //char 'q'

//宏判断
#define isValid(pos) (pos.x>=0&&next_pos.x<COLUMN&&pos.y>=0&&next_pos.y<LINE)
//mysql登录
#define DB_NAME "boxman"
#define DB_HOST "127.0.0.1"
#define DB_PORT 3306
#define DB_USER "root"
#define DB_USER_PASSWD "Malzahar001"
//登录失败次数
#define MAX_RETRY_TIMES 3

//枚举，会默认从0开始给其赋值
enum _PROPS {
    WALL,  //墙 0
    FLOOR, //地板 1
    BOX_des,//箱子目的地 2
    MAN,    //小人 3
    BOX,  //箱子4
    _BOX,  //到达目的地的箱子5
    _MAN,  //此时人站在目的地上6
    END
};