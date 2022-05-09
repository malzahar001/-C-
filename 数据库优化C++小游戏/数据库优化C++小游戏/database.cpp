#include "struct.h"
#include "defData.h"
using namespace std;

bool connect_db(MYSQL& mysql);
bool fetch_user_info(userinfo& user);
bool fetch_level_info(_levelinfo& level, int level_id);
/****************************************************
 *���ܣ�ͨ���û����������ȡ�û���Ϣ
 *���룺
 *     user - �û���Ϣ�ṹ��
 * ����ֵ��
 *       ��ȡ�ɹ�����true��ʧ��false
 ****************************************************/

 //ͨ���û����������ȡ�û���Ϣ����ȡ�ɹ�����true��ʧ��false
bool fetch_user_info(userinfo& user) {
	MYSQL mysql;     //���ݿ����
	char sql[256];   //��Ų�ѯ���
	MYSQL_RES* res;  //�洢��ѯ���н��
	MYSQL_ROW row;   //��Ų�ѯ�����ÿһ��
	bool ret = false;//��ǲ�ѯ�Ƿ�ɹ�

	//1.���ӵ����ݿ⣬ʧ�ܴ����޷����ӷ�����
	if (connect_db(mysql) == false)
		return false;

	//2.�����û����������ȡ�û���Ϣ(id,level_id)
	//snprintf��sql��ֵ�ַ�����䣬�ں��˺�������
	//user.username��Ҫ��c_str()��C�ַ���ת��Ϊ�ַ���string
	snprintf(sql, 256, "select * from users where username='%s' and password='%s';", user.username.c_str(), user.password.c_str());

	//ִ��sql���Ĳ�ѯ���ɹ�����0
	ret = mysql_query(&mysql, sql);
	if (ret) {
		cout << "���ݿ��ѯ���" << sql << " ����ԭ��" << mysql_error(&mysql) << endl;
		mysql_close(&mysql);
		return false;
	}
	//3.��ȡ��ѯ���
	res = mysql_store_result(&mysql);
	row = mysql_fetch_row(res);

	//���û�в��ҵ���¼���͹ر����ݲ�����false
	if (row == NULL) {
		mysql_free_result(res);
		mysql_close(&mysql);
		return false;
	}
	user.id = atoi(row[0]);  //�ַ���ת��������
	user.level_id = atoi(row[3]);  //�ַ���ת��������
	cout << "userid: " << user.id << "  " << "level_id: " << user.level_id << endl;
	//��ӡ�û�ID�͹ؿ����

	//4.���ؽ�����ͷŽ�����͹ر����ݿ�
	mysql_free_result(res);
	mysql_close(&mysql);
	return true;
}

/****************************************************
 *���ܣ���¼���ݿ�
 * ���룺�̶����˺�����˿�
 ****************************************************/
bool connect_db(MYSQL& mysql) {
	//1.��ʼ�����ݿ���
	mysql_init(&mysql);

	//2.�����ַ�����
	mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk");

	//3.�������ݿⲢ�ж��Ƿ����ӳɹ�
	//mysql_real_connect����ֵΪNULL��������ʧ��
	if (mysql_real_connect(&mysql, DB_HOST, DB_USER, DB_USER_PASSWD, DB_NAME, DB_PORT, NULL, 0) == NULL)
	{
		cout << "����ʧ�ܣ�����ԭ��" << mysql_error(&mysql) << endl;
		return false;
	}

	return true;
}

/****************************************************
 *���ܣ�ͨ���ؿ�id��ȡ�����Ĺؿ���Ϣ�����ͼ���ݣ���һ�أ�
 *���룺
 *     level - ����ؿ���Ϣ�Ľṹ�����
 *     level_id - �ؿ�id
 * ����ֵ��
 *       ��ȡ�ɹ�����true��ʧ��false
 ****************************************************/
