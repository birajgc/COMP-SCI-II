	//************************************  PROGRAM IDENTIFICATION  **************************************************
//*																												 *
//*   PROGRAM FILE NAME:  Project4.cpp          ASSIGNMENT #:  4            Grade: _________					 *
//*																												 *
//*   PROGRAM AUTHOR:																							 *
//*                   ___________________________________________________										 *
//*                                     Biraj Singh GC															 *
//*																												 *
//*   COURSE #:  CSC 24400 11                              DUE DATE: November 06, 2019							 *
//*																												 *
//****************************************************************************************************************

//***********************************  PROGRAM DESCRIPTION  ******************************************************
//*																												 *
//*   PROCESS: This program to opens and reads the input files which contain an unknown number of records and    *
//*   processes the student data in accordance with the instructions. It Reads all the data into the             *
//*   appropriate arrays. After reading in all the data, the program prints the list of student Names and all    *
//*   test scores. The program is then sorts the list of students and their test scores by listing the students  *
//*   in albhabetic order by lastname low to high and prints the list again. The program then to calculates the  *
//*   student’s test average and determines a course grade for each student using the standard 10 point spread.  * 
//*   The program then to prints the student information (name and test scores) along with the student’s average *
//*   and course grade.Using the test score average, the program is then to sorts the student information in the *
//*   order of highest test average to lowest test average. The program then prints a final list of the student’s*
//*   name, their test scores, averages, and course grade.														 *
//*																												 *
//*																												 *
//*   USER DEFINED																								 *
//*    MODULES     : FileReader– Reads the input files and stores into array                                     *
//*                  Array1Printer– Prints the Multi dimensional array and First and last name arrayin outputfile*			  
//*                  Array2Printer- Prints first and last name,test data, average data and grade                 *
//*                  Lastname_Sort- Sorts the array data from A thru Z by last name             		         *                 
//*                  Average_calculator- Calculates the Average for every student and stores it in array.	     *                             
//*                  GradeFinder- Seperates the grade according to average and stores in array                   *                            
//*                  SortbyAverage - Sorts all arrays according to average from high to low.                     *
//*                  Header– Adds Header to the program                                                          *
//*                  Footer– Adds footer to the program                                                          *
//*                                                                                                              * 
//****************************************************************************************************************

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>;

using namespace std;

/*Function prototypes*/
void Header(ofstream&);																 //print the header for the project.
void Footer(ofstream&);											                     //print the footer for the project.
void FileReader(ifstream&, float[][4], int&, string[], string[]);					 //read the file from the output into an array.
void Array1Printer(ofstream&, float[][4], int, string[], string[]);					 //print the array data in output.
void Lastname_sort(float[][4], string[],string[],int);							     //Sort the array data from A thru Z by last name.
void Array2Printer(ofstream&, float[][4], float[],int, string[], string[],string[]); //print first and last name test data, average data and grade.
void AverageCalculator(float[][4], float[], int);				                     //Calculate the Average for every student and store it in array.
void GradeFinder(float[], string[], int);						                     //Seperate the grade according to average and stores in array.
void SortbyAverage(float[][4], float[], string[], int, string[], string[]);			 //Sort all arrays according to average from High to low.


