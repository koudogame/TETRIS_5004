#pragma once

#include"Release.h"

class Credit
{
private:
    ID3D11ShaderResourceView* texture_; //�e�N�X�`��
    ID3D11ShaderResourceView* Ctexture_; //�e�N�X�`��
    RECT trim;

public:
    //�R���X�g���N�^
    Credit() { texture_ = NULL; }

    bool init();        //������
    bool update();      //�X�V
    void draw();        //�`��
    void namedraw();    //���O�`��
    void datedraw();
    void destroy();     //�j��

    int menu = 0; //�Q�[�����I���Ƃ���true
    int cnt = 0;

    int name[13] = {8,9,18,15,6,21,13,9,0,19,1,20,15}; //�N���W�b�g�ɕ`�悷�鎩���̖��O
    int creation_date[12] = { 2,0,1,9,42,100,1,42,100,2,8 };
};
