#pragma once

#include"release.h"

//Class
class Adx
{
private:

    static CriAtomExVoicePoolHn voice_pool_;                //ボイスプール
    static CriAtomExAcbHn acb_;                             //ACBハンドル
    static CriAtomExPlayerHn player_;                       //プレイヤーハンドル

public:

    static bool init( const CriChar8* acfFilePath );        //初期化
    static bool load( const CriChar8* acbFilePath, CriChar8* awbFile );       //サウンド
    static void destroy();  //破棄
    static void play( CriAtomExCueId id = 0 );  //再生
    
    //停止
    static void stop() { criAtomExPlayer_Stop( player_ ); } //すべて
    static void stop( CriAtomExCueId id ) { criAtomExPlayback_Stop( id ); } //特定

    //ADXライブラリ更新処理
    static void update() { criAtomEx_ExecuteMain(); }

    //エラー処理関数
    static void userErrorCallBack(
        const CriChar8* Errorld,
        CriUint32 P1,
        CriUint32 P2,
        CriUint32* pArray );
};