//************************************************* Main Fuction *********************************************************//
int main()
{
	int Noofstudents = 0;																	//seed value of no of students
	float Grade[50][4], Average[50];														//initialize the array for grades and average 
	string Firstname[50], Lastname[50],Course_grade[50];									//initial array for Letter grade, Firstname, Lastname

	ifstream infile("DATA4.txt", ios::in);													//import file.
	ofstream outfile("result.txt", ios::out);												//export file.

	if (infile.fail())																		//Error catcher 
	{
		cout << " The file was not found." << endl;
		exit(1);																			//Exit the program
	}

	Header(outfile);																		//print the header for the project.
	FileReader(infile, Grade, Noofstudents, Firstname, Lastname);							//read the file from the input into an array.
	
	outfile << " The original student data is:" << endl;
	Array1Printer(outfile, Grade, Noofstudents, Firstname, Lastname);						//print the student name and grade.

	Lastname_sort(Grade,Firstname,Lastname ,Noofstudents);									//Sort the array data from A thru Z by last name.
	outfile << "The list of students sorted A thru Z by Last Name is:" << endl;
	Array1Printer(outfile, Grade, Noofstudents, Firstname, Lastname);						//print the student name and grade

	AverageCalculator(Grade, Average, Noofstudents);										//Calculate the average of each student and store in array
	GradeFinder(Average, Course_grade, Noofstudents);										//Process the grade using the average
	outfile << "The list of students with their test average and course grade is:" << endl;
	Array2Printer(outfile,Grade, Average, Noofstudents, Course_grade,Firstname,Lastname);	//print the student name, grade, average and letter grade 

	SortbyAverage(Grade, Average, Course_grade, Noofstudents, Firstname,Lastname);			//Sort the data with the average from high to low
	outfile << "The list of students sorted by test average high to low is:" << endl;
	Array2Printer(outfile, Grade, Average, Noofstudents,Course_grade, Firstname, Lastname); //print the processed grade

	Footer(outfile);																		//print	 the footer for the project.
}
//********************************************** End of Main Fuction *******************************************************//

//--------------------------------------------------------------------------------------------------------------------------//

//********************************************** Header Function ***********************************************************//
void Header(ofstream& Outfile)
{
	//Function: Header
	//Receives – the output file
	//Task - Prints the output preamble
	//Returns - Nothing
	Outfile << setw(30) << "Biraj Singh GC";
	Outfile << setw(17) << "CSC 24400";
	Outfile << setw(15) << "Section 11" << endl;
	Outfile << setw(30) << "Fall 2019";
	Outfile << setw(20) << "Assignment #4" << endl;
	Outfile << setw(35) << "---------------------------------- - ";
	Outfile << setw(35) << "---------------------------------- -  " << endl << endl;
	return;
}
//******************************************* End of Header Function ********************************************************//

//---------------------------------------------------------------------------------------------------------------------------//

//********************************************** Footer Function ************************************************************//
void Footer(ofstream& Outfile)
{
	//Function:	 Footer
	//Receives – the output file
	//Task -	 Prints the output salutation
	//Returns -	 Nothing
	Outfile << endl;
	Outfile << setw(35) << "-------------------------------- - " << endl;
	Outfile << setw(35) << " | END OF PROGRAM OUTPUT | " << endl;
	Outfile << setw(35) << "-------------------------------- - " << endl;
	return;
}
//********************************************** End of footer Function ***************************************************//

//-------------------------------------------------------------------------------------------------------------------------//

//********************************************** FileReader Function ******************************************************//
void FileReader(ifstream& infile, float Id_grade[][4], int& Noofstudents, string Firstname[], string Lastname[])
{
	//Function:	FileReader
	//Receives: Input file, array for student id_grade, int for no of students, arrays for firstname and lastname
	//Tasks:	Reads the input file and stores in the array
	//Returns:  Id_grade, Noofstudents, array of firstname ,array of secondname.
	string firstname, lastname,field;			  //seed value for first and last name
	float Marks1, Marks2, Marks3, Marks4;		  //seed value for number grade
	Noofstudents = 0;							  //seed value for no of students

	getline(infile, firstname);					  //load data line into firstname
	while (!infile.eof())						  //loop through the list
	{
		if(firstname.compare(0,3,"No ") == 0)	  //break the loop if first name reads 'No'
		{
			break;
		}
		getline(infile, lastname);				  //load data line into lastname

		//load data for the marks 
		getline(infile, field, ' ');
		stringstream ss1(field);
		ss1 >> Marks1;

		getline(infile, field, ' ');
		stringstream ss2(field);
		ss2 >> Marks2;

		getline(infile, field, ' ');
		stringstream ss3(field);
		ss3 >> Marks3;

		getline(infile, field);
		stringstream ss4(field);
		ss4 >> Marks4;

		//store the data into array
		Firstname[Noofstudents] = firstname;
		Lastname[Noofstudents] = lastname;
		Id_grade[Noofstudents][0] = Marks1;
		Id_grade[Noofstudents][1] = Marks2;
		Id_grade[Noofstudents][2] = Marks3;
		Id_grade[Noofstudents][3] = Marks4;
		Noofstudents++;
		getline(infile, firstname);				  //load the firstname for the nextline to run through the condition
	}
	return;
}
/********************************************** End of FileReader Function *******************************************************/

