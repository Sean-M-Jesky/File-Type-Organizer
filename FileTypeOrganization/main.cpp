//by. Sean Jesky i hope this helps someone out there. Please use in a responsible way.. 
/*
 * FILE('s): main.cpp
 * DATE&TIME: feb 15th 2023 - rewritten and optimized, refactored, etc. 9/xx/2024
 * CREATED_BY: Sean Jesky ()
 * CREATED_FOR: the dream  M520
 * WHAT_IT_DOES:  This data is saved in users requested location. Segregation and organization of file extension type.
 * 
 * 
 * ^this above, before each :, used to start up as a template each time i wrote code on linux using leafpad when i first started learning, before i used an IDE like VS, or Vcode

 
 TESTED & runs ON WINDOWS x86, and x64 arch - an LinuxOS
			
*/
#include "linked_list.h"
#include "fsHelper.h"
//,,,
#include <filesystem>
namespace fs = std::filesystem;
#include <exception>
#include <vector>
using std::vector;
//...
#include <iostream>
#include <chrono>
#include <ctime>
#include <iomanip>
using std::setfill; using std::setw;
//...
//END OF WINDOWS INCLUDES, AND OTHER SPECIFICS NEEDED/WANTED FOR PROPER FUNCTIONING OF WINDOWS API's.
#define __AUTHOR__		"Sean Mikhial Jesky"
#define __EXE_VERSION__		"3.02"
#define __EXECUTABLE_NAME__     "FTO.exe"
#define __YEAR_WRITTEN__	"2023"


/// (LinuxOS compiling Command) clang++ -std=c++17 -lstdc++fs -o FileTypeOrganizer.out main.cpp linked_list.cpp fsHelper.cpp
/// /
/// /
/// @brief (FTeO Version 3.00) 
///			This program goes through a filesystem, gets all the file extensions,
///			creates directories from those extensions, and copies files to the corresponding directory extension name.
/// @param int argv 
/// @param char *argc 
/// @return 
int main(int argv, char* argc[])
{
	//system("color F8");
/*
	if (argv <= 2) {
		std::cout << "\n\t|Written & Disgned By. " << __AUTHOR__ << "|\n";
		std::cerr << "invalid input, proper use:\n\nFileTypeOrganizer.exe <source> <destination> <MODE Choices: <1|2>(Inactive Currently))>\n";
		std::cerr << "\t[!!]MODE - 1: Keep Duplicate Files\n\t[!!]MODE - 2: Don't Keep Duplicates.\n";
		std::cerr << "\nPlease restart program with valid input.";
		return 1;
	}
	if (argv >= 2) {
		if ((!fs::is_directory(argc[1]) || !fs::is_directory(argc[2])))
		{
			std::cout << "\n\t|Written & Disgned By. " << __AUTHOR__ << "|\n";
			std::cerr << "invalid data input....\n";
			std::cerr << "please enter a valid directory(s)";
			return -2;
		}
	}
*/	
	auto time = std::chrono::system_clock::now();
	auto t1_start = std::chrono::high_resolution_clock::now();
	
///
///>	meat
	std::cout << "[!] ...Collecting relevant files from source location provided...\n";
	//const std::string copy_from = argc[1];
	//const element_t path_to_copy_from = copy_from;

	//vector<element_t> p_pfiles { "" };
	std::vector<element_t> p_files {argc[1]}; //&p_pfiles;
	p_files = collect_relivant_files(p_files);

///	potato's
	std::cout << "[!] ...Starting Organization Procedure on the data collected...\n";		

	element_t p_path = "";
	std::shared_ptr<linked_list> llist(new linked_list());
	llist->orgainze_nodes(p_files, p_path);
///<
///
	//utilizing my linked list aux. data structure to hold extra data on the whole set of data collected among all the nodes in total.
	std::cout << "\n[*] Total # of files:\t\t\t\t"			<< llist->lldata.total_vector_files	<< '\n';
	std::cout << "[*] Total # of File Extension's:\t\t"		<< llist->lldata.total_nodes		<< '\n';
	std::cout << "[*] Total physical data of files (GB):\t\t"	<< llist->lldata.total_file_sizeMb / 1024.0000 / 1024.00 << "\n";

	//end of keeping track of run time of copying procedure:
	auto t1_end = std::chrono::high_resolution_clock::now();
	auto total_time = std::chrono::duration_cast<std::chrono::milliseconds>(t1_end - t1_start).count();

	if (total_time <= 1000)
		std::cout << "[+] Total Time to complete 'startp Functions':\t" << total_time << " Miliseconds...\n"; //ambitious for large drives... just FYI
	else
		std::cout << "[+] Total Time to complete 'startp Functions':\t" << total_time * 0.001 << " seconds...\n"; //also ambitious
	std::cout << setw(45) << setfill('|') << '\n';

	//start the timing of copying from source to destination.
	auto t1_copy_start = std::chrono::high_resolution_clock::now();

	
///>
	const std::string save_location = argc[2];
	const element_t base_save_location = save_location;

	//copy files, w/ keep duplicates(true) or dont keep(false) choice.
	int choice = false;
	std::cout << "\n[!] Started: copying files to their correct directory, at: " << base_save_location << "...\n\n";
	llist->copy_relevent_files(base_save_location, choice);
///

	auto t1_copy_end = std::chrono::high_resolution_clock::now();
	auto total_copy_time = std::chrono::duration_cast<std::chrono::minutes> (t1_copy_end - t1_copy_start).count();
	std::cout << setw(45) << setfill('^') << '\n';
	if (total_copy_time <= 60)
		std::cout << "\n[#] Total Time to complete Copying of relevent data:\t" << total_copy_time << " minutes\n";
	else
		std::cout << "[#] Total Time to complete Copying of relevent data:\t" << total_copy_time * 60 << " hours\n"; //obv. if an empty dir. or a single file or two it will say hours when program ends, because the program will end with nothing to copy so it wont even reach seconds... 

	std::cout << setw(45) << setfill('~') << '\n';
	//For M. (prev. date that was posted, was when this program was first written, not for M.

	//M520
}

























/*
	USER OPTIONS TO ADD (eventually) FUNCTIONALITY FOR:
	----------------------------------------------------------------------------------------------------------------------
	SET A:) 1:]	Remove duplicates	-	Remove duplicates from a singular node.
		2:]	Remove all duplicates	-	Remove duplicates from all nodes.

	SET B.)	1:]	Specific Extension	-	copy/move/delete specific node selected.
		2:]	Specific Extensions	-	copy/move/delete specific nodes selected.
		3:]	All Extensions		-	copy/move all files in all nodes.

	SET C.)	1:]	Single Threaded		-	Run the program a single thread (for older systems without MT capability).
		2:}	Multi-Threaded		=	Run the program on multipul threads for blazingly fast speeds.
		3:]	Low and Slow Mode	=	Run the program using slower methods that use less RAM, and on a single thread.

	SET D.)	1:]	copy			-	[default] to copy programs data to location requested.
		2:]	move			-	Move files to the requested location
		3:]	remove			-	Remove files from a specific node(s) specified by text file of entires - (Not blanket removals)

* Require password to remove > 1 all files from the system
*
*/
