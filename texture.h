#pragma once
#include<d3d11.h>
#include<WICTextureLoader.h>
#include"Error.h"

//���O���
using namespace DirectX;

class Texture
{

public:

    static ID3D11ShaderResourceView* load( const wchar_t*Filname );

};