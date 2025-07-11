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
	Vector2 position; // 碰撞盒中心位置
	Vector2 size;     // 碰撞盒大小
	bool enabled = true; // 是否启用碰撞检测
	std::function<void()> on_collide; // 碰撞后的回调函数
	CollisionLayer layer_src = CollisionLayer::None; // 当前碰撞箱自身碰撞层
	CollisionLayer layer_dst = CollisionLayer::None; // 目标碰撞层 
	
private: 
	CollisionBox() = default;
	~CollisionBox() = default;

};
