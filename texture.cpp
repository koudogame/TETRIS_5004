#include<WICTextureLoader.h>
#include<cstdio>
#include"texture.h"
#include"direct3d.h"
#include"Error.h"

ID3D11ShaderResourceView* Texture::load( const wchar_t* FileName )
{
    ID3D11ShaderResourceView* texture;

    if( FAILED( CreateWICTextureFromFileEx(
        Direct3D::getDevice(),                                                                  //D3Dデバイスインターフェース
        Direct3D::getContext(),                                                                 //デバイスコンテキストインターフェース
        FileName,                                                                               //ファイル名（ワイド文字で指定）
        0,                                                                                      //ミニマップレベル
        D3D11_USAGE_DEFAULT,                                                                    //使用方法
        D3D11_BIND_SHADER_RESOURCE,                                                             //バインドの種類
        0,                                                                                      //GPUアクセス方法
        0,                                                                                      //フラグオプション
        WIC_LOADER_DEFAULT,                                                                     //SRGBフラグ
        NULL,                                                                                   //リソースデータ受取先ポインタ
        &texture ) ) )                                                                          //シェーダーリソースビュー受取先ポインタ
    {
        char file_name[ 256 ], str[ 256 ];
        wcstombs( file_name, FileName, 256 );
        sprintf( str, "テクスチャーの読み込みに失敗(%s)", file_name );
        Error::showDialog( str );
        return NULL;
    }

    return texture;


}