//"fsHelper.cpp"
#include "fsHelper.h"
#include <iostream>
#include <vector>
#include <filesystem>
namespace fs = std::filesystem;
typedef fs::path element_t;
#include <cmath>

/// @brief collect all filenames and their paths from the Source location provided by the user to use within the rest of the program.
/// @param const fs::path == element_t, directory location to search for filenames, and the data associated with their use within the program
/// @return const inline vector<element_t>
/// multi-variable [directory(s) with files to copy] function overload
const std::vector<element_t> collect_relivant_files(const std::vector<element_t>& directory)
{
	std::vector<element_t> vfiles; //= new std::vector<element_t>;
	vfiles.reserve(500'000);
	try {
		for (auto dir_iter : directory) {
			for (const fs::directory_entry& dir : fs::recursive_directory_iterator{ dir_iter , fs::directory_options::skip_permission_denied })
			{
				const element_t& file_path = dir;
				const element_t* file_path_p = &file_path;

				if (!fs::is_directory(*file_path_p))
				{
					if (file_path_p->has_extension())
					{
						vfiles.push_back(*file_path_p);
					}
				}
			}
		}
	}
	catch (std::filesystem::filesystem_error& err) {
		std::cout << "Filesys error" << "\n" << err.what() << std::endl;
	}
	return vfiles; //this is. mistake, its not cleaned up (now fixed though), if the vector was stack allocated it woulbe but by using new, im responsible if i use new, to use delete |||||| this should be deleted by RAII (Resource aq. is initialization.. what a bad name) anyways, it should be deleted at the end of scope so no leaks should be happening.
}

//single variable [directory with files to copy] function overload
const std::vector<element_t> collect_relivant_files(const element_t& directory) {

	std::vector<element_t> vfiles; //= new std::vector<element_t>;
	vfiles.reserve(50'000);	//50k is a thought out value for general inputs, change if your requirements are specific each time otherwise if required.
	try {
		for (const fs::directory_entry& dir : fs::recursive_directory_iterator{ directory, fs::directory_options::skip_permission_denied })
		{
			const element_t& file_path = dir;
			const element_t* file_path_p = &file_path;

			if (!fs::is_directory(*file_path_p))
			{
				if (file_path_p->has_extension() && fs::exists(*file_path_p))
				{
					vfiles.push_back(*file_path_p);
				}
			}
		}
	}
	catch (std::filesystem::filesystem_error& err) {
		std::cout << "Filesys error" << "\n" << err.what() << std::endl;
	}
	return vfiles; //fixed this memory leak ignore comment -> this should be deleted by RAII (Resource aq. is initialization.. what a bad name) anyways, it should be deleted at the end of scope so no leaks should be happening.
}
/// @brief create a directorys from the extensions of the files collected from earlier.
/// @param const element_t base_save_location -  destination location; where to save folders, and files.
/// @param const vector<element_t>* extensions - a vector of pointers to a vector of extension types collected from the files
void create_directory_from_extension_type(const element_t base_save_location, const element_t curr_extension)
{
	fs::create_directory((base_save_location.string()) + curr_extension.string().erase(0, 1));
	//std::cout << "\n";
       	//std::cout << "[!] We are currently working on: " << curr_extension.string() << " type files from data collected: ";
}
