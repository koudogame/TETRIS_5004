#pragma once


using namespace DirectX;

class Pad
{
private:

    static GamePad pad_;                                      //ゲームパッドクラス
    static GamePad::State state_;                             //入力格納構造体
    static GamePad::State state2_;
    static GamePad::State state3_;
    static GamePad::State state4_;
    static GamePad::ButtonStateTracker pad_tracker_;
    static GamePad::ButtonStateTracker pad_tracker2_;
    static GamePad::ButtonStateTracker pad_tracker3_;
    static GamePad::ButtonStateTracker pad_tracker4_;

public:

    static void update();                                     //更新処理

    //入力構造体を返す
    static const GamePad::State& getState() { return state_; }
    static const GamePad::State& getState2() { return state2_; }
    static const GamePad::State& getState3() { return state3_; }
    static const GamePad::State& getState4() { return state4_; }

    static const GamePad::ButtonStateTracker& getTracker() { return pad_tracker_; }
    static const GamePad::ButtonStateTracker& getTracker2() { return pad_tracker2_; }
    static const GamePad::ButtonStateTracker& getTracker3() { return pad_tracker3_; }
    static const GamePad::ButtonStateTracker& getTracker4() { return pad_tracker4_; }
};