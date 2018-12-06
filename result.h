#pragma once

#include"sprite.h"
#include"texture.h"
#include"pad.h"
#include"Error.h"
#include"release.h"
#include"key.h"


// class
class Result
{
private:
	ID3D11ShaderResourceView* texture_; //”wŒi 
	ID3D11ShaderResourceView* Rtexture_; //–îˆó
	ID3D11ShaderResourceView* S1texture_; //“_”
    ID3D11ShaderResourceView* Judge1_;   // Ÿ”s”»’è1

	Vector2 position_;

    int judge_num = 0;

	int mash_1 = 0;
	int mash_2 = 0;
	int mash_sum = 0;
public:
	Result();
	bool init(int mash1, int mash2,bool oba);
	void draw();
	void scoredraw1();
	void scoredraw2();
	void arrowdraw();
	int update();
	void destroy();

	int menu = 0;
};