#include "resources_manager.h"

ResourceManager* ResourceManager::manager = nullptr;

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
}

static inline bool check_image_valid(IMAGE* image)
{
	return GetImageBuffer(image);
}

ResourceManager::ResourceManager() = default;

ResourceManager::~ResourceManager() = default;

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

