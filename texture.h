#pragma once
#include"Error.h"

//–¼‘O‹óŠÔ
using namespace DirectX;

class Texture
{

public:

    static ID3D11ShaderResourceView* load( const wchar_t*Filname );

};