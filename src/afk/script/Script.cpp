#include "afk/script/Script.hpp"

#include <GLFW/glfw3.h>

#include "afk/event/Event.hpp"

using Afk::Event;
using Afk::Script;
using std::vector;

const vector<Script::Event> Script::events = {
    {"key_down", static_cast<int>(::Afk::Event::Type::KeyDown)},
    {"key_up", static_cast<int>(::Afk::Event::Type::KeyUp)},
    {"mouse_down", static_cast<int>(::Afk::Event::Type::MouseDown)},
    {"mouse_up", static_cast<int>(::Afk::Event::Type::MouseUp)},
    {"mouse_move", static_cast<int>(::Afk::Event::Type::MouseMove)},
    {"mouse_scroll", static_cast<int>(::Afk::Event::Type::MouseScroll)},
    {"text_enter", static_cast<int>(::Afk::Event::Type::TextEnter)},
    {"update", static_cast<int>(::Afk::Event::Type::Update)},
    {"render", static_cast<int>(::Afk::Event::Type::Render)},
    {"collision", static_cast<int>(::Afk::Event::Type::Collision)}
};

const vector<Script::Mouse> Script::mouse_buttons = {
    {"left", GLFW_MOUSE_BUTTON_1},    {"right", GLFW_MOUSE_BUTTON_2},
    {"middle", GLFW_MOUSE_BUTTON_3},  {"mouse_4", GLFW_MOUSE_BUTTON_4},
    {"mouse_5", GLFW_MOUSE_BUTTON_5}, {"mouse_6", GLFW_MOUSE_BUTTON_6},
    {"mouse_7", GLFW_MOUSE_BUTTON_7}, {"mouse_8", GLFW_MOUSE_BUTTON_8},
};

const vector<Script::Key> Script::keys = {
    {"A", GLFW_KEY_A},
    {"B", GLFW_KEY_B},
    {"C", GLFW_KEY_C},
    {"D", GLFW_KEY_D},
    {"E", GLFW_KEY_E},
    {"F", GLFW_KEY_F},
    {"G", GLFW_KEY_G},
    {"H", GLFW_KEY_H},
    {"I", GLFW_KEY_I},
    {"J", GLFW_KEY_J},
    {"K", GLFW_KEY_K},
    {"L", GLFW_KEY_L},
    {"M", GLFW_KEY_M},
    {"N", GLFW_KEY_N},
    {"O", GLFW_KEY_O},
    {"P", GLFW_KEY_P},
    {"Q", GLFW_KEY_Q},
    {"R", GLFW_KEY_R},
    {"S", GLFW_KEY_S},
    {"T", GLFW_KEY_T},
    {"U", GLFW_KEY_U},
    {"V", GLFW_KEY_V},
    {"W", GLFW_KEY_W},
    {"X", GLFW_KEY_X},
    {"Y", GLFW_KEY_Y},
    {"Z", GLFW_KEY_Z},
    {"Num0", GLFW_KEY_0},
    {"Num1", GLFW_KEY_1},
    {"Num2", GLFW_KEY_2},
    {"Num3", GLFW_KEY_3},
    {"Num4", GLFW_KEY_4},
    {"Num5", GLFW_KEY_5},
    {"Num6", GLFW_KEY_6},
    {"Num7", GLFW_KEY_7},
    {"Num8", GLFW_KEY_8},
    {"Num9", GLFW_KEY_9},
    {"Escape", GLFW_KEY_ESCAPE},
    {"LControl", GLFW_KEY_LEFT_CONTROL},
    {"LShift", GLFW_KEY_LEFT_SHIFT},
    {"LAlt", GLFW_KEY_LEFT_ALT},
    {"LSystem", GLFW_KEY_LEFT_SUPER},
    {"RControl", GLFW_KEY_RIGHT_CONTROL},
    {"RShift", GLFW_KEY_RIGHT_SHIFT},
    {"RAlt", GLFW_KEY_RIGHT_ALT},
    {"RSystem", GLFW_KEY_RIGHT_SUPER},
    {"Menu", GLFW_KEY_MENU},
    {"LBracket", GLFW_KEY_LEFT_BRACKET},
    {"RBracket", GLFW_KEY_RIGHT_BRACKET},
    {"Semicolon", GLFW_KEY_SEMICOLON},
    {"Comma", GLFW_KEY_COMMA},
    {"Period", GLFW_KEY_PERIOD},
    {"Quote", GLFW_KEY_APOSTROPHE},
    {"Slash", GLFW_KEY_SLASH},
    {"Backslash", GLFW_KEY_BACKSLASH},
    {"Tilde", GLFW_KEY_GRAVE_ACCENT},
    {"Equal", GLFW_KEY_EQUAL},
    {"Hyphen", GLFW_KEY_MINUS},
    {"Space", GLFW_KEY_SPACE},
    {"Enter", GLFW_KEY_ENTER},
    {"Backspace", GLFW_KEY_BACKSPACE},
    {"Tab", GLFW_KEY_TAB},
    {"PageUp", GLFW_KEY_PAGE_UP},
    {"PageDown", GLFW_KEY_PAGE_DOWN},
    {"End", GLFW_KEY_END},
    {"Home", GLFW_KEY_HOME},
    {"Insert", GLFW_KEY_INSERT},
    {"Delete", GLFW_KEY_DELETE},
    {"NpAdd", GLFW_KEY_KP_ADD},
    {"NpSubtract", GLFW_KEY_KP_SUBTRACT},
    {"NpMultiply", GLFW_KEY_KP_MULTIPLY},
    {"NpDivide", GLFW_KEY_KP_DIVIDE},
    {"Left", GLFW_KEY_LEFT},
    {"Right", GLFW_KEY_RIGHT},
    {"Up", GLFW_KEY_UP},
    {"Down", GLFW_KEY_DOWN},
    {"Numpad0", GLFW_KEY_KP_0},
    {"Numpad1", GLFW_KEY_KP_1},
    {"Numpad2", GLFW_KEY_KP_2},
    {"Numpad3", GLFW_KEY_KP_3},
    {"Numpad4", GLFW_KEY_KP_4},
    {"Numpad5", GLFW_KEY_KP_5},
    {"Numpad6", GLFW_KEY_KP_6},
    {"Numpad7", GLFW_KEY_KP_7},
    {"Numpad8", GLFW_KEY_KP_8},
    {"Numpad9", GLFW_KEY_KP_9},
    {"F1", GLFW_KEY_F1},
    {"F2", GLFW_KEY_F2},
    {"F3", GLFW_KEY_F3},
    {"F4", GLFW_KEY_F4},
    {"F5", GLFW_KEY_F5},
    {"F6", GLFW_KEY_F6},
    {"F7", GLFW_KEY_F7},
    {"F8", GLFW_KEY_F8},
    {"F9", GLFW_KEY_F9},
    {"F10", GLFW_KEY_F10},
    {"F11", GLFW_KEY_F11},
    {"F12", GLFW_KEY_F12},
    {"F13", GLFW_KEY_F13},
    {"F14", GLFW_KEY_F14},
    {"F15", GLFW_KEY_F15},
    {"Pause", GLFW_KEY_PAUSE},
};
