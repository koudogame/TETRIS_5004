#pragma once

#include"key.h"
#include"pad.h"
#include"sprite.h"
#include"texture.h"
#include"release.h"
#include"adx.h"

class Clear
{
private:
    ID3D11ShaderResourceView* texture_;

public:
    Clear();
    bool init();
    int update(int menu_type);
    void draw();
    void cursordraw();
    void destroy();

    //���j���[�E�B���h�E�̎��
    int mode = 0;

    //���O���͔z��(�t�@�C���o�͂ɕς���)
    int name[3] = { 0 };

    //���̕�������͂���������悤
    int num = 0;
    int digit = 0;
    
    //���͏I��
    bool end = false;

    int menu = 0; //���g���C���j���[

};