//---------------------------------------------------------------------------------------------------------------------------------//

//********************************************** Array1Printer Function ************************************************************//
void Array1Printer(ofstream& Outfile, float grade[][4], int Noofstudents,string Firstname[], string Lastname[])
{
	//Function:	Array1Printer.
	//Receives: output file, arrays for student first and last name, array for grade, int for no of students.
	//Tasks:	Prints Student names and grade into the output file.
	//Returns:  Nothing.
	Outfile << "     Student Name" << endl;
	Outfile << "  First       Last          Test 1  Test 2  Test 3  Test 4" << endl;
	Outfile << "----------    ----------    ------  ------  ------  ------" << endl;
	for (int i = 0; i < Noofstudents; i++)												// loop through the students and print the data out.
	{
		Outfile<<setw(14)<<left<<Firstname[i]<<setw(14)<<left<<Lastname[i]<<" "<<setprecision(2)<<fixed<<grade[i][0]<<"   "<<grade[i][1]<<"   "<<grade[i][2]<<"   "<<grade[i][3]<<endl;
	}
	Outfile << endl << endl;
	return;
}
//********************************************** End of Array1Printer Function *******************************************************//

//-----------------------------------------------------------------------------------------------------------------------------------//
//********************************************** Array2Printer Function ************************************************************//
void Array2Printer(ofstream& Outfile, float grade[][4], float Average[], int Noofstudents, string Course_grade[],string Firstname[],string Lastname[])
{
	//Function:	Array2Printer.
	//Receives: output file, arrays for student's first and last name, array for grade, int for no of students , arrays for letter grade and average.
	//Tasks:	Prints Student names, grade,Test Average and letter grade into the output file.
	//Returns:  Nothing.
	Outfile << "     Student Name" << endl;
	Outfile << "  First       Last          Test 1  Test 2  Test 3  Test 4   Average   Grade" << endl;
	Outfile << "----------    ----------    ------  ------  ------  ------   -------   ------" << endl;
	for (int i = 0; i < Noofstudents; i++)												   // loop through the students and print the data out.
	{
		Outfile<<setw(14)<<left<<Firstname[i]<<setw(14)<<left<<Lastname[i]<<" "<<setprecision(2)<<fixed<<grade[i][0]<<"   "<<grade[i][1]<<"   "<<grade[i][2]<<"   "<<grade[i][3]<<"    "<<Average[i]<<"      "<< Course_grade[i]<<endl;
	}
	Outfile << endl << endl;
	return;
}
//********************************************** End of ArrayPrinter Function ***************************************************************//


//-----------------------------------------------------------------------------------------------------------------------------------------//'

//********************************************** Lastname_sort Function *************************************************************************//
void Lastname_sort(float Id_grade[][4], string Firstname[], string Lastname[], int Noofstudents)
{
	//Function:	Lastname_sort.
	//Receives: Multidimensional Array of grades,arrays for firstname & lastname and total number of sudents.
	//Tasks:	Sorts the array using lastname of the students from A thru Z
	//Returns:  Sorted arrays from lastname.

	float temp;																//Seed value of for grades
	string tempf, templ;													//Seed value of names
	for(int i = 0; i < Noofstudents - 1; i++)								//Use exchange sort to sort the array
	{
		for (int j = i + 1; j < Noofstudents; j++)
		{
			if (Lastname[i].compare(Lastname[j]) > 0)						//sort the array alphabetically A thru Z.
			{
				//swap the names as per the condition.
				templ = Lastname[i];
				Lastname[i] = Lastname[j];
				Lastname[j] = templ;

				tempf = Firstname[i];
				Firstname[i] = Firstname[j];
				Firstname[j] = tempf;

				for(int col = 0; col < 4; col++)							 //exchange the value for all columns
				{
					temp = Id_grade[i][col];
					Id_grade[i][col] = Id_grade[j][col];
					Id_grade[j][col] = temp;
				}
			}
		}
	}

	return;
}
//********************************************** End of Lastname_sort Function *******************************************************//

