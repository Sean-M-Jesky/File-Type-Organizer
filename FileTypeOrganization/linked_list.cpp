//"linked_list.cpp"
#include "linked_list.h"
#include <cstdint>
#include <cstring>
#include <filesystem>
#include <cstdlib>
#include <cmath>
#include <memory>
#include <string>


/// <summary>
/// create node and link, and add elements of data to the next node
/// </summary>
linked_list& linked_list::add_to_tail_node(element_t& el, std::vector<element_t>& vector_of_elements)
{
	size_t total_node_cnt = 0;

	if (head != nullptr) {
		tail->pNext_link = new node(el, vector_of_elements);
		tail = tail->pNext_link;
	}
	else {
		head = tail = new node(el, vector_of_elements);
	}
	total_node_cnt += 1;

	size_t total_file_count = 0;
	if (vector_of_elements.size() > 0)
	{
		for (auto& fs_iter : vector_of_elements)
		{
			lldata.total_file_sizeMb += (double(fs::file_size(fs_iter)) / 1024.0000);
			total_file_count += 1;
		}

		lldata.total_nodes		+= total_node_cnt;
		lldata.total_vector_files	+= total_file_count;
		lldata.total_vector_files	+= vector_of_elements.size();
	}

	return *this;
}
/// <summary>
/// get the length of the linked list structure. eg. n = 6
/// </summary>
int linked_list::linked_list_size() const
{
	int node_cnt = 0;
	for (node* current = head; current; current = current->pNext_link)
	{
		node_cnt += 1;
	}
	return node_cnt;
}

/// <summary>
/// print the data within the node with the correct matching elem. data type
/// </summary>
void linked_list::print_linked_list_node(const element_t& elems)
{
	for (node* current = head; current; current = current->pNext_link)
	{
		if (current->file_extension_type.string() == elems.string())
		{
			std::cout << "\n\n[+] Current Node:\t\t\t" << current->file_extension_type << '\n';
			std::cout << "[+] Total # of Files In This Node:\t" << current->files_of_type.size() << "\n";
			std::cout << "[+] Total Accum. File Sizes (Mb):\t" << get_node_file_size(current->file_extension_type) << "\n\n";
		}
	}
	std::cout << std::dec;
}
/// <summary>
/// print each node and its elem name.
/// </summary>
void linked_list::print_all_linked_list_node_data() const
{
	for (node* current = head; current; current = current->pNext_link)
	{
		for (auto& fs_iter : current->files_of_type)
		{
			std::cout << fs_iter << '\n';
		}
	}
}
/// <summary>
/// print the linked list node w/ correct elem. and data within it.
/// </summary>
void linked_list::print_all_linked_node_data(const element_t& elems) const
{
	for (node* current = head; current; current = current->pNext_link)
	{
		//check !empty()
		if (current->file_extension_type.string() == elems.string())
		{
			for (auto& fs_iter : current->files_of_type)
			{
				std::cout << fs_iter << '\n';
			}
		}
	}
}
/// <summary>
/// print each node, the elem type, the size of each vector of elem within the node, and size of all the data sizes accum. together
/// </summary>
void linked_list::print_all_linked_list_nodes()
{
	for (node* current = head; current; current = current->pNext_link)
	{
		std::cout << "Extension Type of Node:\t\t" << current->file_extension_type << '\n';
		std::cout << "Size Of Vector In Node:\t\t" << current->files_of_type.size() << '\n';
		std::cout << "Total Accumulated Size of This node's file data: (Mb):\t" << get_node_file_size(current->file_extension_type) << "\n\n";
	}
}
/// <summary>
/// get the file sizes of a specific node within the linked list.
/// </summary>
const double linked_list::get_node_file_size(const element_t& elem)
{
	double ll_nfs = 0.0000;
	for (node* current = head; current; current = current->pNext_link)
	{
		if (current->file_extension_type.string() == elem.string()) {
			if (current->files_of_type.size() > 0) {
				for (const auto& cfto : current->files_of_type)
				{
					ll_nfs += (double(fs::file_size(cfto)) / 1024.0000 / 1024.0000);
				}			
			}
			else {
				return 0;
			}
		}
	}
	return ll_nfs;
}

