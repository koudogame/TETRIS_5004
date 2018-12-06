#include "hit_scene.h"
#include"adx.h"


// �R���X�g���N�^
HitScene::HitScene()
{
    // �e�N�X�`����NULL�����Ă���
    texture1_car = NULL;
    texture2_bike = NULL;
    texture3_back = NULL; hit_flag_ = NULL;
}

// ������
bool HitScene::init(bool oba, int p2)
{
    // �e�N�X�`���ǂݍ���
	if (oba)
	{
		texture1_car = Texture::load(L"oba1.png");
	}
	else
	{
		texture1_car = Texture::load(L"car_side.png");
	}
    if (!oba)
    {
        //�Ђ���鑤�̎��
        if (p2 == 0)
        {
            texture2_bike = Texture::load(L"�`����.png");
        }
        else if (p2 == 1)
        {
            texture2_bike = Texture::load(L"�o�C�N��.png");
        }
        else if (p2 == 2)
        {
            texture2_bike = Texture::load(L"�o�C�N��.png");
        }
    }
    else
    {
        texture2_bike = Texture::load(L"�`����.png");
    }

    
    texture3_back = Texture::load( L"field.png" );

    
    // ���]�Ԃ̍��W
    position1_bike.x = static_cast<float>(1280.0F);
    position1_bike.y = static_cast<float>(390.0F);

    // �Ԃ̍��W
    if (oba)
    {
        position2_car.x = static_cast<float>(0.0F);
        position2_car.y = static_cast<float>(600.0F - 196.0F);

    }
    else //�ʏ탂�[�h
    {
        position2_car.x = static_cast<float>(0.0F);
        position2_car.y = static_cast<float>(600.0F - 350.0F);

    }

    hit_flag_ = NULL;

    //NULL�`�F�b�N
    if( texture1_car == NULL )
    {

        Error::showDialog( "texture_1���ǂݍ��߂܂���" );

        //�G���[
        return false;
    }

    if( texture2_bike == NULL )
    {

        Error::showDialog( "texture_2���ǂݍ��߂܂���" );

        //�G���[
        return false;
    }

    if( texture3_back == NULL )
    {

        Error::showDialog( "texture_2���ǂݍ��߂܂���" );

        //�G���[
        return false;
    }

    return true;
}

bool HitScene::update(bool oba)
{

    cnt++;
    int tmp=0;
    if (oba)
    {
        tmp = 5;
    }
	// ���]�Ԃ̍��W�����ȏ�̂Ƃ��Փ˃t���O���I�t�Ȃ獶�Ɉړ�
    if( position1_bike.x>=640&&hit_flag_!=true )
    {
        position1_bike.x-=5;
    }
    if (oba)
    {
        position2_car.x += 5;
    }
	// �Ԃ̍��W�����ȉ��̂Ƃ��Փ˃t���O���I�t�Ȃ�E�Ɉړ�
    if (position2_car.x + 600 <= position1_bike.x&&hit_flag_ != true)
    {
        if (!oba)
        {
            position2_car.x += 5;
        }
    }

	// �ԂƎ��]�Ԃ��Փ˂����Ƃ��̏���
    if( position1_bike.x <= position2_car.x + 550&&!hit_flag_ )
    {
       
		// ���搶���[�h�Ȃ珬�ۂ̉��ɂ���
		if (oba)
		{

			Adx::play(7);
		}
		else
		{
			Adx::play(8);
		}
		// �Փ˃t���O���I��
        hit_flag_ = true;
    }

	// �Փ˃t���O���I���Ŏ��]�Ԃ���ʓ��ɂ܂�����Ƃ����]�Ԃ𐁂���΂�
    if( hit_flag_ == true && position1_bike.x <= 1280 + 210 )
    {
        position1_bike.y -= 5;
        position1_bike.x += 10;
    }
	// ���]�Ԃ���������I��
    else if( hit_flag_ == true && position1_bike.x >= 1280 + 210+tmp)
    {
        return false;
    }
    return true;
}

// �`��
void HitScene::draw(bool oba)
{
    RECT rect;

    if (oba)
    {
        if (!hit_flag_)
        {
            rect.top = 0L;
            rect.left = 0L;
            rect.right = rect.left + 600L;
            rect.bottom = rect.top + 196L;
        }
        else
        {
            rect.top = 196L;
            rect.left = 0L;
            rect.right = rect.left + 600L;
            rect.bottom = rect.top + 196L;
        }
    }
    else
    {
        rect.top = 0L;
        rect.left = 0L;
        rect.right = rect.left + 600L;
        rect.bottom = rect.top + 360L;
    }

    Vector2 scale(1.0F, 1.0F);
    Vector2 origin(0.0F, 0.0F);

    Sprite::draw(texture3_back, Vector2::Zero);       // �w�i��`��
    Sprite::draw(texture2_bike, position1_bike);       // ���]�Ԃ�`��
    if (oba)
    {
        Sprite::draw(texture1_car, position2_car, &rect); // �Ԃ�`��

    }
    else
    {
        Sprite::draw(texture1_car, position2_car, &rect); // �Ԃ�`��
    }

}

void HitScene::destroy()
{
    SAFE_RELEASE( texture1_car );
    SAFE_RELEASE( texture2_bike );
    SAFE_RELEASE( texture3_back );
}
