#include "struct.h"
#include "defData.h"
using namespace std;
/************************
*��ʼ����̨
************************/
void init_graphic(IMAGE images[],int k, IMAGE bg_image) {
    //��̨��Ϸ(������̨���趨���)
    initgraph(SCREEN_WIDTH, SCREEN_HEIGHT);

    //��ͼƬ�ļ����ص�ͼ�����ڣ���ͼ����ָ�룬�ļ�������Ҫ��˫�ۺţ�ͼƬҪ�ڹ����ļ��£�
    loadimage(&bg_image, _T("blackground.bmp"), SCREEN_WIDTH, SCREEN_HEIGHT, true);
    loadimage(&images[END], _T("QQͼƬ20220311031450.png"), SCREEN_WIDTH, SCREEN_HEIGHT, true);
    //���Ѽ���ͼƬ��ͼ����(����)�ŵ���̨��
    putimage(0, 0, &bg_image);


    //�������е��߸�ͼ��������
    //ע�⣺�ļ��ַ����ĸ�ʽ��������Ҫ�ü��� _T("")�ķ���ͳһ�ӿڸ�ʽ��
    //�����ַ��������� ��abc�� �� _T(��abc��) ��ʾ�����Ǽ��� _T("")
    loadimage(&images[WALL], _T("wall_right.bmp"), Normalsize, Normalsize, true);
    loadimage(&images[FLOOR], _T("floor.bmp"), Normalsize, Normalsize, true);
    loadimage(&images[BOX_des], _T("des.bmp"), Normalsize, Normalsize, true);
    loadimage(&images[MAN], _T("man.bmp"), Normalsize, Normalsize, true);
    loadimage(&images[BOX], _T("box.bmp"), Normalsize, Normalsize, true);
    loadimage(&images[_BOX], _T("box.bmp"), Normalsize, Normalsize, true);
    loadimage(&images[_MAN], _T("man.bmp"), Normalsize, Normalsize, true);

}