/// <summary>
/// collect, sort, and organize files (and their file extensions),
/// collected, then organize all the data into the linked list nodes of their type
/// </summary>
/// i dont like how this function looks or how it works, can and should be optimized.
linked_list& linked_list::orgainze_nodes(const std::vector<element_t>& collected_file_data, element_t& previous_exten)
{
	std::unique_ptr<std::vector<std::string>> p_types (new std::vector<std::string> {}); //just for practice using smart pointers.
	//std::vector<std::string>* p_types = &p_types;

	//reserve data, prevent reallocating each time we need more data, and we keep adding and we dont know so i put a guess on it.
	//basically, the collected file size should have the same amount as the extensions (before they are removed of duplicates), so ya,.. thats my reasoning.
	p_types->reserve(collected_file_data.size());


	//[!THIS WILL BE CHANGED INTO USING MAPS INSTEAD OF A VECTOR SOON!]
	//iterate over all the files from the dir. provided by  the user check if it has a extn. and if so, place that extn. type into the vector.
	for (const auto& current_filename : (collected_file_data))
	{
		if (current_filename.has_extension())
		{
			//collect all extensions from the files within the directory as iteration goes over them
			std::string path_str = current_filename.extension().string();
			p_types->push_back(path_str);
		}
	}
	//sort all the types collected - makes it so they are easy to remove duplicates.
	std::sort(p_types->begin(), p_types->end());

	int cnt = 0;
	std::vector<element_t> data; //find out why smart pointers didnt work in this case
	unsigned int counter = 0;

	for (auto& extn : *p_types) // go through a vector of extensions one by one
	{
		if (previous_exten != extn) //<--- chatgpt line
		{
			previous_exten = (*p_types)[counter];
//#pragma omp parallel for
//#pragma omp barrier 
			for (const auto& cfto : collected_file_data)
			{
				//remove duplicates.
				if ((*p_types)[counter] == cfto.extension().string())
				{
					data.push_back(cfto);
				}
//#pragma omp flush(cfto)
			}
			// hidden functionality of add_to_tail_node():
			// when adding to node; aux. data memb.s of an associated class holds 
			// all the accumulated global data of the linked list nodes - relevent to the data stored as well.
			add_to_tail_node(previous_exten, data);
			//data is used to transfer into the tail node, after that its cleard for the next nodes data, as the prev. entrys are now stored in the prev. node.
			data.clear();
		}
		counter += 1;
	}
	return *this;
}
/// <summary>
/// copy files from 'destination' after organization of the data, to a directory also created.
/// </summary>
/// <param name="dest"></param>		where are you saving this data being copied too.
/// <param name="choice"></param>	copy condition true, means keep copies, false does not keep the copies
/// 
/// PROGRAMMER NOTICE: this function is way too big... honestly... this should have been smaller, keep in mind functions should be <30 lines, if you CAN help it, you cant always
void linked_list::copy_relevent_files(const element_t dest, const bool copy_condition)
{

	int total_ext = 0;
	int i = 1;
	for (node* current = head; current; current = current->pNext_link)
	{
		create_directory_from_extension_type(dest, current->file_extension_type);

		std::cout << "[!] ... " << current->file_extension_type << " type files from data collected are being copied ...\n";
		auto t1_start = std::chrono::high_resolution_clock::now();

		for (const auto& file_iter : ((current->files_of_type)))
		{
			//worst code anyone has written or seen below.. i cant prove it - my code feels it, as such, i do too.. i will never touch it again... i cant stand the sight of it :(
		
#if __linux__
			const element_t core_path	= dest.string() + current->file_extension_type.string().erase(0, 1);//this part of the
			const element_t fname_loc	= core_path.string() + '/' + file_iter.filename().string();//i hope i never
			const element_t fname_		= core_path.string() + '/' + file_iter.filename().string();//have to rewrite

			//IF WINDOS, USE \\ INSTEAD OF LINUX /

#elif _WIN64
			const element_t core_path	= dest.string() + current->file_extension_type.string().erase(0, 1);//this part of the
			const element_t fname_loc	= core_path.string() + '\\' + file_iter.filename().string();//i hope i never
			const element_t fname_		= core_path.string() + '\\' + file_iter.filename().string();//have to rewrite
			
			LPCWSTR fname__ = fname_.c_str();
			LPCWSTR fitr	= file_iter.c_str();
#elif _WIN32
			const element_t core_path	= dest.string() + current->file_extension_type.string().erase(0, 1);//this part of the
			const element_t fname_loc	= core_path.string() + '\\' + file_iter.filename().string();//i hope i never
			const element_t fname_		= core_path.string() + '\\' + file_iter.filename().string();//have to rewrite
			
			LPCWSTR fname__ = fname_.c_str();
			LPCWSTR fitr = file_iter.c_str();
#endif
			copy_conditions cc;
			if (copy_condition == cc.keep_copies) 
			{
				if (fs::exists(fname_loc)) 
				{
					fs::rename(fname_loc.string(), fname_.string() + "( Copy #" + std::to_string(i) + ')' + current->file_extension_type.string());
				}
				i += 1;
#if _WIN64
				if (CopyFileEx(fitr, fname__, NULL, NULL, FALSE, COPY_FILE_NO_BUFFERING | COPY_FILE_FAIL_IF_EXISTS)) 
					total_ext += 1;
				else {}

#elif _WIN32
				CopyFileEx(fitr, fname__, NULL, NULL, FALSE, COPY_FILE_NO_BUFFERING | COPY_FILE_FAIL_IF_EXISTS);
				total_ext += 1;
#else
				fs::copy(file_iter.string().c_str(), (fname_loc.string().c_str()), fs::copy_options::update_existing);
				total_ext += 1;
#endif
			}
			else if (copy_condition == cc.keep_no_copies)
			{
				if (fs::exists(file_iter)) {
					if (file_iter.extension() == current->file_extension_type)
					{
#if _WIN64
						if (CopyFileEx(fitr, fname__, NULL, NULL, FALSE, COPY_FILE_NO_BUFFERING | COPY_FILE_FAIL_IF_EXISTS))
							total_ext += 1;
						else {}
#elif _WIN32 
						if (CopyFileEx(fitr, fname__, NULL, NULL, FALSE, COPY_FILE_FAIL_IF_EXISTS))
							total_ext += 1;
						else {}
#else
						fs::copy(file_iter.string().c_str(), (fname_loc.string().c_str()), fs::copy_options::update_existing);
						total_ext += 1;	
//#elif _APPLE		
			//TODO:
				//APPLE STUFFS
#endif
					}
				}
				else;
			}
		}
		auto t2_end = std::chrono::high_resolution_clock::now();
		auto time_to_copy = std::chrono::duration_cast<std::chrono::milliseconds> (t2_end - t1_start).count();
		
		//print the total time to copy and the extn. associated with this time.
		std::cout << "[*] Total Time To Copy " << current->file_extension_type << ":\t\t" << time_to_copy << " ms\n\n";

		total_ext = 0;	 //count of copies
		i = 1;		 //count of duplicates //idk yet.
	}
}

