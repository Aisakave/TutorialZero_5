#include "resources_manager.h"

ResourceManager* ResourceManager::manager = nullptr;

struct ImageResInfo
{
	std::string id;
	LPCTSTR path;
};

struct AtlasResInfo
{
	std::string id;
	LPCTSTR path;
	int num_frame = 0;
};

// 添加图片信息列表的定义
static const std::vector<ImageResInfo> image_info_list =
{

	// R标记表示原始字符串，就不用对字符串的反斜线进行转义处理了

	{ "background",					_T(R"(resources\background.png)") },

	{ "ui_heart",					_T(R"(resources\ui_heart.png)")},



	{ "player_attack_right",		_T(R"(resources\player\attack.png)")},

	{ "player_dead_right",			_T(R"(resources\player\dead.png)")},

	{ "player_fall_right",			_T(R"(resources\player\fall.png)")},

	{ "player_idle_right",			_T(R"(resources\player\idle.png)")},

	{ "player_jump_right",			_T(R"(resources\player\jump.png)")},

	{ "player_run_right",			_T(R"(resources\player\run.png)")},

	{ "player_roll_right",			_T(R"(resources\player\roll.png)")},



	{ "player_vfx_attack_down",		_T(R"(resources\player\vfx_attack_down.png)")},

	{ "player_vfx_attack_left",		_T(R"(resources\player\vfx_attack_left.png)")},

	{ "player_vfx_attack_right",	_T(R"(resources\player\vfx_attack_right.png)")},

	{ "player_vfx_attack_up",		_T(R"(resources\player\vfx_attack_up.png)")},

	{ "player_vfx_jump",			_T(R"(resources\player\vfx_jump.png)")},

	{ "player_vfx_land",			_T(R"(resources\player\vfx_land.png)")},

};

// 添加图集信息列表的定义
static const std::vector<AtlasResInfo> atlas_info_list =
{

	{ "barb_break",					_T(R"(resources\enemy\barb_break\%d.png)"),	3},

	{ "barb_loose",					_T(R"(resources\enemy\barb_loose\%d.png)"),	5},

	{ "silk",						_T(R"(resources\enemy\silk\%d.png)"),		9},

	{ "sword_left",					_T(R"(resources\enemy\sword\%d.png)"),		3},



	{ "enemy_aim_left",				_T(R"(resources\enemy\aim\%d.png)"),			9 },

	{ "enemy_dash_in_air_left",		_T(R"(resources\enemy\dash_in_air\%d.png)"),	2 },

	{ "enemy_dash_on_floor_left",	_T(R"(resources\enemy\dash_on_floor\%d.png)"),	2 },

	{ "enemy_fall_left",			_T(R"(resources\enemy\fall\%d.png)"),			4 },

	{ "enemy_idle_left",			_T(R"(resources\enemy\idle\%d.png)"),			6 },

	{ "enemy_jump_left",			_T(R"(resources\enemy\jump\%d.png)"),			8 },

	{ "enemy_run_left",				_T(R"(resources\enemy\run\%d.png)"),			8 },

	{ "enemy_squat_left",			_T(R"(resources\enemy\squat\%d.png)"),			10},

	{ "enemy_throw_barb_left",		_T(R"(resources\enemy\throw_barb\%d.png)"),		8 },

	{ "enemy_throw_silk_left",		_T(R"(resources\enemy\throw_silk\%d.png)"),		17},

	{ "enemy_throw_sword_left",		_T(R"(resources\enemy\throw_sword\%d.png)"),	16},



	{ "enemy_vfx_dash_in_air_left",		_T(R"(resources\enemy\vfx_dash_in_air\%d.png)"),	5},

	{ "enemy_vfx_dash_on_floor_left",	_T(R"(resources\enemy\vfx_dash_on_floor\%d.png)"),	6},

};

static inline bool check_image_valid(IMAGE* image)
{
	return GetImageBuffer(image);
}

ResourceManager* ResourceManager::get_instance()
{
	if (manager == nullptr)
	{
		manager = new ResourceManager();
	}
	return manager;
}

