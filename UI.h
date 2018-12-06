#pragma once

#include<d3d11.h>
#include<SimpleMath.h>
#include"key.h"
#include"pad.h"
#include"release.h"
#include"texture.h"
#include"sprite.h"
#include"Error.h"

#define SPEED 5

class UI
{
private:
    ID3D11ShaderResourceView* texture_;  // UI�e�N�X�`��
    ID3D11ShaderResourceView* Mtexture_; //���[�^�[�̃e�N�X�`��
    ID3D11ShaderResourceView* Ptexture_; //�d�؂�̃e�N�X�`��
    Vector2 position;                    // ���[�^�[�̍��W
    RECT trim;                           //���[�^�[�̃g���~���O�͈�

public:
    UI();                     //�R���X�g���N�^
    bool init();              //������
    void update();            //�X�V
    void draw();              //�`��
    void meterdraw();         //���[�^�[�`��
    void partitiondraw();     //�d�؂�`��
    void destroy();           //�j��

    int cnt = 0;            //�����ꂽ�u�Ԏ擾�p
    int Bcnt = 0;           //�����ꂽ�u�Ԏ擾�p
    int carmeter = 0;       //�A�Ń��[�^�[(��)
    int bicyclemeter = 0;   //�A�Ń��[�^�[(���]��)
    int tmp = 0;            //�����Ԍ��Z�J�E���g
};