//for_testing_only, if this is active, and if the program reads corn from a file, it will terminate the program.
/*
int kill_switch(element_t kill_condition) {
	if (kill_condition == ".CORN" || kill_condition == ".corn")
		throw std::logic_error("reached testing kill point");
	else {
		//std::cout << "No corn discovered in these parts... yet!";
	}
	return 0;
}
*/









//--------------------------------------------------------
/*
		for(node* curr = head; curr; curr = curr->pNext_linked_list){
			element_t prev_fext = "";
			int count  = 0;
			//if(curr->file_extension_type != prev_fext)
			//{

				//bored..my psudorandom number generator:
				std::unique_ptr<unsigned int> x(new unsigned int);
				//x = (int *)&x;

				uintptr_t addy = reinterpret_cast<uintptr_t>(x.get());
				static int  hash = addy;
			//std::reinterpret_pointer_cast()
				hash += hash % 11 + (1 - addy); //make a p-random memory address the rng_seed
				curr->hash_value ^=  ~hash | hash & 1;
				curr->hash_value |= hash;

				//..
				auto TMP = hash;

				//...
				hash ^= hash << 3;
				hash ^= (hash * 13) << TMP;
				hash ^= curr->hash_value;

				//..
				curr->hash_value ^= hash;
				hash += curr->hash_value;
				//...
				curr->hv2 = std::to_string(curr->hash_value);
				curr->hv1 = std::to_string(hash);

				std::cout << stoi(curr->hv1) << ",\n";
			}

			//}
				prev_fext = curr->file_extension_type;

				count = 0;
		
		just moving it down here, makes it hard to read the beauty i wrote above.
		
		*/
