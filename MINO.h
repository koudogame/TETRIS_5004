#pragma once

#define field_width 12 //�t�B�[���h����
#define field_height 23 //�t�B�[���h�c��

#define block_width 4 //�u���b�N����
#define block_height 4 //�u���b�N�c��

#define fall_time 1500 //�����b��

#define SPEED 1 //�������x���i���x)

#include"texture.h"
#include"player.h"
#include"sprite.h"
#include"key.h"
#include"pad.h"
#include"tetris_acf.h"
#include"CueSheet_0.h"
#include"adx.h"
#include<ctime>
#include"gameover.h"

class Mino
{
private:
    ID3D11ShaderResourceView* texture_; //�e�N�X�`��
    Gameover gameover_;
public:
    Mino();

    bool init(int player_num);
    int update(int player_num);
    void ghostupdate(int player_num);

    void srsystem(int rotation_type, int player_num); //�X�[�p�[���[�e�[�V����
    void change();

    //�`��
    void draw(int player_num);
    void maindraw(int player_num); //�ς݂�����z��̕`��
    void nextdraw(int player_num); //�l�N�X�g�u���b�N�̕`��
    void holddraw(int player_num); //�z�[���h���Ă���u���b�N�̕`��
    void leveldraw(int player_num); //���x���̕\��
    void ghostdraw(int player_num);
    void scoredraw(int player_num); //�X�R�A�ƃ��x���̕`��
    void cleardraw();
    void menudraw();

	void destroy();  //�j��
    void reset(int player_num);    //�ςݏグ�z��͈͓̔��̑S����������

    //�����蔻��
    void collisionleft(int player_num);
    void collisionright(int player_num);
    void collisiondown(int player_num);
    bool collisionsrs(int player_num);

    //�l�N�X�g
    void nextpattern();

    //�S����
    void allclear(int player_num);

    //�X�[�p�[���[�e�[�V����
    int turnover_rate = 0; //�~�m�̉�]��
    int type = 40; //0 = a��d 2 = 
    bool srstest = false;

    //�~�m
    int main[4][23][12]={ 0 };  //�ς݂�����{��(�l����
    int sub[22][12] = { 9 }; //�T�u
    const int next0[7]{ 0,1,2,3,4,5,6 }; //�l�N�X�g�p�^�[�� ���{
    int next1[7]{ 0,1,2,3,4,5,6 }; //�l�N�X�g�p�^�[��
    int next2[7]{ 0,1,2,3,4,5,6 }; //�l�N�X�g�p�^�[����[�p
    float transparency = 1.0F; //�����x
    const int mino[7][4][4] = {
        { //I�~�m
        {0,0,1,0},
        {0,0,1,0},
        {0,0,1,0},
        {0,0,1,0}
        },
        { //L�~�m
        {0,0,0,0},
        {0,2,2,0},
        {0,0,2,0},
        {0,0,2,0}
        },
        { //S�~�m
        {0,0,0,0},
        {0,3,0,0},
        {0,3,3,0},
        {0,0,3,0}
        },
        { //Z�~�m
        {0,0,0,0},
        {0,0,4,0},
        {0,4,4,0},
        {0,4,0,0}
        },
        { //J�~�m
        {0,0,0,0},
        {0,0,5,0},
        {0,0,5,0},
        {0,5,5,0}
        },
        { //O�~�m
        {0,0,0,0},
        {0,6,6,0},
        {0,6,6,0},
        {0,0,0,0}
        },
        { //T�~�m
        {0,0,0,0},
        {0,0,7,0},
        {0,7,7,0},
        {0,0,7,0}
        }
    };

    int test [4][4] = { 0 }; //�����p�̔z��
    int clearlinepos[22] = { 0 }; //����񂻂���Ă���ꏊ�̊m�F�p
   
    //��]����tmp
    int tmp[4][4] = { 0 };

    //���Ԋ֌W
    int nowtime = 0; //���݂̎���
    int oldtime = 0; //�O��̎���
    int time = 1;    //�����ɂ����鎞��

    //�����L�[
    int up = 0;   //��
    int down = -5; //��
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
    int hold_a;
    int holdtmp_a;

    bool srs = false; //�X�[�p�[���[�e�[�V����

	//�Q�[���I�[�o�[�����֌W
	bool gameover = false; //�Q�[���I�[�o�[�ɂȂ����Ƃ���������
	int overcnt = 0; //�Q�[���I�[�o�[�ɂȂ������̒��g�̓���ւ��ϐ�
    int overcnt2 = 0; //�Q�[���I�[�o�[�ɂȂ��Ă��烁�j���[���\�������܂ł̎���
    int testcnt = 0;
    // ������
    int erase = 0;
    int fall_speed = SPEED;

    //�X�R�A
    unsigned int score = 0;
    int erase_line = 0; //�����ꂽ���C����
    int olderasenum = 0; //�O��������s��������Ă���(B2B�p)
    float back_to_back = 1; //back_to_back���������̃X�R�A�{��
    const int linescore[4] = { 40,100,300,1200 }; //���������̓_���\

    //�S�[�X�g
    int transparent = 50; //�����x
    int ghost[4][4] = { 0 }; 
    int gdown; //�S�[�X�g��y��
    bool gcollsion = false; //�S�[�X�g�̓����蔻��

    //multi�p
    int playerx = 0;
    int mainx = 0;
    int nextx = 0;
    int holdx = 0;
    
    //�S����
    int leaveline[22];
    int clearline = 0;
    bool first = false; //�ŏ��͑S���������ɂ��Ȃ�
    bool all_clear = false; //�S����

    //�I�v�V����
    int option[8]; //�I�v�V�����̍��ڕۑ�
    int maxlevelop; //���x�����
    bool holdop;    //�z�[���h�g�p�ݒ�
    int nextop;     //�l�N�X�g�����\�����邩
    bool hidden;    //�B�������邩
    bool vsop;      //vs���[�h�ɂ��邩
    bool reverseop; //����𔽓]�����邩
    bool scorereset;//�����L���O�X�R�A���Z�b�g

    float op_bonus = 1.0;

};