#include "struct.h"
#include "defData.h"
using namespace std;

/************************
*ʵ����Ϸ��������ת��һ��
* ���룺����ͼ����
* ���������ͼ������ף�ػ��
************************/
void gameOverScene(IMAGE* bg) {
    putimage(0, 0, bg);
    settextcolor(WHITE); //������ɫ
    RECT rec = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
    settextstyle(20, 0, _T("����"));  //������ʽ
    drawtext(_T("��ϲ����ͨ���ˣ�"),
        &rec, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    //::system("pause");��Ϸ��������Ҫ��ͣ
    //DT_SINGLELINE :������ʾ��DT_CENTER:������ʾ��DT_VCENTER : ��ֱ������ʾ
}
void gameNextScene(IMAGE* bg) {
    putimage(0, 0, bg);
    settextcolor(WHITE); //������ɫ
    RECT rec = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
    settextstyle(20, 0, _T("����"));  //������ʽ
    drawtext(_T("��ϲ�����˹���ս�ɹ����������ת����һ�أ�"),
        &rec, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    //DT_SINGLELINE :������ʾ��DT_CENTER:������ʾ��DT_VCENTER : ��ֱ������ʾ
    ::system("pause");
    cleardevice();    //���Ҫ��ת����һ�أ����Ҫ������ȥ������

}