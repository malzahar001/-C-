#pragma once
#include <string>
using namespace std;

//用户信息结构
struct userinfo {
	int id;       //用户id
	string username; //用户名
	string password; //密码
	int level_id;    //关卡号
};
struct _levelinfo {
	int id;      //关卡id
	string name;//关卡名字
	int map_row; //地图总行数
	int map_column;//地图总列数
	string map_data;//二维地图数据
	int next_level;//下一关卡的id
};
//小人所在坐标
struct POS {
	int x;//小人所在的二维数组的列
	int y;//小人所在的二维数组的行
};//记录小人的当前坐标