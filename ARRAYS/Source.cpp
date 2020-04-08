//************************************  PROGRAM IDENTIFICATION  ***************************************
//*                                                                                                   *
//*   PROGRAM FILE NAME:  Project2.cpp          ASSIGNMENT #:  2            Grade: _________          *
//*                                                                                                   *
//*   PROGRAM AUTHOR:                                                                                 *
//*                   ___________________________________________________                             *
//*                                     Biraj Singh GC                                                *
//*                                                                                                   *
//*   COURSE #:  CSC 24400 11                              DUE DATE: October 9, 2019                  *
//*                                                                                                   *
//*****************************************************************************************************

//***********************************  PROGRAM DESCRIPTION  *******************************************
//*                                                                                                   *
//*   PROCESS: This program to reads an unknown number of student ID numbers and test scores from an  *
//*	  input file. After reading in all the data into the appropriate arrays, the program prints the   *
//*	  list of student ID numbers and scores.Then it prints a list of all students in groups           * 
//*   according to the letter grade they received. Next it finds the highest score and lowest score   *
//*   and print those scores along with the student ID of the student who received those respective   *
//*   scores. Finally it computes the average test score of ALL tests and prints it out.              *
//*                                                                                                   *
//*                                                                                                   *
//*   USER DEFINED                                                                                    *
//*    MODULES     : FileReader		– Reads the input files and stores into array                     *
//*                  ArrayPrinter	– Prints the array in outputfile								  *
//*                  GradePrinter	- Separates and prints the grade into the outputfile              * 
//*                  LowScore		- Searches for the lowest grade.		                          *
//*                  HighScore		- Searches for the Highest grade.	                              *
//*                  AvgScore		- Calculates the average grade.                                   *
//*                  Header			– Adds Header to the program                                      *
//*                  Footer			– Adds footer to the program                                      *
//*                                                                                                   * 
//*****************************************************************************************************

#include <iostream>;
#include <fstream>;
#include <iomanip>;

using namespace std;

/*Function prototypes*/
void Header(ofstream&);										//prints the header for the project.
void Footer(ofstream&);										//prints the footer for the project.
void FileReader(ifstream&,int[],float[],int&);				//reads the file from the output into an array
void ArrayPrinter(ofstream&, int[],float[],int&);			//prints the array data
void GradePrinter(ofstream&, int[],float[],int&);			//prints the processed grade
int LowScoreindex(float[], int&);							//Finds the lowest score in the array.
int HighScoreindex(float[], int&);							//Finds the highest score in the array
float AvgScore(float[], int&);								//Finds the average score in the array.

