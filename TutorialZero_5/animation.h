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

	// 加载一张长条的动画图片素材 num_h 代表需要切成几帧
	void add_frame(IMAGE* image, int num_h)
	{
		int width = image->getwidth();
		int height = image->getheight();
		int width_frame = width / num_h;

		for (int i = 0; i < num_h; i++)
		{
			Rect rect_src;
			rect_src.x = i * width_frame, rect_src.y = 0;
			rect_src.w = width_frame, rect_src.h = height;

			frame_list.emplace_back(image, rect_src);
		}

	}

	void add_frame(Atlas* atlas)
	{
		for (int i = 0; i < atlas->get_size(); i++)
		{
			IMAGE* image = atlas->get_image(i);
			int width = image->getwidth();
			int height = image->getheight();

			Rect rect_src;
			rect_src.x = 0, rect_src.y = 0;
			rect_src.w = width, rect_src.h = height;

			frame_list.emplace_back(image, rect_src);
		}

	}

	void on_update(float delta)
	{
		timer.on_update(delta);
	}

	void on_render()
	{
		const Frame& frame = frame_list[idx_frame];

		Rect rect_dst;
		rect_dst.x = (int)position.x - frame.rect_src.w / 2;
		rect_dst.y = (anchor_mode == AnchorMode::Centered) ?
			(int)position.y - frame.rect_src.h / 2 :
			(int)position.y - frame.rect_src.h;
		rect_dst.w = frame.rect_src.w, rect_dst.h = frame.rect_src.h;

		putimage_ex(frame.image, &rect_dst, &frame.rect_src);
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
