#ifndef CUBE_H_
#define CUBE_H_

class Cube
{
    private:
        int cube[4][2]; // ����Ϊ� �|�檺x y�y��
        int type; // �Ϊ��s�� 1~7
        void typeforcube(); // �Ыؤ��
        bool isstart; // �O�_�}�l�C��
        int clockwiseRotate(); // ������ɰw����
        int anticlockwiseRotate(); // ����f�ɰw����
        double color[3]; // ����C��
    public:
        Cube();
        ~Cube();
        void reset(); // ��l���᪺�Ы�
        void updatecube(); // ��s���(�U�Y)
        int** usecube() const; // �ϥΤ������
        int usetype() const; // ����Ϊ��s��
        void movecube(int key); // ���ʤ��
        void setstatestart(); //�}�l
        bool isstatestart() const; // �O�_�}�l
        int isrotate;  // 0:���� 1:�f�ɰw -1:���ɰw
        double* paintcolor(); // ø�s
};

#endif#pragma once
