#pragma once
#include <string>
using namespace std;

//�û���Ϣ�ṹ
struct userinfo {
	int id;       //�û�id
	string username; //�û���
	string password; //����
	int level_id;    //�ؿ���
};
struct _levelinfo {
	int id;      //�ؿ�id
	string name;//�ؿ�����
	int map_row; //��ͼ������
	int map_column;//��ͼ������
	string map_data;//��ά��ͼ����
	int next_level;//��һ�ؿ���id
};
//С����������
struct POS {
	int x;//С�����ڵĶ�ά�������
	int y;//С�����ڵĶ�ά�������
};//��¼С�˵ĵ�ǰ����