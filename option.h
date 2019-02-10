#pragma once
#include"release.h"
#include"player.h"
#include"key.h"
#include"texture.h"
#include"sprite.h"
#include"pad.h"
#include"player.h"
#include"adx.h"
#include"Error.h"

class Option
{
private:
    ID3D11ShaderResourceView* texture_; //�e�N�X�`��
    RECT trim;

public:
    //�R���X�g���N�^
    Option() { texture_ = NULL; }

    bool init();        //������
    bool update();       //�X�V
    void draw();        //�`��
    void cursordraw();  //�㉺�̃J�[�\��
    void opdraw();      //�I�v�V�����̖��
    void destroy();     //�j��

    int pstart = 0;

    int opmenu = 0;

    int difficulty;
    int hold; 
    int next;
    int hidden;
    int vs;
    int reverse;
    int score;

    int option[7];
};