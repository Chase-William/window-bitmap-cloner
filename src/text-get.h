#pragma once

#include <vector>
#include <string>
#include "types.h"

std::tuple<std::vector<Sector *>, Error *> Scan(const char *source, const char *tessData, std::vector<Sector *> sectors);