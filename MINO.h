#pragma once

#define field_width 12
#define field_height 23

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
    int update();
    void ghostupdate();

    void srsystem(); //�X�[�p�[���[�e�[�V����
    void change();

    //�`��
    void draw();
    void maindraw(); //�ς݂�����z��̕`��
    void nextdraw(); //�l�N�X�g�u���b�N�̕`��
    void holddraw(); //�z�[���h���Ă���u���b�N�̕`��
    void ghostdraw();
    void scoredraw(); //�X�R�A�ƃ��x���̕`��

	void destroy();  //�j��
    void reset();    //�ςݏグ�z��͈͓̔��̑S����������

    //�����蔻��
    void collisionleft();
    void collisionright();
    void collisiondown();

    //�l�N�X�g
    void nextpattern();

    //�~�m
    int main[4][26][12]={ 0 };  //�ς݂�����{��(�l����
    int sub[22][12] = { 9 }; //�T�u
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
        {0,0,3,0},
        {0,3,3,0},
        {0,0,3,0}
        },
        { //J�~�m
        {0,0,0,0},
        {0,0,4,0},
        {0,0,4,0},
        {0,4,4,0}
        },
        { //L�~�m
        {0,0,0,0},
        {0,5,5,0},
        {0,0,5,0},
        {0,0,5,0}
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

    int test [4][4] = { 0 };
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
    int pos = 4;  //��

    //�J�E���g
    int cnt = 0;
    int right = 0;
    int left = 0;

    //�����蔻��
    bool collisionf = false;
    bool collision_down = false;

    //�l�N�X�g
    bool nextblock = true; //���̃u���b�N���o��
    bool shuffle = false;  //�l�N�X�g�u���b�N�̔z��v�f���V���b�t��
    bool shift = false;    //�l�N�X�g�u���b�N�̕`�掞�̃V�t�g�p
    int next = 0;          //���̃u���b�N
    int a = 0;             //�z��̓Y����

    //�ςݏグ
    bool Accumulate = false;
    bool downf = false;

    //�z�[���h�֌W
    bool holdf = false;        //�z�[���h
    bool holdcheck = false;    //���łɃz�[���h�����̔���(�z�[���h���Ȃ�true)
    bool holdbutton = false;   //���łɃz�[���h���g�p�������̔���
    int holdtmp[4][4] = { 0 }; //�z�[���htmp
    int hold[4][4] = { 0 };    //�z�[���h�p

    bool srs = false; //�X�[�p�[���[�e�[�V����

	//�Q�[���I�[�o�[�����֌W
	bool gameover = false; //�Q�[���I�[�o�[�ɂȂ����Ƃ���������
	int overcnt = 0; //�Q�[���I�[�o�[�ɂȂ������̒��g�̓���ւ��ϐ�
    int overcnt2 = 0; //�Q�[���I�[�o�[�ɂȂ��Ă��烁�j���[���\�������܂ł̎���

    // ������
    int erase = 0;
    int fall_speed = 1;

    //�S�[�X�g
    int transparent = 50;
    int ghost[4][4] = { 0 };
    int gdown = 0;
};