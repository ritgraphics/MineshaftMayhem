#include "pch.h"
#include "ScriptComponent.h"

ScriptComponent::ScriptComponent(const char* bytes, size_t nBytes, sol::state& state, std::string entityName)
{
    //state.script(bytes);

    auto chunk_name = std::format("[string {}]", entityName);
    auto result = state.load_buffer(bytes, nBytes, chunk_name.c_str());
   
    //sol::load_result result = state.load_buffer(bytes, nBytes, {}, sol::load_mode::binary);
    //if (!result)
    //{
    //    throw std::runtime_error("Failed to load script");
    //}
    result();
    
    m_updateFunc = state["Tick"];
}


void ScriptComponent::Tick()
{
    m_updateFunc();
}