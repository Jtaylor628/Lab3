#include <fstream>
#include <iostream>
#include <vector>
#include "StudentRecord.h"
#include "Grade.h"
#include <iomanip>
using namespace std;
bool ReadStudentRecord(StudentRecord* studentRecord, int& numberOfRecord);
bool readDelimiter(string input, std::vector<string>& output, char delimiter);
void PrintGrade(StudentRecord* studentRecord, int numberOfRecords);
double get_average_grade(StudentRecord* stundentRecord, int i);
int main()
{
	int numberOfRecords;
	StudentRecord studentRecord[1024];

	//Read StudentRecords
	ReadStudentRecord(studentRecord, numberOfRecords);

	//Print out read result
	cout << "There are " << numberOfRecords << " student records." << endl;



	//Calculation
	PrintGrade(studentRecord, numberOfRecords);

	cin.get();
}

void PrintGrade(StudentRecord* studentRecord, int numberOfRecords)
{
	cout << "\n\n\n";
	for (int i = 0; i < numberOfRecords; i++) {
		cout << "Name: " << studentRecord[i].name <<"\t\tFinal Score: "<<  fixed << setprecision(2) <<get_average_grade(studentRecord, i) << "\tLetter Grade: ";
		if (get_average_grade(studentRecord, i) >= 90)
			cout << "A";
		else if (get_average_grade(studentRecord, i) >= 80)
			cout << "B";
		else if (get_average_grade(studentRecord, i) >= 70)
			cout << "C";
		else if (get_average_grade(studentRecord, i) >= 60)
			cout << "D";
		else 
			cout << "F";
		
		cout << endl;



	}
}

double get_average_grade(StudentRecord * stundentRecord, int i)
{
	double final_exam_grade = stundentRecord[i].finalexam * 0.5;

	double midterm_examGrade = stundentRecord[i].finalexam * 0.25;
	double quiz1_percent = stundentRecord[i].quiz1;
	double quiz2_percent = stundentRecord[i].quiz2;
	double two_quizGrade = ((stundentRecord[i].quiz1 + stundentRecord[i].quiz2) / 20.0) * 100;
	double result;
	result = final_exam_grade + midterm_examGrade + 0.25 * two_quizGrade;
	return result;


}


///////////////////////////////////////////////////
//Function: Read Student Record from a file
//Return: bool
//		  true - success read student records
//		  false - faile to read student records
///////////////////////////////////////////////////
bool ReadStudentRecord(StudentRecord* studentRecord, int& numberOfRecords)
{
	using namespace std;
	ifstream is;
	const string INPUTFILENAME = "studentrecords.txt";
	try {
		is.open(INPUTFILENAME);

		numberOfRecords = 0;

		string readline;
		while (!is.eof())
		{
			is >> readline;
			cout << readline << endl;

			char delimiter = ',';
			std::vector<string> output;
			readDelimiter(readline, output, delimiter);

			int index = 0;
			std::vector<string>::iterator recordIterator;
			for (recordIterator = output.begin(); recordIterator != output.end(); recordIterator++)
			{
				switch (index)
				{
				case NAME:
					studentRecord[numberOfRecords].name = *recordIterator;
					break;
				case QUIZ1:
					studentRecord[numberOfRecords].quiz1 = std::stoi(*recordIterator);
					break;
				case QUIZ2:
					studentRecord[numberOfRecords].quiz2 = std::stoi(*recordIterator);
					break;
				case MIDTERM:
					studentRecord[numberOfRecords].midterm = std::stoi(*recordIterator);
					break;
				case FINALEXAM:
					studentRecord[numberOfRecords].finalexam = std::stoi(*recordIterator);
					break;
				}
				index++;
			}
			numberOfRecords++;
		}

		is.close();
	}
	catch (ifstream::failure e)
	{
		cout << "Exception Open/Read/Close file";
		return false;
	}
	return true;
}

/////////////////////////////////////////////////////////////////////////
//Function: readDelimiter, read delimiter string into a vector<string>
//parameter: 
//string input - input string
//std::vector<string>& output - return vector<string>
//char delimiter -- delimiter
//return: bool
//		true -- if there is delimiter in the string
//		false - if there is no string
/////////////////////////////////////////////////////////////////////////
bool readDelimiter(string input, std::vector<string>& output, char delimiter)
{
	string acc = "";
	
	for (int i = 0; i < input.size(); i++)
	{
		if (input[i] == delimiter)
		{
			output.push_back(acc);
			acc = "";
		}
		else
		{
			acc += input[i];
		}
	}
	if (acc.size() != 0)
		output.push_back(acc);
	else
	{
		if( input.size() == 0 )
			return false;
	}
	return true;
}