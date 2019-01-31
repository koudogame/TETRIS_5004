#pragma once

#include"release.h"
#include"Error.h"

using namespace DirectX;
using namespace SimpleMath;

//�N���X�錾
class Player
{
private:
    ID3D11ShaderResourceView* texture_1;                                                         // �e�N�X�`��
    ID3D11ShaderResourceView* texture_2;
    Vector2 position_;                                                                          // ���W
    float speed_;                                                                               // �ړ����x

    // �A�j���[�V�����֘A
    int animation_pattern_;                                                                     // �A�j���[�V�����p�^�[��                                         
    int animation_no_;                                                                          // �A�j���[�V�����ԍ�
    int animation_counter_;                                                                     // �A�j���[�V�����J�E���^                            


    // �A�N�V�����֘A
    bool action_flag_;       // �A�N�V�����̃t���O
    int action_count_;       // �A�N�V�������s���̎��ԊǗ�������ϐ�

    // �A�Ő�
    static int mash_point1_;      // �v���C���[1
    static int mash_point2_;      // �v���C���[2
    

public:
    Player();                                                                                   // �R���X�g���N�^
    ~Player();                                                                                  // �f�X�g���N�^

    //������
    bool init();
    int get_position_x() { return position_.x; }
    int get_animation_pattern() { return animation_pattern_; }
 

    void update();                                                // �X�V
    void draw();                                                  // �`��
    void draw2();
    void destroy();                                               // �j��
};