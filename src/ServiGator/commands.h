#pragma once

#include "json.hpp"

#include <memory>

void ProcessCommand(std::shared_ptr<nlohmann::json> cmd);
