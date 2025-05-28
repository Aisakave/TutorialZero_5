#pragma once
#include "atlas.h"
#include "util.h"
#include <string>
#include <unordered_map>
#include <graphics.h>

class ResourceManager
{
public:
	static ResourceManager* get_instance();

	void load();

	Atlas* find_atlas(const std::string& id) const;
	IMAGE* find_image(const std::string& id) const;

private:
	static ResourceManager* manager;

	std::unordered_map<std::string, Atlas*> atlas_pool;
	std::unordered_map<std::string, IMAGE*> image_pool;

private:
	ResourceManager();
	~ResourceManager();

	void flip_image(IMAGE* src_image, IMAGE* dst_image, int num_h = 1);
	void flip_image(const std::string& src_id, const std::string& dst_id, int num_h = 1);
	void flip_atlas(const std::string& src_id, const std::string& dst_id);

};