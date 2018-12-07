#pragma once

#include<d3d11.h>
#include"release.h"
#include"player.h"
#include"key.h"
#include"texture.h"
#include"sprite.h"
#include"pad.h"
#include"adx.h"
#include"Error.h"
#include"pov.h"


class Title
{
private:

    ID3D11ShaderResourceView* texture_;         //�e�N�X�`��
    

    Vector2 position_;                                                                                                                                           // �ړ����x

public:

    Title();
    ~Title();


    //������
    bool init();                                // ������
    int update();                               // �X�V
    void draw();                                // �w�i�`��
    void dpaddraw();                            // �\���L�[�`��
    void buttondraw();                          // �{�^���`��
    void cursordraw();                          //�J�[�\���`��
    void destroy();                             // �j��
    int menu = 0;

    bool tmp = false;                           //���[�h�ؑ֎��̃t���O����p
    int penter = 0;                             //���肪�����ꂽ
    int pov = 0;

};