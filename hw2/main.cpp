#include "cube.h"
#include <GL/freeglut.h>
#include <iostream>
#include <cmath>
#include <windows.h>
#include <string>
using std::string;

int csize = 20;
int** map; // 遊戲畫布
Cube cube;
Cube cuberemind;
double*** mapcolor; // 畫布顏色
int TimerInterval = 500; // 速度
int main_w, w1, w2, w3; //主視窗 & 子視窗
int score;
bool isPause;



void display()
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // 以bitmap方式繪製文字
    wglUseFontBitmaps(wglGetCurrentDC(), 0, 256, 1000);
    glListBase(1000);
    glColor3f(1.0, 1.0, 1.0);
    glRasterPos2f(15.0, 1.5);
    glCallLists(5, GL_UNSIGNED_BYTE, "SCORE");

    glColor3f(1.0, 1.0, 0.0);
    glRasterPos2f(10.0, 1.5);
    if (score >= 80)
        glCallLists(7, GL_UNSIGNED_BYTE, "Level 6");
    else if (score >= 60)
        glCallLists(7, GL_UNSIGNED_BYTE, "Level 5");
    else if (score >= 40)
        glCallLists(7, GL_UNSIGNED_BYTE, "Level 4");
    else if (score >= 20)
        glCallLists(7, GL_UNSIGNED_BYTE, "Level 3");
    else if (score >= 10)
        glCallLists(7, GL_UNSIGNED_BYTE, "Level 2");
    else
        glCallLists(7, GL_UNSIGNED_BYTE, "Level 1");


    glColor3f(1.0, 1.0, 1.0);
    glRasterPos2f(17.0, 1.5);
    string s = std::to_string(score);
    char const* c = s.c_str();
    int n = strlen(c);
    for (int i = 0; i < n; i++)
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, *(c + i));

    glPointSize(800 / csize);
    glBegin(GL_POINTS);

    // 繪製遊戲中方塊
    double* tempcubecolor = cube.paintcolor(); // 取得顏色
    glColor3f(tempcubecolor[0], tempcubecolor[1], tempcubecolor[2]);
    int** temp = cube.usecube(); // 取得方塊各點座標
    for (int i = 0; i < 4; i++)
    {
        if (temp[i][1] > 2)
            glVertex2f(temp[i][0], temp[i][1]);
    }

    // 繪製提示框
    double* tempcuberemindcolor = cuberemind.paintcolor(); // 取得顏色
    int** tempremind = cuberemind.usecube(); // 取得方塊各點座標
    glColor3f(tempcuberemindcolor[0], tempcuberemindcolor[1], tempcuberemindcolor[2]);
    for (int i = 0; i < 4; i++)
    {
        glVertex2f(abs(tempremind[i][0] - tempremind[0][0] + 3), abs(tempremind[i][1] - tempremind[0][1] + 2));
    }

    // 繪製其餘方塊
    for (int i = 1; i <= csize - 1; i++)
        for (int j = 1; j <= csize - 1; j++)
            if (map[j][i] == 1)
            {
                glColor3f(mapcolor[j][i][0], mapcolor[j][i][1], mapcolor[j][i][2]);
                glVertex2f(i, j);
            }




    glEnd();
    glFlush();

}





// 下層滿則消失
void lowestlayer()
{
    int flag = 0;
    int* temp = new int[csize] {0};
    // 判斷是否排滿
    for (int i = csize - 1; i > 2; i--)
    {
        int isfull = 1;
        for (int j = 1; j < csize - 1; j++)
            if (map[i][j] == 0) // 還有空位
            {
                isfull = 0;
                break;
            }
        if (isfull == 1) // 已排滿
        {
            temp[flag] = i; // 紀錄要消去的排
            flag++;
        }
    }
    score += 10 * flag * flag;
    //printf("%d\n", score);
    int full = 0;
    while (temp[full] != 0) // 重繪
    {
        for (int i = temp[full++]; i > 2; i--)
        {
            for (int j = 1; j <= csize - 1; j++)
                map[i][j] = map[i - flag][j];
        }
    }
}

