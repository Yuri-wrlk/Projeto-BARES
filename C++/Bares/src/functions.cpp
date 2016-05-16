#include "header.h"


/*!
 *	@brief Open the file passed as an argument
 *	@param argc An integer containing the number of arguments received
 *	@param argv A vector of strings, keeps the aarguments received
 *	@param src_file Will keep the file that will be read
 *	@param dest_file Stores destination file
 *
 *	This function checks if a input file and a destination file were passed as
 *	arguments, if no input file was passed, the function sends an error and is 
 *	terminated, outherwise it is set to src_file. If no destination file was passed
 *	the a default one is created at data/results.txt
 * 	@return False if input_file argument is invalid or non-existent, True otherwise
 */
bool openFile (int argc,const char * argv[], std::ifstream & src_file, std::ofstream & dest_file)
{
	/* If only 
	 */
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
		std::cout << "The program must be initialized as bin/drive_bares [input file]" << std::endl;
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