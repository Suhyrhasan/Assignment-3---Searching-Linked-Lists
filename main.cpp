/*******************************************************************************
 * AUTHOR		 : Suhyr Hasan
 * STUDENT ID 	 : 1022520
 * Assignment #3 : Searching Linked Lists
 * CLASS 		 : CS1B
 * SECTION 		 : MW 7:30p - 9:50p
 * DUE DATE		 : 11/06/2019
 *****************************************************************************/
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include<cstdlib>
using namespace std;

// DECLARE struct
struct MovieInfo
{
	string title;
	string actor1;
	string actor2;
	string genre;
	string altGenre;
	string synopsis;
	double year;
	int rating;
	struct MovieInfo* next;
};
// Initializing Struct
struct MovieInfo* front = NULL;
struct MovieInfo* rear  = NULL;
/******************************************************************************
 * FUNCTION PrinterHeader
 * ____________________________________________________________________________
 * This function receives an assignment name, type and number then
 * 		outputs the appropriate class heading. asType is defaulted to Lab
 * 		as there are more labs than Assignments.
 * 		==> returns nothing - This will output the class heading.
 * ____________________________________________________________________________
 * PRE-CONDITIONS
 * 	  The following parameters need to have a defined value prior to calling
 * 	  the function:
 * 	  			  asName : Assignment Name
 * 	  			  asNum  : Assignment Number
 *				  asType : Assignment Type ==> THIS SHOULD CONTAIN:
 *				  							   'L' for Labs
 *				  							   'A' for Assignments
 *
 * POST-CONDITIONS
 * 	  This function will output the class heading.
 *
 ******************************************************************************/

string PrinterHeader(string asName,   // IN - Assignment Name
		int asNum ,      // IN - Assignment Number
		char asType)     // IN - Assignment Type ('L' = Lab,
//                       'A' = Assignment)
{
	ostringstream output;

	output << left;
	output << "**************************************************\n";
	output << "*  PROGRAMMED BY : Suhyr Hasan\n";
	output << "*  " << setw(14) << "STUDENT IDs" << ": 1022520 \n";
	output << "*  " << setw(14) << "CLASS"	     << ": CS1B - MW - 7:30p - 9:30p\n";
	output << "*  " ;

	// PROCESSING - This will adjust setws and format appropriately based
	//              based on if this is a lab 'L' or assignment.

	if(toupper(asType) == 'L')
	{
		output << "LAB #" << setw(9);
	}
	else
	{
		output << "ASSIGNMENT #" << setw(2);
	}
	output<< asNum << ": " << asName << endl;
	output << "**************************************************\n\n";
	output << right;


	return output.str();
}
/******************************************************************************
 * FUNCTION CreateList
 * ____________________________________________________________________________
 * This function will reads in all the data from InFile.txt and create a
 * linked list.
 *
 * PRE-CONDITIONS
 * 	  The following parameters need to have a defined value prior to calling
 * 	  the function:
 * 	                inFile = Input File
 *
 * POST-CONDITIONS
 * 	  This function will return the head of the linked list.
 ******************************************************************************/
