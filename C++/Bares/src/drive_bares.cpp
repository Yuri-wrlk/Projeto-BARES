#include "header.h"
#include "expression_lib.h"

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
			
			if( not tempExp.tokenize() )
			{
				destFile << tempExp.errorMessage() << std::endl;
				continue;
			}
			
			if ( not (tempExp.calculate()) )
			{
				destFile << tempExp.errorMessage() << std::endl;
				continue;	
			}
			
			destFile << tempExp.getResult() << std::endl;
			
		}

	}

	destFile.close();

	return EXIT_SUCCESS;
}