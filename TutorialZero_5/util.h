#pragma once
#include <graphics.h>

#pragma comment(lib, "MSIMG32.LIB")		// AlphaBlend
#pragma comment(lib, "WINMM.LIB")		// mp3

struct Rect 
{
	int x, y;
	int w, h;
};

// 裁剪img任意大小的图并显示在任意处
	// src	裁剪
	// dst	缩放	
void putimage_ex(IMAGE* img, const Rect* rect_dst, const Rect* rect_src = nullptr)
{

	Rect src_{ 0, 0, img->getwidth(), img->getheight() };

	if (rect_src)
		src_ = *rect_src;

	// 将(src_x, src_y), w, h 的图像 复制到 (dst_x, dst_y)处
	AlphaBlend(GetImageHDC(GetWorkingImage()),
		rect_dst->x, rect_dst->y, rect_dst->w, rect_dst->h,
		GetImageHDC(img),
		src_.x, src_.y, src_.w, src_.h,
		{ AC_SRC_OVER, 0, 255, AC_SRC_ALPHA });
}

inline void load_audio(LPCTSTR path, LPCTSTR id)
{
	static TCHAR str_cmd[512];
	_stprintf_s(str_cmd, _T("open %s alias %s"), path, id);
	mciSendString(str_cmd, nullptr, 0, nullptr);
}

inline void play_audio(LPCTSTR id, bool is_loop = false)
{
	static TCHAR str_cmd[512];
	_stprintf_s(str_cmd, _T("play %s %s from 0"), id, is_loop ? _T("repeat") : _T(""));
	mciSendString(str_cmd, nullptr, 0, nullptr);
}

inline void stop_audio(LPCTSTR id)
{
	static TCHAR str_cmd[512];
	_stprintf_s(str_cmd, _T("stop %s"), id);
	mciSendString(str_cmd, nullptr, 0, nullptr);
}