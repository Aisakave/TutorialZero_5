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
		Centered, // ����
		BottomCentered // �ײ�����
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

	// ����һ�ų����Ķ���ͼƬ�ز�
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
	Timer timer; // ��ʱ�������ƶ�֡����
	Vector2 position; // �����ڴ����е���Ⱦλ��
	bool is_loop = true; // �����Ƿ�ѭ������
	size_t idx_frame = 0; // ��ǰ�������ŵ�֡����
	std::vector<Frame> frame_list; // ������������ÿһ֡��֡��Ϣ
	std::function<void()> on_finished; // ����������Ϻ�Ļص�����
	AnchorMode anchor_mode = AnchorMode::Centered; // ê��ģʽ
};
