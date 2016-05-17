## Project BARES

##### Version 1.0.0 - Monday May 16th 2016

by Thiago Cesar Morais Diniz de Lucena & Yuri Reinaldo da Silva  


Introduction
--------------------------------------------------------------------------------------

BARES, or *Basic ARithmetic Expression Evaluator based on Stacks*, is a program
made in C++ with the main purpose to take a series of arithmetic expressions,
analyse it searching if there is any problem within the formula and, if it is 
everything correct, give the expression result.

The current version does not support algebraic or any other type of numeral 
other than integers.

Instalation and running
--------------------------------------------------------------------------------------

To install and execute the program, follow these steps: 

1. The file must be extracted from the accompanying zip folder 
  "Project_Bares.zip", it should come with all the files necessary.
2. Open your terminal and navigate to the folder where the files where extracted
   to.
3. Simply input the __make__ command.
..* Instead of make, another way to do it is by inputting the following command 
	at the terminal:

g++ -std=c++11 -I include src/drive\_bares.cpp src/functions.cpp -o bin/drive_bares


Then, to execute the program, you just run it by inputting the following command:
	
	bin/drive\_bares *input file* *output file*
	
*input file* should be substituted by the file containing the expressions who 
should be analyzed. 

*output file* is where you want the results to be saved. It is optional and if 
you do not wish to designate it the program will automatically generate a file
at the "data" folder called "results.txt".

A reminder: the input file must contain only expressions with integers. Any 
unsupported symbol such as a letter will be interpreted as an invalid character
and will be properly treated as an error.

Operations and terms supported
--------------------------------------------------------------------------------------

The current version of BARES supports the use of:

- Integer numeric constants (-32.768 to 32.767)
- Operators (+, −, /, ∗,ˆ, %)
- Parenthesis

The operations precedence follows the rules of the table below.

Operator  | Precedence
() 		  |		0
+, - 	  |		1
*, /, %   |		2
^ 		  |		3
- (unary) |		4



Table of possible errors found by BARES
--------------------------------------------------------------------------------------

If any expression has an error in it, the program will send the first error's 
code to the output file and, if aplicable, in which position of the original 
expression it can be found. The possible errors are:

| Code | Associated error													|
|:----:|:------------------------------------------------------------------:|
|  E1  | A number in the expression is above the integer limit (-+ 32.767	| 
|  E2  | A binary operator does not find it's 2nd operand					|
|  E3  | There is a symbol who's neither a supported operator nor a number	|
|  E4  | A 'lost' symbol is found within the expression 					|
|  E5  | There is a ')' without a corresponding '(' in the expression		|
|  E6  | A binary operator does not find it's first operand					|
|  E7  | There is a '(' which does not find a ')'							|
|  E8* | At some point, the expression leads to a division by zero			|
|  E9* | At some point, a number higher than the limit is generated			|
 
Obs.: The number of the column indicating the error on expressions indicates:

- The column which a number starts, when the error is on that number
(E.g.: "12 * 1800 5" has "E4 11" as result.)

 *_codes indicated by * do not show the column where it ocurred, because they are_
 _only found during the expression is being calculated_

Examples of valid and correct expressions
--------------------------------------------------------------------------------------

Expression					| Result
-3 - -4						| 1
35 - 3 * (-2 + 5)^2			| 8
54 / 3 ^ (12%5) * 2			| 12
((2-3)\* 10 - (2^3*5))		| -50
-3 + 4						| 1
(27) / (-3)					| -9
((((((((((7 ^ 2))))))))))	| 49 

Bugs and limitations
--------------------------------------------------------------------------------------

Terms non-supported by the program:

- Unary plus. (E.g.: +3 * 5)
- More than one unary minus in sequence. (E.g.: --5 * -------3)
