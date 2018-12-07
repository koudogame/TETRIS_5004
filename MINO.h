#pragma once
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
    void draw();
    void destroy();
    int back[22][12]; //�����悤�z��

    int nowtime = 0;
    int oldtime = 0;

    //�����L�[
    int right = 0;
    int left = 0;
    int up = 0;
    int down = 0;
    int pos = 0;

    //�J�E���g
    int cnt = 0;
    int acnt = 0;
    int bcnt = 0;
    int ccnt = 0;
};