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
			// ���贫������ path_template �ǣ�_T("images\\enemy%d.png")
			// path_file ����ʽ��Ϊ "images\enemy1.png", "images\enemy2.png", ......
			_stprintf_s(path_file, path_template, i + 1);
			// �Ѵ����ϵ�ͼƬ��·���� path_file�����ص�ͼ�������еĵ� i ��ͼ��img_list[i]����
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