MovieInfo *CreateList(ifstream &inFile) // In - Input File
{
	MovieInfo *perPtr;
	MovieInfo *searchPtr;
	bool found = false;
	// Will loop until the program
	// reaches NULL in the file.
	while(inFile && perPtr != NULL)
	{
		perPtr = new MovieInfo();
		getline(inFile, perPtr->title);
		getline(inFile, perPtr->actor1);
		getline(inFile, perPtr->actor2);
		getline(inFile, perPtr->genre);
		getline(inFile, perPtr->altGenre);
		inFile >> perPtr->year;
		inFile >> perPtr->rating;
		inFile.ignore(1000,'\n');
		getline(inFile, perPtr->synopsis);
		string emptyLine;
		getline(inFile, emptyLine);
		perPtr-> next = NULL;
		// If statement will make sure the
		//node is in alphabetical order.
		if (front == NULL || front->title > perPtr->title)
		{ // insert in front
			perPtr->next = front;
			front = perPtr;
		}
		else
		{ // insert in middle
			searchPtr = front;
			while (searchPtr->next != NULL && !found)
			{
				if (searchPtr->next->title > perPtr->title)
					found = true;
				else
					searchPtr = searchPtr -> next;
			}
			// insert the node
			perPtr->next = searchPtr->next;
			searchPtr->next = perPtr;
		}
	}
	return front;
}
/******************************************************************************
 * FUNCTION TitleWrap
 * ____________________________________________________________________________
 *  This function will word wrap the title to make sure it does not pass the
 *  character limit.
 * ____________________________________________________________________________
 * PRE-CONDITIONS
 * 	  The following parameters need to have a defined value prior to calling
 * 	  the function:
 * 	               out = Output File
 * 	               title = The title of the movie.
 * 	               maxLength = The max length of characters
 * 	                           the title can have.
 *
 * POST-CONDITIONS
 * 	  This function will not return anything.
 ******************************************************************************/
void TitleWrap(ofstream &out, // OUT  - Output File
		string title,  // IN   - The title of the movie.
		int maxLength) // CALC - The max length of characters
//        the title can have.
{
	string newTitle;
	int colWidth;
	colWidth =  67 - front->title.size();
	// IF statement will determine if the program should output
	// the whole title or cut off some of the characters and instead
	// include "..."
	if (title.size() > 46)
	{
		newTitle = title.substr(0, maxLength);
		out << left << setw(5) << " " <<  setw(colWidth - 9) << newTitle << "... ";
	}
	else if (title.size() <= 47)
	{
		out << left << setw(5) << " " <<  setw(colWidth) << title;
	}
}
/******************************************************************************
 * FUNCTION Actor1Wrap
 * ____________________________________________________________________________
 *  This function will word wrap the leading actor's name to make sure it does
 *  not pass the character limit.
 * ____________________________________________________________________________
 * PRE-CONDITIONS
 * 	  The following parameters need to have a defined value prior to calling
 * 	  the function:
 * 	               out = Output File
 * 	               actor = The name of the Leading actor.
 * 	               maxLength = The max length of characters
 * 	                           the actor's name can have.
 *
 * POST-CONDITIONS
 * 	  This function will not return anything.
 ******************************************************************************/
void Actor1Wrap(ofstream &out, // OUT  -  Output File
		string actor,  // IN   - The name of the Leading actor.
		int maxLength) // CALC - The max length of characters
//        the actor's name can have.
{
	string newActor;
	int actorWidth;
	actorWidth = 32 - front->actor1.size();
	// IF statement will determine if the program should output
	// the leading actor's whole name or cut off some the characters
	// and instead include "..."
	if (actor.size() > 19)
	{
		newActor = actor.substr(0, maxLength);
		out << left << setw(3) << " " <<  setw(actorWidth - 7) << newActor << "...";
	}
	else if (actor.size() <= 20)
	{
		out << left << setw(3) << " " <<  setw(actorWidth) << actor;
	}
}
/******************************************************************************
 * FUNCTION Actor2Wrap
 * ____________________________________________________________________________
 *   This function will word wrap the supporting actor's name to make sure it
 *   does not pass the character limit.
 * ____________________________________________________________________________
 * PRE-CONDITIONS
 * 	  The following parameters need to have a defined value prior to calling
 * 	  the function:
 * 	               out = Output File
 * 	               actor = The name of the supporting actor.
 * 	               maxLength = The max length of characters
 * 	                           the actor's name can have.
 *
 * POST-CONDITIONS
 * 	  This function will not return anything.
 ******************************************************************************/
void Actor2Wrap(ofstream &out, // OUT -  Output File
		string actor,  // IN   - The name of the Supporting actor.
		int maxLength) // CALC - The max length of characters
