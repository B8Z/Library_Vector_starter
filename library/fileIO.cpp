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
	string line;
	ifstream myFile;

	myFile.open(filename);
	if (!myFile.is_open()) {
		return COULD_NOT_OPEN_FILE;
	}
	if (myFile.is_open()) {
		while (getline(myFile, line)) {
			book currentBook;
			stringstream ss(line);
			vector<string> extractedWords;
			string substring;
			while (getline(ss, substring, ',')) {
				extractedWords.push_back(substring);
			}
			if (extractedWords.size() != NONE) {
				currentBook.book_id = atoi(extractedWords[0].c_str());
				currentBook.title = extractedWords[1];
				currentBook.author = extractedWords[2];
				currentBook.state = book_checkout_state(
						atoi(extractedWords[3].c_str()));
				currentBook.loaned_to_patron_id = atoi(
						extractedWords[4].c_str());

				books.push_back(currentBook);

			}
		}
		myFile.close();
	}
	if (books.size() == 0) {
		return NO_BOOKS_IN_LIBRARY;
	}

	return SUCCESS;
}

/* serializes books to the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * 			NO_BOOKS_IN_LIBRARY if there are 0 entries books (do not create file)
 * 			SUCCESS if all data is saved
 * */
int saveBooks(std::vector<book> &books, const char *filename) {
	ofstream myFile;
	myFile.open(filename);
	if (!myFile.is_open()) {
		return COULD_NOT_OPEN_FILE;
	}
	if (myFile.is_open()) {
		for (int i = 0; i < books.size(); i++) {
			myFile
					<< to_string(books[i].book_id) + "," + books[i].title + ","
							+ books[i].author + "," + to_string(books[i].state)
							+ "," + to_string(books[i].loaned_to_patron_id);
			myFile << endl;
		}
		myFile.close();
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
	string line;
	ifstream myFile;

	myFile.open(filename);
	if (!myFile.is_open()) {
		return COULD_NOT_OPEN_FILE;
	}
	if (myFile.is_open()) {
		while (getline(myFile, line)) {
			patron currentPatron;
			stringstream ss(line);
			vector<string> extractedWords;
			string substring;
			while (getline(ss, substring, ',')) {
				extractedWords.push_back(substring);
			}
			if (extractedWords.size() != NONE) {
				currentPatron.patron_id = atoi(extractedWords[0].c_str());
				currentPatron.name = extractedWords[1];
				currentPatron.number_books_checked_out = atoi(
						extractedWords[2].c_str());

				patrons.push_back(currentPatron);
			}
		}
		myFile.close();
	}
	if (patrons.size() == 0) {
		return NO_PATRONS_IN_LIBRARY;
	}

	return SUCCESS;
}

/* serializes patrons to the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * 			NO_PATRONS_IN_LIBRARY if there are 0 entries in patrons  (do not create file)
 * 			SUCCESS if all data is saved
 * */
int savePatrons(std::vector<patron> &patrons, const char *filename) {
	ofstream myFile;
	myFile.open(filename);
	if (!myFile.is_open()) {
		return COULD_NOT_OPEN_FILE;
	}
	if (myFile.is_open()) {
		for (int i = 0; i < patrons.size(); i++) {
			myFile
					<< to_string(patrons[i].patron_id) + "," + patrons[i].name
							+ ","
							+ to_string(patrons[i].number_books_checked_out);
			myFile << endl;
		}
		myFile.close();
		return SUCCESS;
	}
	if (patrons.size() == 0) {
		return NO_PATRONS_IN_LIBRARY;
	}
	return SUCCESS;
}
