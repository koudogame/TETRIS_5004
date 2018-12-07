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
#include"time_limit.h"
#include"MINO.h"

//Class
class Game
{
private:
    Player player_;                     // プレイヤークラス
    UI ui_;                             //uiクラス
    Title title_;                       // タイトルクラス
    Start start_;                       //スタートクラス
    TimeLimit time_;                    //タイムクラス
    Result result_;                     //リザルトクラス
    Field field_;                       //フィールドクラス
    TimeLimit timelimit_;               //タイムリミットクラス
    Pov pov_;                           //povクラス
    Mino mino_;
public:
    Game();                             // コンストラクタ
    ~Game();                            // デストラクタ
    bool init();                // 初期化
    bool update();              // 更新
    void draw();                // 描画
    void destroy();                     // 破棄

    int tmp = 0;
};
