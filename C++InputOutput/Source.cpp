
//************************************  PROGRAM IDENTIFICATION  *****************************************
//*                                                                                                     *
//*   PROGRAM FILE NAME:  Assignment 1.cpp        ASSIGNMENT #:  1          Grade: _________            *
//*                                                                                                     *
//*   PROGRAM AUTHOR:                                                                                   *
//*                   ___________________________________________________                               *
//*                                    Biraj Singh GC                                                   *
//*                                                                                                     *
//*   COURSE #:  CSC 24400 11                              DUE DATE: September 20, 2019                 *
//*                                                                                                     *
//*******************************************************************************************************

//*************************************  PROGRAM DESCRIPTION  *******************************************
//*                                                                                                     *
//*     PROCESS: This program is designed to read data from a text file and compile it into a "ticket"  *
//*      that can be used to see what type of vehicle is being used, how long the vehicle has been      *
//*      parked (or in the parking lot), and finally how much moeny is due to be paid.                  *
//*                                                                                                     *  
//*                                                                                                     *
//*                                                                                                     *
//*     USER DEFINED                                                                                    *
//*     MODULES     :  Output – Echo prints the ticket with new data.                                   * 
//*                    Header – Adds a header to the program.                                           *
//*                    Footer – Adds a footer to the program.                                           *
//*			  	       converter – Convert minutes into hours.                                          *
//*                    payment_calc – Calculates the amount of money to be paid.                        *
//*                                                                                                     *
//*                                                                                                     * 
//*******************************************************************************************************

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

int converter(int enter_time, int exit_time)		//The converter framework
{
	int hours = 0;									//Sets the integer for hours to 0, to be modified
	int total_mins = (exit_time - enter_time);		//Calculates the total minutes spent in the parking lot
	int total_hours = total_mins / 60;				//Calculates the total hours from the total minutes
	if (total_mins % 60 > 0)						//If statement that deducts whether or not minutes divided by 60 has a greater than 0 remainder
		hours = ++total_hours;						//If it does, then total_hours integer gets incremented by one
	else
		hours = total_hours;						//If not, then it sets the hours integer to equal the total_hours integer
	return hours;									//Returns the hours value
}

double payment_calc(string vtype, int enter_time, int exit_time)			//The payment_calc framework
{
	int hours = converter(enter_time, exit_time);
	double fees = 0;														//Creates the double variable fees to be used

	if (vtype.compare("C") == 0)											//Checks to see if the vehicle is a car
	{
		if (hours > 0 && hours <= 2)										//If the time in the parking lot is greater than 0 hours and less than or equal to 2 hours
			fees = hours * 0.20;											//Fees are hours multiplied by car hourly price
		else if (hours > 2 && hours <= 5)									//Else, if the hours are greater than 2 hours and less than or equal to 5 hours
			fees = (2 * 0.20) + (((double)hours - 2) * 0.15);				//Fees are first 2 hour fees plus remaining hours minus first 2 hours multiplied by car hourly price
		else																//Else, if none of the previous criteria are met
			fees = (2 * 0.20) + (3 * 0.15) + (((double)hours - 5) * 0.05);	//Fees are first 5 hour fees plus remaining hours minus first 5 hours multiplied by car hourly price
	}

	else if (vtype.compare("T") == 0)										//Checks to see if the vehicle type is a truck
	{
		if (hours == 1)														//If the time in the parking lot is equal to 1 hour
			fees = hours * 0.40;											//Fees are hours multiplied by truck hourly price
		else if (hours > 1 && hours <= 4)									//Else, if the hours are greater than 1 hour and less than or equal to 4 hours
			fees = (0.40) + (((double)hours - 1) * 0.25);					//Fees are first hour fees plus remaining hours minus first hour multiplied by truck hourly price
		else																//Else, if none of the previous criteria are met
			fees = (2 * 0.20) + (3 * 0.15) + (((double)hours - 5) * 0.05);	//Fees are the first 5 hour fees plus remaining hours minus first 5 hours multiplied by truck hourly price
	}

	else if (vtype.compare("S") == 0)										//Checks to see if the vehicle is a senior one
	{
		fees = hours * 0.12;												//Fees are hours in parking lot multiplied by senior hourly price
	}
	return fees;
}

