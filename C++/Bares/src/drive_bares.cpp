#include "header.h"
#include "expressions_lib.h"

bool openFile (int argc,const char * argv[], std::ifstream & src_file, std::ofstream & dest_file);

int main (int argc, const char *argv[])
{
	std::ifstream dataFile;
	std::ofstream destFile;
	std::string expLine;
	
	if(openFile(argc, argv, dataFile, destFile) == false)
		return EXIT_SUCCESS;

	while(!dataFile.eof())
	{
		std::getline(dataFile, expLine);
		if(expLine.length() != 0)
		{
			
			Expression tempExp(expLine);
			
			if(tempExp.tokenize())
				std::cout << "Deu certo!" << std::endl;
			else
			{
				continue;
			}
			
			
			/*
			if (tempExp.analysis())
			{
				std::cout << "OK!\n";
			}
			else
			{
				std::string error = tempExp.getError();
				std::cout << error << "\n"; // to debug
			}
			
			tempExp.tokenize();
			if ( not tempExp.analysis() )
			{
				std::string error = tempExp.getError();
				std::cout << error << "\n"; // to debug
				destFile << error << "\n";
				continue;
			}
			
			destFile << tempExp.results();
			*/
		}

	}

	destFile.close();

	return EXIT_SUCCESS;
}