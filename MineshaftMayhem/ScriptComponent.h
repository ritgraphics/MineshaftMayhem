#pragma once

#include <sol/sol.hpp>

class ScriptComponent
{
public:
    ScriptComponent(const char* bytes, size_t nBytes, sol::state& state, std::string entityName);

    void Tick();

private:
    sol::function m_updateFunc;
};
