#include "Pinkey.h"
#include "DxLib.h"
#include "../../Utility/ResourceManager.h"
#include "../../../Player/Player.h"
#include "../../Utility/InputManager.h"

#define D_ENEMY_SPEED (50.0f)

//�R���X�g���N�^
Pinkey::Pinkey()
{
	Player* player;
	eEnemyState enemy_state;
}
//�f�X�g���N�^
Pinkey::~Pinkey()
{
}

//����������
void Pinkey::Initialize()
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
void Pinkey::Update(float delta_second)
{
	EnemyBase::Movement(delta_second);
	enemy_time++;
}

//�`�揈��
void Pinkey::Draw(const Vector2D& screen_offset)const
{
	// �e�N���X�̕`�揈�����Ăяo��
	__super::Draw(screen_offset);
}

//�I��������
void Pinkey::Finalize()
{
	// ���I�z��̉��
	move_animation.clear();
	eye_animation.clear();
}

//�����蔻�菈��
void Pinkey::OnHitCollision(GameObjectBase* hit_object)
{
		// ���������A�I�u�W�F�N�g���ǂ�������
		if (hit_object->GetCollision().object_type == eObjectType::wall && pinkey_state == eEnemyState::TERRITORY || pinkey_state == eEnemyState::CHASE)
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
		enemy_state = eEnemyState::RUN;
	}
}

//�ړ�����
void Pinkey::Movement(float delta_second)
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
		break;
	case eMoveState::DOWN:
		velocity.y = 1.0f;
		break;
	case eMoveState::LEFT:
		velocity.x = -1.0f;
		break;
	case eMoveState::RIGHT:
		velocity.x = 1.0f;
		break;
	default:
		break;
	}

	// �ړ��� * ���� * ���� �ňړ�������肷��
	location += velocity * D_ENEMY_SPEED * delta_second;
}

//�G�l�~�[�ҋ@����
void Pinkey::WaitMoment(float delta_second)
{
	image = move_animation[2];

	enemy_state = pinkey_state;
	now_direction = next_direction_state;

	if (enemy_time > 300) {
		now_direction = eMoveState::UP;
		pinkey_state = eEnemyState::TERRITORY;
	}
}

//�i���o�����񏈗�
void Pinkey::TerritoryMove(float delta_second)
{
		// �i���o�����̎��Ԑݒ�Ǝ��Ԍ�̏���
		if (enemy_time > 2700) {
			pinkey_state = eEnemyState::CHASE;
			player->GetLocation();
		}

		if (now_direction == eMoveState::UP)
		{
			now_direction = eMoveState::LEFT;
		}

		// ���㏈��
		if (location.x == 35.5f && location.y == 35.5f) {
			now_direction = eMoveState::DOWN;
			if (now_direction == eMoveState::DOWN) {
				next_direction_state = eMoveState::DOWN;
			}
		}

		// ��������
		if (location.x == 35.5f && location.y > 115.5f) {
			now_direction = eMoveState::RIGHT;
			if (now_direction == eMoveState::RIGHT) {
				next_direction_state = eMoveState::RIGHT;
			}
		}

		// �E������
		if (location.x > 131.5f && location.y == 132.5f) {
			now_direction = eMoveState::DOWN;
			if (now_direction == eMoveState::DOWN) {
				next_direction_state = eMoveState::DOWN;
			}
		}
}

//�C�W�P���
void Pinkey::WeekendMove(float delta_second)
{
	image = move_animation[17];
}
//�ǂ���������
void Pinkey::ChaseMoment(float delta_second)
{

}
	

void Pinkey::RunMoment(float delta_second)
{
	if (enemy_state == eEnemyState::RUN)
	{

	}
	image = eye_animation[4];
}

//�A�j���[�V��������
void Pinkey::AnimationControl(float delta_second)
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
		}

	}
}