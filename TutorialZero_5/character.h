#pragma once

#include "vector2.h"
#include "animation.h"
#include "collision_box.h"
#include "state_machine.h"

#include <string>
#include <graphics.h>
#include <unordered_map>

class Character
{
public:
	Character();
	~Character();

	void decrease_hp();

	int get_hp() const
	{
		return hp;
	}

	void set_position(const Vector2& position)
	{
		this->position = position;
	}

	const Vector2& get_position() const
	{
		return position;
	}

	void set_velocity(const Vector2& velocity)
	{
		this->velocity = velocity;
	}

	Vector2 get_logic_center() const
	{
		return Vector2(position.x, position.y - logic_height / 2);
	}

	void set_gravity_enabled(bool flag)
	{
		enabled_gravity = flag;
	}

	CollisionBox* get_hit_box()
	{
		return hit_box;
	}

	CollisionBox* get_hurt_box()
	{
		return hurt_box;
	}

	bool is_on_floor() const
	{
		return position.y >= FLOOR_Y;
	}

	float get_floor_y() const
	{
		return FLOOR_Y;
	}

	void make_invulnerable()
	{
		is_invulnerable = true;
		timer_invulnerable_status.restart();
	}

	virtual void on_input(const ExMessage& msg);
	virtual void on_update(float delta);
	virtual void on_render();

	virtual void on_hurt();

	void switch_state(const std::string& id);
	void set_animation(const std::string& id);


protected:
	struct AnimationGroup
	{
		Animation left;
		Animation right;
	};

protected:
	const float FLOOR_Y = 620;										// 地板的竖直方向坐标
	const float GRAVITY = 980 * 2;									// 重力大小	

protected:
	int hp = 10;													// 角色生命值
	Vector2 position;												// 角色脚底位置			
	Vector2 velocity;												// 角色速度
	float logic_height = 0;											// 逻辑高度，用于计算角色的逻辑中心位置	
	bool is_facing_left = true;										// 角色是否面向左侧
	StateMachine state_machine;										// 角色逻辑状态机
	bool enabled_gravity = true;									// 启用重力模拟
	bool is_invulnerable = false;									// 是否无敌状态
	Timer timer_invulnerable_blink;									// 无敌状态闪烁计时器
	Timer timer_invulnerable_status;								// 无敌状态计时器
	bool is_blink_invisible = false;								// 是否闪烁隐形状态
	CollisionBox* hit_box = nullptr;								// 攻击碰撞盒
	CollisionBox* hurt_box = nullptr;								// 受击碰撞盒
	AnimationGroup* current_animation = nullptr;					// 当前角色动画
	std::unordered_map<std::string, AnimationGroup> animation_pool; // 角色动画池
};