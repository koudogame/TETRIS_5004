#include"pad.h"

//���̂̐錾
GamePad Pad::pad_;
GamePad::State Pad::state_;
GamePad::State Pad::state2_;
GamePad::State Pad::state3_;
GamePad::State Pad::state4_;
GamePad::ButtonStateTracker Pad::pad_tracker_;
GamePad::ButtonStateTracker Pad::pad_tracker2_;
GamePad::ButtonStateTracker Pad::pad_tracker3_;
GamePad::ButtonStateTracker Pad::pad_tracker4_;

//�X�V����
void Pad::update()
{
    //���͂��擾
    //�����ŉ��Ԗڂ̃R���g���[���̓��͂��Ƃ邩���߂�
    state_ = pad_.GetState( 0 );
    state2_ = pad_.GetState( 1 );
    state3_ = pad_.GetState( 2 );
    state4_ = pad_.GetState( 3 );
    // �g���b�J�[���X�V
    pad_tracker_.Update( state_ );
    pad_tracker2_.Update( state2_ );
    pad_tracker3_.Update( state3_ );
    pad_tracker4_.Update( state4_ );
}