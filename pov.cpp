#include "pov.h"

int Pov::update()
{
    const GamePad::State pad = Pad::getState();
    const Keyboard::State state = Key::getState();

    //十字キー入力状態表示
    if ((state.Up || pad.dpad.up) && (state.Right || pad.dpad.right))
    {
        //右上
        pov = UPPER_RIGHT;
    }
    else if ((state.Up || pad.dpad.up) && (state.Left || pad.dpad.left))
    {
        //左上
        pov = UPPER_LEFT;
    }
    else  if (state.Up || pad.dpad.up)
    {
        //上
        pov = UP;
    }
    else if ((state.Right || pad.dpad.right) && (state.Down || pad.dpad.down))
    {
        //右下
        pov = BOTTOM_RIGHT;
    }
    else if (state.Right || pad.dpad.right)
    {
        //右
        pov = RIGHT;
    }
    else if ((state.Left || pad.dpad.left) && (state.Down || pad.dpad.down))
    {
        //左下
        pov = BOTTOM_LEFT;
    }
    else if (state.Down || pad.dpad.down)
    {
        //下
        pov = DOWN;
    }
    else if (state.Left || pad.dpad.left)
    {
        //左
        pov = LEFT;
    }
    else
    {
        //入力なし
        pov = NOINPUT;
    }
    return pov;
}