//************************************************* Main Fuction *********************************************************//
int main()
{	
	int Noofstudents = 0;													//seed value of no of students
	int StudentID[50];														//initialize the array for student id 
	float Grade[50];														//initialize the array for student grade

	ifstream infile("data.txt", ios::in);									//import file.
	ofstream outfile("result.txt", ios::out);								//export file.

	if (infile.fail())														//Error catcher 
	{
		cout << " The file was not found." << endl;	
		exit(1);															//Exits the program
	}

	Header(outfile);														//prints the header for the project.
	FileReader(infile, StudentID, Grade, Noofstudents);						//reads the file from the output into an array
	ArrayPrinter(outfile, StudentID, Grade, Noofstudents);					//prints the array data
	GradePrinter(outfile, StudentID, Grade, Noofstudents);					//prints the processed grade
	outfile << "The lowest test score was " << Grade[LowScoreindex(Grade, Noofstudents)] << " achieved by student #" << StudentID[LowScoreindex(Grade, Noofstudents)] << endl << endl;
	outfile << "The highest test score was " << Grade[HighScoreindex(Grade, Noofstudents)] << " achieved by student #" << StudentID[HighScoreindex(Grade, Noofstudents)] << endl << endl;
	outfile << "The average test score for the group is " << setprecision(2) << fixed <<  AvgScore(Grade,Noofstudents) << endl << endl;
	Footer(outfile);														//prints the footer for the project.
	return(0);
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
	Outfile << setw(20) << "Assignment #2" << endl;
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
void FileReader(ifstream& infile, int StudentId[], float Grade[], int& Noofstudents)
{
//Function:	FileReader
//Receives: Input file, array for student id, array for grade, int for no of students
//Tasks:	Reads the inpu file and stores in the array
//Returns:  Nothing.
	int ID;
	float Marks;
	Noofstudents = 0;

	while(infile>>ID>>Marks)						//store the data from file to variables
	{
		if(ID < 0)									//stop when negative number is read
		{
			break;
		}
		if (Marks > 100)
		{
			Marks = 100;                            //Marks cannot go above hundred
		}
		StudentId[Noofstudents] = ID;				// fill the array with the data
		Grade[Noofstudents] = Marks;
		++Noofstudents;
	}
	return;
}
//********************************************** End of FileReader Function *******************************************************//

//---------------------------------------------------------------------------------------------------------------------------------//

//********************************************** ArrayPrinter Function ************************************************************//
void ArrayPrinter(ofstream& Outfile, int StudentId[], float Grade[], int& Noofstudents)
{
//Function:	ArrayPrinter.
//Receives: output file, array for student id, array for grade, int for no of students.
//Tasks:	Prints the array into the output file.
//Returns:  Nothing.
	Outfile << "The Original list of test scores is:" << endl;
	Outfile << "Student ID #   Test Score" << endl;
	for (int i = 0; i < Noofstudents; i++)								// loop through the array and print it out.
	{
		Outfile << " "<< StudentId[i] << "            " << setprecision(2) << fixed << Grade[i] << endl;
	}
	Outfile << endl << endl;
	return;
}
//********************************************** End of ArrayPrinter Function *******************************************************//

//-----------------------------------------------------------------------------------------------------------------------------------//

//************************************************** GradePrinter Function **********************************************************//
void GradePrinter(ofstream& outfile,int StudentId[], float Grade[], int& Noofstudents)
{
//Function:	GradePrinter.
//Receives: output file, array for student id, array for grade, int for no of students.
//Tasks:	Prints the grade of the students
//Returns:  Nothing.
	outfile << "Student Receiving Garade of A are: ";
	for (int i = 0; i < Noofstudents; i++)			//loop through array to find all the students with grade above 90
	{
		if (Grade[i] > 90)
		{
			outfile << StudentId[i] << " ";
		}	
	}
	outfile << endl;

	outfile << "Student Receiving Garade of B are: ";
	for (int i = 0; i < Noofstudents; i++)			//loop through array to find all the students with grade above 80 and below 90
	{
		if (Grade[i] >= 80 && Grade[i] < 90)
		{
			outfile << StudentId[i] << " ";
		}
	}
	outfile << endl;

	outfile << "Student Receiving Garade of C are: ";
	for (int i = 0; i < Noofstudents; i++)			//loop through array to find all the students with grade above 70 and below 80
	{
		if (Grade[i] >= 70 && Grade[i] < 80)
		{
			outfile << StudentId[i] << " ";
		}
	}
	outfile << endl;

	outfile << "Student Receiving Garade of D are: ";
	for (int i = 0; i < Noofstudents; i++)			//loop through array to find all the students with grade above 60 and below 70
	{
		if (Grade[i] >= 60 && Grade[i] < 70)
		{
			outfile << StudentId[i] << " ";
		}
	}
	outfile << endl;

	outfile << "Student Receiving Garade of F are: ";
	for (int i = 0; i < Noofstudents; i++)			//loop through array to find all the students with grade below 60
	{
		if (Grade[i] < 60)
		{
			outfile << StudentId[i] << " ";
		}
	}
	outfile << endl << endl;
	return;
}
//************************************************** End of GradePrinter Function ********************************************************//

//----------------------------------------------------------------------------------------------------------------------------------------//

//************************************************** LowScoreIndex Function **************************************************************//
int LowScoreindex(float Grades[], int& Noofstudents)
{
//Function:	LowScoreindex.
//Receives: array for grade, int for no of students.
//Tasks:	Finds the stodent with lowest grade.
//Returns:  Location of student with lowest grade.
	int Index = 0;
	float LowestGrade = 100;								//seed value for lowest grade
	for (int i = 0; i < Noofstudents; i++)					//loop through array to find the students with lowest grade
	{
		if (LowestGrade > Grades[i])
		{
			LowestGrade = Grades[i];
			Index = i;									
		}
	}
	return Index;											//Returns the location of the Lowest grade
}
//************************************************** End of LowScoreIndex Function *******************************************************//

//----------------------------------------------------------------------------------------------------------------------------------------//

//************************************************** HighScoreIndex Function **************************************************************//
int HighScoreindex(float Grades[], int& Noofstudents)
{
//Function:	HighScoreindex.
//Receives: array for grade, int for no of students.
//Tasks:	Finds the stodent with Highest grade.
//Returns:  Location of student with Highest grade.
	int Index = 0;
	float HighestGrade = 0;								//seed value for highest grade
	for (int i = 0; i < Noofstudents; i++)				//loop through array to find the students with Highest grade
	{
		if (HighestGrade < Grades[i])
		{
			HighestGrade = Grades[i];
			Index = i;
		}
	}
	return Index;										//Returns the location of the Highest grade
}
//************************************************** End of HighScoreIndex Function *******************************************************//

//----------------------------------------------------------------------------------------------------------------------------------------//

//************************************************** AvgScore Function **************************************************************//
float AvgScore(float Grades[], int& Noofstudents)
{
//Function:	AvgScore.
//Receives: array for grade, int for no of students.
//Tasks:	Finds the stodents average grade.
//Returns:  Average grade.
	float SumOfGrades = 0;								//seed value for sum of grades
	for (int i = 0; i < Noofstudents; i++)				//loop through array to find the sum of grades
	{
		SumOfGrades += Grades[i];
	}
	float Average = SumOfGrades / float(Noofstudents);	//calculate average
	return Average;										//return average grade
}
//************************************************** End of AvgScore Function *******************************************************//

//----------------------------------------------------------------------------------------------------------------------------------------//

//************************************************** End of the Program **************************************************************//

