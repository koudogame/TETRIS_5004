#include"pad.h"

//実体の宣言
GamePad Pad::pad_;
GamePad::State Pad::state_;
GamePad::State Pad::state2_;
GamePad::State Pad::state3_;
GamePad::State Pad::state4_;
GamePad::ButtonStateTracker Pad::pad_tracker_;
GamePad::ButtonStateTracker Pad::pad_tracker2_;
GamePad::ButtonStateTracker Pad::pad_tracker3_;
GamePad::ButtonStateTracker Pad::pad_tracker4_;

//更新処理
void Pad::update()
{
    //入力を取得
    //引数で何番目のコントローラの入力をとるか決める
    state_ = pad_.GetState( 0 );
    state2_ = pad_.GetState( 1 );
    state3_ = pad_.GetState( 2 );
    state4_ = pad_.GetState( 3 );
    // トラッカーを更新
    pad_tracker_.Update( state_ );
    pad_tracker2_.Update( state2_ );
    pad_tracker3_.Update( state3_ );
    pad_tracker4_.Update( state4_ );
}