//             the actor's name can have.
{
	string newActor;
	int actorWidth;
	actorWidth = 25 - front->actor2.size();
	// IF statement will determine if the program should output
	// the supporting actor's whole name or cut off some the characters
	// and instead include "..."
	if (actor.size() > 19)
	{
		newActor = actor.substr(0, maxLength);
		out << left << setw(3) << " " <<  setw(actorWidth - 6) << newActor << "...";
	}
	else if (actor.size() <= 20)
	{
		out << left << setw(1) << " " <<  setw(actorWidth) << actor;
	}
}
/******************************************************************************
 * FUNCTION DisplayMenu
 * ____________________________________________________________________________
 * This function will output the entire list of movies, without including the
 * plot.
 * PRE-CONDITIONS
 * 	  The following parameters need to have a defined value prior to calling
 * 	  the function:
 * 	                out = Output File
 *
 * POST-CONDITIONS
 * 	  This function will not return anything.
 ******************************************************************************/
void DisplayMenu(ofstream &out) // OUT - Output File
{
	// If Statement- will make sure
	// to check if the stack if empty first.
	if(front == NULL)
	{
		cout << "\nCan" << '\'' << "t DISPLAY an empty stack!" << endl;
	}
	cout << "\nListing all movies!" << endl;
	out << "\nCOMPLETE MOVIE LISTING" << endl;
	out << "MOVIE #  TITLE";
	// will output and format the column
	out << left;
	out << setw(43) << " " << "YEAR";
	out << setw(1) << " " << "RATING";
	out << setw(2) << " " << "GENRE";
	out << setw(13) << " " << "ALT GENRE";
	out << setw(9) << " " << "LEAD ACTOR";
	out << setw(10) << " " << "SUPPORTING ACTOR";
	out << right << endl;
	out << "------- "
			<< "------------------------------------------------ "
			<< "---- "
			<< "------ "
			<< "----------------- "
			<< "----------------- "
			<< "------------------- "
			<< "------------------- "
			<< endl;
	MovieInfo *perPtr;
	perPtr = front;
	int counter = 0;
	int genreWidth;
	int altGenreWidth;
	genreWidth =  23 - perPtr->genre.size();
	altGenreWidth = 24 - perPtr->altGenre.size();
	while( perPtr != NULL)
	{
		counter++;
		// will make sure to output the first 10 movies
		if( counter <= 10)
		{
			out  << right << setw(4) << counter;
			TitleWrap(out, perPtr->title, 44);
			out  << right  << perPtr->year;
			out  << setw(4)	<< " " << perPtr->rating;
			out << left << setw(4) << " " <<  setw(genreWidth)    <<  perPtr->genre;
			out << left << setw(1) << " " <<  setw(altGenreWidth) <<  perPtr->altGenre;
			Actor1Wrap(out, perPtr->actor1, 15);
			Actor2Wrap(out, perPtr->actor1, 15);
			out << endl;
		}
		perPtr = perPtr -> next;
	}
}
/******************************************************************************
 * FUNCTION WordWrap
 * ____________________________________________________________________________
 * This function will word wrap the plot to make sure it outputs in the
 * correct format.
 * ____________________________________________________________________________
 * PRE-CONDITIONS
 * 	  The following parameters need to have a defined value prior to calling
 * 	  the function:
 * 	               out = Output File
 * 	               synopsis = The plot of the movie
 * 	               maxLength = The max length of characters
 * 	                           the each line should have.
 * POST-CONDITIONS
 * 	  This function will not return anything.
 ******************************************************************************/
void WordWrap(ofstream &out, // OUT - Output File
		string synopsis,  // IN - The plot of the movie
		std::string::size_type maxLength) // CALC - The max length of characters
