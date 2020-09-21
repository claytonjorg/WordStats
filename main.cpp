
/*
	Project Description: A program that collects the statistics of word, 
	number, and character usage in a file (redirected as the standard input). 

	Author: Clayton Jorgensen
	Date: 01/26/2018
	Last Modified: 02/1/2018

	Method of Choice: STL Maps
*/

/* Includes */
#include <iostream>
#include <string>
#include <cctype>
#include <iomanip>
#include <vector>
#include <map>

using namespace std;

/* Function Prototypes */
void Print_CharsOutput(map<char, int> &MyMap, const int maxDisplay);
void Print_WordOutput(map<string, int> &MyMap, map<string, int> &MyMapOrder, const int maxDisplay);
void Print_NumberOutput(map<string, int> &MyMap, map<string, int> &MyMapOrder, const int maxDisplay);

int GetDisplaySize(const int maxDisplay, int size);

/* Main Function */
int main()
{
	/* Declare Maps */
	map<char, int> map_Char;															// map_Char["char"] = int;
	map<string, int> map_Word;															// map_Word["string"] = int;
	map<string, int> map_Num;															// map_Num["string"] = int;

	map<string, int> map_W_order;														// map_W_order["string"] = int;
	map<string, int> map_N_order;														// map_N_order["string"] = int;

	map<string, int>::iterator track_words;												// Iterator for ordering
	map<string, int>::iterator track_nums;												// Iterator for ordering

	/* Declare our variables (uninitialized) */
	char ch;
	char ch2;
	string str;
	string str2;

	/* Declare our variables (initialized) */
	const int maxDisplay = 10;
	int words = 0;
	int nums = 0;

	/* Peek next char */
	ch = cin.peek(); 

	/* Phase 1 - Read in file as "input" and fill maps with data */
	while (!cin.eof())																	// Read until not at end of file
	{
		if (isalpha(ch))																// Checks whether ch is an alphabetic letter
		{
			str.clear();																// Empty our string so it displays properly
			while (isalpha(ch))															// While ch is an alphabetic letter loop
			{
				cin.get(ch);															// Read in char (ch)
				map_Char[ch]++;															// Increment map_Char

				ch2 = tolower(ch);														// Stores lowercase char (ch) in ch2
				str += ch2;																// Stores s1 and ch2 into string s1
				ch = cin.peek();														// Get next ch or exit loop
			}
			track_words = map_Word.find(str);											// Track order for displaying
			if (track_words == map_Word.end()) { map_W_order[str] = words++; }			// Cont.
			map_Word[str]++;															// Increment map_Word
		}
		else if (isdigit(ch))															// Checks whether ch is a decimal digit character
		{
			str2.clear();																// Empty our string so it displays properly
			while (isdigit(ch))															// While ch is a decimal digit character loop
			{
				cin.get(ch);															// Read in char (ch)
				map_Char[ch]++;															// Increment map_Char

				str2 += ch;																// Stores s2 and ch into string s2
				ch = cin.peek();														// Get next ch or exit loop
			}
			track_nums = map_Num.find(str2);											// Track order for displaying
			if (track_nums == map_Num.end()) { map_N_order[str2] = nums++; }			// Cont.
			map_Num[str2]++;															// Increment map_Num
		}
		else																			// Remianing chars
		{
			cin.get(ch);																// Read in char (ch)
			map_Char[ch]++;																// Increment map_Char
			ch = cin.peek();															// Peek
		}
	}

	/* Phase 2 - Output Results */
	Print_CharsOutput(map_Char, maxDisplay);											// Call
	Print_WordOutput(map_Word, map_W_order, maxDisplay);								// Call
	Print_NumberOutput(map_Num, map_N_order, maxDisplay);								// Call

	/* End Program */
	cin.ignore();
	cout << endl;

	return 0;																			// End of program - Good day
}

/* Function Definitions */

/* 
	*Note: Functions were used to clean up code in main.
*/

/* 
	Function: Print_CharsOutput
	Purpose: This function outputs all most used chars and how many times that char was used.
*/
void Print_CharsOutput(map<char, int> &MyMap, const int maxDisplay)
{
	int charsize = MyMap.size();																					// Get map size												
	int chardisplaysize = GetDisplaySize(maxDisplay, charsize);														// Get Loop size by calling GetDisplaySize()

	char charmostused;																					
	int charmostused_times;

	cout << "\nTotal " << charsize << " different characters, " << chardisplaysize 
		 << " most used characters:\n";																				// Output basic text to console

	if (!MyMap.empty())																								// Check that map isn't empty, if it is exit
	{
		for (int i = 0; i < chardisplaysize; i++)																	// Basic for loop to loop a max of 10 elements
		{
			charmostused = 0;																						// The most used char in current run
			charmostused_times = 0;																					// Number of times the mostused char has been used

			for (map<char, int>::iterator charii = MyMap.begin(); charii != MyMap.end(); charii++)					// For loop to run through a map
			{
				if (charmostused_times < charii->second)															// Contiue if less than else jump to else if
				{
					charmostused = charii->first;																	// Set the most used char to map_Char's Key
					charmostused_times = charii->second;															// Set number of times to map_Char's value
				}
				else if (charmostused_times == charii->second)														// if equal, continue
				{
					if (charmostused > charii->first)																// if greater than, continue
					{
						charmostused = charii->first;																// Set the most used char to map_Char's Key (Repeat)
						charmostused_times = charii->second;														// Set number of times to map_Char's value	(Repeat)
					}
				}
			}
			MyMap.erase(charmostused);																				// Clear most recent
																		
			switch (charmostused)																					// Displays chars to console using a switch
			{
			case '\t':
				cout << "No. " << i << ": " << setw(20) << left << "\\t" << charmostused_times << "\n";
				break;
			case '\n':
				cout << "No. " << i << ": " << setw(20) << left << "\\n" << charmostused_times << "\n";
				break;
			default:
				cout << "No. " << i << ": " << setw(20) << left << charmostused << charmostused_times << "\n";
			}
		}
	}
}

