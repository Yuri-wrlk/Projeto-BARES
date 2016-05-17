/*!
 *  @mainpage Project BARES
 *  @authors Thiago Cesar Morais Diniz de Lucena
 *  @authors Yuri Reinaldo da Silva
 *  @date May, 2016
 *  @version Beta
 *
 *	@file drive_bares.cpp
 *
 *  File with the main function, and the program's functionality.
 */

#include "header.h"
#include "expression_lib.h"

/*!
 *	@brief Open the file passed as an argument
 *
 *	This function handles the input file operations.
 */
 
//For detailed description, see file 'src/functions.cpp'.
bool openFile (int argc, const char * argv[], std::ifstream & src_file, std::ofstream & dest_file);

/*!
 * @brief The program's main funcion
 *
 * Main function that reads expressions from file, call class methods to perform
 * analysis and calculations, and send the result to the output file.
 */
int main (int argc, const char *argv[])
{
	std::ifstream dataFile;
	std::ofstream destFile;
	std::string expLine;
	
	// If file could not be opened successfully, the program exits.
	if(openFile(argc, argv, dataFile, destFile) == false)
		return EXIT_SUCCESS;
		
	while(!dataFile.eof())
	{
		// Reads a single expression.
		std::getline(dataFile, expLine);
		if(expLine.length() != 0)
		{
			// An object with the expression is created.
			Expression tempExp(expLine);
			
			// Tries to tokenize the expression.
			// If tokenization was not successfull, sends error message to the output file
			// and continues to the next expression.
			if( not tempExp.tokenize() )
			{
				destFile << tempExp.errorMessage() << std::endl;
				continue;
			}
			
			// Tries to calculate the expression result.
			// If calculation was not successfull, sends error message to the output file
			// and continues to the next expression.
			if ( not (tempExp.calculate()) )
			{
				destFile << tempExp.errorMessage() << std::endl;
				continue;	
			}
			
			// In case the expression has no errors, its result is send to the output file.
			destFile << tempExp.getResult() << std::endl;
			
		}

	}

	destFile.close();

	return EXIT_SUCCESS;
}