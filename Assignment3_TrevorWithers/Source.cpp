#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
using namespace std;
//Trevor Withers
//Program to create arrays to store wine sale data including quarterly sales and yearly sales.
const int SIZE = 25;
const int QUARTERLY = 4;

void loadArrays(ifstream&, string[], double[][QUARTERLY], int&);
void findWine(const double[][QUARTERLY], int&, int&, int);
void printReport(ofstream&, string[], const double[][QUARTERLY], const double[], int, int);
void computeSum(const double[][QUARTERLY], double[], int);
void mostWineSold(double[], int&, int);

int main()
{
	double salesAmt[SIZE][4];  //no need to change your variable names to match mine!
	string wine[SIZE];
	double yearlySales[SIZE] = { 0.00 };
	int noWines;
	int highestRow, highestCol, mostSold;
	cout << fixed << setprecision(2);
	ifstream fin("wines.dat");
	if (!fin.is_open())
	{
		cout << "error opening wines.dat file - contact systems";
		system("pause");
		exit(-1);
	}
	ofstream fout("winesales.rpt");
	if (!fout.is_open())
	{
		cout << "error opening winesales.rpt file - contact systems";
		system("pause");
		exit(-2);
	}
	fout << fixed << setprecision(2);

	cout << "\n\nLoad arrays\n\n";
	loadArrays(fin, wine, salesAmt, noWines);
	cout << "\n\n=======================================================\n\n";

	cout << "\n\nCompute yearly Sale\n\n";
	computeSum(salesAmt, yearlySales, noWines);
	cout << "\n\n=======================================================\n\n";

	cout << "\n\nFind best selling wine and highest sales amount:\n\n";
	findWine(salesAmt, highestRow, highestCol, noWines);
	cout << "\n\n" << wine[highestRow] << " had the highest sales amount = $"
		<< salesAmt[highestRow][highestCol] << endl;
	cout << "\n\n=======================================================\n\n";

	cout << "\n\nFind the most sold wine:\n\n";
	mostWineSold(yearlySales, mostSold, noWines);
	cout << "\n\n Most sold wine is " << wine[mostSold] << endl;

	cout << "\n\n=======================================================\n\n";
	printReport(fout, wine, salesAmt, yearlySales, mostSold, noWines);
	cout << "\n\n=======================================================\n\n";

	cout << "program ended successfully" << endl;
	cout << "\n\n Printing wines.dat file\n\n";
	system("type wines.dat");
	cout << "\n\n Printing winesales.rpt file\n\n";
	system("type winesales.rpt");
	system("pause");

}

/// <summary>
/// Fills arrays with data from file
/// </summary>
/// <param name="fin"></param>
/// <param name="wine"></param>
/// <param name="salesAmt"></param>
/// <param name="noWines"></param>
void loadArrays(ifstream& fin, string wine[], double salesAmt[][QUARTERLY], int& noWines)
{
	noWines = 0;
	for (int row = 0; row < SIZE; row++)
	{
		getline(fin, wine[row]);
		if (fin.eof())
		{
			break;
		}

		for (int col = 0; col < QUARTERLY; col++)
		{
			fin >> salesAmt[row][col];
		}
		noWines++;
		fin.ignore(80, '\n');
	}
}

/// <summary>
/// Calculates yearly sales based on the quarterly sales
/// </summary>
/// <param name="salesAmt"></param>
/// <param name="yearlySales"></param>
/// <param name="noWines"></param>
void computeSum(const double salesAmt[][QUARTERLY], double yearlySales[], int noWines)
{
	for (int row = 0; row < noWines; row++)
	{
		for (int col = 0; col < QUARTERLY; col++)
		{
			yearlySales[row] += salesAmt[row][col];
		}
	}
}

/// <summary>
/// Finds the wine with the most sales in a particular quarter.
/// </summary>
/// <param name="salesAmt"></param>
/// <param name="highestRow"></param>
/// <param name="highestCol"></param>
/// <param name="noWines"></param>
void findWine(const double salesAmt[][QUARTERLY], int& highestRow, int& highestCol, int noWines)
{
	double highest = 0.0;
	for (int row = 0; row < noWines; row++)
	{
		for (int col = 0; col < QUARTERLY; col++)
		{
			if (highest < salesAmt[row][col])
			{
				highest = salesAmt[row][col];
				highestRow = row;
				highestCol = col;
			}
		}
	}
}

