#include"pad.h"

//���̂̐錾
GamePad Pad::pad_;
GamePad::State Pad::state_;
GamePad::State Pad::state2_;
GamePad::ButtonStateTracker Pad::pad_tracker_;
GamePad::ButtonStateTracker Pad::pad_tracker2_;

//�X�V����
void Pad::update()
{
    //���͂��擾
    //�����ŉ��Ԗڂ̃R���g���[���̓��͂��Ƃ邩���߂�
    state_ = pad_.GetState( 0 );
    state2_ = pad_.GetState( 1 );

    // �g���b�J�[���X�V
    pad_tracker_.Update( state_ );
    pad_tracker2_.Update( state2_ );
}