#include "pch.h"
#include "Level.h"

#include <pugixml.hpp>


#include "File.h"
#include "ScriptComponent.h"

struct NameComponent
{
    std::string name;
};

namespace
{

}

void CustomPrint(std::string text)
{
    auto formatted = std::format("{}\n", text);
    OutputDebugStringA(formatted.c_str());
}

Level::Level(const uint8_t* pBytes, size_t nBytes)
{
    m_luaState.open_libraries();

    m_luaState.set_function("CustomPrint", &CustomPrint);

    pugi::xml_document     doc;
    pugi::xml_parse_result result = doc.load_buffer(pBytes, nBytes);
    if (!result)
    {
        throw std::runtime_error("Failed to parse level");
    }

    for (pugi::xml_node entity_node : doc.child("level").children("entity"))
    {
        auto entity = m_enttRegistry.create();

        auto name = entity_node.attribute("name").as_string();
        m_enttRegistry.emplace<NameComponent>(entity, name);

        ParseEntityComponents(entity_node, entity);
    }

    auto view = m_enttRegistry.view<NameComponent>();
    for (auto entity : view)
    {
        const auto& name = view.get<NameComponent>(entity).name;
        const auto  name_formatted = std::format("{} \n", name);
        OutputDebugStringA(name_formatted.c_str());
    }
}

Level::~Level()
{
    m_enttRegistry.clear();
}

void Level::Update()
{
    auto view = m_enttRegistry.view<ScriptComponent>();
    for (auto entity : view)
    {
        auto& script = view.get<ScriptComponent>(entity);
        script.Tick();
    }
}

void Level::ParseEntityComponents(const pugi::xml_node& entity_node, entt::entity entity)
{
    for (pugi::xml_node component : entity_node.child("components").children())
    {
        if (!strcmp(component.name(), "script"))
        {
            const auto& filePath = component.attribute("file").as_string();

            try
            {
                File file(filePath);

                auto view = m_enttRegistry.view<NameComponent>();

                const auto bytes = file.ReadAll();
                m_enttRegistry.emplace<ScriptComponent>(entity, (const char*)bytes.data(), bytes.size(), m_luaState,
                                                        view.get<NameComponent>(entity).name);
            }
            catch (const std::exception& e)
            {
                OutputDebugStringA(e.what());
            }
        }
    }
}