#include "struct.h"
#include "defData.h"
using namespace std;

bool connect_db(MYSQL& mysql);
bool fetch_user_info(userinfo& user);
bool fetch_level_info(_levelinfo& level, int level_id);
/****************************************************
 *功能：通过用户名和密码获取用户信息
 *输入：
 *     user - 用户信息结构体
 * 返回值：
 *       获取成功返回true，失败false
 ****************************************************/

 //通过用户名和密码获取用户信息，获取成功返回true，失败false
bool fetch_user_info(userinfo& user) {
	MYSQL mysql;     //数据库对象
	char sql[256];   //存放查询语句
	MYSQL_RES* res;  //存储查询所有结果
	MYSQL_ROW row;   //存放查询结果的每一项
	bool ret = false;//标记查询是否成功

	//1.连接到数据库，失败代表无法连接服务器
	if (connect_db(mysql) == false)
		return false;

	//2.根据用户名和密码获取用户信息(id,level_id)
	//snprintf给sql赋值字符串语句，内含账号与密码
	//user.username需要用c_str()由C字符串转换为字符串string
	snprintf(sql, 256, "select * from users where username='%s' and password='%s';", user.username.c_str(), user.password.c_str());

	//执行sql语句的查询，成功返回0
	ret = mysql_query(&mysql, sql);
	if (ret) {
		cout << "数据库查询输错" << sql << " 错误原因：" << mysql_error(&mysql) << endl;
		mysql_close(&mysql);
		return false;
	}
	//3.获取查询结果
	res = mysql_store_result(&mysql);
	row = mysql_fetch_row(res);

	//如果没有查找到记录，就关闭数据并返回false
	if (row == NULL) {
		mysql_free_result(res);
		mysql_close(&mysql);
		return false;
	}
	user.id = atoi(row[0]);  //字符串转换成整型
	user.level_id = atoi(row[3]);  //字符串转换成整型
	cout << "userid: " << user.id << "  " << "level_id: " << user.level_id << endl;
	//打印用户ID和关卡序号

	//4.返回结果，释放结果集和关闭数据库
	mysql_free_result(res);
	mysql_close(&mysql);
	return true;
}

/****************************************************
 *功能：登录数据库
 * 输入：固定的账号密码端口
 ****************************************************/
bool connect_db(MYSQL& mysql) {
	//1.初始化数据库句柄
	mysql_init(&mysql);

	//2.设置字符编码
	mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk");

	//3.连接数据库并判断是否连接成功
	//mysql_real_connect返回值为NULL代表连接失败
	if (mysql_real_connect(&mysql, DB_HOST, DB_USER, DB_USER_PASSWD, DB_NAME, DB_PORT, NULL, 0) == NULL)
	{
		cout << "连接失败！错误原因：" << mysql_error(&mysql) << endl;
		return false;
	}

	return true;
}

/****************************************************
 *功能：通过关卡id获取完整的关卡信息（如地图数据，下一关）
 *输入：
 *     level - 保存关卡信息的结构体变量
 *     level_id - 关卡id
 * 返回值：
 *       获取成功返回true，失败false
 ****************************************************/
