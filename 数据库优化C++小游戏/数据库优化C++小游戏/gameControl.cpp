#include "struct.h"
#include "defData.h"
using namespace std;
/************************
*ʵ�����������ͼ��˫������ת��
*
************************/
void changeMap(POS* pos, enum _PROPS prop,int map[][COLUMN],int n, IMAGE images[],int k) {
    //�ڵ�ͼmap��ָ�������޸�ֵ����Ӧ��ͼ��
    map[pos->y][pos->x] = prop;
    //���µ�λ�����ɶ�Ӧ��ͼ��
    putimage(START_X + pos->x * Normalsize, START_Y + pos->y * Normalsize, &images[prop]);
}
/************************
*ʵ����Ϸ�ĸ�����Ŀ���
* ���룺
* direct - ��ǰ������
************************/
void gameControl(char direct, int flag[][COLUMN], int map[][COLUMN], int n,POS &man, IMAGE images[], int k) {
    POS next_pos = man;//�˵�ǰһ��λ��
    POS next_next_pos = man;//�˵�ǰ����λ��

    //�����˵�ǰһ��λ�ú�ǰ����λ��
    switch (direct) {
    case KEY_UP:
        next_pos.y = man.y - 1;
        next_next_pos.y = man.y - 2;
        break;
    case KEY_DOWN:
        next_pos.y = man.y + 1;
        next_next_pos.y = man.y + 2;
        break;
    case KEY_LEFT:
        next_pos.x = man.x - 1;
        next_next_pos.x = man.x - 2;
        break;
    case KEY_RIGHT:
        next_pos.x = man.x + 1;
        next_next_pos.x = man.x + 2;
        break;
    default:  //��������
        return;
    };

    //����˵�ǰ���ǵذ壬�ҵذ�λ���ǺϷ��ģ����˵������¼�ı䣬ǰһλ�øĳ���
    if (isValid(next_pos) && map[next_pos.y][next_pos.x] == FLOOR) {
        changeMap(&next_pos, MAN,map, LINE,images,k);  //��ǰ��λ�õĵذ�ĳ���
        if (flag[man.y][man.x] == 0)       //�ж���ԭ����վλ���Ƿ���Ŀ�ĵ�
            changeMap(&man, FLOOR, map, LINE, images, k);     //����ԭ��λ�øĳɵذ�
        else changeMap(&man, BOX_des, map, LINE, images, k);     //����ԭ��λ�øĳ�Ŀ�ĵ�
        man = next_pos;             //��Ŀǰ��¼������ı�
    }
    //�˵�ǰ�������ӣ��������������ǰ���ǵذ����������Ŀ�ĵ� 
    else if (isValid(next_next_pos) && map[next_pos.y][next_pos.x] == BOX)
    {
        if (map[next_next_pos.y][next_next_pos.x] == FLOOR) {
            changeMap(&next_next_pos, BOX, map, LINE, images, k);
            changeMap(&next_pos, MAN, map, LINE, images, k); //С��ǰ��һ��
            if (flag[man.y][man.x] == 0)//�ж���ԭ����վλ���Ƿ���Ŀ�ĵ�
                changeMap(&man, FLOOR, map, LINE, images, k);     //����ԭ��λ�øĳɵذ�
            else changeMap(&man, BOX_des, map, LINE, images, k);     //����ԭ��λ�øĳ�Ŀ�ĵ�
            man = next_pos;
        }
        else if (map[next_next_pos.y][next_next_pos.x] == BOX_des)
        {
            changeMap(&next_next_pos, _BOX, map, LINE, images, k);
            changeMap(&next_pos, MAN, map, LINE, images, k); //С��ǰ��һ�� 
            if (flag[man.y][man.x] == 0)//�ж���ԭ����վλ���Ƿ���Ŀ�ĵ�
                changeMap(&man, FLOOR, map, LINE, images, k);     //����ԭ��λ�øĳɵذ�
            else changeMap(&man, BOX_des, map, LINE, images, k);     //����ԭ��λ�øĳ�Ŀ�ĵ�
            man = next_pos;
        }
    }
    //��ǰ����Ŀ�ĵ�
    else if (isValid(next_next_pos) && map[next_pos.y][next_pos.x] == BOX_des)
    {
        changeMap(&next_pos, _MAN, map, LINE, images, k);  //��ǰ��λ�õ�Ŀ�ĵظĳɣ�����������Ŀ�ĵأ�
        if (flag[man.y][man.x] == 0)//�ж���ԭ����վλ���Ƿ���Ŀ�ĵ�
            changeMap(&man, FLOOR, map, LINE, images, k);     //����ԭ��λ�øĳɵذ�
        else changeMap(&man, BOX_des, map, LINE, images, k);     //����ԭ��λ�øĳ�Ŀ�ĵ�
        man = next_pos;             //��Ŀǰ��¼������ı�
    }
    //��ǰ�棨����Ŀ�ĵ��������ӣ�,�������������ǰ���ǵذ����������Ŀ�ĵ� 
    else if (isValid(next_next_pos) && map[next_pos.y][next_pos.x] == _BOX)
    {
        if (map[next_next_pos.y][next_next_pos.x] == FLOOR) {
            changeMap(&next_next_pos, BOX, map, LINE, images, k);  //����ǰ��
            changeMap(&next_pos, _MAN, map, LINE, images, k); //С��ǰ��һ�񣬱�ɼ���������Ŀ�ĵ�
            if (flag[man.y][man.x] == 0)//�ж���ԭ����վλ���Ƿ���Ŀ�ĵ�
                changeMap(&man, FLOOR, map, LINE, images, k);     //����ԭ��λ�øĳɵذ�
            else changeMap(&man, BOX_des, map, LINE, images, k);     //����ԭ��λ�øĳ�Ŀ�ĵ�
            man = next_pos;
        }
        else if (map[next_next_pos.y][next_next_pos.x] == BOX_des)
        {
            changeMap(&next_next_pos, _BOX, map, LINE, images, k);//����ǰ����������������Ŀ�ĵ�
            changeMap(&next_pos, _MAN, map, LINE, images, k); //С��ǰ��һ�� ����ɼ���������Ŀ�ĵ�
            if (flag[man.y][man.x] == 0)//�ж���ԭ����վλ���Ƿ���Ŀ�ĵ�
                changeMap(&man, FLOOR, map, LINE, images, k);     //����ԭ��λ�øĳɵذ�
            else changeMap(&man, BOX_des, map, LINE, images, k);     //����ԭ��λ�øĳ�Ŀ�ĵ�
            man = next_pos;
        }
    }
}