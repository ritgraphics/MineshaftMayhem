#pragma once

#include <entt/entt.hpp>
#include <pugixml.hpp>
#include <sol/sol.hpp>

class Level
{
public:
    explicit Level(const uint8_t* pBytes, size_t nBytes);

    ~Level();

    void Update();


private:
    entt::registry m_enttRegistry;
    sol::state     m_luaState;

    void ParseEntityComponents(const pugi::xml_node& entity_node, entt::entity entity);
};