//         the each line should have.
{
	string word;
	string line;
	for(std::string::size_type i = 0; i < synopsis.size(); i++ )
	{
		if(synopsis[i] != ' ')
		{
			word = word + synopsis[i];
		}
		else
		{
			if(line.size() + word.size() > maxLength)
			{
				out << line << endl;
				line.clear();
			}
			line = line + word + ' ';
			word.clear();
		}

	}
	if(line.size() + word.size() > maxLength)
	{
		out << line << endl;
		line.clear();
		out << word << endl;
	}
	else
	{
		line =  line + word;
		out << line << endl;
	}
}
/******************************************************************************
 * FUNCTION searchTitle
 * ____________________________________________________________________________
 *  This function will search for a title and then output the movie if the
 *  program finds it.
 * ____________________________________________________________________________
 * PRE-CONDITIONS
 * 	  The following parameters need to have a defined value prior to calling
 * 	  the function:
 * 	               out = Output File
 *
 * POST-CONDITIONS
 * 	  This function will not return anything
 ******************************************************************************/
void SearchTitle(ofstream &out) // OUT - Output File
{
	string search;
	cout << "\nWhich title are you looking for? ";
	getline(cin, search);
	cout << "\nSearching for the title " << search << endl;
	MovieInfo *perPtr = front;
	bool found = false;
	int line1Width = 10 - front->actor1.size();
	int line2Width = 10 - front->actor2.size();
	while(perPtr!= NULL && !found)
	{
		if (perPtr->title == search)
		{
			found = true;
			cout << "Found the movie " << search << "!" << endl;
			// Outputting results into OFile
			out <<"\n************************************";
			out << "***************************************\n";
			out << "Title: " << perPtr->title << endl;
			out << "----------------------------------------";
			out << "-----------------------------------\n";
			out << "Year: " << perPtr->year;
			out << setw(9) << " " << "Rating: " << perPtr->rating<< endl;
			out << "----------------------------------------";
			out << "-----------------------------------\n";
			out << "Leading Actor:    " << left << setw(26) << perPtr->actor1;
			out << right << setw(line1Width) << " " <<  "Genre 1: " << perPtr->genre << endl;
			out << "Supporting Actor: " << left << setw(25) << perPtr->actor2;
			out << right << setw(line2Width) << "  " << "Genre 2: " << perPtr->altGenre << endl;
			out << "----------------------------------------";
			out << "-----------------------------------\n";
			out << "Plot: " << endl;
			WordWrap(out, perPtr->synopsis, 75);
			out <<"************************************";
			out << "***************************************" << endl;
		}
		else
		{
			perPtr = perPtr -> next;
		}
	}
	if(!found){
		cout <<"Sorry, the movie \""<< search << "\" was not found." <<endl;
	}
}
/******************************************************************************
 * FUNCTION SearchGenre
 * ____________________________________________________________________________
 *  This function will search for a genre then output all the movies
 *  that have that genre specified for either the genre of the alternate genre.
 * ____________________________________________________________________________
 * PRE-CONDITIONS
 * 	  The following parameters need to have a defined value prior to calling
 * 	  the function:
 *
 * POST-CONDITIONS
 * 	  This function will return the proper index (of type int) to the calling
 * 	  function.
 ******************************************************************************/
