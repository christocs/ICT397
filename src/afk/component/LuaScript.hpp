#pragma once

#include <filesystem>
#include <string>
extern "C" {
#include <lua/lauxlib.h>
#include <lua/lua.h>
#include <lua/lualib.h>
}
#include <LuaBridge/LuaBridge.h>

#include "afk/event/Event.hpp"
#include "afk/event/EventManager.hpp"

using luabridge::LuaRef;

namespace Afk {
  // Script needs to remember what calls it has registered to the event manager
  // so it can get rid of them later
  struct RegisteredLuaCall {
    Afk::Event::Type event_type;
    Afk::EventManager::Callback callback;
  };

  class LuaScript {
  public:
    LuaScript(EventManager *events);
    // required for luabridge to work
    LuaScript(const LuaScript &other);
    LuaScript(LuaScript &&other);
    // required for luabridge to work
    auto operator=(const LuaScript &other) -> LuaScript &;
    auto operator=(LuaScript &&other) -> LuaScript &;
    ~LuaScript();
    auto load(const std::filesystem::path &filename, lua_State *lua) -> void;
    auto unload() -> void;
    static auto setup_lua_state(lua_State *lua) -> void;

  private:
    /**
     * Allows script to register its functions into the event system
     */
    auto register_fn(int event_val, LuaRef func) -> void;
    EventManager *event_manager;
    std::shared_ptr<std::vector<RegisteredLuaCall>> registered_events;
  };
}
