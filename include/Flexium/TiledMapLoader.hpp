#ifndef TILED_MAP_LOADER_H
#define TILED_MAP_LOADER_H

#include <Flexium/Flexium.hpp>

#include <map>

namespace flx {

	class World;

	struct SpawnInfo {

		Vector position;
		Vector dimensions;
		World * world;
		std::string name;
		std::map<std::string, std::string> parameters;

	};

	typedef std::map<std::string, void(*)(const SpawnInfo&) > RuleSet;

	RuleSet& tiledMapRules();
	void tiledMapLoad(const char * filename, World * world);

}

#endif