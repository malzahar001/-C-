#pragma once
#include <graphics.h>
#include <conio.h>
#include <string>
#include <iostream>
#include <mysql.h>
using namespace std;
/************************
*�궨��
************************/
#define LINE 48  //��ͼ�������
#define COLUMN 48  //��ͼ�������

#define SCREEN_WIDTH 780  //��̨���
#define SCREEN_HEIGHT 585  //��̨�߶�

#define Normalsize 65  //����һ��ߴ磬Ҳ��ÿ��λ�õ�ƫ����

#define START_X  0    //��ͼ����ʼ����
#define START_Y  0    //��ͼ����ʼ����

//�ȼ�
#define KEY_UP  'w'    //char 'w'
#define KEY_LEFT  'a'    //char 'a'
#define KEY_RIGHT  'd'    //char 'd'
#define KEY_DOWN  's'    //char 's'
#define KEY_QUIT  'q'    //char 'q'

//���ж�
#define isValid(pos) (pos.x>=0&&next_pos.x<COLUMN&&pos.y>=0&&next_pos.y<LINE)
//mysql��¼
#define DB_NAME "boxman"
#define DB_HOST "127.0.0.1"
#define DB_PORT 3306
#define DB_USER "root"
#define DB_USER_PASSWD "Malzahar001"
//��¼ʧ�ܴ���
#define MAX_RETRY_TIMES 3

//ö�٣���Ĭ�ϴ�0��ʼ���丳ֵ
enum _PROPS {
    WALL,  //ǽ 0
    FLOOR, //�ذ� 1
    BOX_des,//����Ŀ�ĵ� 2
    MAN,    //С�� 3
    BOX,  //����4
    _BOX,  //����Ŀ�ĵص�����5
    _MAN,  //��ʱ��վ��Ŀ�ĵ���6
    END
};