/*
	Function: Print_WordOutput
	Purpose : This function outputs all most used words and how many times that word was used.
*/
void Print_WordOutput(map<string, int> &MyMap, map<string, int> &MyMapOrder, const int maxDisplay)
{
	int wordsize = MyMap.size();																					// Get map size
	int worddisplaysize = GetDisplaySize(maxDisplay, wordsize);														// Get Loop size by calling GetDisplaySize()

	string wordmostused;
	int wordmostused_times;

	cout << "\nTotal " << wordsize << " different words, " << worddisplaysize << " most used words:\n";				// Output basic text to console

	if (!MyMap.empty())																								// Check that map isn't empty, if it is exit
	{
		for (int i = 0; i < worddisplaysize; i++)																	// Basic for loop to loop a max of 10 elements
		{
			wordmostused.clear();																					// Most used word in current run
			wordmostused_times = 0;																					// Number of times the mostused word has been used

			for (map<string, int>::iterator wordii = MyMap.begin(); wordii != MyMap.end(); wordii++)				// For loop to run through a map
			{
				if (wordmostused_times < wordii->second)															// Contiue if less than else jump to else if
				{
					wordmostused = wordii->first;																	// Set the most used char to map_Word's Key
					wordmostused_times = wordii->second;															// Set number of times to map_Word's value
				}
				else if (wordmostused_times == wordii->second)														// if equal, continue
				{
					if (MyMapOrder[wordmostused] > MyMapOrder[wordii->first])										// if greater than, continue
					{
						wordmostused = wordii->first;																// Set the most used char to map_Word's Key (Repeat)
						wordmostused_times = wordii->second;														// Set number of times to map_Word's value (Repeat)
					}
				}
			}
			MyMap.erase(wordmostused);																				// Clear most recent
			cout << "No. " << i << ": " << setw(20) << left << wordmostused << wordmostused_times << "\n";			// Display words to console
		}
	}
}

/*
	Function: Print_NumberOutput
	Purpose : This function outputs all most used numbers and how many times that number was used.
*/
void Print_NumberOutput(map<string, int> &MyMap, map<string, int> &MyMapOrder, const int maxDisplay)
{
	int numsize = MyMap.size();																						// Get map size
	int numdisplaysize = GetDisplaySize(maxDisplay, numsize);														// Get Loop size by calling GetDisplaySize()

	string nummostused;																				
	int nummostused_times;

	cout << "\nTotal " << numsize << " different numbers, " << numdisplaysize << " most used numbers:\n";			// Output basic text to console 

	if (!MyMap.empty())																								// Check that map isn't empty, if it is exit
	{
		for (int i = 0; i < numdisplaysize; i++)																	// Basic for loop to loop a max of 10 elements
		{
			nummostused.clear();																					// Most used number in current run
			nummostused_times = 0;																					// Number of times the mostused number has been used

			for (map<string, int>::iterator numii = MyMap.begin(); numii != MyMap.end(); numii++)					// For loop to run through a map
			{
				if (nummostused_times < numii->second)																// Contiue if less than else jump to else if
				{
					nummostused = numii->first;																		// Set the most used char to map_Num's Key
					nummostused_times = numii->second;																// Set number of times to map_Num's value
				}
				else if (nummostused_times == numii->second)														// if equal, continue
				{
					if (MyMapOrder[nummostused] > MyMapOrder[numii->first])											// if greater than, continue
					{
						nummostused = numii->first;																	// Set the most used char to map_Num's Key (Repeat)
						nummostused_times = numii->second;															// Set number of times to map_Num's value (Repeat)
					}
				}
			}
			MyMap.erase(nummostused);																				// Clear most recent
			cout << "No. " << i << ": " << setw(20) << left << nummostused << nummostused_times << "\n";			// Display numbers to console
		}
	}
}

/*
	Function: GetDisplaySize
	Purpose : This function returns a int with the size of the loop (0-10)
*/
int GetDisplaySize(const int maxDisplay, int size)
{
	if (maxDisplay <= size)								// if size is more than 10 only display 10
		return maxDisplay;								// return 10
	else
		return size;									// return smaller size instead of 10
}
