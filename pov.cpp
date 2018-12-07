#include "pov.h"

int Pov::update()
{
    const GamePad::State pad = Pad::getState();
    const Keyboard::State state = Key::getState();

    //�\���L�[���͏�ԕ\��
    if ((state.Up || pad.dpad.up) && (state.Right || pad.dpad.right))
    {
        //�E��
        pov = UPPER_RIGHT;
    }
    else if ((state.Up || pad.dpad.up) && (state.Left || pad.dpad.left))
    {
        //����
        pov = UPPER_LEFT;
    }
    else  if (state.Up || pad.dpad.up)
    {
        //��
        pov = UP;
    }
    else if ((state.Right || pad.dpad.right) && (state.Down || pad.dpad.down))
    {
        //�E��
        pov = BOTTOM_RIGHT;
    }
    else if (state.Right || pad.dpad.right)
    {
        //�E
        pov = RIGHT;
    }
    else if ((state.Left || pad.dpad.left) && (state.Down || pad.dpad.down))
    {
        //����
        pov = BOTTOM_LEFT;
    }
    else if (state.Down || pad.dpad.down)
    {
        //��
        pov = DOWN;
    }
    else if (state.Left || pad.dpad.left)
    {
        //��
        pov = LEFT;
    }
    else
    {
        //���͂Ȃ�
        pov = NOINPUT;
    }
    return pov;
}


