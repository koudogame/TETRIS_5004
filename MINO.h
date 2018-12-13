#pragma once


#define field_width 11
#define field_height 21


#define block_width 4
#define block_height 4


#include"texture.h"
#include"player.h"
#include"sprite.h"
#include"key.h"
#include"pad.h"
#include<ctime>
    



enum
{
    i, //�_
    o, //�l�p
    t, //T��
    j, //J��
    l, //L��
    s, //S��
    z  //Z��
};

class Mino
{
private:
    ID3D11ShaderResourceView* texture_; //�e�N�X�`��
public:
    Mino();

    bool init();
    bool update();
    void draw();
    void maindraw();
    void destroy();

    //�~�m
    int back[22][12]; //�����悤�z��
    int main[22][12]{ 0 };
    int sub[22][12] = { 0 }; //�T�u
    int mino[7][4][4] = {
        { //I�~�m
        {0,0,0,0},
        {0,0,0,0},
        {1,1,1,1},
        {0,0,0,0}
        },
        { //O�~�m
        {0,0,0,0},
        {0,2,2,0},
        {0,2,2,0},
        {0,0,0,0}
        },
        { //T�~�m
        {0,0,0,0},
        {0,0,3,0},
        {0,3,3,3},
        {0,0,0,0}
        },
        { //J�~�m
        {0,0,0,0},
        {0,0,4,0},
        {0,0,4,0},
        {0,4,4,0}
        },
        { //L�~�m
        {0,0,0,0},
        {0,0,5,0},
        {0,0,5,0},
        {0,0,5,5}
        },
        { //S�~�m
        {0,0,0,0},
        {0,6,0,0},
        {0,6,6,0},
        {0,0,6,0}
        },
        { //Z�~�m
        {0,0,0,0},
        {0,0,7,0},
        {0,7,7,0},
        {0,7,0,0}
        }
    };

    int test[4][4] = {
        {0,0,0,0},
        {0,1,0,0},
        {0,1,1,0},
        {0,0,1,0}
    }; //�����p�e�X�g
    int clearlinepos[21] = { 0 }; //����񂻂���Ă���ꏊ�̊m�F�p
    int tmp[4][4] = { 0 };

    int nowtime = 0;
    int oldtime = 0;

    int time = 1;

    //�����L�[
    int up = 0;
    int down = 0;
    int pos = 3;

    //�J�E���g
    int cnt = 0;
    bool downf = false;

    bool collision_left = false;
    bool collision_right = false;
    bool collision_down = false;
    bool rotation_a = false;
    bool rotation_b = false;

    int block = 0;
};