#pragma once


#include"player.h"
#include"key.h"
#include"release.h"
#include"title.h"
#include"UI.h"
#include"start.h"
#include"time.h"
#include"result.h"
#include"field.h"
#include"MINO.h"
#include"pause.h"
#include"start.h"
#include"tetrismulti.h"
#include"clear.h"
#include"gameover.h"

//Class
class Game
{
private:
    Player player_;                     // プレイヤークラス
    UI ui_;                             //uiクラス
    Title title_;                       // タイトルクラス
    Start start_;                       //スタートクラス
    Result result_;                     //リザルトクラス
    Field field_;                       //フィールドクラス
    Pov pov_;                           //povクラス
    Mino mino_;
    Pause pause_;
    Clear clear_;
    Gameover gameover_;
    

public:
    Game();                             // コンストラクタ
    ~Game();                            // デストラクタ
    bool init();                // 初期化
    int update(int player_num);              // 更新
    void draw();                // 描画
    void drawmulti();                // 描画
    void destroy();                     // 破棄

    int minotype = 0; //ミノの種類
    int menu_type = 1; //メニューの種類   
    int pausecnt = 0; //ポーズメニューのカウント
    bool play = false;
};
