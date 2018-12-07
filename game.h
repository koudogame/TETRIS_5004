#pragma once


#include"player.h"
#include"key.h"
#include"release.h"
#include"title.h"
#include"UI.h"
#include"start.h"
#include"time.h"
#include"result.h"
#include"field.h"
#include"time_limit.h"
#include"MINO.h"

//Class
class Game
{
private:
    Player player_;                     // �v���C���[�N���X
    UI ui_;                             //ui�N���X
    Title title_;                       // �^�C�g���N���X
    Start start_;                       //�X�^�[�g�N���X
    TimeLimit time_;                    //�^�C���N���X
    Result result_;                     //���U���g�N���X
    Field field_;                       //�t�B�[���h�N���X
    TimeLimit timelimit_;               //�^�C�����~�b�g�N���X
    Pov pov_;                           //pov�N���X
    Mino mino_;
public:
    Game();                             // �R���X�g���N�^
    ~Game();                            // �f�X�g���N�^
    bool init();                // ������
    bool update();              // �X�V
    void draw();                // �`��
    void destroy();                     // �j��

    int tmp = 0;
};
