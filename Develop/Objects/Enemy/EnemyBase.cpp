#include "EnemyBase.h"
#include "DxLib.h"
#include "../../Utility/ResourceManager.h"

//�R���X�g���N�^
EnemyBase::EnemyBase() 
: move_animation(),
  eye_animation(),
  velocity(0.0f),
  enemy_state(eEnemyState::WAIT),
  now_direction(eMoveState::UP),
  next_direction_state(eMoveState::UP),
  animation_time(0.0f),
  animation_count(0),
  enemy_time(0.0f),
  flame_time(0.0f)
{
}
//�f�X�g���N�^
EnemyBase::~EnemyBase()
{
}

//����������
void EnemyBase::Initialize() 
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
}

//�X�V����
void EnemyBase::Update(float delta_second) 
{
	//Movement;
}

//�`�揈��
void EnemyBase::Draw(const Vector2D& screen_offset)const 
{
	// �e�N���X�̕`�揈�����Ăяo��
	__super::Draw(screen_offset);
}

//�I��������
void EnemyBase::Finalize() 
{
	// ���I�z��̉��
	move_animation.clear();
	eye_animation.clear();
}

//�����蔻�菈��
void EnemyBase::OnHitCollision(GameObjectBase* hit_object)
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
	// ������Ƃ��v���C���[�����G��Ԃł���ꍇ
	if (hit_object->GetCollision().object_type == eObjectType::special)
	{
		enemy_state = eEnemyState::WEEKEND;
	}
}

//�ړ�����
void EnemyBase::Movement(float delta_second)
{
	switch (enemy_state)
	{
	case eEnemyState::WAIT:
		// �摜�̐ݒ�
		image = move_animation[9];
		break;
	case eEnemyState::WORK:
		// �A�j���[�V��������
		AnimationControl(delta_second);
		break;
	case eEnemyState::TERRITORY:
		break;
	case eEnemyState::WEEKEND:
		break;
	case eEnemyState::CHASE:
		break;
	case eEnemyState::RUN:
		break;
	default:
		break;
	}
}

//�G�l�~�[�ҋ@����
void EnemyBase::WaitMoment(float delta_second)
{
	if (enemy_state == WAIT)
	{

	}
}

//�i���o�����񏈗�
void EnemyBase::TerritoryMove(float delta_second)
{
	if (enemy_state == TERRITORY)
	{

	}
}

//�C�W�P��ԏ���
void EnemyBase::WeekendMove(float delta_second)
{
	if (enemy_state == WEEKEND)
	{

	}
}

//�ǂ���������
void EnemyBase::ChaseMoment(float delta_second)
{
	if (enemy_state == CHASE)
	{

	}
}

//�A������
void EnemyBase::RunMoment(float delta_second)
{
	if (enemy_state == RUN)
	{

	}
}

//�A�j���[�V��������
void EnemyBase::AnimationControl(float delta_second)
{
	
}