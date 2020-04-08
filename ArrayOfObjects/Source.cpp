//************************************  PROGRAM IDENTIFICATION  **************************************************
//*																												 *
//*   PROGRAM FILE NAME:  Project6.cpp          ASSIGNMENT #:  6            Grade: _________					 *
//*																												 *
//*   PROGRAM AUTHOR:																							 *
//*                   ___________________________________________________										 *
//*                                     Biraj Singh GC															 *
//*																												 *
//*   COURSE #:  CSC 24400 11                              DUE DATE: December 09, 2019							 *
//*																												 *
//****************************************************************************************************************

//***********************************  PROGRAM DESCRIPTION  ******************************************************
//*																												 *
//*   PROCESS: The program creates (defines) a class of objects in which each object will hold the data          *
//*   information about a group of employees of an IT company. The data will consist of the following information*
//*   Employee’s Identification Number, First Name, Last Name, Department, Title, Pay.This information is        *
//*   contained in a structure data type. Each object has a private variable member of the structure data type   * 
//*   the program then to instantiates an array of objects to be processed by your program.Each employee’s record*
//*   is an element of the array. The program then load the data from the input file and prints the data as      *
//*   suggested in input file.                                                                                   *
//*																												 *
//*																												 *
//*   USER DEFINED																								 *
//*    MODULES     : Class: division - Stores id number, first name, last name, department, title and payment    *			                
//*                  totalcalc- calculates the total amount of payment                                           *                            
//*					 arrange - sorts the array with ID from low to high                                          *
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

//************************************************* Division Class *********************************************************//
class division
{
public:
	division()										//Add constuctor of division class that initializes all value.
	{
		ID = 0;
		Pay = 0;
		FName, LName, DepName, Title = "";
	}
	void reinisialize(int id, string Fname, string Lname, string depname, string title, double PPAY)
	{
		//Function: Reinitialize
		//Receives: Id number, First and last name, department name, title, and payment amount.
		//Task - sets the value of the data inside the class
		//Returns - Nothing
		setid(id);
		setFname(Fname);
		setLname(Lname);
		setDepName(depname);
		setTitle(title);
		setpay(PPAY);
	}

	void setid(int num) { ID = num; }						//Create function to set id for the staff.
	int getid() { return ID; }								//Create function to returm the id.
	void setpay(double pay) { Pay = pay; }					//Create function to set the payment for the staff.
	double getPay() { return Pay; }							//Create function to return the payment.
	void setFname(string first) { FName = first; }			//Create function to set the first name of the staff.
	string getFname() { return FName; }						//Create function to return the firstname of the staff.
	void setLname(string Last) { LName = Last; }			//Create function to set the last name of the staff.
	string getLname() { return LName; }						//Create function to return the last name of the staff
	void setDepName(string dep) { DepName = dep; }			//Create function to set the department name
	string getdepname() { return DepName; }					//Create function to return the department name.
	void setTitle(string tit) { Title = tit; }				//Create function to set the title of the staff.
	string getTitle() { return Title; }						//Create function to return the title of the staff.
		
private:
	//declare the variable for the data of the staff.
	int ID;
	string FName, LName, DepName, Title;
	double Pay;											 		
};	
//************************************************End of Division Class ****************************************************//

/*Function prototypes*/

void Header(ofstream&);						//function to print the header for the project.
void Footer(ofstream&);						//function to print the footer for the project.
double totalcalc(division[], int);			//function to calculate the sum of all payments
void arrange(division[], int);				//function to sort the data from low to high accordinf to staff id.

/*End of function prototypes*/

