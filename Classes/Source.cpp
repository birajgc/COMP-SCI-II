//************************************  PROGRAM IDENTIFICATION  **************************************************
//*																												 *
//*   PROGRAM FILE NAME:  Project5.cpp          ASSIGNMENT #:  5            Grade: _________					 *
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
//*   PROCESS:This program keeps track of the budget activities for an organization. The organization consist of *
//*   one Corporate Headquarters and five divisions.The program uses one class to maintain the information for   *
//*   each of the six (6) objects of the same class (1 Headquarters and 5 Divisions). It keeps track of each of  *
//*   the division's budgets and the corporation's budget. Budget Information that are monitored are: Division   *
//*   Balance, Division Credits, and Division Debits.This prograb then processes the input data and isitializes  *
//*   All the datas into an object. then the program prints the data as suggested into the input file.           *
//*																												 *
//*																												 *
//*   USER DEFINED																								 *
//*    MODULES     : Class: Division- Stores the ID, balance credit and debit abount of a division in an object  *
//*                  CAction -Adds credit to the credit amount and total balance                                 *			  
//*                  DAction -Add debit to the credit amount and subtract from total balance                     *
//*                  PSAction(division& ID, ofstream &outfile);	//print the data                                 *
//*                  Header– Adds Header to the program                                                          *
//*                  Footer– Adds footer to the program                                                          *
//*                                                                                                              * 
//****************************************************************************************************************

#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

//************************************************* Division Class *********************************************************//
class division
{
	public:
		division(int id, double Credit, double Debit, double Balance) //Add constructor function to initialize ID, debit, crdeit and balance.
		{
			setid(id);
			setbalance(Balance);
			setcredit(Credit);
			setdebit(Debit);
		}
		void setid(int num) { ID = num; }					//Create function to set ID for the division			
		int getid() { return ID; }							//Create function to return ID 
		void setbalance(double bal) { balance = bal; }		//Create function to set balance for the division
		double getbalance() { return balance;}				//Create function to return balance
		void setcredit(double crd) { credit = crd; }		//Create function to set credit for the division
		double getcredit() { return credit; }				//Create function to return credit
		void setdebit(double dbt) { debit = dbt; }			//Create function to set debit for the division
		double getdebit() { return debit; }					//Create function to return debit
	private:
		//declare the variable tfot the data to be stored in the class.
		int ID;
		double balance;
		double credit;
		double debit;

	/*Friend Function prototypes*/
	friend void CAction(division &ID , double credit);		//Add credit to the credit amount and total balance
	friend void DAction(division &ID, double debit);		//Add debit to the credit amount and subtract from total balance
	friend void PSAction(division& ID, ofstream &outfile);	//print the data
	/*End of Friend function prototype*/
};
//************************************************End of Division Class ****************************************************//

/*Function prototypes*/

void Header(ofstream&);																 //print the header for the project.
void Footer(ofstream&);											                     //print the footer for the project.

/*End of function prototype*/

