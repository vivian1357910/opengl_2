#include "cube.h"
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <GL/freeglut.h>

extern int csize;
extern int** map;

// 初始化
Cube::Cube() 
{
    srand(time(0));
    type = rand() % 7 + 1;
    typeforcube();
    isstart = false;
    isrotate = 0;
    for (int i = 0; i < 3; i++)
        color[i] = double(rand()) / RAND_MAX;
}

// 初始之後的創建
void Cube::reset() 
{
    type = rand() % 7 + 1;
    typeforcube();
    isrotate = 0;
    for (int i = 0; i < 3; i++)
        color[i] = double(rand()) / RAND_MAX;
}

Cube::~Cube()
{

}

// 創建方塊
void Cube::typeforcube()
{
    int r;
    switch (type) {
    case 1:
        r = rand() % (csize - 4) + 1;
        cube[0][0] = r + 2, cube[0][1] = 2;
        cube[1][0] = r + 1, cube[1][1] = 2;
        cube[2][0] = r, cube[2][1] = 2;
        cube[3][0] = r + 3, cube[3][1] = 2;
        break;
    case 2:
        r = rand() % (csize - 2) + 1;
        cube[0][0] = r, cube[0][1] = 2;
        cube[1][0] = r, cube[1][1] = 1;
        cube[2][0] = r + 1, cube[2][1] = 2;
        cube[3][0] = r + 1, cube[3][1] = 1;
        break;
    case 3:
        r = rand() % (csize - 2) + 1;
        cube[0][0] = r, cube[0][1] = 1;
        cube[1][0] = r + 1, cube[1][1] = 1;
        cube[2][0] = r, cube[2][1] = 0;
        cube[3][0] = r + 1, cube[3][1] = 2;
        break;
    case 4: 
        r = rand() % (csize - 2) + 1;
        cube[0][0] = r + 1, cube[0][1] = 1;
        cube[1][0] = r, cube[1][1] = 1;
        cube[2][0] = r, cube[2][1] = 2;
        cube[3][0] = r + 1, cube[3][1] = 0;
        break;
    case 5:
        r = rand() % (csize - 3) + 1;
        cube[0][0] = r + 1, cube[0][1] = 2;
        cube[1][0] = r, cube[1][1] = 2;
        cube[2][0] = r + 2, cube[2][1] = 2;
        cube[3][0] = r + 2, cube[3][1] = 1;
        break;
    case 6:
        r = rand() % (csize - 3) + 1;
        cube[0][0] = r + 1, cube[0][1] = 2;
        cube[1][0] = r, cube[1][1] = 1;
        cube[2][0] = r, cube[2][1] = 2;
        cube[3][0] = r + 2, cube[3][1] = 2;
        break;
    case 7:
        r = rand() % (csize - 3) + 1;
        cube[0][0] = r + 1, cube[0][1] = 2;
        cube[1][0] = r + 1, cube[1][1] = 1;
        cube[2][0] = r, cube[2][1] = 2;
        cube[3][0] = r + 2, cube[3][1] = 2;
        break;
    }
}

// 取得方塊各點座標
int** Cube::usecube() const
{
    int** useCube = new int* [4];
    for (int i = 0; i < 4; i++) {
        useCube[i] = new int[2];
        useCube[i][0] = cube[i][0];
        useCube[i][1] = cube[i][1];
    }
    return useCube;
}

int Cube::usetype() const
{
    return type;
}

// 更新方塊(下墜)
void Cube::updatecube()
{
    for (int i = 0; i < 4; i++)
        cube[i][1]++;
}

// 方塊逆時針旋轉
int Cube::anticlockwiseRotate()
{
    if (type != 1 && type != 2)
    {
        // 暫存方塊九宮格
        int temp[3][3] = { 0 };
        for (int i = 0; i < 4; i++)
            temp[abs(cube[0][0] - cube[i][0] - 1)][abs(cube[0][1] - cube[i][1] - 1)] = 1;
        // 暫存旋轉後的九宮格
        int temp_r[3][3] = { 0 };
        for (int i = 0; i < 3; i++)
            for (int j = 2; j >= 0; j--)
                temp_r[2 - j][i] = temp[i][j];
        // 判斷變形後是否有被佔據的情況
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                if (temp_r[i][j] == 1 && map[cube[0][1] + j - 1][cube[0][0] + i - 1] == 1 &&
                    cube[0][1] + j - 1 < 1 && cube[0][0] + j + 1 > csize - 1 &&
                    cube[0][0] + i - 1 < 1 && cube[0][0] + i + 1 > csize - 1)
                    return 0;   // 不旋轉
        int k = 1;
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                if (!(i == 1 && j == 1) && temp_r[i][j] == 1)
                {
                    cube[k][0] = cube[0][0] + i - 1;
                    cube[k++][1] = cube[0][1] + j - 1;
                }
        return 1;
    }
    else if (type == 1)
    {
        // 暫存25方格矩陣
        int temp[5][5] = { 0 };
        for (int i = 0; i < 4; i++)
            temp[abs(cube[0][0] - cube[i][0] - 2)][abs(cube[0][1] - cube[i][1] - 2)] = 1;
        // 暫存旋轉後矩陣
        int temp_r[5][5] = { 0 };
        for (int i = 0; i < 5; i++)
            for (int j = 4; j >= 0; j--)
                temp_r[4 - j][i] = temp[i][j];
        // 判斷變形後是否有被佔據的情況
        for (int i = 0; i < 5; i++)
            for (int j = 0; j < 5; j++)
                if (temp_r[i][j] == 1 &&
                    map[cube[0][1] + j - 2][cube[0][0] + i - 2] == 1 && cube[0][1] + j - 2 > 1 &&
                    cube[0][0] + j + 2 < csize && cube[0][0] + i - 2 > 1 && cube[0][0] + i + 2 < csize)
                    return 0;   // 不旋轉
        int k = 1;
        for (int i = 0; i < 5; i++)
            for (int j = 0; j < 5; j++)
                if (!(i == 2 && j == 2) && temp_r[i][j] == 1) {
                    cube[k][0] = cube[0][0] + i - 2;
                    cube[k++][1] = cube[0][1] + j - 2;
                }
        return 1;
    }
    else
        return 0;
}