void SearchGenre(ofstream &out) // OUT - Output File
{
	MovieInfo *perPtr = front;
	string search;
	int counter = 0;
	int genreWidth;
	int altGenreWidth;
	genreWidth =  23 - perPtr->genre.size();
	altGenreWidth = 24 - perPtr->altGenre.size();
	cout << "\nWhich genre are you looking for? ";
	getline(cin, search);
	cout << "\nSearching for the genre " << search << endl;
	while(perPtr!= NULL)
	{
		if (perPtr->genre == search || perPtr->altGenre == search)
		{
			counter++;
			if(counter == 1)
			{
				out << "\nSearch by genre for " << search << " found:" << endl;
				out << "MOVIE #  TITLE";
				out << left;
				out << setw(43) << " " << "YEAR";
				out << setw(1) << " " << "RATING";
				out << setw(2) << " " << "GENRE";
				out << setw(13) << " " << "ALT GENRE";
				out << setw(9) << " " << "LEAD ACTOR";
				out << setw(10) << " " << "SUPPORTING ACTOR";
				out << right << endl;
				out << "------- "
						<< "------------------------------------------------ "
						<< "---- "
						<< "------ "
						<< "----------------- "
						<< "----------------- "
						<< "------------------- "
						<< "------------------- "
						<< endl;
			}
			if( counter <= 10)
			{
				out  << right << setw(4) << counter;
				TitleWrap(out, perPtr->title, 44);
				out  << right  << perPtr->year;
				out  << setw(4)	<< " " << perPtr->rating;
				out << left << setw(4) << " " <<  setw(genreWidth)    <<  perPtr->genre;
				out << left << setw(1) << " " <<  setw(altGenreWidth) <<  perPtr->altGenre;
				Actor1Wrap(out, perPtr->actor1, 15);
				Actor2Wrap(out, perPtr->actor1, 15);
				out << endl;
			}
		}
		perPtr = perPtr -> next;
	}
	if( counter <= 0)
	{
		cout <<"Sorry, no movie for the genre, "<< search << " were found." <<endl;
	}
	else
	{
		cout << "Found " << counter << " movies for the genre "
				<< search << "!\n";

	}
}
/******************************************************************************
 * FUNCTION SearchActor
 * ____________________________________________________________________________
 * This function will search for an actor then output all the movies that have
 * that specified actor for as either a leading or supporting actor.
 * ____________________________________________________________________________
 * PRE-CONDITIONS
 * 	  The following parameters need to have a defined value prior to calling
 * 	  the function::
 * 	               out = Output File
 *
 * POST-CONDITIONS
 * 	  This function will not return anything
 ******************************************************************************/
void SearchActor(ofstream &out) // OUT - Output File
{
	MovieInfo *perPtr = front;
	string search;
	int counter = 0;
	int genreWidth;
	int altGenreWidth;
	genreWidth =  23 - perPtr->genre.size();
	altGenreWidth = 24 - perPtr->altGenre.size();
	cout << "\nWhich actor are you looking for? ";
	getline(cin, search);
	cout << "\nSearching for the actor " << search << endl;
	while(perPtr!= NULL)
	{
		if (perPtr->actor1 == search || perPtr->actor2 == search)
		{
			counter++;
			if(counter == 1)
			{
				out << "\nSearch by Actor for " << search << " found:" << endl;
				out << "MOVIE #  TITLE";
				out << left;
				out << setw(43) << " " << "YEAR";
				out << setw(1) << " " << "RATING";
				out << setw(2) << " " << "GENRE";
				out << setw(13) << " " << "ALT GENRE";
				out << setw(9) << " " << "LEAD ACTOR";
				out << setw(10) << " " << "SUPPORTING ACTOR";
				out << right << endl;
				out << "------- "
						<< "------------------------------------------------ "
						<< "---- "
						<< "------ "
						<< "----------------- "
						<< "----------------- "
						<< "------------------- "
						<< "------------------- "
						<< endl;
			}
			if( counter <= 10)
			{
				out  << right << setw(4) << counter;
				TitleWrap(out, perPtr->title, 44);
				out  << right  << perPtr->year;
				out  << setw(4)	<< " " << perPtr->rating;
				out << left << setw(4) << " " <<  setw(genreWidth)    <<  perPtr->genre;
				out << left << setw(1) << " " <<  setw(altGenreWidth) <<  perPtr->altGenre;
				Actor1Wrap(out, perPtr->actor1, 15);
				Actor2Wrap(out, perPtr->actor1, 15);
				out << endl;
			}
		}
		perPtr = perPtr -> next;
	}
	if( counter <= 0)
	{
		cout <<"Sorry, no movies for the actor, "<< search << " were found.\n";
	}
	else
	{
		cout << "Found " << counter << " movies for the actor "<< search << "!\n";
	}
}
/******************************************************************************
 * FUNCTION SearchYear
 * ____________________________________________________________________________
 *  This function will search for the program will search a year then output
 *  all the movies that have that were made during that year.
 * ____________________________________________________________________________
 * PRE-CONDITIONS
 * 	  The following parameters need to have a defined value prior to calling
 * 	  the function::
 * 	               out = Output File
 *
 * POST-CONDITIONS
 * 	  This function will not return anything
 ******************************************************************************/
