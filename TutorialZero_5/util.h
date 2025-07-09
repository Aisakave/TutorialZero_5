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
inline void putimage_ex(IMAGE* img, const Rect* rect_dst, const Rect* rect_src = nullptr)
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

/*
一、inline 的本意：内联函数
最早 inline 的设计目的是让函数的代码在编译时被“展开”到调用处，而不是像普通函数那样跳转调用，目的是提高执行效率，尤其用于短小函数：
inline int add(int a, int b) {
	return a + b;
}
如果你写了：
int x = add(2, 3);
编译器可能就会直接变成：
int x = 2 + 3;  // 编译器内联展开了函数
不过现在现代编译器会自动决定是否内联，你写了 inline 它不一定真的内联，你不写它也可能会内联，所以：

inline 的实际用处已经不是为了“展开调用”，而是为了-> “允许在头文件中定义函数”。

二、为什么头文件中定义函数会报错？
因为如果你在.h 文件里直接写函数实现：
// utils.h
void say_hi() {
	std::cout << "hi\n";
}
如果多个.cpp 文件都 #include "utils.h"，那么 say_hi 会在多个.obj 文件中各生成一份定义，链接器报错：
LNK2005 : 函数重复定义

三、什么时候需要加 inline？
在头文件中定义函数实现时加 inline，避免重复定义错误。
// utils.h
#pragma once
#include <iostream>

inline void say_hi() {
	std::cout << "hi\n";
}
这样即使多个.cpp 文件包含这个头文件，也不会重复定义。
*/