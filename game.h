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
#include"MINO.h"
#include"pause.h"
#include"start.h"
#include"tetrismulti.h"
#include"clear.h"
#include"gameover.h"

//Class
class Game
{
private:
    Player player_;                     // �v���C���[�N���X
    UI ui_;                             //ui�N���X
    Title title_;                       // �^�C�g���N���X
    Start start_;                       //�X�^�[�g�N���X
    Result result_;                     //���U���g�N���X
    Field field_;                       //�t�B�[���h�N���X
    Pov pov_;                           //pov�N���X
    Mino mino_;
    Pause pause_;
    Clear clear_;
    Gameover gameover_;
    

public:
    Game();                             // �R���X�g���N�^
    ~Game();                            // �f�X�g���N�^
    bool init();                // ������
    int update(int player_num);              // �X�V
    void draw();                // �`��
    void drawmulti();                // �`��
    void destroy();                     // �j��

    int minotype = 0; //�~�m�̎��
    int menu_type = 1; //���j���[�̎��   
    int pausecnt = 0; //�|�[�Y���j���[�̃J�E���g
    bool play = false;
};