void ResourceManager::load()
{
	for (const auto& info : image_info_list)
	{
		IMAGE* image = new IMAGE();
		loadimage(image, info.path);
		if (!check_image_valid(image))
			throw info.path;
		image_pool[info.id] = image;
	}

	for (const auto& info : atlas_info_list)
	{
		Atlas* atlas = new Atlas();
		atlas->load(info.path, info.num_frame);
		for (int i = 0; i < atlas->get_size(); i++)
		{
			IMAGE* image = atlas->get_image(i);
			if (!check_image_valid(image))
				throw info.path;
		}
		atlas_pool[info.id] = atlas;
	}	

	// 翻转图片
	flip_image("player_attack_right", "player_attack_left", 5);

	flip_image("player_dead_right", "player_dead_left", 6);

	flip_image("player_fall_right", "player_fall_left", 5);

	flip_image("player_idle_right", "player_idle_left", 5);

	flip_image("player_jump_right", "player_jump_left", 5);

	flip_image("player_run_right", "player_run_left", 10);

	flip_image("player_roll_right", "player_roll_left", 7);



	flip_atlas("sword_left", "sword_right");

	flip_atlas("enemy_aim_left", "enemy_aim_right");

	flip_atlas("enemy_dash_in_air_left", "enemy_dash_in_air_right");

	flip_atlas("enemy_dash_on_floor_left", "enemy_dash_on_floor_right");

	flip_atlas("enemy_fall_left", "enemy_fall_right");

	flip_atlas("enemy_idle_left", "enemy_idle_right");

	flip_atlas("enemy_jump_left", "enemy_jump_right");

	flip_atlas("enemy_run_left", "enemy_run_right");

	flip_atlas("enemy_squat_left", "enemy_squat_right");

	flip_atlas("enemy_throw_barb_left", "enemy_throw_barb_right");

	flip_atlas("enemy_throw_silk_left", "enemy_throw_silk_right");

	flip_atlas("enemy_throw_sword_left", "enemy_throw_sword_right");



	flip_atlas("enemy_vfx_dash_in_air_left", "enemy_vfx_dash_in_air_right");

	flip_atlas("enemy_vfx_dash_on_floor_left", "enemy_vfx_dash_on_floor_right");

	load_audio(_T(R"(resources\audio\bgm.mp3)"), _T("bgm"));

	load_audio(_T(R"(resources\audio\barb_break.mp3)"), _T("barb_break"));

	load_audio(_T(R"(resources\audio\bullet_time.mp3)"), _T("bullet_time"));

	load_audio(_T(R"(resources\audio\enemy_dash.mp3)"), _T("enemy_dash"));

	load_audio(_T(R"(resources\audio\enemy_run.mp3)"), _T("enemy_run"));

	load_audio(_T(R"(resources\audio\enemy_hurt_1.mp3)"), _T("enemy_hurt_1"));

	load_audio(_T(R"(resources\audio\enemy_hurt_2.mp3)"), _T("enemy_hurt_2"));

	load_audio(_T(R"(resources\audio\enemy_hurt_3.mp3)"), _T("enemy_hurt_3"));

	load_audio(_T(R"(resources\audio\enemy_throw_barbs.mp3)"), _T("enemy_throw_barbs"));

	load_audio(_T(R"(resources\audio\enemy_throw_silk.mp3)"), _T("enemy_throw_silk"));

	load_audio(_T(R"(resources\audio\enemy_throw_sword.mp3)"), _T("enemy_throw_sword"));

	load_audio(_T(R"(resources\audio\player_attack_1.mp3)"), _T("player_attack_1"));

	load_audio(_T(R"(resources\audio\player_attack_2.mp3)"), _T("player_attack_2"));

	load_audio(_T(R"(resources\audio\player_attack_3.mp3)"), _T("player_attack_3"));

	load_audio(_T(R"(resources\audio\player_dead.mp3)"), _T("player_dead"));

	load_audio(_T(R"(resources\audio\player_hurt.mp3)"), _T("player_hurt"));

	load_audio(_T(R"(resources\audio\player_jump.mp3)"), _T("player_jump"));

	load_audio(_T(R"(resources\audio\player land.mp3)"), _T("player_land"));

	load_audio(_T(R"(resources\audio\player_roll.mp3)"), _T("player_roll"));

	load_audio(_T(R"(resources\audio\player_run.mp3)"), _T("player_run"));


}

Atlas* ResourceManager::find_atlas(const std::string& id) const
{
	const auto& it = atlas_pool.find(id);
	if (it == atlas_pool.end())
		return nullptr;

	return it->second;
}

IMAGE* ResourceManager::find_image(const std::string& id) const
{
	const auto& it = image_pool.find(id);
	if (it == image_pool.end())
		return nullptr;

	return it->second;
}

ResourceManager::ResourceManager() = default;

ResourceManager::~ResourceManager() = default;

// 定义处不带默认值默认参数只能在声明（.h）文件中指定一次, 所以这里不能写成 int num_h = 1
// 在定义（.cpp）文件中再写默认参数会被认为是“重定义”，导致 C2572 编译错误

void ResourceManager::flip_image(IMAGE* src_image, IMAGE* dst_image, int num_h)
{
	int w = src_image->getwidth();
	int h = src_image->getheight();
	int w_frame = w / num_h;

	Resize(dst_image, w, h); // 保留整张图大小

	DWORD* src_buffer = (DWORD*)GetImageBuffer(src_image);
	DWORD* dst_buffer = (DWORD*)GetImageBuffer(dst_image);

	for (int i = 0; i < num_h; i++)
	{
		int x_left = i * w_frame;
		int x_right = (i + 1) * w_frame;

		for (int y = 0; y < h; y++)
		{
			for (int x = x_left; x < x_right; x++)
			{
				int idx_src = y * w + x;
				int idx_dst = y * w + (x_right - 1 - (x - x_left)); // 修正越界
				dst_buffer[idx_dst] = src_buffer[idx_src];
			}
		}
	}
}


void ResourceManager::flip_image(const std::string& src_id, const std::string& dst_id, int num_h)
{
	IMAGE* src_image = image_pool[src_id];
	IMAGE* dst_image = new IMAGE();

	flip_image(src_image, dst_image, num_h);

	image_pool[dst_id] = dst_image;
}

void ResourceManager::flip_atlas(const std::string& src_id, const std::string& dst_id)
{
	Atlas* src_atlas = atlas_pool[src_id];
	Atlas* dst_atlas = new Atlas();

	for (int i = 0; i < src_atlas->get_size(); i++)
	{
		IMAGE img_flipped;
		flip_image(src_atlas->get_image(i), &img_flipped);
		dst_atlas->add_image(img_flipped);
	}
	atlas_pool[dst_id] = dst_atlas;
}