// 方塊順時針旋轉
int Cube::clockwiseRotate()
{
    if (type != 1 && type != 2)
    {
        // 暫存方塊九宮格
        int temp[3][3] = { 0 };
        for (int i = 0; i < 4; i++)
            temp[abs(cube[0][0] - cube[i][0] - 1)][abs(cube[0][1] - cube[i][1] - 1)] = 1;
        // 暫存旋轉後的九宮格
        int temp_r[3][3] = { 0 };
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                temp_r[j][i] = temp[i][j];
        // 判斷變形後是否有被佔據的情況
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                if (temp_r[i][j] == 1 &&
                    map[cube[0][1] + j - 1][cube[0][0] + i - 1] == 1 && cube[0][1] + j - 1 < 1 &&
                    cube[0][0] + j + 1 > csize - 1 && cube[0][0] + i - 1 < 1 && cube[0][0] + i + 1 > csize - 1)
                    return 0;   // 不旋轉
        int k = 1;
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                if (!(i == 1 && j == 1) && temp_r[i][j] == 1)
                {
                    cube[k][0] = cube[0][0] + i - 1;
                    cube[k++][1] = cube[0][1] + j - 1;
                }
        return -1;
    }
    else if (type == 1)
    {
        // 暫存25方格矩陣
        int temp[5][5] = { 0 };
        for (int i = 0; i < 4; i++)
            temp[abs(cube[0][0] - cube[i][0] - 2)][abs(cube[0][1] - cube[i][1] - 2)] = 1;
        // 暫存旋轉後矩陣
        int temp_r[5][5] = { 0 };
        for (int i = 0; i < 5; i++)
            for (int j = 0; j < 5; j++)
                temp_r[j][i] = temp[i][j];
        // 判斷變形後是否有被佔據的情況
        for (int i = 0; i < 5; i++)
            for (int j = 0; j < 5; j++)
                if (temp_r[i][j] == 1 && map[cube[0][1] + j - 2][cube[0][0] + i - 2] == 1 &&
                    cube[0][1] + j - 2 > 1 && cube[0][0] + j + 2 < csize && cube[0][0] + i - 2 > 1 &&
                    cube[0][0] + i + 2 < csize)
                    return 0;   // 不旋轉
        int k = 1;
        for (int i = 0; i < 5; i++)
            for (int j = 0; j < 5; j++)
                if (!(i == 2 && j == 2) && temp_r[i][j] == 1) {
                    cube[k][0] = cube[0][0] + i - 2;
                    cube[k++][1] = cube[0][1] + j - 2;
                }
        return -1;
    }
    else
        return 0;
}

// 移動方塊
void Cube::movecube(int key)
{
    int flag = 0; // 是否碰到邊界
    switch (key)
    {
        case GLUT_KEY_LEFT: // 左移
            for (int i = 0; i < 4; i++)
                if (map[cube[i][1]][cube[i][0] - 1] != 0) {
                    flag = 1;
                    break;
                }
            if (flag == 0) {
                for (int i = 0; i < 4; i++)
                    cube[i][0]--;
            }
            break;
        case GLUT_KEY_RIGHT: // 右移
            for (int i = 0; i < 4; i++)
                if (map[cube[i][1]][cube[i][0] + 1] != 0) {
                    flag = 1;
                    break;
                }
            if (flag == 0) {
                for (int i = 0; i < 4; i++)
                    cube[i][0]++;
            }
            break;
        case GLUT_KEY_CTRL_L: // 順時針旋轉
            isrotate = clockwiseRotate();
            break;
        case GLUT_KEY_ALT_L: // 逆時針旋轉
            isrotate = anticlockwiseRotate();
            break;
        case GLUT_KEY_DOWN: // 下降
            for (int i = 0; i < 4; i++)
                if (map[cube[i][1] + 1][cube[i][0]] != 0)
                {
                    flag = 1;
                    break;
                }
            if (flag == 0)
            {
                for (int i = 0; i < 4; i++)
                    cube[i][1]++;
            }
            break;
    }
}

// 開始
void Cube::setstatestart()
{
    isstart = true;
}

bool Cube::isstatestart() const
{
    return isstart;
}

// 繪製
double* Cube::paintcolor()
{
    return color;
}