void SearchYear(ofstream &out) // OUT - Output File
{
	MovieInfo *perPtr = front;
	int search;
	int counter = 0;
	int genreWidth;
	int altGenreWidth;
	bool found = false;
	genreWidth =  23 - perPtr->genre.size();
	altGenreWidth = 24 - perPtr->altGenre.size();
	// will make sure to loop until the user inputs a vaild input
	while (!found)
	{
		cout << "\nWhat year are you looking for? ";
		if (!(cin >> search))
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << endl;
			cout << "****Please input a number between 1878 and 3000 ****\n";
		}
		else
		{
			//If Statement
			if (search < 1878 ||search > 3000)
			{
				cout << "\n****The number " << search << " is an invalid entry        "
						" ****\n";
				cout << "****Please input a number between 1878 and 3000 ****\n";
			}
			else
			{
				cout << "\nSearching for the year: " << search << endl;
				while(perPtr!= NULL)
				{
					if (perPtr->year == search)
					{
						counter++;
						// // will make sure to output the layout only once
						if(counter == 1)
						{
							out << "\nSearch by Year for " << search << " found: " << endl;
							out << "MOVIE #  TITLE";
							out << left;
							out << setw(43) << " " << "YEAR";
							out << setw(1) << " " << "RATING";
							out << setw(2) << " " << "GENRE";
							out << setw(13) << " " << "ALT GENRE";
							out << setw(9) << " " << "LEAD ACTOR";
							out << setw(10) << " " << "SUPPORTING ACTOR";
							out << right << endl;
							out << "------- "
									<< "------------------------------------------------ "
									<< "---- "
									<< "------ "
									<< "----------------- "
									<< "----------------- "
									<< "------------------- "
									<< "------------------- "
									<< endl;
						}
						// will make sure to output the first 10 movies
						if( counter <= 10)
						{
							out  << right << setw(4) << counter;
							TitleWrap(out, perPtr->title, 44);
							out  << right  << perPtr->year;
							out  << setw(4)	<< " " << perPtr->rating;
							out << left << setw(4) << " " <<  setw(genreWidth)    <<  perPtr->genre;
							out << left << setw(1) << " " <<  setw(altGenreWidth) <<  perPtr->altGenre;
							Actor1Wrap(out, perPtr->actor1, 15);
							Actor2Wrap(out, perPtr->actor1, 15);
							out << endl;
						}
					}
					perPtr = perPtr -> next;
				}
				if( counter <= 0)
				{
					cout <<"Sorry, no movies for the year, "<< search << " were found.\n";
				}
				else
				{
					cout << "Found " << counter << " movies for the year "<< search << "!\n";
				}
				found = true;
			}
		}
	}
}
/******************************************************************************
 * FUNCTION SearchRating
 * ____________________________________________________________________________
 *  This function will search will search for a rating then output all the
 *  movies that have that have the same rating.
 * ____________________________________________________________________________
 * PRE-CONDITIONS
 * 	  The following parameters need to have a defined value prior to calling
 * 	  the function:
 * 	               out = Output File
 *
 * POST-CONDITIONS
 * 	  This function will not return anything.
 ******************************************************************************/
