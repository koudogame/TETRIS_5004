#pragma once

#include<d3d11.h>
#include<SimpleMath.h>
#include"key.h"
#include"pad.h"
#include"release.h"
#include"texture.h"
#include"sprite.h"
#include"Error.h"
#include"pov.h"

#define SPEED 5
enum
{
    NOT_FOUND,
    Title_,          //�^�C�g��
    rank_credit,    //�����L���O�E�N���W�b�g
    result_option,  //���U���g�I�v�V����
    tetoris_s,      //�e�g���X�V���O��
    puyopuyo,       //�Ղ�Ղ�
    tetris_multi    //�e�g���X�}���`
};

class UI
{
private:
    ID3D11ShaderResourceView* texture_;  // UI�e�N�X�`��

public:
    UI();                     //�R���X�g���N�^
    bool init();              //������
    void update();            //�X�V
    void draw(int type);              //�`��
    void inputdraw(int type);
    void Hiddendraw();
    void destroy();           //�j��

    //���͏��
    int uipov = 0; //�\�����͏�ԕ`��
    int penter = 0; //A���͏�ԕ`��
    int pspace = 0; //B���͏��
    int plb = 0;   //LB���͏��
    int pstart = 0; //start���͏��
};