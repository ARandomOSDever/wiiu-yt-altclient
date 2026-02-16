#include <nlohmann/json.hpp>

using json = nlohmann::json;

json defaultConfig{
    {"theme", "dark"},
    {"lang", "en"},
    {"apdOverride", 0},
    {"brightnessOverride", -1}
};