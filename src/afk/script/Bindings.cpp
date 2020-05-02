#include "Bindings.hpp"
extern "C" {
#include <lua/lauxlib.h>
#include <lua/lua.h>
#include <lua/lualib.h>
}
#include <LuaBridge/LuaBridge.h>

#include "afk/Afk.hpp"
#include "afk/asset/Asset.hpp"
#include "afk/asset/AssetFactory.hpp"
#include "afk/component/BaseComponent.hpp"
#include "afk/component/ScriptsComponent.hpp"
#include "afk/ecs/GameObject.hpp"
#include "afk/io/ModelSource.hpp"
#include "afk/physics/PhysicsBody.hpp"
#include "afk/physics/Transform.hpp"
#include "afk/renderer/Camera.hpp"
#include "afk/script/Script.hpp"

// todo move to keyboard mgmt
#include <GLFW/glfw3.h>

static auto get_camera() -> Afk::Camera & {
  return Afk::Engine::get().camera;
}

static auto new_vec3(float x, float y, float z) -> glm::vec3 {
  return glm::vec3{x, y, z};
}
static auto new_vec2(float x, float y) -> glm::vec2 {
  return glm::vec2{x, y};
}
static auto new_quat(float x, float y, float z, float w) -> glm::quat {
  return glm::quat{x, y, z, w};
}
static auto get_delta_time() -> float {
  return Afk::Engine::get().get_delta_time();
}

struct GameObjectWrapped {
  Afk::GameObject e;
  template<typename T>
  auto get_component() -> T * {
    return Afk::Engine::get().registry.try_get<T>(this->e);
  }
};

template<typename T>
static auto get_parent(T *bc) -> ENTT_ID_TYPE {
  return static_cast<ENTT_ID_TYPE>(bc->owning_entity);
}

static auto v3_add(glm::vec3 *a, glm::vec3 b) -> glm::vec3 {
  auto n = glm::vec3{*a};
  n += b;
  return n;
}
static auto v3_sub(glm::vec3 *a, glm::vec3 b) -> glm::vec3 {
  auto n = glm::vec3{*a};
  n -= b;
  return n;
}
static auto v3_mul(glm::vec3 *a, float f) -> glm::vec3 {
  auto n = glm::vec3{*a};
  n *= f;
  return n;
}
static auto v3_normal(glm::vec3 *a) -> glm::vec3 {
  return glm::normalize(*a);
}

// todo move to keyboard mgmt
static auto key_pressed(int key_code) -> bool {
  return glfwGetKey(Afk::Engine::get().renderer.window, key_code) == GLFW_PRESS;
}

static auto gameobject_get_entity(Afk::Asset::Asset *e) -> GameObjectWrapped {
  return GameObjectWrapped{std::get<Afk::Asset::Asset::Object>(e->data).ent};
}

static auto get_wireframe() -> bool {
  return Afk::Engine::get().renderer.get_wireframe();
}

static auto set_wireframe(bool b) -> void {
  Afk::Engine::get().renderer.set_wireframe(b);
}