//------------------------------------------------------------------------------------------------------------------------------//

//********************************************** AverageCalculator *************************************************************//
void AverageCalculator(float grade[][4], float Average[], int Noofstudents)
{
	//Function:	AverageCalcuator.
	//Receives: Multidimensional Array of grades ,Average grade ,total number of sudents.
	//Tasks:	Calculates the average for each students and stores into Average array
	//Returns:  Array of Average grade
	float tempsum;
	for (int i = 0; i < Noofstudents; i++)								//loop through the students 
	{
		tempsum = 0;													//seed value for total grade
		for (int j = 0; j < 4; j++)										//loop through the grades
		{
			tempsum += grade[i][j];										//add all the grades
		}
		Average[i] = tempsum / 4;										//divide the total grade by number of tests.
	}

	return;
}
//********************************************** End of AverageCalculator Function *********************************************//

//------------------------------------------------------------------------------------------------------------------------------//

//************************************************** GradeFinder Function ******************************************************//
void GradeFinder(float Average[], string Grade[], int Noofstudents)
{
	//Function:	GradeFinder.
	//Receives: Array for average grade, array for letter grade, number of students.
	//Tasks:	Assign letter grade for each student by compring the average grade and stores it into array
	//Returns:  Array of Course letter grade
	for (int i = 0; i < Noofstudents; i++)			//loop through average of grades and assign letter grade by storing it in the array
	{
		if (Average[i] > 90)						// Assign A if the average is above 90
		{
			Grade[i] = "A";
		}
		if (Average[i] >= 80 && Average[i] < 90)    // Assign B if the average is above 80 and below 90
		{
			Grade[i] = "B";
		}
		if (Average[i] >= 70 && Average[i] < 80)   // Assign C if the average is above 70 and below 80
		{
			Grade[i] = "C";
		}
		if (Average[i] >= 60 && Average[i] < 70)   // Assign D if the average is above 60 and below 70
		{
			Grade[i] = "D";
		}
		if (Average[i] < 60)                       // Assign F if the average is below 60
		{
			Grade[i] = "F";
		}
	}
	return;
}
//************************************************** End of GradePrinter Function ********************************************************//

//----------------------------------------------------------------------------------------------------------------------------------------//

//********************************************** SortbyAverage Function *************************************************************************//
void SortbyAverage(float Id_grade[][4], float Average[], string Grade[], int Noofstudents,string Firstname[],string Lastname[])
{
	//Function:	SortbyAverage.
	//Receives: Array for Student grade, array for Average, string arrays of letter grade,firstname and lastname, Number of students.
	//Tasks:	Sorts all the arrays using Average grade array.
	//Returns:  Sorted Id_grade, Average, Grade.
	float tempMultiarray, tempaverage;										//seed values for ID_grade, Average and grade
	string tempgrade, tempf, templ;

	for (int i = 0; i < Noofstudents - 1; i++)								//Use exchange sort to sort the array.
	{
		for (int j = i + 1; j < Noofstudents; j++)
		{
			if (Average[i] < Average[j])									//Sort from High to low.
			{
				tempaverage = Average[i];
				Average[i] = Average[j];
				Average[j] = tempaverage;

				tempgrade = Grade[i];										//Sort the letter grade accordingly.
				Grade[i] = Grade[j];
				Grade[j] = tempgrade;

				templ = Lastname[i];										//swap the elements from lastname array. 
				Lastname[i] = Lastname[j];
				Lastname[j] = templ;

				tempf = Firstname[i];										//swap the elements from firstname array.
				Firstname[i] = Firstname[j];
				Firstname[j] = tempf;

				for(int col = 0; col < 4; col++)							//swap the number grade accordingly.
				{
					tempMultiarray = Id_grade[i][col];
					Id_grade[i][col] = Id_grade[j][col];
					Id_grade[j][col] = tempMultiarray;
				}

			}
		}
	}

	return;
}
//********************************************** End of SortbyAverage Function *******************************************************//

//********************************************** End of the Program ************************************************************//