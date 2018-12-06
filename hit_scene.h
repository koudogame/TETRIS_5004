#pragma once


#include "player.h"
#include "field.h"
#include "UI.h"

class HitScene
{
private:
    ID3D11ShaderResourceView* texture1_car;     // ���]��
    ID3D11ShaderResourceView* texture2_bike;    // ��
    ID3D11ShaderResourceView* texture3_back;    // �w�i

    Vector2 position1_bike;                         //���]�� 
    Vector2 position2_car;                         // ��

    bool hit_flag_;                                // ������t���O

public:
    HitScene();     // �R���X�g���N�^
    bool init(bool oba, int p2);    // ������
    bool update(bool oba);  // �X�V
    void draw(bool oba);    // �`��
    void destroy(); // �j��

    int cnt = 0;
};