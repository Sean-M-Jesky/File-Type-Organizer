# FileTypeOrganization (WIN64, WIN32, LinuxOS, & others - cross-platform safe)

    >>>deleteprogam branch now moved into its own repo, no need to download from the branch anymore, branch will soon be deleted from this repo, and work will only continue from the DeleteFilesOfExtensionType repo:

    https://github.com/Sean-Jesky/DeleteFilesOfExtensionType.git

--- 

https://chatgpt.com/share/8b1e8992-3577-4b93-bcfb-a51f909d8b48
Ai is dr. feel good. I always wanted to tutor and be an teacher... honestly i dreamed of that, and cuddlying with a book and a fire in the mountains. 

---

tested on LinuxOS, kali and windows (x86, & x64) (cross-compiling error currently):
but stupid inputs == stupid results, unttil i can place proper validation checks. (i almost always expect people will try and break it anyways, so i do that last. 
anyways, finished patching, will work on both OS's now: 

for LinuxOS - To compile code, go to directory of this programs files, open the command prompt to that location and run this command:

    clang++ main.cpp linked_list.cpp fsHelper.cpp -std=c++17 -lstdc++fs -o FileTypeExtensionOrganizer.out
    or using gcc, g++.  
    [gcc/g++] main.cpp linked_list.cpp fsHelper.cpp -std=c++17 -lstdc++fs -o FileTypeEx...

for windows - open in VS code double click on the .sln file, build program, then run form command line.

to run:

    [from compiled directory]./FileExtensionTypeOrganizer.out <source (directory location to copy from)> <destination (where to save copies from the source location)> 

options:

1: keep copies of files, if its documents this might be a better choice, especially if you dont know which version to keep and/or you have many versions to keep and/or look through. 


2: dont keep copies of files. 

    currently these options need to be changed in the code directly until final version of code is completed. (fixing bugs, fixing formatting, adding/removing a few things here and there first)
---
[+] Each extension type is a node within a singly linked list. 

[+] Inside each node, from the directory copying from, are all the files of that extension type and their location/path 

[+] Every extension type creates a folder with that value (.mp3, .png, .jpeg, .jpg, etc.) and copys files of that extension type (specific ext. type paths are stored in the nodes satallite data, in the form of a vector) to its respective folder name of that very extension type itself. 


---

examples/explaining how it works:

---
whats cools is, the nature of nodes and sorting makes this all happen naturally. if the nodes are in order, then being copied over to its correct destination is as easy as reaching a node of that type. 

![RunningOnWindos-](https://github.com/user-attachments/assets/1e21d3a7-18e6-41be-9f00-50143bc89cf7)

example runs:

[previous node] <|.jpg|>

current node:    <|.mp3|>

[next node]     <|.mp4|> 
 
  go through vector of file paths, if -as it finds mp3 files:
  ![HowItWorks_](https://github.com/user-attachments/assets/b52dec5b-93eb-475f-b7c3-58d124f9bff7)

    [directory path]/.../.../***.mp4
    [directory path]/.../.../***.tiff
    [directory path]/.../.../***.zip
    [directory path]/.../.../***.mp3 > copy to mp3 node
    [directory path]/.../.../***.png
    [directory path]/.../.../***.tiff
    [directory path]/.../.../***.mp3 > copy to mp3 node
    [directory path]/.../.../***.mp3 > copy to mp3 node

collect the collection of extension namess to put into a node each of their own [Head Node] -...-> [mp3]->[mp4]->[m4a]-...->[Tail Node]


for each node in the linked list we visit, create a folder of that nodes extension type, this is to place the files of that extension type at. 
![HowItWorks](https://github.com/user-attachments/assets/fbebbb26-9b35-4cf9-a183-09eee4f77aae)

now we can copy from each node one by one (or multithread it if you really need speed... but you dont its fine as it is... u know... C++..) by accessing the node and reading the data within it.  

  next, we copy these collected file paths from each of the vectors of paths node by node. (still being affected by hate crime right this second. every time i try and work they are so much worse. its so hard to keep this up.)
  
do this for each file extension type (node) until all nodes have been visited.. 
![ExampleOutputFile](https://github.com/user-attachments/assets/40f7d053-6e63-45bd-ba9f-b081473724cb)

---

i hope one of these helps explain it. depending on who you are one should at least be helpful. 

---

    or another way to explain:

 
it goes through the vector of file paths found in the source directory provided by the user, the program checks to see if the file path being looked at matches the current nodes extension-type, if it is the same extension type as the node we are currently on, we copy that data to copy later. the vector doesnt need to be sorted for the nodes to end up sorted and i really like that for a lot of reasions. 


Hope that makes sense. if not the images of screenshots of it in action should help elaborate how its working. 


did not reqlize this was a public repo. yet....