bool fetch_level_info(_levelinfo& level, int level_id) {
	MYSQL mysql;     //���ݿ����
	char sql[256];   //��Ų�ѯ���
	MYSQL_RES* res;  //�洢��ѯ���н��
	MYSQL_ROW row;   //��Ų�ѯ�����ÿһ��
	bool ret = false;//��ǲ�ѯ�Ƿ�ɹ�

	//1.���ӵ����ݿ⣬ʧ�ܴ����޷����ӷ�����
	if (connect_db(mysql) == false)
		return false;
	//2.���ݹؿ�id��ѯ���ݿ��ȡ��ͼ��Ϣ
	snprintf(sql, 256,
		"select * from levels where id=%d;",
		level_id);
	//ִ��sql���Ĳ�ѯ���ɹ�����0
	ret = mysql_query(&mysql, sql);
	if (ret) {
		cout << "���ݿ��ѯ���" << sql << " ����ԭ��" << mysql_error(&mysql) << endl;
		mysql_close(&mysql);
		return false;
	}
	//3.��ȡ��ѯ���
	res = mysql_store_result(&mysql);
	row = mysql_fetch_row(res);

	//���û�в��ҵ���¼���͹ر����ݲ�����false
	if (row == NULL) {
		mysql_free_result(res);
		mysql_close(&mysql);
		return false;
	}
	level.id = level_id;  //row[0]
	level.name = row[1];
	level.map_row = atoi(row[2]);//�ַ���ת��������
	level.map_column = atoi(row[3]);
	level.map_data = row[4];
	level.next_level = atoi(row[5]);  //�ַ���ת��������

	//�����ѯ���нṹ������н��
	cout << "��ͼ���: " << level.id << "  " << "��ͼ��: " << level.name << endl
		<< "��ͼ������: " << level.map_row << "  " << "��ͼ������: " << level.map_column << endl
		<< "��ͼ����: " << level.map_data << "  " << "��һ�����: " << level.next_level << endl;

	//4.���ؽ�����ͷŽ�����͹ر����ݿ�
	mysql_free_result(res);
	mysql_close(&mysql);
	return true;
}
//����ͼ����ת��Ϊ��ά������
bool transform_map_db2array(_levelinfo& level, int map[LINE][COLUMN]) {
	if (level.map_row > LINE || level.map_column > COLUMN) {
		cout << "��ͼ̫������������" << endl;
		return false;
	}
	if (level.map_data.length() < 1) {
		cout << "��ͼ������������������" << endl;
		return false;
	}

	int start = 0, end = 0;
	int i = 0;
	do {
		end = level.map_data.find('|', start); //end��λÿ���ֽ��

		if (end < 0)
			end = level.map_data.length();   //����ֽ��Ѿ���λ���ˣ����ʱendΪ-1�����Ϊ��ͼ���ݵ���󳤶ȡ�
		if (start >= end)
			break;     //�����ʱ�⴮�����ǿյģ����˳�

		string line = level.map_data.substr(start, end - start);  //��ȡһ������
		cout << "get line:  " << line << endl;

		//�������ݽ��н���
		//strtok_s�����ܽ�һ���ַ�0,0,0,0,0,0,0,0�ƻ���ȥ��ָ�����Ŷ��ţ�
		//Ȼ�󽫳��˶��ŵ������ַ����ֿ���Ȼ�󷵻�һ��һ����ʣ�൥�ַ���
		char* next_token = NULL;  //���ӿ��õģ����ù�
		char* item = strtok_s((char*)line.c_str(), ",", &next_token);//
		int j = 0;
		while (item) {   //�����еĵ����ַ�������ȡ���itemΪnull
			map[i][j++] = *item - '0';
			item = strtok_s(NULL, ",", &next_token);
		}

		if (j < level.map_column) {//��������һ�����ָ���j������ǰ�涨������������Ϊ����
			cout << "��ͼ���ݽ��������ֹ!" << endl;
			return false;
		}
		if (i >= level.map_column) { //���Ŀǰ������������ڵ�����ǰ�涨��������Ӧ����ֹ���������ͼ����
			break;
		}
		cout << endl;
		start = end + 1;  //��ȡ��һ�����ֺ���������
	} while (++i < LINE);

	if (i < level.map_row) {     //��������ͼ������Ϻ�ʵ�������������ڹ涨������������Ϊ����
		cout << "��ͼ���������趨����ֹ��" << endl;
		return false;
	}

	return true;
}

/****************************************************
 *���ܣ�������һ�ص�ͼ
 *���룺
 *     level - ����ؿ���Ϣ�Ľṹ�����
 *     level_id - �ؿ�id
 * ����ֵ��
 *       ��ȡ�ɹ�����true��ʧ��false
 ****************************************************/
bool updata_user_level(userinfo& user, int next_level_id) {
	MYSQL mysql;     //���ݿ����
	char sql[256];   //��Ų�ѯ���
	bool ret = false;//��ǲ�ѯ�Ƿ�ɹ�

	//1.���ӵ����ݿ⣬ʧ�ܴ����޷����ӷ�����
	if (connect_db(mysql) == false)
		return false;
	//2.�����û�id������һ�ص�level_id
	snprintf(sql, 256, "update users set level_id= %d where id=%d;", next_level_id, user.id);

	ret = mysql_query(&mysql, sql);
	//��ѯʧ�ܷ���1
	if (ret) {
		cout << "���ݿ���³���" << mysql_error(&mysql) << endl;
		mysql_close(&mysql);
		return false;
	}

	//3.���ؽ�����ͷŽ�����͹ر����ݿ�
	mysql_close(&mysql);
	return true;
}