void SearchRating(ofstream &out) // OUT - Output File
{
	MovieInfo *perPtr = front;
	int search;
	int counter = 0;
	int genreWidth;
	int altGenreWidth;
	bool found = false;
	genreWidth =  23 - perPtr->genre.size();
	altGenreWidth = 24 - perPtr->altGenre.size();
	// will make sure to loop until the user inputs a vaild input
	while (!found)
	{
		cout << "\nWhich rating are you looking for? ";
		if (!(cin >> search))
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << endl;
			cout << "****Please input a number between 0 and 9 ****\n";
		}
		else
		{
			//If Statement
			if (search < 0 ||search > 9)
			{
				cout << "\n****The number " << search << " is an invalid entry     ****\n";
				cout << "****Please input a number between 0 and 9 ****\n";
			}
			else
			{
				while(perPtr!= NULL)
				{
					if (perPtr->rating == search)
					{
						counter++;
						// will make sure to only output the layout once
						if(counter == 1)
						{
							out << "\nSearch by Rating for " << search << " found:" << endl;
							out << "MOVIE #  TITLE";
							out << left;
							out << setw(43) << " " << "YEAR";
							out << setw(1) << " " << "RATING";
							out << setw(2) << " " << "GENRE";
							out << setw(13) << " " << "ALT GENRE";
							out << setw(9) << " " << "LEAD ACTOR";
							out << setw(10) << " " << "SUPPORTING ACTOR";
							out << right << endl;
							out << "------- "
									<< "------------------------------------------------ "
									<< "---- "
									<< "------ "
									<< "----------------- "
									<< "----------------- "
									<< "------------------- "
									<< "------------------- "
									<< endl;
						}
						// will make sure to output the first 10 movies
						if( counter <= 10)
						{
							out  << right << setw(4) << counter;
							TitleWrap(out, perPtr->title, 44);
							out  << right  << perPtr->year;
							out  << setw(4)	<< " " << perPtr->rating;
							out << left << setw(4) << " " <<  setw(genreWidth)    <<  perPtr->genre;
							out << left << setw(1) << " " <<  setw(altGenreWidth) <<  perPtr->altGenre;
							Actor1Wrap(out, perPtr->actor1, 15);
							Actor2Wrap(out, perPtr->actor1, 15);
							out << endl;
						}
					}
					perPtr = perPtr -> next;
				}
				if( counter <= 0)
				{
					cout <<"Sorry, no movies for the rating, "<< search << " were found.\n";
					found = true;
				}
				else
				{
					cout << "Found " << counter << " movies for the rating "<< search << "!\n";
					found = true;
				}
			}
		}
	}
}
/******************************************************************************
 * SEARCHING LINKED LISTS
 * ----------------------------------------------------------------------------
 * This program will allows a user to track/search their DVDs.
 * allow the user to specify an input and output files. Allow the user the
 * option to use a default file.
 * ----------------------------------------------------------------------------
 *	INPUT:
 *	      inp_file = The name of the input file
 *	      out_file  = The name of the output file
 *	      option    =  IN - The menu option
 *
 *	OUTPUT:

 *****************************************************************************/
