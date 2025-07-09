#pragma once
#include <graphics.h>
#include <vector>

class Atlas
{
public:
	Atlas() = default;
	~Atlas() = default;
public:
	void load(LPCTSTR path_template, int num)
	{
		img_list.clear();
		img_list.resize(num);

		TCHAR path_file[256];
		for (int i = 0; i < num; i++)
		{
			// 假设传进来的 path_template 是：_T("images\\enemy%d.png")
			// path_file 被格式化为 "images\enemy1.png", "images\enemy2.png", ......
			_stprintf_s(path_file, path_template, i + 1);
			// 把磁盘上的图片（路径是 path_file）加载到图像数组中的第 i 张图（img_list[i]）中
			loadimage(&img_list[i], path_file);
		}
	}

	void clear()
	{
		img_list.clear();
	}

	int get_size() const
	{
		return (int)img_list.size();
	}

	IMAGE* get_image(int idx)
	{
		if (idx < 0 || idx >= (int)img_list.size())
			return nullptr;
		return &img_list[idx];
	}

	void add_image(const IMAGE& img)
	{
		img_list.push_back(img);
	}

private:
	std::vector<IMAGE> img_list;
};
