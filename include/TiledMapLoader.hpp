#ifndef TILED_MAP_LOADER_H
#define TILED_MAP_LOADER_H

#include "Flexium.hpp"

#include <map>

/*
#include <map>

typedef std::map<std::string, std::string> PropertyList;

class Loader {

	public:

		class Rule {

		};

	private:

		std::map<std::string, Rule>

	public:


};
*/

class World;

struct SpawnInfo {

	Vector position;
	Vector dimensions;
	World * world;
	std::string name;

};

typedef std::map<std::string, void(*)(const SpawnInfo&) > RuleSet;

RuleSet& tiledMapRules();
void tiledMapLoad(const char * filename, World * world);



#endif