using namespace luabridge;
auto Afk::add_engine_bindings(lua_State *lua) -> void {
  getGlobalNamespace(lua)
      .beginClass<glm::vec3>("vector3")
      .addStaticFunction("new", &new_vec3)
      .addData("x", &glm::vec3::x)
      .addData("y", &glm::vec3::y)
      .addData("z", &glm::vec3::z)
      .addFunction("normalized", &v3_normal)
      .addFunction("vec_add", &v3_add)
      .addFunction("vec_sub", &v3_sub)
      .addFunction("scalar_mul", &v3_mul)
      .endClass()

      .beginNamespace("math")
      .addFunction("clamp", &std::clamp<float>)
      .endNamespace()

      .beginClass<glm::vec2>("vector2")
      .addStaticFunction("new", &new_vec2)
      .addData("x", &glm::vec2::x)
      .addData("y", &glm::vec2::y)
      .endClass()

      .beginClass<glm::quat>("quaternion")
      .addStaticFunction("new", &new_quat)
      .addProperty("x", &glm::quat::x)
      .addProperty("y", &glm::quat::y)
      .addProperty("z", &glm::quat::y)
      .addProperty("w", &glm::quat::w)
      .endClass()

      .beginClass<Afk::Camera>("camera")
      .addStaticFunction("current", &get_camera)
      .addFunction("get_pos", &Afk::Camera::get_position)
      .addFunction("set_pos", &Afk::Camera::set_position)
      .addFunction("get_angle", &Afk::Camera::get_angles)
      .addFunction("set_angle", &Afk::Camera::set_angles)
      .addFunction("front", &Afk::Camera::get_front)
      .addFunction("right", &Afk::Camera::get_right)
      .addFunction("up", &Afk::Camera::get_up)
      .endClass()

      .beginClass<GameObjectWrapped>("entity")
      .addFunction("get_transform", &GameObjectWrapped::get_component<Transform>)
      .addFunction("get_physics", &GameObjectWrapped::get_component<PhysicsBody>)
      .addFunction("get_model", &GameObjectWrapped::get_component<ModelSource>)
      .addFunction("get_script", &GameObjectWrapped::get_component<ScriptsComponent>)
      .endClass()

      .beginClass<Afk::PhysicsBody>("physics_component")
      .addFunction("parent", &get_parent<Afk::PhysicsBody>)
      .addFunction("apply_force", &Afk::PhysicsBody::apply_force)
      .addFunction("apply_torque", &Afk::PhysicsBody::apply_torque)
      .addFunction("translate", &Afk::PhysicsBody::translate)
      .endClass()

      .beginClass<Afk::Transform>("transform_component")
      .addFunction("parent", &get_parent<Afk::Transform>)
      .addData("translation", &Afk::Transform::translation)
      .addData("rotation", &Afk::Transform::rotation)
      .addData("scale", &Afk::Transform::scale)
      .endClass()

      .beginClass<Afk::ScriptsComponent>("script_component")
      .addFunction("parent", &get_parent<Afk::ScriptsComponent>)
      .addFunction("add", &Afk::ScriptsComponent::add_script)
      .addFunction("remove", &Afk::ScriptsComponent::remove_script)
      .endClass()

      .beginClass<Afk::ModelSource>("model_component")
      .addFunction("parent", &get_parent<Afk::ModelSource>)
      .addData("name", &Afk::ModelSource::name)
      .endClass()

      .beginClass<Afk::BaseComponent>("component")
      .addFunction("parent", &get_parent<Afk::BaseComponent>)
      .endClass()

      .beginNamespace("keyboard")
      .addFunction("is_pressed", &key_pressed)
      .endNamespace()

      .beginClass<Afk::Asset::Asset>("asset")
      .addFunction("unwrap", &gameobject_get_entity)
      .endClass()

      .beginNamespace("engine")
      .addFunction("delta_time", &get_delta_time)
      .addFunction("load_asset", &Afk::Asset::game_asset_factory)
      .addProperty("wireframe", &get_wireframe, &set_wireframe)
      .endNamespace();

  auto key_ns = luabridge::getGlobalNamespace(lua).beginNamespace("key");
  for (const auto &key : Afk::Script::keys) {
    // key.code can't be changed from lua's side
    key_ns.addVariable<int>(key.name.c_str(), const_cast<int *>(&key.code), false);
  }
  key_ns.endNamespace();

  auto mouse_ns = luabridge::getGlobalNamespace(lua).beginNamespace("mouse");
  for (const auto &mouse_button : Afk::Script::mouse_buttons) {
    mouse_ns.addVariable<int>(mouse_button.name.c_str(),
                              const_cast<int *>(&mouse_button.button), false);
  }
  mouse_ns.endNamespace();

  luabridge::getGlobalNamespace(lua)
      .beginNamespace("events")
      .beginClass<Afk::Event::Key>("key")
      .addData("alt", &Afk::Event::Key::alt, false)
      .addData("control", &Afk::Event::Key::control, false)
      .addData("shift", &Afk::Event::Key::shift, false)
      .addData("key", &Afk::Event::Key::key, false)
      .addData("key_code", &Afk::Event::Key::scancode, false)
      .endClass()
      .beginClass<Afk::Event::MouseMove>("mouse_move")
      .addData("x", &Afk::Event::MouseMove::x, false)
      .addData("y", &Afk::Event::MouseMove::y, false)
      .endClass()
      .beginClass<Afk::Event::MouseButton>("mouse_button")
      .addData("alt", &Afk::Event::MouseButton::alt, false)
      .addData("control", &Afk::Event::MouseButton::control, false)
      .addData("shift", &Afk::Event::MouseButton::shift, false)
      .addData("button", &Afk::Event::MouseButton::button, false)
      .endClass()
      .beginClass<Afk::Event::MouseScroll>("mouse_scroll")
      .addData("x", &Afk::Event::MouseScroll::x, false)
      .addData("y", &Afk::Event::MouseScroll::y, false)
      .endClass()
      .beginClass<Afk::Event::Text>("text")
      .addData("codepoint", &Afk::Event::Text::codepoint, false)
      .endClass()
      .beginClass<Afk::Event::Update>("update")
      .addData("delta", &Afk::Event::Update::dt, false)
      .endClass()
      .endNamespace();

  auto afk_event_class =
      luabridge::getGlobalNamespace(lua).beginClass<Afk::Event>("event");
  for (const auto &event : Afk::Script::events) {
    afk_event_class.addStaticData<int>(event.name.c_str(),
                                       const_cast<int *>(&event.type), false);
  }
  afk_event_class.addFunction("to_key", &Afk::Event::get<Afk::Event::Key>);
  afk_event_class.addFunction("to_mouse_move", &Afk::Event::get<Afk::Event::MouseMove>);
  afk_event_class.addFunction("to_mouse_button", &Afk::Event::get<Afk::Event::MouseButton>);
  afk_event_class.addFunction("to_mouse_scroll", &Afk::Event::get<Afk::Event::MouseScroll>);
  afk_event_class.addFunction("to_text", &Afk::Event::get<Afk::Event::Text>);
  afk_event_class.addFunction("to_update", &Afk::Event::get<Afk::Event::Update>);
  afk_event_class.endClass();

  auto script_class = luabridge::getGlobalNamespace(lua)
                          .beginClass<LuaScript>("__AFK__SCRIPT")
                          .addFunction("register_event", &Afk::LuaScript::register_fn)
                          .endClass();
}
