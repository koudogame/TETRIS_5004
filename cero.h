#pragma once
#include"game.h"

class Cero
{
private:
    ID3D11ShaderResourceView* texture_;     // ���[�e�B���O
    
public:
    bool init();
    bool update();
    void draw();
    void destroy();

    int cnt = 0; //���[�e�B���O��ʂ̕`�掞��
};