//*****************************************  FUNCTION OUTPUT  *****************************************
//Receives - fees, hours, enter_time, exit_time, typev, printt
//Task - Outputs the finalised ticket
//Returns - Nothing
void Output(ofstream& Outfile, double fees, int hours, int enter_time, int exit_time, string typev, string printt)
{
	Outfile << " The input data was: " << endl;														//Provides informative text prior to the ticket information
	Outfile << "   " << typev << " " << enter_time << " " << exit_time << endl << endl;				//Provides the data regarding vehicle type, entry time, and exit time
	Outfile << " $$$$$$$$$$$$$$$$$$$$$$$$$$ " << endl;												//Provides the border and preliminary text for the ticket
	Outfile << " $                        $ " << endl;
	Outfile << " $    MISSOURI WESTERN    $ " << endl;
	Outfile << " $       UNIVERSITY       $ " << endl;
	Outfile << " $                        $ " << endl;
	Outfile << " $$$$$$$$$$$$$$$$$$$$$$$$$$ " << endl;
	Outfile << " $      PARKING FEE       $ " << endl;
	Outfile << " $                        $ " << endl;
	Outfile << " $  Customer              $ " << endl;
	Outfile << " $  Category:  " << setw(6) << left << printt << "     $ " << endl;				//Provides and includes the category of vehicle on the ticket
	Outfile << " $                        $ " << endl;
	Outfile << " $  Time:      " << setw(3) << left << hours << "hours" << "   $" << endl;		//Provides and includes the time spent in the parking lot by the vehicle
	Outfile << " $                        $ " << endl;
	Outfile << " $  Amount                $ " << endl;
	Outfile << " $  Paid:      " << "$" << setw(4) << left << fees << "      $ " << endl;		//Provides and includes the amount necessary to be paid
	Outfile << " $                        $ " << endl;
	Outfile << " $$$$$$$$$$$$$$$$$$$$$$$$$$ " << endl;
	Outfile << " \n" << endl;
}
//**************************************  END OF FUNCTION OUTPUT  *************************************



//*****************************************  FUNCTION HEADER  *****************************************
//Receives - Output file
//Task - Prints the output preamble
//Returns - Nothing
void Header(ofstream& Outfile)
{
	Outfile << setw(30) << "Biraj Singh GC";
	Outfile << setw(17) << "CSC 24400";
	Outfile << setw(15) << "Section 11" << endl;
	Outfile << setw(30) << "Fall 2019";
	Outfile << setw(20) << "Assigment 1" << endl;
	Outfile << setw(35) << "----------------------------------";
	Outfile << setw(35) << "----------------------------------" << endl << endl;
	return;
}
//**************************************  END OF FUNCTION HEADER  *************************************



//*****************************************  FUNCTION FOOTER  *****************************************
//Receives - Output file
//Task - Prints the output
//Returns - Nothing
void Footer(ofstream& Outfile)
{
	Outfile << endl;
	Outfile << setw(35) << "----------------------------------" << endl;
	Outfile << setw(35) << "|    END OF PROGRAM OUTPUT       |" << endl;
	Outfile << setw(35) << "----------------------------------" << endl;
	return;
}
//**************************************  END OF FUNCTION FOOTER  *************************************



void inputer(ifstream& infile, ofstream& Outfile)
{
	int enter_time;				//Creates an int variable for the entry time of a vehicle
	int exit_time;				//Creates an int variable for the exit time of a vehicle
	string vtype;				//Creates a string for the vehicle type
	string printt;				//Creates a string for the printing of the ticket

	while (infile >> vtype >> enter_time >> exit_time)	//Stores all the data in a variable through a loop
	{
		string printt;

		if (vtype.compare("C") == 0)					//Checks to see if the vehicle is a car
			printt = "Car";								//If it is, then the printt variable equals Car
		else if (vtype.compare("T") == 0)				//Checks to see if the vehicle is a truck
			printt = "Truck";							//If it is, then the printt variable equals Truck
		else if (vtype.compare("S") == 0)				//Checks to see if the vehicle is a senior
			printt = "SN";								//If it is, then the printt variable equals Senior

		Output(Outfile, payment_calc(vtype, enter_time, exit_time), converter(enter_time, exit_time), enter_time, exit_time, vtype, printt);	//Prints the ticket with all of the data on it
	}
}


int main()
{
	ifstream infile("data1.txt", ios::in);									//Declares a variable for the data text file, and inputs it (opens)
	ofstream Outfile("Ticket.txt", ios::out);								//Outputs the file where the data is meant to be printed off
	cout << "File successfully found, Ticket.txt created" << endl;			//Informs the user of a successful run

	Header(Outfile);														//Provides the file with a Header
	inputer(infile, Outfile);
	Footer(Outfile);														//Adds a Footer to the file
}

//___________________________________________________________________________________________________________________________________________________________________________