bool fetch_level_info(_levelinfo& level, int level_id) {
	MYSQL mysql;     //数据库对象
	char sql[256];   //存放查询语句
	MYSQL_RES* res;  //存储查询所有结果
	MYSQL_ROW row;   //存放查询结果的每一项
	bool ret = false;//标记查询是否成功

	//1.连接到数据库，失败代表无法连接服务器
	if (connect_db(mysql) == false)
		return false;
	//2.根据关卡id查询数据库获取地图信息
	snprintf(sql, 256,
		"select * from levels where id=%d;",
		level_id);
	//执行sql语句的查询，成功返回0
	ret = mysql_query(&mysql, sql);
	if (ret) {
		cout << "数据库查询输错" << sql << " 错误原因：" << mysql_error(&mysql) << endl;
		mysql_close(&mysql);
		return false;
	}
	//3.获取查询结果
	res = mysql_store_result(&mysql);
	row = mysql_fetch_row(res);

	//如果没有查找到记录，就关闭数据并返回false
	if (row == NULL) {
		mysql_free_result(res);
		mysql_close(&mysql);
		return false;
	}
	level.id = level_id;  //row[0]
	level.name = row[1];
	level.map_row = atoi(row[2]);//字符串转换成整型
	level.map_column = atoi(row[3]);
	level.map_data = row[4];
	level.next_level = atoi(row[5]);  //字符串转换成整型

	//输出查询所有结构体的所有结果
	cout << "地图序号: " << level.id << "  " << "地图名: " << level.name << endl
		<< "地图总行数: " << level.map_row << "  " << "地图总列数: " << level.map_column << endl
		<< "地图数据: " << level.map_data << "  " << "下一关序号: " << level.next_level << endl;

	//4.返回结果，释放结果集和关闭数据库
	mysql_free_result(res);
	mysql_close(&mysql);
	return true;
}
//将地图数据转换为二维数组中
bool transform_map_db2array(_levelinfo& level, int map[LINE][COLUMN]) {
	if (level.map_row > LINE || level.map_column > COLUMN) {
		cout << "地图太大，请重新设置" << endl;
		return false;
	}
	if (level.map_data.length() < 1) {
		cout << "地图数据有误，请重新设置" << endl;
		return false;
	}

	int start = 0, end = 0;
	int i = 0;
	do {
		end = level.map_data.find('|', start); //end定位每个分界符

		if (end < 0)
			end = level.map_data.length();   //如果分界已经定位完了，则此时end为-1，则改为地图数据的最大长度。
		if (start >= end)
			break;     //如果此时这串数字是空的，则退出

		string line = level.map_data.substr(start, end - start);  //截取一串数字
		cout << "get line:  " << line << endl;

		//对行数据进行解析
		//strtok_s函数能将一串字符0,0,0,0,0,0,0,0破坏，去除指定符号逗号，
		//然后将除了逗号的其他字符都分开，然后返回一个一个的剩余单字符。
		char* next_token = NULL;  //给接口用的，不用管
		char* item = strtok_s((char*)line.c_str(), ",", &next_token);//
		int j = 0;
		while (item) {   //当所有的单个字符都被截取完后，item为null
			map[i][j++] = *item - '0';
			item = strtok_s(NULL, ",", &next_token);
		}

		if (j < level.map_column) {//如果载入的一串数字个数j不到提前规定的列数，则认为出错
			cout << "地图数据解析出差，终止!" << endl;
			return false;
		}
		if (i >= level.map_column) { //如果目前输入的行数大于等于提前规定的行数，应该终止继续输入地图数据
			break;
		}
		cout << endl;
		start = end + 1;  //截取完一串数字后就重设界限
	} while (++i < LINE);

	if (i < level.map_row) {     //如果输入地图数据完毕后，实际输入行数少于规定的行数，则认为错误
		cout << "地图行数少于设定，终止！" << endl;
		return false;
	}

	return true;
}

/****************************************************
 *功能：载入下一关地图
 *输入：
 *     level - 保存关卡信息的结构体变量
 *     level_id - 关卡id
 * 返回值：
 *       获取成功返回true，失败false
 ****************************************************/
bool updata_user_level(userinfo& user, int next_level_id) {
	MYSQL mysql;     //数据库对象
	char sql[256];   //存放查询语句
	bool ret = false;//标记查询是否成功

	//1.连接到数据库，失败代表无法连接服务器
	if (connect_db(mysql) == false)
		return false;
	//2.根据用户id更新下一关的level_id
	snprintf(sql, 256, "update users set level_id= %d where id=%d;", next_level_id, user.id);

	ret = mysql_query(&mysql, sql);
	//查询失败返回1
	if (ret) {
		cout << "数据库更新出错，" << mysql_error(&mysql) << endl;
		mysql_close(&mysql);
		return false;
	}

	//3.返回结果，释放结果集和关闭数据库
	mysql_close(&mysql);
	return true;
}