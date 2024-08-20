#include "Akabe.h"
#include "DxLib.h"
#include "../../Utility/ResourceManager.h"
#include "../../../Player/Player.h"
#include "../../Utility/InputManager.h"

#define D_ENEMY_SPEED (100.0f)

//�R���X�g���N�^
Akabe::Akabe() 
{
	Player* player;
	Akabe* akabe;
}
//�f�X�g���N�^
Akabe::~Akabe()
{
}

//����������
void Akabe::Initialize()
{
	// �A�j���[�V�����摜�̓ǂݍ���
	ResourceManager* rm = ResourceManager::GetInstance();
	move_animation = rm->GetImages("Resource/Images/monster.png", 20, 12, 1, 32, 32);
	eye_animation = rm->GetImages("Resource/Images/eyes.png", 4, 11, 1, 32, 32);

	// �����蔻��̐ݒ�
	collision.is_blocking = true;
	collision.object_type = eObjectType::enemy;
	collision.hit_object_type.push_back(eObjectType::player);
	collision.hit_object_type.push_back(eObjectType::wall);
	collision.hit_object_type.push_back(eObjectType::special);
	collision.radius = (D_OBJECT_SIZE - 1.0f) / 2.0f;

	// ���C���[�̐ݒ�
	z_layer = 5;

	// �����̐ݒ�
	mobility = eMobilityType::Movable;

	enemy_time = 0.0f;
}

//�X�V����
void Akabe::Update(float delta_second)
{
	EnemyBase::Movement(delta_second);
	enemy_time++;
}

//�`�揈��
void Akabe::Draw(const Vector2D& screen_offset)const
{
	// �e�N���X�̕`�揈�����Ăяo��
	__super::Draw(screen_offset);

	DrawFormatString(5, 5, 0xffffff, "X���W:%f", location.x);
	DrawFormatString(5, 20, 0xffffff, "Y���W:%f", location.y);
	DrawFormatString(5, 40, 0xffffff, "�G�l�~�[����:%f", enemy_time);
}

//�I��������
void Akabe::Finalize()
{
	// ���I�z��̉��
	move_animation.clear();
	eye_animation.clear();
}

//�����蔻�菈��
void Akabe::OnHitCollision(GameObjectBase* hit_object)
{
	// ���������A�I�u�W�F�N�g���ǂ�������
	if (hit_object->GetCollision().object_type == eObjectType::wall)
	{
		// �����蔻������擾���āA�J�v�Z��������ʒu�����߂�
		CapsuleCollision hc = hit_object->GetCollision();
		hc.point[0] += hit_object->GetLocation();
		hc.point[1] += hit_object->GetLocation();

		// �ŋߖT�_�����߂�
		Vector2D near_point = NearPointCheck(hc, this->location);

		// Enemy����near_point�ւ̕����x�N�g�����擾
		Vector2D dv2 = near_point - this->location;
		Vector2D dv = this->location - near_point;

		// �߂荞�񂾍���
		float diff = (this->GetCollision().radius + hc.radius) - dv.Length();

		// diff�̕������߂�
		location += dv.Normalize() * diff;
	}
	// ������Ƃ��v���C���[���ł���ꍇ
	if (hit_object->GetCollision().object_type == eObjectType::special)
	{
		enemy_state = eEnemyState::WEEKEND;
	}
	// �����C�W�P��ԂȂ�
	if (enemy_state == eEnemyState::WEEKEND)
	{
		if (hit_object->GetCollision().object_type == eObjectType::player)
		{
			enemy_state = eEnemyState::RUN;
		}
	}
}

//�ړ�����
void Akabe::Movement(float delta_second)
{
	switch (enemy_state)
	{
	case eEnemyState::WAIT:
		WaitMoment(delta_second);
		break;
	case eEnemyState::WORK:
		// �A�j���[�V��������
		AnimationControl(delta_second);
		break;
	case eEnemyState::TERRITORY:
		TerritoryMove(delta_second);
		break;
	case eEnemyState::WEEKEND:
		WeekendMove(delta_second);
		break;
	case eEnemyState::CHASE:
		ChaseMoment(delta_second);
		break;
	case eEnemyState::RUN:
		RunMoment(delta_second);
		break;
	default:
		break;
	}

	// �i�s�����̈ړ��ʂ�ǉ�
	switch (now_direction)
	{
	case eMoveState::UP:
		velocity.y = -1.0f;
		eye_image = eye_animation[0];
		break;
	case eMoveState::DOWN:
		velocity.y = 1.0f;
		eye_image = eye_animation[2];
		break;
	case eMoveState::LEFT:
		velocity.x = -1.0f;
		eye_image = eye_animation[3];
		break;
	case eMoveState::RIGHT:
		velocity.x = 1.0f;
		eye_image = eye_animation[1];
		break;
	default:
		break;
	}

	// �O����W�̍X�V
	old_location = location;

	// �ړ��� * ���� * ���� �ňړ�������肷��
	location += velocity * D_ENEMY_SPEED * delta_second;
}

//�G�l�~�[�ҋ@����
void Akabe::WaitMoment(float delta_second)
{
	image = move_animation[0];
	eye_image = eye_animation[0];

	now_direction = next_direction_state;
	enemy_state = eEnemyState::WAIT;
	next_direction_state = eMoveState::RIGHT;
	

	if (enemy_time < 100.0f) {
		
		next_direction_state = eMoveState::RIGHT;
	}

	if (location.y == 35.5f&& location.x==636.5f) {
		next_direction_state = eMoveState::DOWN;
	}
	/* �E�� �� ����̈ړ����������
	if (location.x == 636.5f && location.y == 204.0f) {
		next_direction_state = eMoveState::UP;

    // ����
    f(){
	}

	// ����
	f(){
	}

	}*/

	
	
}

//�i���o�����񏈗�
void Akabe::TerritoryMove(float delta_second)
{
	
	akabe->SetLocation(location);
}

//�C�W�P���
void Akabe::WeekendMove(float delta_second)
{
	image = move_animation[16];
}

//�ǂ���������
void Akabe::ChaseMoment(float delta_second)
{
	akabe->GetLocation();

	now_direction = RIGHT;
}

void Akabe::RunMoment(float delta_second)
{
	if (enemy_state == eEnemyState::RUN)
	{

	}
}

//�A�j���[�V��������
void Akabe::AnimationControl(float delta_second)
{
	// �ړ����̃A�j���[�V����
	animation_time += delta_second;
	if (animation_time >= (1.0f / 16.0f))
	{
		animation_time = 0.0f;
		animation_count++;
		if (animation_count >= 4)
		{
			animation_count = 0;
		}
		// �摜�̐ݒ�
		int dir_num = (int)now_direction;
		if (0 <= dir_num && dir_num < 4)
		{
			image = move_animation[(dir_num * 3) + animation_num[animation_count]];
			eye_image = eye_animation[(dir_num * 3) + animation_num[animation_count]];
		}

	}
}