#pragma once

#include<GamePad.h>

using namespace DirectX;

class Pad
{
private:

    static GamePad pad_;                                      //ゲームパッドクラス
    static GamePad::State state_;                             //入力格納構造体
    static GamePad::State state2_;
    static GamePad::ButtonStateTracker pad_tracker_;
    static GamePad::ButtonStateTracker pad_tracker2_;

public:

    static void update();                                     //更新処理

    //入力構造体を返す
    static const GamePad::State& getState() { return state_; }
    static const GamePad::State& getState2() { return state2_; }

    static const GamePad::ButtonStateTracker& getTracker() { return pad_tracker_; }
    static const GamePad::ButtonStateTracker& getTracker2() { return pad_tracker2_; }
};