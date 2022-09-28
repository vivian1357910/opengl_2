#ifndef CUBE_H_
#define CUBE_H_

class Cube
{
    private:
        int cube[4][2]; // 方塊形狀 四格的x y座標
        int type; // 形狀編號 1~7
        void typeforcube(); // 創建方塊
        bool isstart; // 是否開始遊戲
        int clockwiseRotate(); // 方塊順時針旋轉
        int anticlockwiseRotate(); // 方塊逆時針旋轉
        double color[3]; // 方塊顏色
    public:
        Cube();
        ~Cube();
        void reset(); // 初始之後的創建
        void updatecube(); // 更新方塊(下墜)
        int** usecube() const; // 使用中的方塊
        int usetype() const; // 方塊形狀編號
        void movecube(int key); // 移動方塊
        void setstatestart(); //開始
        bool isstatestart() const; // 是否開始
        int isrotate;  // 0:不轉 1:逆時針 -1:順時針
        double* paintcolor(); // 繪製
};

#endif#pragma once
