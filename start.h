#pragma once

#include"release.h"
#include"player.h"
#include"title.h"
#include"texture.h"
#include"sprite.h"
#include"pad.h"
#include"adx.h"
#include"key.h"

class Start
{
private:
    ID3D11ShaderResourceView* texture_;         //1p��������


public:

    Start();
    ~Start();

    //������
    bool init();                                //������
    bool update();                              //�X�V
    void draw();                                //�`��
    void cntdraw();                             //�b���`��
    void godraw();                              //GO!!�`��
    void destroy();                             //�j��

    //�ϐ�
    int nowtime = 0;
    int oldtime = 0;

    int starttimer = 3;

    //�t���O
    bool goflag = false;

    //�J�E���g
    int cnt = 0;
};