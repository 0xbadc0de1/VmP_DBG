#ifndef TYPES_H
#define TYPES_H
#include <tchar.h>
#include <string>
#include <vector>
#include <string>
#include <stdint.h>
#include <unordered_map>

typedef std::vector<std::string> type_handler;
typedef std::tuple<type_handler, std::vector<uint32_t>> hashmap;
#endif // TYPES_H

