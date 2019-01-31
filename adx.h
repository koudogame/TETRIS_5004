#pragma once

#include"release.h"

//Class
class Adx
{
private:

    static CriAtomExVoicePoolHn voice_pool_;                //�{�C�X�v�[��
    static CriAtomExAcbHn acb_;                             //ACB�n���h��
    static CriAtomExPlayerHn player_;                       //�v���C���[�n���h��

public:

    static bool init( const CriChar8* acfFilePath );        //������
    static bool load( const CriChar8* acbFilePath, CriChar8* awbFile );       //�T�E���h
    static void destroy();  //�j��
    static void play( CriAtomExCueId id = 0 );  //�Đ�
    
    //��~
    static void stop() { criAtomExPlayer_Stop( player_ ); } //���ׂ�
    static void stop( CriAtomExCueId id ) { criAtomExPlayback_Stop( id ); } //����

    //ADX���C�u�����X�V����
    static void update() { criAtomEx_ExecuteMain(); }

    //�G���[�����֐�
    static void userErrorCallBack(
        const CriChar8* Errorld,
        CriUint32 P1,
        CriUint32 P2,
        CriUint32* pArray );
};