// 判斷gameover
void gameover()
{
    for (int j = 1; j < csize - 1; j++)
    {
        if (map[2][j] == 1)
        {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            glPointSize(800 / csize);
            glBegin(GL_POINTS);
            // 繪製其餘方塊
            for (int i = 1; i <= csize - 1; i++)
                for (int j = 1; j <= csize - 1; j++)
                    if (map[j][i] == 1)
                    {
                        glColor3f(0.2, 0.2, 0.2);
                        glVertex2f(i, j);
                    }
            glEnd();
            
            

            wglUseFontBitmaps(wglGetCurrentDC(), 0, 256, 1000);
            glListBase(1000);
            glColor3f(1.0, 1.0, 1.0);
            glRasterPos2f(10.0, 10.0);
            glCallLists(9, GL_UNSIGNED_BYTE, "Game Over");

            glFlush();
            
            Sleep(5000);
            exit(EXIT_FAILURE);
        }
    }
}

// 更新圖形&坐標
void update()
{
    int** temp = cube.usecube();
    double* tempcolor = cube.paintcolor();
    for (int i = 0; i < 4; i++)
    {

        // 判斷是否下一個位置已經被佔據
        if (map[temp[i][1] + 1][temp[i][0]] == 1)
        {
            for (int k = 0; k < 4; k++)
            {
                // 被佔據則標記為1
                map[temp[k][1]][temp[k][0]] = 1;
                // 著色
                mapcolor[temp[k][1]][temp[k][0]][0] = tempcolor[0];
                mapcolor[temp[k][1]][temp[k][0]][1] = tempcolor[1];
                mapcolor[temp[k][1]][temp[k][0]][2] = tempcolor[2];
            }
            cube = cuberemind;

            //重新生成新的方塊
            cuberemind.reset();
            break;
        }
    }
    // 不被佔據則更新坐標
    cube.updatecube();
    // 判斷下層是否滿
    lowestlayer();
    // 判斷是否gameover
    gameover();
}


void timer(int timeid)
{
    // 不旋轉則下墜
    if (cube.isrotate == 0)
        update();

    cube.isrotate = 0; // 預設為不旋轉

    if (score >= 80)
        TimerInterval = 100;
    else if (score >= 60)
        TimerInterval = 200;
    else if (score >= 40)
        TimerInterval = 300;
    else if (score >= 20)
        TimerInterval = 400;
    else if (score >= 10)
        TimerInterval = 450;

    //繪製
    display();
    glutTimerFunc(TimerInterval, timer, 1);
}


void keypress(int key, int x, int y)
{
    int** temp = cube.usecube();
    int flag = 0;
    if (key == GLUT_KEY_SHIFT_L && !cube.isstatestart())
    {
        cube.setstatestart();
        cuberemind.setstatestart();
        glutTimerFunc(TimerInterval, timer, 1);
    }

    cube.movecube(key);

    if (key == GLUT_KEY_SHIFT_R)
    {
        
        exit(0);
    }


}

// 初始化遊戲畫布
void InitMap()
{
    // 遊戲畫布初始為0 (沒有方塊填入)
    map = new int* [csize + 1];
    for (int i = 0; i < csize + 1; i++)
        map[i] = new int[csize + 1]{ 0 };

    // 邊界設為1
    for (int i = 0; i < csize + 1; i++)
    {
        map[csize][i] = 1;
        map[i][csize] = map[i][0] = -1;
    }

    mapcolor = new double** [csize + 1];

    // 畫布顏色初始為0 (黑色)
    for (int i = 0; i < csize + 1; i++)
        mapcolor[i] = new double* [csize + 1];

    for (int i = 0; i < csize + 1; i++)
        for (int j = 0; j < csize + 1; j++)
            mapcolor[i][j] = new double[3]{ 0 };

    // 分數初始為0
    score = 0;
    isPause = false;
}

// openGL
void Init()
{
    glClearColor(0.0, 0.0, 0.0, 0.0); // 背景色
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, csize, csize, 0);

}

int main(int argc, char** argv)
{

    InitMap(); //初始化遊戲畫布
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 800); // 主視窗大小

    glutCreateWindow("TERIS");
    Init();

    glutDisplayFunc(display);
    glutSpecialFunc(keypress);


    glutMainLoop();

}