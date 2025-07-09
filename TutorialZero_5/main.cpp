#include <graphics.h>
#include <chrono>
#include <thread>

#include "util.h"
#include "resources_manager.h"


static void draw_background()
{
	static IMAGE* img_background = ResourceManager::get_instance()->find_image("background");
	// 窗口位于背景图中间
	static Rect rect_dst =
	{
		(getwidth() - img_background->getwidth()) / 2,
		(getheight() - img_background->getheight()) / 2,
		img_background->getwidth(),
		img_background->getheight()
	};
	putimage_ex(img_background, &rect_dst);
}

int main(int argc, char** argv)
{
	using namespace std::chrono;

	HWND hwnd = initgraph(1280, 720, EW_SHOWCONSOLE);
	SetWindowText(hwnd, _T("Hollow katana"));

	try
	{
		ResourceManager::get_instance()->load();
	}
	catch (const LPCTSTR id)
	{
		TCHAR err_msg[512];
		_stprintf_s(err_msg, _T("无法加载: %s"), id);
		MessageBox(hwnd, err_msg, _T("资源加载失败"), MB_OK | MB_ICONERROR);
		return -1;
	}

	const nanoseconds FPS(1000000000 / 144);
	steady_clock::time_point last_tick = steady_clock::now();

	ExMessage msg;
	bool is_quit = false;

	BeginBatchDraw();

	while (!is_quit)
	{
		while (peekmessage(&msg))
		{
			// 处理消息
		}

		steady_clock::time_point frame_start = steady_clock::now();
		duration<float> delta = duration<float>(frame_start - last_tick);

		// 处理更新

		setbkcolor(RGB(0, 0, 0));
		cleardevice();

		// 处理绘图

		draw_background();

		FlushBatchDraw();

		last_tick = frame_start;
		nanoseconds sleep_duration = FPS - (steady_clock::now() - frame_start);
		if (sleep_duration > nanoseconds(0))
			std::this_thread::sleep_for(sleep_duration);
		/*
		这三行做了什么？
			当前帧已经执行了一些代码（处理绘图等），耗时是：now - frame_start

			距离目标帧时间（6.94ms）还差多久？差值是：FPS - 已耗时

			如果还没到目标时间，就 sleep 等一等, 每 6.94ms（144 次/秒）要刷新一次画面以及一些处理

			否则就不等了（说明这一帧太慢）
		*/
	}

	EndBatchDraw();

	return 0;
}