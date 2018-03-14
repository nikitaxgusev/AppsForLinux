#include <iostream>
#include <sys/types.h> // For <dirent.h>
#include <dirent.h>    // For opening a dir
#include <fstream>
#include <vector>
#include <regex>
#include <cmath>



void help_note();
void find_files_in_dir( const char*);
void read_from_file(const char* myPath,std::string fileName);

int main(int argc,char* argv[])
{
  std::string help="-h";
  std::string path="-p";
    
    if(1==argc)
    {
        help_note();
    }
 

    if(argv[1]==help){
	 help_note();
	 exit(-1);
    }
    
    if(path==argv[1])
	{
     const char* myPath=argv[2];
     find_files_in_dir(myPath);
    }
	else 
	{
	 help_note();
	 exit(-1);
	}

    return 0;
}
void read_from_file(const char* myPath,std::string fileName)
{
    std::string s1=myPath;
    std::string fullPath= myPath+fileName;      // Getting the full path

    std::ifstream file(fullPath);               // Open with using the full path
    std::string line;

    while(!file.eof()){
     std::getline(file,line);                   // Read line by line
     std::cout<<line<<std::endl;
    }

    file.close();                               // Close file
}

void find_files_in_dir(const char* myPath)
{
     std::vector<std::string> myVecFiles;
     std::cmatch result;
	 /* See only files, not dirs and files*/
     std::regex regularExpr ("([\\w-]+)(\\.)([\\w-]+)");

     DIR *dir;                                   // for dir using
     struct dirent *ent;
     /*Checking if the dir exists*/
     if ((dir = opendir (myPath)) != NULL)
     {
    /*  all the files and directories within directory */
       while ((ent = readdir (dir)) != NULL)
       {
        if(std::regex_match(ent->d_name,result,regularExpr))
        {
          std::cout<<"File name from your dir: "<<ent->d_name<<std::endl;
          myVecFiles.push_back(ent->d_name);       // Get name file into vector of strings
        }

       }
      std::cout<<std::endl;
	  std::cout<<std::endl;
	  closedir (dir);                              // Close the dir


        /*Call function of reading vector's size() times*/
       for (int i=0;i<myVecFiles.size();i++)
       {    std::cout<<"File number: ["<<i+1<<"]"<<std::endl;
            read_from_file(myPath,myVecFiles[i]);
            std::cout<<std::endl;
	        std::cout<<std::endl;
       }

     }
     else{
        /* could not open directory */
        perror ("Oops!");
     }
}
void help_note()
{
 std::cout<<"help note:"<<std::endl;
 std::cout<<"Usage: [nameApp] -p [yourPathToDirectory]"<<std::endl;
}
