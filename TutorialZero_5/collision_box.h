#pragma once
#include "vector2.h"
#include "collision_layer.h"

#include <functional>

class CollisionManager;

class CollisionBox
{
	friend class CollisionManager;
public:
	void set_enabled(bool flag)
	{
		enabled = flag;
	}

	void set_layer_src(CollisionLayer layer)
	{
		layer_src = layer;
	}
	
	void set_layer_dst(CollisionLayer layer)
	{
		layer_dst = layer;
	}

	void set_on_collide(std::function<void()> on_collide)
	{
		this->on_collide = on_collide;
	}

	void set_size(const Vector2& size)
	{
		this->size = size;
	}

	const Vector2& get_size() const
	{
		return size;
	}

	void set_position(const Vector2& position)
	{
		this->position = position;
	} 
private:
	Vector2 position; // ��ײ������λ��
	Vector2 size;     // ��ײ�д�С
	bool enabled = true; // �Ƿ�������ײ���
	std::function<void()> on_collide; // ��ײ��Ļص�����
	CollisionLayer layer_src = CollisionLayer::None; // ��ǰ��ײ��������ײ��
	CollisionLayer layer_dst = CollisionLayer::None; // Ŀ����ײ�� 
	
private: 
	CollisionBox() = default;
	~CollisionBox() = default;

};
