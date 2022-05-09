#include "struct.h"
#include "defData.h"
using namespace std;
/************************
*初始化舞台
************************/
void init_graphic(IMAGE images[],int k, IMAGE bg_image) {
    //搭台唱戏(创建舞台，设定宽高)
    initgraph(SCREEN_WIDTH, SCREEN_HEIGHT);

    //将图片文件加载到图变量内（给图变量指针，文件名必须要有双眼号，图片要在工程文件下）
    loadimage(&bg_image, _T("blackground.bmp"), SCREEN_WIDTH, SCREEN_HEIGHT, true);
    loadimage(&images[END], _T("QQ图片20220311031450.png"), SCREEN_WIDTH, SCREEN_HEIGHT, true);
    //将已加载图片的图变量(背景)放到舞台上
    putimage(0, 0, &bg_image);


    //加载所有道具给图变量数组
    //注意：文件字符串的格式多样，需要用加上 _T("")的方法统一接口格式。
    //对于字符串，例如 “abc” 用 _T(“abc”) 表示。就是加上 _T("")
    loadimage(&images[WALL], _T("wall_right.bmp"), Normalsize, Normalsize, true);
    loadimage(&images[FLOOR], _T("floor.bmp"), Normalsize, Normalsize, true);
    loadimage(&images[BOX_des], _T("des.bmp"), Normalsize, Normalsize, true);
    loadimage(&images[MAN], _T("man.bmp"), Normalsize, Normalsize, true);
    loadimage(&images[BOX], _T("box.bmp"), Normalsize, Normalsize, true);
    loadimage(&images[_BOX], _T("box.bmp"), Normalsize, Normalsize, true);
    loadimage(&images[_MAN], _T("man.bmp"), Normalsize, Normalsize, true);

}
