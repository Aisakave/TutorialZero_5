#pragma once
#include "atlas.h"
#include "timer.h"
#include "vector2.h"
#include "util.h"

#include <vector>
#include <functional>

class Animation
{

public:
	enum class AnchorMode
	{
		Centered, // 居中
		BottomCentered // 底部居中
	};

public:
	Animation()
	{
		timer.set_one_shot(false);
		timer.set_on_timeout(
			[&]()
			{
				idx_frame++;
				if (idx_frame >= frame_list.size())
				{
					idx_frame = is_loop ? 0 : frame_list.size() - 1;
					if (!is_loop && on_finished)
						on_finished();
				}
			}
		);
	}

	~Animation() = default;

public:
	void reset()
	{
		timer.restart();

		idx_frame = 0;
	}

	void set_anchor_mode(AnchorMode mode)
	{
		anchor_mode = mode;
	}

	void set_position(const Vector2& position)
	{
		this->position = position;
	}

	void set_loop(bool is_loop)
	{
		this->is_loop = is_loop;
	}

	void set_interval(float interval)
	{
		timer.set_wait_time(interval);
	}

	void set_on_finished(std::function<void()> on_finished)
	{
		this->on_finished = on_finished;
	}

	// 加载一张长条的动画图片素材
	void add_frame(IMAGE* image, int num_h)
	{


	}

	void add_frame(Atlas* atlas)
	{


	}





private:
	struct Frame
	{
		Rect rect_src;
		IMAGE* image = nullptr;

		Frame() = default;
		Frame(IMAGE* image, const Rect& rect_src)
			: image(image), rect_src(rect_src) { }
			
		~Frame() = default;
	};

private:
	Timer timer; // 定时器——推动帧索引
	Vector2 position; // 动画在窗口中的渲染位置
	bool is_loop = true; // 动画是否循环播放
	size_t idx_frame = 0; // 当前动画播放的帧索引
	std::vector<Frame> frame_list; // 动画所包含的每一帧的帧信息
	std::function<void()> on_finished; // 动画播放完毕后的回调函数
	AnchorMode anchor_mode = AnchorMode::Centered; // 锚点模式
};
