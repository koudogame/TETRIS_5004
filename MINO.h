#pragma once


#define field_width 12
#define field_height 22


#define block_width 4
#define block_height 4


#include"texture.h"
#include"player.h"
#include"sprite.h"
#include"key.h"
#include"pad.h"
#include<ctime>

class Mino
{
private:
    ID3D11ShaderResourceView* texture_; //�e�N�X�`��
public:
    Mino();

    bool init();
    bool update();
    void srsystem(); //�X�[�p�[���[�e�[�V�����V�X�e��
    void draw();
    void maindraw(); //�ς݂�����z��̕`��
    void nextdraw(); //�l�N�X�g�u���b�N�̕`��
    void holddraw(); //�z�[���h���Ă���u���b�N�̕`��
    void destroy();  //�j��
    void reset();    //�ςݏグ�z��͈͓̔��̑S����������

    //�~�m
    int main[22][12]{ 0 };  //�ς݂�����{��
    int sub[22][12] = { 0 }; //�T�u
    const int next0[7]{ 0,1,2,3,4,5,6 }; //�l�N�X�g�p�^�[�� ���{
    int next1[7]{ 0,1,2,3,4,5,6 }; //�l�N�X�g�p�^�[��
    int next2[7]{ 0,1,2,3,4,5,6 }; //�l�N�X�g�p�^�[����[�p
    const int mino[7][4][4] = {
        { //I�~�m
        {0,0,1,0},
        {0,0,1,0},
        {0,0,1,0},
        {0,0,1,0}
        },
        { //O�~�m
        {0,0,0,0},
        {0,2,2,0},
        {0,2,2,0},
        {0,0,0,0}
        },
        { //T�~�m
        {0,0,0,0},
        {0,3,0,0},
        {0,3,3,0},
        {0,3,0,0}
        },
        { //J�~�m
        {0,0,0,0},
        {0,0,4,0},
        {0,0,4,0},
        {0,4,4,0}
        },
        { //L�~�m
        {0,0,0,0},
        {0,5,0,0},
        {0,5,0,0},
        {0,5,5,0}
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
   
    //��]����tmp
    int tmp[4][4] = { 0 };

    //���Ԋ֌W
    int nowtime = 0; //���݂̎���
    int oldtime = 0; //�O��̎���
    int time = 1;    //�����ɂ����鎞��

    //�����L�[
    int up = 0;   //��
    int down = 0; //��
    int pos = 3;  //��

    //�J�E���g
    int cnt = 0;
    int right = 0;
    int left = 0;

    //�����蔻��
    bool collision_left = false;
    bool collision_right = false;
    bool collision_down = false;

    //��]
    bool rotation_a = false; //90
    bool rotation_b = false; //270

    //�l�N�X�g
    bool nextblock = true; //���̃u���b�N���o��
    bool shuffle = false;  //�l�N�X�g�u���b�N�̔z��v�f���V���b�t��
    bool shift = false;    //�l�N�X�g�u���b�N�̕`�掞�̃V�t�g�p
    int next = 0;          //���̃u���b�N
    int a = 0;             //�z��̓Y����
    
    //�n�[�h�h���b�v
    bool harddrop = false;

    //�ςݏグ
    bool Accumulate = false;

    //�~�m�������鎞��
    int down_now_time = 0;
    int down_old_time = 0;

    bool downf = false;

    //�z�[���h�֌W
    bool holdf = false;        //�z�[���h
    bool holdcheck = false;    //���łɃz�[���h�����̔���(�z�[���h���Ȃ�true)
    bool holdbutton = false;   //���łɃz�[���h���g�p�������̔���
    int holdtmp[4][4] = { 0 }; //�z�[���htmp
    int hold[4][4] = { 0 };    //�z�[���h�p

    bool srs = false; //�X�[�p�[���[�e�[�V����

    int srstest = 0;

};