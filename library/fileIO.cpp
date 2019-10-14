#include "../includes_usr/fileIO.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;
/* clears, then loads books from the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * 			NO_BOOKS_IN_LIBRARY if there are 0 entries in books
 * 			SUCCESS if all data is loaded
 * */
int loadBooks(std::vector<book> &books, const char *filename) {
	//create ifstream myFile and temporary string line
	string line;
	ifstream myFile;

	//open file
	myFile.open(filename);

	//return COULD_NOT_OPEN_FILE if file isn't open
	if (!myFile.is_open()) {
		return COULD_NOT_OPEN_FILE;
	}

	//if file is open, continue
	if (myFile.is_open()) {
		//while there is another line in myFile
		while (getline(myFile, line)) {
			//create book object
			book currentBook;
			//create stringstream and split line string
			stringstream ss(line);
			//create vector to hold extracted words
			vector<string> extractedWords;
			//create substring to store words
			string substring;

			//while the split string has another line
			while (getline(ss, substring, ',')) {
				//push to extractedWords vector
				extractedWords.push_back(substring);
			}
			//if there are no words in extractedWords
			if (extractedWords.size() != NONE) {
				//populate correct book values
				currentBook.book_id = atoi(extractedWords[0].c_str());
				currentBook.title = extractedWords[1];
				currentBook.author = extractedWords[2];
				currentBook.state = book_checkout_state(
						atoi(extractedWords[3].c_str()));
				currentBook.loaned_to_patron_id = atoi(
						extractedWords[4].c_str());

				//push current book value to the books vector
				books.push_back(currentBook);
			}
		}
		//return NO_BOOKS_IN_LIBRARY if no books are in library
		if (books.size() == NONE) {
			return NO_BOOKS_IN_LIBRARY;
		}
		//close file
		myFile.close();
	}
	//return SUCCESS if books are properly loaded
	return SUCCESS;
}

/* serializes books to the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * 			NO_BOOKS_IN_LIBRARY if there are 0 entries books (do not create file)
 * 			SUCCESS if all data is saved
 * */
int saveBooks(std::vector<book> &books, const char *filename) {
	//create ofstream myFile
	ofstream myFile;

	//open file
	myFile.open(filename);

	//return COULD_NOT_OPEN_FILE if file isn't open
	if (!myFile.is_open()) {
		return COULD_NOT_OPEN_FILE;
	}

	//if file is open, continue
	if (myFile.is_open()) {
		//loop through books vector
		for (int i = 0; i < books.size(); i++) {
			//write book to file in proper format
			myFile
					<< to_string(books[i].book_id) + "," + books[i].title + ","
							+ books[i].author + "," + to_string(books[i].state)
							+ "," + to_string(books[i].loaned_to_patron_id);
			myFile << endl;
		}

		//close file
		myFile.close();

		//return SUCCESS if books properly saved
		return SUCCESS;
	}

	return SUCCESS;
}

/* clears, then loads patrons from the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * 			NO_PATRONS_IN_LIBRARY if there are 0 entries in patrons
 * 			SUCCESS if all data is loaded
 * */
int loadPatrons(std::vector<patron> &patrons, const char *filename) {
	//create ifstream myFile and temporary string line
	string line;
	ifstream myFile;

	//open file
	myFile.open(filename);

	//return COULD_NOT_OPEN_FILE if file isn't open
	if (!myFile.is_open()) {
		return COULD_NOT_OPEN_FILE;
	}

	//if file is open, continue
	if (myFile.is_open()) {
		//while there is another line in myFile
		while (getline(myFile, line)) {
			//create patron object
			patron currentPatron;
			//create stringstream and split line string
			stringstream ss(line);
			//create vector to hold extracted words
			vector<string> extractedWords;
			//create substring to store words
			string substring;

			//while the split string has another line
			while (getline(ss, substring, ',')) {
				//push to extractedWords vector
				extractedWords.push_back(substring);
			}
			//if extracted words vector isn't empty
			if (extractedWords.size() != NONE) {
				//populate correct patron values
				currentPatron.patron_id = atoi(extractedWords[0].c_str());
				currentPatron.name = extractedWords[1];
				currentPatron.number_books_checked_out = atoi(
						extractedWords[2].c_str());

				//push current patron value to the patrons vector
				patrons.push_back(currentPatron);
			}
		}
		//return NO_PATRONS_IN_LIBRARY if patrons array is empty
		if (patrons.size() == NONE) {
			return NO_PATRONS_IN_LIBRARY;
		}
		//close file
		myFile.close();
	}

	//return SUCCESS if patrons are properly loaded
	return SUCCESS;
}

/* serializes patrons to the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * 			NO_PATRONS_IN_LIBRARY if there are 0 entries in patrons  (do not create file)
 * 			SUCCESS if all data is saved
 * */
int savePatrons(std::vector<patron> &patrons, const char *filename) {
	//create ofstream myFile
	ofstream myFile;

	//open file
	myFile.open(filename);

	//return COULD_NOT_OPEN_FILE if file isn't open
	if (!myFile.is_open()) {
		return COULD_NOT_OPEN_FILE;
	}

	//if file is open, continue
	if (myFile.is_open()) {

		//loop through patrons vector
		for (int i = 0; i < patrons.size(); i++) {
			//write patron to file in proper format
			myFile
					<< to_string(patrons[i].patron_id) + "," + patrons[i].name
							+ ","
							+ to_string(patrons[i].number_books_checked_out);
			myFile << endl;
		}
		//if patrons vector is empty return NO_PATRONS_IN_LIBRARY
		if (patrons.size() == NONE) {
			return NO_PATRONS_IN_LIBRARY;
		}
		//close file
		myFile.close();
	}

	//return SUCCESS if patrons properly saved
	return SUCCESS;
}