//******************************************** main Function ***********************************************************//
int main()
{
	division Dataobjarray[50];										//declare array of objects of dicision class
	string data, firstname, lastname, department, position, field;	//declare variable for first and last name, department,position and field as string.
	double Payment;													//declare variable for payment ofstaff
	int IDnum,IDforchange;											//declare variavble for Id of the staff as int.
	int Noofdata = 0,memory_i = 0;									//declare seed value for no of data.
	ifstream infile("DATA6.txt", ios::in);							//import the data file.
	ofstream outfile("result.txt", ios::out);						//export the result text file.

	if (infile.fail())												//Error catcher 
	{
		cout << " The file was not found." << endl;
		exit(1);													//Exit the program
	}

	Header(outfile);												//Header function for the output
	getline(infile, data);											//load type of action line into data.
	while (!infile.eof())											//loop through the list
	{
		if (data.compare("Q") == 0)									//break the loop if type reads 'Q'
		{
			break;
		}

		if (data.compare("I") == 0)									//initialize and store data if type reads I.
		{
			//store the data into variable.
			getline(infile, field);
			stringstream ss1(field);
			ss1 >> IDnum;

			getline(infile, firstname);
			getline(infile, lastname);
			getline(infile, department);
			getline(infile, position);

			getline(infile, field);
			stringstream ss2(field);
			ss2 >> Payment;
			//use the variable to add the data into object inside the array
			Dataobjarray[Noofdata].reinisialize(IDnum, firstname, lastname, department, position, Payment);
			Noofdata++;
			arrange(Dataobjarray, Noofdata);						//Sort the data according to ID.
		}
		
		if (data.compare("P") == 0)									//Print the data if the type reads 'P'
		{
			getline(infile, field);
			if (field.compare("E") == 0)							//Print Entire stored data if the type reads 'E'
			{
				double sum = totalcalc(Dataobjarray, Noofdata);		//Calculate the sum for all payments.
				//format for the ouput
				outfile << "ID #   	       Name                  Department      Position          Pay    " << endl;
				outfile << "------------------------------------------------------------------------------" << endl;
				for (int i = 0; i < Noofdata; i++)					//loop through the array to print the data.
				{
					outfile<<setw(9)<<left<<Dataobjarray[i].getid()<<setw(14)<<Dataobjarray[i].getFname()<<Dataobjarray[i].getLname()<<setw(16)<<Dataobjarray[i].getdepname()<<Dataobjarray[i].getTitle()<<setw(9)<<right<<fixed<<setprecision(2)<<Dataobjarray[i].getPay()<<endl;
				}
				outfile << "------------------------------------------------------------------------------" << endl;
				outfile << "                            Total Amount of Payroll" << setw(27) << right << sum << endl<<endl;
				outfile << "********************************************************************************" << endl<<endl;

			}
			else													//Print mentioned data if the type reads 'S'
			{
				//Read the id to be printed
				getline(infile, field);
				stringstream ss3(field);	
				ss3 >> IDforchange;
				//find the id in the array of objects.															
				for (int i = 0; i < Noofdata; i++)				
				{
					if (Dataobjarray[i].getid() == IDforchange)
					{
						memory_i = i;
					}

				}
				//print the id with proper format
				outfile << "ID #   	       Name                  Department      Position          Pay    " << endl;
				outfile << "------------------------------------------------------------------------------" << endl;
				outfile << setw(9)<<left<<Dataobjarray[memory_i].getid()<<setw(14)<< Dataobjarray[memory_i].getFname() << Dataobjarray[memory_i].getLname() <<setw(16)<< Dataobjarray[memory_i].getdepname() << Dataobjarray[memory_i].getTitle() <<setw(9)<<right<<fixed<< Dataobjarray[memory_i].getPay() << endl<<endl;
				outfile << "********************************************************************************" << endl<<endl;		
			}
		}
		getline(infile, data);		
	}
	Footer(outfile);												//add the footer to the output file.
}
//******************************************* End of Main Function ************************************************************//
//---------------------------------------------------------------------------------------------------------------------------//
//********************************************** totalcalc Function ***********************************************************//
double totalcalc(division obofarray[],int Noofdata)
{
	//Function:	totalcalc.
	//Receives: Array of division class, number of data in array.
	//Tasks:	Sums up the total pay of the staffs.
	//Returns:  total sum of payments(double).

	double sum = 0;							//set seed value for sum
	for (int i = 0; i < Noofdata; i++)		//loop through the array
	{
		sum += obofarray[i].getPay();		//sum all the payment
	}
	return sum;								//return sum
}
//******************************************* End of totalclac Function *****************************************************//
//---------------------------------------------------------------------------------------------------------------------------//
//********************************************** arrange Function ***********************************************************//
void arrange(division obofarray[], int Noofdata)
{
	//Function:	arrange.
	//Receives: Array of division class, number of data in array.
	//Tasks:	Sorts the array low to high according to ID.
	//Returns:  Sorted array of division class.

	division tempobj;					//declare temprary division class.
	for (int i = 0; i < Noofdata-1; i++)//loop through the array
	{
		for (int j = i+1 ; j < Noofdata; j++)
		{
			if (obofarray[i].getid() > obofarray[j].getid())
			{
				tempobj = obofarray[i];
				obofarray[i] = obofarray[j];//exchange the data as required.
				obofarray[j] = tempobj;
			}
		}
	}
}
//******************************************* End of arrange Function ********************************************************//
//---------------------------------------------------------------------------------------------------------------------------//
//********************************************** Header Function ************************************************************//
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
	Outfile << setw(20) << "Assignment #6" << endl;
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
//********************************************** End of footer Function *********************************************************//
//********************************************** End of the Program ************************************************************//