/// <summary>
/// Finds the wine with the most yearly sales
/// </summary>
/// <param name="yearlySales"></param>
/// <param name="mostSold"></param>
/// <param name="noWines"></param>
void mostWineSold(double yearlySales[], int& mostSold, int noWines)
{
	double highest = 0.0;
	for (int index = 0; index < noWines; index++)
	{
		if (highest < yearlySales[index])
		{
			highest = yearlySales[index];
			mostSold = index;
		}
	}
}

/// <summary>
/// Prints the report to a file
/// </summary>
/// <param name="fout"></param>
/// <param name="wine"></param>
/// <param name="salesAmt"></param>
/// <param name="yearlySales"></param>
/// <param name="mostSold"></param>
/// <param name="noWines"></param>
void printReport(ofstream& fout, string wine[], const double salesAmt[][QUARTERLY], const double yearlySales[], int mostSold, int noWines)
{
	double total = 0.0;
	fout << fixed << setprecision(2);
	fout << left << setw(5) << "Wine" << right << setw(43) << "Quarterly Sales" << endl;
	fout << right << setw(25) << "1st"
		<< setw(15) << "2nd" << setw(15) << "3rd" << setw(15) << "4th" << setw(15) << "Yearly" << endl << endl;
	for (int row = 0; row < noWines; row++)
	{
		fout << left << setw(10) << wine[row];
		for (int col = 0; col < QUARTERLY; col++)
		{
			fout << right << setw(15) << salesAmt[row][col];
		}
		fout << right << setw(15) << yearlySales[row];
		if (row == mostSold)
		{
			fout << " ***most sold***";
		}
		fout << endl;
	}

	for (int index = 0; index < noWines; index++)
	{
		total += yearlySales[index];
	}
	fout << endl << "Total Sales Amount $" << total << endl;
	system("type wineSales.rpt");
}

/*


	Load arrays



	=======================================================



	Compute yearly Sale



	=======================================================



	Find best selling wine and highest sales amount:



	Champagne had the highest sales amount = $66553344.08


	=======================================================



	Find the most sold wine:



	 Most sold wine is Champagne


	=======================================================

	Wine                             Quarterly Sales
						  1st            2nd            3rd            4th         Yearly

	Red             200000.00       50000.00       57000.00       16800.00      323800.00
	Rose             25000.00           0.00        4500.00        7800.00       37300.00
	White           300000.00        4400.00       23000.00        5300.00      332700.00
	Champagne       362566.22        5648.00      656879.23    66553344.08    67578437.53 ***most sold***
	Chardonnay     5599864.23       65687.55       45781.26     6598654.23    12309987.27
	Merlot         5689475.23      554127.66       45124.22      551247.23     6839974.34

	Total Sales Amount $87422199.14


	=======================================================

	program ended successfully


	 Printing wines.dat file

	Red
	200000.00       50000.00        57000.00        16800.00
	Rose
	25000.00                0.00      4500.00         7800.00
	White
	300000.00            4400.00            23000.00              5300.00
	Champagne
	362566.22                        5648.00                        656879.23                         66553344.08
	Chardonnay
	5599864.23                       65687.55                       45781.26                          6598654.23
	Merlot
	5689475.23                       554127.66                      45124.22                          551247.23

	 Printing winesales.rpt file

	Wine                             Quarterly Sales
						  1st            2nd            3rd            4th         Yearly

	Red             200000.00       50000.00       57000.00       16800.00      323800.00
	Rose             25000.00           0.00        4500.00        7800.00       37300.00
	White           300000.00        4400.00       23000.00        5300.00      332700.00
	Champagne       362566.22        5648.00      656879.23    66553344.08    67578437.53 ***most sold***
	Chardonnay     5599864.23       65687.55       45781.26     6598654.23    12309987.27
	Merlot         5689475.23      554127.66       45124.22      551247.23     6839974.34

	Total Sales Amount $87422199.14
	Press any key to continue . . .

	C:\Users\withe\OneDrive - St. Lawrence College\Documents\School\St. Lawrence\Year 1\Semester 2\COMP1200\Projects\Assignment3_TrevorWithers\x64\Debug\Assignment3_TrevorWithers.exe (process 38376) exited with code 0.
	To automatically close the console when debugging stops, enable Tools->Options->Debugging->Automatically close the console when debugging stops.
	Press any key to close this window . . .
*/