int main()
{
	// In & Out file.
	ifstream inFile;
	ofstream out;

	// output header to console
	cout << PrinterHeader("Searching Linked Lists", 3 , 'A');

	string inp_file; // IN - The name of the input file
	string out_file; // IN - The name of the output file
	int option;      // IN - The menu option
	/**************************************************************************
	 * INPUT: The program will ask the user which input and output file they
	 *        would like to use. Then it will use an If Statement if the
	 *        user inputed a valid file or not.
	 *
	 * Example: What input file would you like to use?  : InFile.txt
	 *          What output file would you like to use? : OutFile.txt
	 **************************************************************************/

	cout << "What input file would you like to use (type d for default file)?  ";

	cin >> inp_file;

	cout << "What output file would you like to use (type d for default file)? ";

	cin >> out_file;

	// IF statement will check the user's input, if user inputs
	//  'd' the program will automatically open the default file
	if ( inp_file == "d")
	{
		inFile.open("BigInFile.txt");
	}
	else
	{
		inFile.open(inp_file.c_str());
	}
	if (inFile.fail()) {

		cout << "Unable to open input file" << endl;
		return -1;
	}
	// IF statement will check the user's input, if user inputs
	//  'd' the program will automatically open the default file
	if( out_file == "d")
	{
		out.open("OFile.txt");
	}
	else
	{
		out.open(out_file.c_str());
	}
	// Output header to file
	out << PrinterHeader("Searching Linked Lists", 3 , 'A');

	// This function will create a linked list.
	CreateList(inFile);
	/**************************************************************************
	 * INPUT: Using a while loop the program will display a menu to the user.
	 *        Then it will the ask the user to input their choice. Using an
	 *        If Statement the program will validate the user's input by making
	 *        sure the user input's an in and not a char. After the program
	 *        will use a switch statement.
	 *
	 * Example: DVD MENU OPTIONS
	 *          1.Output Entire List
	 *          2.Title Search
	 *          3.Genre Search
	 *          4.Actor Search
	 *          5.Year Search
	 *          6.Rating Search (0-9)
	 *          0.to Exit
	 *          Enter an option (0 to exit):
	 **************************************************************************/
	while(1)
	{
		// Enumating Menu Items
		enum menu {EXIT,DISPLAY,TITLE,GENRE,ACTOR,YEAR,RATING};
		// MENU OPTION
		cout << "\n\nDVD MENU OPTIONS" << endl;
		cout << "1 – Output Entire List" << endl;
		cout << "2 – Title Search" << endl;
		cout << "3 – Genre Search" << endl;
		cout << "4 – Actor Search" << endl;
		cout << "5 – Year Search" << endl;
		cout << "6 – Rating Search (0-9)" << endl;
		cout << "0 - EXIT" << endl;
		cout << "Enter an option (0 to exit): ";

		//If Statement
		if (!(cin >> option))
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "\n*** Please input a number between 0 and 6   ****\n";
		}
		else
		{
			cin.ignore(1000, '\n');
			switch (option) {
			/**************************************************************************
			 * Case DISPLAY : Using the function, DisplayMenu(out), the program will
			 *                will output the entire list of movies, without including
			 *                the plot.
			 *************************************************************************/
			case DISPLAY: {
				DisplayMenu(out);
			} break;
			/**************************************************************************
			 * Case TITLE : Using the function, SearchTitle, the program will search
			 *              for a title and then output the movie if the program finds.
			 *************************************************************************/
			case TITLE:{
				SearchTitle(out);
			} break;
			/**************************************************************************
			 * Case GENRE: Using the function, SearchGenre, the program will search
			 *             for a genre then output all the movies that have that genre
			 *             specified for either the genre of the alternate genre.
			 *************************************************************************/
			case GENRE:{
				SearchGenre(out);
			}break;
			/**************************************************************************
			 * Case ACTOR: Using the function, SearchActor, the program will search
			 *             for an actor then output all the movies that have that
			 *             specified actor for as either a leading or supporting actor.
			 *************************************************************************/
			case ACTOR: {
				SearchActor(out);
			}break;
			/**************************************************************************
			 * Case YEAR : Using the function, SearchYear, the program will search
			 *             for a year then output all the movies that have that were
			 *             made during that year.
			 *************************************************************************/
			case YEAR: {
				SearchYear(out);
			}break;
			/**************************************************************************
			 * Case RATING : Using the function, SearchRating, the program will search
			 *               for a rating then output all the movies that have that have
			 *               the same rating.
			 *************************************************************************/
			case RATING: {
				SearchRating(out);
			} break;
			/**************************************************************************
			 * Case 0 - When the user inputs '0' the program will end.
			 *
			 * Case default - If the user inputs an int less than 0 or greater then 6
			 *                the program will output an error message.
			 *************************************************************************/
			case EXIT: exit(1);

			default:
				cout << "\n****The number " << option << " is an invalid entry     ****"
				<< endl;
				cout << "****Please input a number between 0 and 6 ****";
				cout << endl;
			}// END OF SWITCH STATEMENT
		}// END OF IF STATEMENT
	}// END OF WHILE LOOP

	// CLOSE InFile & OFile
	inFile.close();
	out.close();
	return 0;
}
