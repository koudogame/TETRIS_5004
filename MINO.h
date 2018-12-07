#pragma once
#include"texture.h"
#include"player.h"
#include"sprite.h"
#include"key.h"
#include"pad.h"

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

    //�����L�[
    int right = 0;
    int left = 0;
    int up = 0;
    int down = 0;

    //�J�E���g
    int cnt = 0;
    int acnt = 0;
    int bcnt = 0;
    int ccnt = 0;
};