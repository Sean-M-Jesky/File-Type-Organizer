#pragma once
//"linked_list.h"
#pragma once
#include <iostream>
#include <vector>
#include <filesystem>
namespace fs = std::filesystem;
typedef fs::path element_t;
#include <string>
using std::string;
#include <iostream>
#include <algorithm>
///     TODO:
/// add Linux and Apple API librarys, & write sections for Linux, Windows, & Apple products 
/// for everything else, the standard - Windows Specific API only; currenty, TBW (To Be Written): 1/18/2024
#if _WIN64
#include <Windows.h>
//for cross compiling code to be used from wine or otherwise to be used on windows but only compiled on linux:
//#include "/usr/share/mingw-w64/include/windows.h"
#define WIN64_LEAN_AND_MEAN
#elif _WIN32
#include <Windows.h>
//#include "/usr/share/mingw-w64/include/windows.h"
#define WIN32_LEAN_AND_MEAN
#endif
#include "fsHelper.h" 				//filesystem helper functions used within the program and linked list

struct copy_conditions {

	enum copy_condition {
		keep_copies = true,
		keep_no_copies = false
	};
};

struct LINKED_LIST_DATA
{
	size_t total_vector_files	= 0;		//how many files are within all the vectors within the nodes within the linked list
	size_t total_nodes		= 0;		//holds the size of the node network
	double total_file_sizeMb	= 0.0000;	// holds the size of all files if added together in Megabytes
};

class node
{
public:
	node() { pNext_link = nullptr; }

	node(const element_t& fet, std::vector<element_t>& fot, node* next = nullptr)
		:
		file_extension_type	{ fet },	// get the current type of extension found within this linked list
		files_of_type		{ fot },	// store all files of type here
		pNext_link		{ next }	// pointer to next node.

	{}
	const element_t			file_extension_type;
	std::vector<element_t>		files_of_type;
	node*				pNext_link;
};

class linked_list 
{
public:

	LINKED_LIST_DATA lldata;			//auxillary data structure

	linked_list() { head = tail = nullptr; }

	int is_Empty() { return head == nullptr; }

	linked_list& add_to_tail_node(element_t& element, std::vector<element_t>& vector_of_files);

	linked_list& orgainze_nodes(const std::vector<element_t>& collected_file_data, element_t& previous_exten);

	void  print_linked_list_node(const element_t& element);

	void  print_all_linked_list_nodes();

	void  print_all_linked_list_node_data() const;

	void print_all_linked_node_data(const element_t& elems) const;

	int  linked_list_size() const;

	const double get_node_file_size(const element_t& elem);

	void copy_relevent_files(const element_t dest, const bool copy_condition);

private:

	node* head, *tail;

};

/// <summary>
/// linked list of vectors to directory entries, the data is then examined, 
/// and then a directory with the same name as the extension of the entry;
/// the file is then copied to that location.
/// AI did not help on this code, it suggested i fix nulls and such, but thats it, also it didnt do the below, that was hard work and it was me.
/// </summary>
/// [DIRECTORY(s) TO EXAMINE] #------------------------------------>----> ... -----* 
/// 	|		      |					   |			
///	|		      |					 __#_______	 		
///	|		      #					| AUX. Data| <---------[auxillery structure of data variables; for other (related) linked list data per node]>
///	|--------->   ---------				 --------- Struct. |  
///		      |	      |				 |	| |	   |
///	              |	      |				 |	| |	   |
///		      |	      |        --Links-->	 |	 ----------
//  HEAD  -- ... --*  | .TIF  |>---...  ... ... ...----* | .TIFF  |>----- ... -----* TAIL
///		      |       |				 |        |    
///		      |       |				 |        |    
///		      |       |				 |        |    
///		      ---------				 ----------
///		       <|>				   <|>
///		       <|>				_____________
///		     <--|>				|    DATA   |
///	  	     <|>-----------------------		|   SET n+1 |
///		        | Dynamic set of data |		-------------
///		        | as a vector, etc.   |
///			| DATA SET n          |    <-----------[each Node has a vector that (.jpeg, .tif, .xml, etc.) Contains the filenames file-paths w/ that Extension Type]>
///		        -----------------------
///				|
///				|
///				eg. [+] Total Size of all files sizes (disk space Size of All files in the Vectors, accumulated in MB or GB of data).
///				    [+] Total Number Of accum. Nodes. (each unique extension type produces its own node w/ a vector to use for file paths that have that extension type).
///			            [+] Total Number Of accum. Files within all the nodes data vectors.
//run batch file before trying to compile on Windows vcvars64.bat

//[STEP #1]: cd "C:/Program Files/Microsoft Visual Studio/2022/Community/VC/Auxiliary/Build//"
//[STEP #2]: ./vcvars64.bat
//[STEP #3]: cd C:\Users\Lynx\source\repos_linux\UpdatedWinTest\fto\FileTypeExtensionOrganize
//[Compile]: cl main.cpp /std:c++17 /O2