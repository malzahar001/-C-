#include <iostream>
#include <mysql.h>
#include <string>
#include <conio.h>
#include <graphics.h>
#include "struct.h"
#include "defData.h"
using namespace std;
//������ͨ���û����������ȡ�û���Ϣ����ȡ�ɹ�����true��ʧ��false
bool fetch_user_info(userinfo& user);  //������һ��Դ�ļ��ĺ�������������

//ʵ�ֶ�ε�¼���ܣ��������Ƿ�ɹ���¼���ж�
bool login(userinfo& user) {
    bool ret = false;
    int times = 0;
    do {
        cout << "�����˺ţ�";
        cin >> user.username;
        cout << "�������룺";
        cin >> user.password;

        ret = fetch_user_info(user);//���Ե�¼��������ֵ��trueΪ�ɹ���¼
        times++;

        if (times >= MAX_RETRY_TIMES) {  //��������صǴ����ͷ���ret��Ĭ��ֵfalse
            break;
        }
        if (ret == false) {
            cout << "��¼ʧ�ܣ����������룡" << endl;
        }
    } while (!ret);
    return ret;
}
