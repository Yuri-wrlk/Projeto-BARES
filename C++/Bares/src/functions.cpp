#include "header.h"

bool openFile (int argc,const char * argv[], std::ifstream & src_file, std::ofstream & dest_file)
{
	if(argc > 1)
	{
		src_file.open(argv[1], std::fstream::in);
		if(!src_file.is_open())
		{
			std::cout << "The file name is invalid!" << std::endl;
			std::cout << "Exiting program..." << std::endl;
			return false;
		}
	} else {
		std::cout << "No file was passed as an argument." << std::endl;
		std::cout << "Exiting program..." << std::endl;
		return false;
	}
	
	if(argc > 2)
	{
		 dest_file.open(argv[2]);
	} else {
		std::cout << "No destination file was designated as an argument." << std::endl;
		std::cout << "Creating a default destination file at data/results.txt" << std::endl;
		dest_file.open("data/results.txt");
	}
	return true;

}