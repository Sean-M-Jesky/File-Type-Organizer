#pragma once
//"fsHelper.h"
#pragma once
#include <vector>
#include <filesystem>
namespace fs = std::filesystem;
typedef fs::path element_t;


const std::vector<element_t> collect_relivant_files(const std::vector<element_t>& directory);

const std::vector<element_t> collect_relivant_files(const element_t& directory); //idk yet...

void create_directory_from_extension_type(const element_t base_save_location, const element_t curr_extension);