//************************************************* Main Fuction *********************************************************//
int main()
{
	int Noofid = 0;																			//seed value for no of divisions		
	char Type, printway;																	//declare variable for type of action and way of printing
	int ID, IDforchange;																	//declare variable for ID and ID to be changed.
	double Balance, debit, credit, change,Id[5][4];											//declare variable for balance, debit and credit.
	ifstream infile("DATA5.txt", ios::in);													//import file.
	ifstream infile2("DATA5.txt", ios::in);													//import the same file again.
	ofstream outfile("result.txt", ios::out);												//export file.
	int id_fix = 0;
	double corpcrd = 0, corpdbt = 0, corpbal = 0;											//seed value for corporation totals.

	if (infile.fail())																		//Error catcher 
	{
		cout << " The file was not found." << endl;
		exit(1);																			//Exit the program
	}
	if (infile2.fail())																		//Error catcher 2
	{
		cout << " The file was not found." << endl;
		exit(1);																			//Exit the program
	}

	Header(outfile);																		//print the header for the project.
	while (infile >> Type)																    //loop through the list
	{
		if (Type == 'Q')																	//Quit the program if type reads 'Q'
			break;
		else if (Type == 'I')																//Read and initialize data if type reads 'I'
		{
			infile >> ID >> credit >> debit >> Balance;
			//store the data in an array.
			Id[Noofid][0] = ID;
			Id[Noofid][1] = credit;
			Id[Noofid][2] = debit;
			Id[Noofid][3] = Balance;
			Noofid++;
		}
	}
	//Use the array to store the data into objects.
	division ID1(Id[0][0], Id[0][1], Id[0][2], Id[0][3]);
	division ID2(Id[1][0], Id[1][1], Id[1][2], Id[1][3]);
	division ID3(Id[2][0], Id[2][1], Id[2][2], Id[2][3]);
	division ID4(Id[3][0], Id[3][1], Id[3][2], Id[3][3]);
	division ID5(Id[4][0], Id[4][1], Id[4][2], Id[4][3]);

	while(infile2 >> Type)																	//Go through the list again to perorm action in sequential steps.
	{
		if (Type == 'Q')																				
			break;																			//Quit the program if type reads 'Q'

		else if (Type == 'I')																//Read the data to move the cursor.
		{
			infile2 >> ID >> credit >> debit >> Balance;
			id_fix = ID;
		}

		else if (Type == 'C')																//Perfrom credit action if the tyoe reads 'C'
		{
			infile2 >> IDforchange >> change;
			//find the ID where the change is required and make the change
			if (IDforchange == ID1.getid())
			{
				CAction(ID1, change);
			}
			else if (IDforchange == ID2.getid())
			{
				CAction(ID2, change);
			}
			else if (IDforchange == ID3.getid())
			{
				CAction(ID3, change);
			}
			else if (IDforchange == ID4.getid())
			{
				CAction(ID4, change);
			}
			else if (IDforchange == ID5.getid())
			{
				CAction(ID5, change);
			}

		}
		else if (Type == 'D')																//Perfrom debit action if the tyoe reads 'C'
		{
			infile2 >> IDforchange >> change;
			//find the ID where the change is required and make the change
			if (IDforchange == ID1.getid())
			{
				DAction(ID1, change);
			}
			else if (IDforchange == ID2.getid())
			{
				DAction(ID2, change);
			}
			else if (IDforchange == ID3.getid())
			{
				DAction(ID3, change);
			}
			else if (IDforchange == ID4.getid())
			{
				DAction(ID4, change);
			}
			else if (IDforchange == ID5.getid())
			{
				DAction(ID5, change);
			}
		}
		else if (Type == 'P')																//Perfrom debit action if the tyoe reads 'C'
		{
			infile2 >> printway;
			//Find the way the data is to be printed.	
			if (printway == 'E')															//Print the entire data if the printtype is 'E'
			{
				//set the output format.
				outfile << "               Amount of     Amount of      Account" << endl;
				outfile << "Division ID    Credits       Debits         Balance" << endl;
				outfile << "---------------------------------------------------" << endl;
				//print the data accordint to initialized data.
				if (id_fix == ID1.getid())
				{
					PSAction(ID1, outfile);
					corpcrd = ID1.getcredit();
					corpdbt = ID1.getdebit();
					corpbal = ID1.getbalance();
				}
				else if (id_fix == ID2.getid())
				{
					PSAction(ID1, outfile);
					PSAction(ID2, outfile);
					corpcrd = ID1.getcredit() + ID2.getcredit();
					corpdbt = ID1.getdebit() + ID2.getdebit();
					corpbal = ID1.getbalance() + ID2.getbalance();
				}
				else if (id_fix == ID3.getid())
				{
					PSAction(ID1, outfile);
					PSAction(ID2, outfile);
					PSAction(ID3, outfile);
					corpcrd = ID1.getcredit() + ID2.getcredit()+ID3.getcredit();
					corpdbt = ID1.getdebit() + ID2.getdebit() + ID3.getdebit();
					corpbal = ID1.getbalance() + ID2.getbalance()+ ID3.getbalance();
				}
				else if (id_fix == ID4.getid())
				{
					PSAction(ID1, outfile);
					PSAction(ID2, outfile);
					PSAction(ID3, outfile);
					PSAction(ID4, outfile);
					corpcrd = ID1.getcredit() + ID2.getcredit() + ID3.getcredit()+ ID4.getcredit();
					corpdbt = ID1.getdebit() + ID2.getdebit() + ID3.getdebit()+ID4.getdebit();
					corpbal = ID1.getbalance() + ID2.getbalance() + ID3.getbalance() + ID4.getbalance();
				}
				else if (id_fix == ID5.getid())
				{
					PSAction(ID1, outfile);
					PSAction(ID2, outfile);
					PSAction(ID3, outfile);
					PSAction(ID4, outfile);
					PSAction(ID5, outfile);
					corpcrd = ID1.getcredit() + ID2.getcredit() + ID3.getcredit() + ID4.getcredit()+ ID5.getcredit();
					corpdbt = ID1.getdebit() + ID2.getdebit() + ID3.getdebit() + ID4.getdebit() + ID5.getdebit();
					corpbal = ID1.getbalance() + ID2.getbalance() + ID3.getbalance() + ID4.getbalance() + ID5.getbalance();
				}
				outfile << "---------------------------------------------------" << endl;
				outfile << "Corporation" << endl;
				outfile <<"Totals"<<fixed<<setprecision(2)<<right<<setw(16)<<corpcrd<<setw(14)<< corpdbt <<setw(15)<< corpbal << endl << endl;
				outfile << "***************************************************" << endl << endl;
			}
			else
			{
				infile2 >> IDforchange;														//Print the entire data if the printtype is 'E'
				//Set the output format
				outfile << "               Amount of     Amount of      Account" << endl;
				outfile << "Division ID    Credits       Debits         Balance" << endl;
				outfile << "---------------------------------------------------" << endl;
				//Find the object data to be printed
				if (IDforchange == ID1.getid())
				{
					PSAction(ID1, outfile);
				}
				else if (IDforchange == ID2.getid())
				{
					PSAction(ID2, outfile);
				}
				else if (IDforchange == ID3.getid())
				{
					PSAction(ID3, outfile);
				}
				else if (IDforchange == ID4.getid())
				{
					PSAction(ID4, outfile);
				}
				else if (IDforchange == ID5.getid())
				{
					PSAction(ID5, outfile);
				}
				outfile << endl;
				outfile << "***************************************************" << endl << endl;
			}
		}
	}
	Footer(outfile);																		//print	 the footer for the project.
}
//********************************************** End of Main Fuction *******************************************************//
//--------------------------------------------------------------------------------------------------------------------------//
//********************************************** CACTION Function ***********************************************************//
void CAction(division& ID, double credit)
{
	//Function:	CAction
	//Receives: object of Division class, and amount of credit
	//Tasks:	Add the credit amount in the credit and the total balance section.
	//Returns:	Updated division object

	ID.credit = ID.credit + credit;											//add the new credit amount in the credit section
	ID.balance = ID.balance + credit;										//add the new credit amount in the balance section
}
//********************************************** End of CAction Fuction *******************************************************//
//--------------------------------------------------------------------------------------------------------------------------//
//********************************************** DAction Function ***********************************************************//
void DAction(division& ID, double debit)
{
	//Function:	DAction
	//Receives: object of Division class, and amount of Debit
	//Tasks:	Add the Debit amount in the debit and subtract from total balance section.
	//Returns:	Updated division object

	ID.debit = ID.debit + debit;											//add the new debit amount in the debit section
	ID.balance = ID.balance - debit;										//add the new debit amount in the balance section
}
//********************************************** End of DAction Fuction *******************************************************//
//--------------------------------------------------------------------------------------------------------------------------//
//********************************************** PSAction Function ***********************************************************//
void PSAction(division& ID, ofstream& outfile)
{
	//Function:	PSAction
	//Receives: object of Division class, and amount of credit
	//Tasks:	Prints the data of the object.
	//Returns:	Updated division object

	outfile << setw(7) << setprecision(2) << fixed << ID.getid() << setw(15) << ID.getcredit() << setw(14) << ID.getdebit() << setw(15) << ID.getbalance() << endl;
}
//********************************************** End of PSAction Fuction *******************************************************//
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
	Outfile << setw(20) << "Assignment #5" << endl;
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