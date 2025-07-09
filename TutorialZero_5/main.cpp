#include <graphics.h>
#include <chrono>
#include <thread>

#include "util.h"
#include "resources_manager.h"


static void draw_background()
{
	static IMAGE* img_background = ResourceManager::get_instance()->find_image("background");
	// ����λ�ڱ���ͼ�м�
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
		_stprintf_s(err_msg, _T("�޷�����: %s"), id);
		MessageBox(hwnd, err_msg, _T("��Դ����ʧ��"), MB_OK | MB_ICONERROR);
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
			// ������Ϣ
		}

		steady_clock::time_point frame_start = steady_clock::now();
		duration<float> delta = duration<float>(frame_start - last_tick);

		// �������

		setbkcolor(RGB(0, 0, 0));
		cleardevice();

		// �����ͼ

		draw_background();

		FlushBatchDraw();

		last_tick = frame_start;
		nanoseconds sleep_duration = FPS - (steady_clock::now() - frame_start);
		if (sleep_duration > nanoseconds(0))
			std::this_thread::sleep_for(sleep_duration);
		/*
		����������ʲô��
			��ǰ֡�Ѿ�ִ����һЩ���루�����ͼ�ȣ�����ʱ�ǣ�now - frame_start

			����Ŀ��֡ʱ�䣨6.94ms�������ã���ֵ�ǣ�FPS - �Ѻ�ʱ

			�����û��Ŀ��ʱ�䣬�� sleep ��һ��, ÿ 6.94ms��144 ��/�룩Ҫˢ��һ�λ����Լ�һЩ����

			����Ͳ����ˣ�˵����һ̫֡����
		*/
	}

	EndBatchDraw();

	return 0;
}