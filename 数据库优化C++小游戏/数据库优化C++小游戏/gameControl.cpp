#include "struct.h"
#include "defData.h"
using namespace std;
/************************
*实现两个坐标的图形双方单向转换
*
************************/
void changeMap(POS* pos, enum _PROPS prop,int map[][COLUMN],int n, IMAGE images[],int k) {
    //在地图map的指定坐标修改值，对应新图形
    map[pos->y][pos->x] = prop;
    //在新的位置生成对应的图形
    putimage(START_X + pos->x * Normalsize, START_Y + pos->y * Normalsize, &images[prop]);
}
/************************
*实现游戏四个方向的控制
* 输入：
* direct - 人前进方向
************************/
void gameControl(char direct, int flag[][COLUMN], int map[][COLUMN], int n,POS &man, IMAGE images[], int k) {
    POS next_pos = man;//人的前一格位置
    POS next_next_pos = man;//人的前两格位置

    //计算人的前一个位置和前两格位置
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
    default:  //不做处理
        return;
    };

    //如果人的前面是地板，且地板位置是合法的，则人的坐标记录改变，前一位置改成人
    if (isValid(next_pos) && map[next_pos.y][next_pos.x] == FLOOR) {
        changeMap(&next_pos, MAN,map, LINE,images,k);  //将前面位置的地板改成人
        if (flag[man.y][man.x] == 0)       //判断人原来所站位置是否是目的地
            changeMap(&man, FLOOR, map, LINE, images, k);     //将人原来位置改成地板
        else changeMap(&man, BOX_des, map, LINE, images, k);     //将人原来位置改成目的地
        man = next_pos;             //人目前记录的坐标改变
    }
    //人的前方是箱子，两种情况，箱子前面是地板或者是箱子目的地 
    else if (isValid(next_next_pos) && map[next_pos.y][next_pos.x] == BOX)
    {
        if (map[next_next_pos.y][next_next_pos.x] == FLOOR) {
            changeMap(&next_next_pos, BOX, map, LINE, images, k);
            changeMap(&next_pos, MAN, map, LINE, images, k); //小人前进一格
            if (flag[man.y][man.x] == 0)//判断人原来所站位置是否是目的地
                changeMap(&man, FLOOR, map, LINE, images, k);     //将人原来位置改成地板
            else changeMap(&man, BOX_des, map, LINE, images, k);     //将人原来位置改成目的地
            man = next_pos;
        }
        else if (map[next_next_pos.y][next_next_pos.x] == BOX_des)
        {
            changeMap(&next_next_pos, _BOX, map, LINE, images, k);
            changeMap(&next_pos, MAN, map, LINE, images, k); //小人前进一格 
            if (flag[man.y][man.x] == 0)//判断人原来所站位置是否是目的地
                changeMap(&man, FLOOR, map, LINE, images, k);     //将人原来位置改成地板
            else changeMap(&man, BOX_des, map, LINE, images, k);     //将人原来位置改成目的地
            man = next_pos;
        }
    }
    //人前面是目的地
    else if (isValid(next_next_pos) && map[next_pos.y][next_pos.x] == BOX_des)
    {
        changeMap(&next_pos, _MAN, map, LINE, images, k);  //将前面位置的目的地改成（既有人且有目的地）
        if (flag[man.y][man.x] == 0)//判断人原来所站位置是否是目的地
            changeMap(&man, FLOOR, map, LINE, images, k);     //将人原来位置改成地板
        else changeMap(&man, BOX_des, map, LINE, images, k);     //将人原来位置改成目的地
        man = next_pos;             //人目前记录的坐标改变
    }
    //人前面（既是目的地又是箱子）,两种情况，箱子前面是地板或者是箱子目的地 
    else if (isValid(next_next_pos) && map[next_pos.y][next_pos.x] == _BOX)
    {
        if (map[next_next_pos.y][next_next_pos.x] == FLOOR) {
            changeMap(&next_next_pos, BOX, map, LINE, images, k);  //箱子前进
            changeMap(&next_pos, _MAN, map, LINE, images, k); //小人前进一格，变成既有人又有目的地
            if (flag[man.y][man.x] == 0)//判断人原来所站位置是否是目的地
                changeMap(&man, FLOOR, map, LINE, images, k);     //将人原来位置改成地板
            else changeMap(&man, BOX_des, map, LINE, images, k);     //将人原来位置改成目的地
            man = next_pos;
        }
        else if (map[next_next_pos.y][next_next_pos.x] == BOX_des)
        {
            changeMap(&next_next_pos, _BOX, map, LINE, images, k);//箱子前进，既有箱子又有目的地
            changeMap(&next_pos, _MAN, map, LINE, images, k); //小人前进一格 ，变成既有人又有目的地
            if (flag[man.y][man.x] == 0)//判断人原来所站位置是否是目的地
                changeMap(&man, FLOOR, map, LINE, images, k);     //将人原来位置改成地板
            else changeMap(&man, BOX_des, map, LINE, images, k);     //将人原来位置改成目的地
            man = next_pos;
        }
    }
}