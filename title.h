#pragma once

#include<d3d11.h>
#include"release.h"
#include"player.h"
#include"key.h"
#include"texture.h"
#include"sprite.h"
#include"pad.h"
#include"player.h"
#include"adx.h"
#include"Error.h"

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
    void destroy();                             // �j��
    int cnt = 0;                                //��ꃂ�[�h�N���R�}���h�̃J�E���g
    int subcnt = 0;                             //�ʏ탂�[�h�N���R�}���h�̃J�E���g
    int menu = 0;

    bool oba = false;                           //���搶�o��
    bool tmp = false;                           //���[�h�ؑ֎��̃t���O����p
};