#include <string>
#include <vector>
#include <algorithm>
#include <time.h>
#include <iostream>

#include "../includes_usr/library.h"
#include "../includes_usr/datastructures.h"
#include "../includes_usr/fileIO.h"
using namespace std;

vector<book> books;
vector<patron> patrons;

//NOTE: please ensure patron and book data are loaded from disk before calling the following
//NOTE: also make sure you save patron and book data to disk any time you make a change to them
//NOTE: for files where data is stored see constants.h BOOKFILE and PATRONFILE

/*
 * clear books and patrons containers
 * then reload them from disk 
 */
void reloadAllData() {
	books.clear();
	patrons.clear();
	loadBooks(books, BOOKFILE.c_str());
	loadPatrons(patrons, PATRONFILE.c_str());
}

/**
 * checks to see if a patron is enrolled.
 *
 * returns FALSE if patron isn't enrolled
 * 			or TRUE if patron is enrolled
 */
bool patronEnrolled(int patronid) {
	for (patron eachPatron : patrons) {
		if (eachPatron.patron_id == patronid) {
			return true;
		}
	}
	return false;
}

/**
 * checks to see if a book is in collection.
 *
 * returns FALSE if book isn't in collection
 * 			or TRUE if book is in collection
 */
bool bookInCollection(int bookid) {
	for (book eachBook : books) {
		if (eachBook.book_id == bookid) {
			return true;
		}
	}
	return false;
}

/* checkout a book to a patron
 * first load books and patrons from disk
 * make sure patron enrolled (patronid is assigned to a patron in patrons container)
 * make sure book in collection (bookid is assigned to a book in books container)
 * 
 * see if patron can check out any more books 
 * 	if not return TOO_MANY_OUT patron has the MAX_BOOKS_ALLOWED_OUT
 * 	
 * if so then check the book out to the patron, set the following fields for the book in the
 * books container
 * book.loaned_to_patron_id = patronid;
 * book.state = OUT;
 * 
 * Finally save the contents of the books and patrons containers to disk
 * 
 * returns SUCCESS checkout worked
 *         PATRON_NOT_ENROLLED
 * 		   BOOK_NOT_IN_COLLECTION
 *         TOO_MANY_OUT patron has the max number of books allowed checked out
 */
int checkout(int bookid, int patronid) {
	loadBooks(books, BOOKFILE.c_str());
	loadPatrons(patrons, PATRONFILE.c_str());

	if (!bookInCollection(bookid)) {
		return BOOK_NOT_IN_COLLECTION;
	}
	if (!patronEnrolled(patronid)) {
		return PATRON_NOT_ENROLLED;
	}
	if (patrons[patronid].number_books_checked_out >= MAX_BOOKS_ALLOWED_OUT) {
		return TOO_MANY_OUT;
	} else {
		books[bookid].loaned_to_patron_id = patronid;
		books[bookid].state = OUT;
		patrons[patronid].number_books_checked_out++;
	}
	saveBooks(books, TMP_FILE.c_str());
	savePatrons(patrons, TMP_FILE.c_str());
	return SUCCESS;
}

/* check a book back in 
 * first load books and patrons from disk
 * make sure book in collection (bookid is assigned to a book in books container)
 *  	
 * if so find the the patron the book is checked out to and decrement his/hers number_books_checked_out
 * then check the book back in by marking the book.loaned_to_patron_id = NO_ONE and the book.state = IN;
 
 * Finally save the contents of the books and patrons containers to disk
 * 
 * returns SUCCESS checkout worked
 * 		   BOOK_NOT_IN_COLLECTION
 */
int checkin(int bookid) {
	loadBooks(books, BOOKFILE.c_str());
	loadPatrons(patrons, PATRONFILE.c_str());

	if (!bookInCollection(bookid)) {
		return BOOK_NOT_IN_COLLECTION;
	}

	patrons[books[bookid].loaned_to_patron_id].number_books_checked_out--;
	books[bookid].loaned_to_patron_id = NO_ONE;
	books[bookid].state = IN;

	saveBooks(books, TMP_FILE.c_str());
	savePatrons(patrons, TMP_FILE.c_str());

	return SUCCESS;
}

/*
 * enroll a patron, duplicate names are fine as patrons are uniquely identified by their patronid
 * first load books and patrons from disk
 * create a patron object, initialize its fields as appropriate, assign him/her the nextPatronID
 * then push the patron onto the patrons container
 * save all changes to the patrons container to disk
 * return 
 *    the patron_id of the person added
 */
int enroll(std::string &name) {
	loadBooks(books, BOOKFILE.c_str());
	loadPatrons(patrons, PATRONFILE.c_str());

	patron newPatron;

	newPatron.name = name;
	newPatron.number_books_checked_out = NONE;
	newPatron.patron_id = numbPatrons();
	patrons.push_back(newPatron);

	savePatrons(patrons, TMP_FILE.c_str());

	return newPatron.patron_id;
}

/*
 * the number of books in the books container
 * (ie. if 3 books returns 3)
 * 
 */
int numbBooks() {
	loadBooks(books, BOOKFILE.c_str());
	return books.size();
}

/*
 * the number of patrons in the patrons container
 * (ie. if 3 patrons returns 3)
 */
int numbPatrons() {
	loadPatrons(patrons, PATRONFILE.c_str());
	return patrons.size();
}

/*the number of books patron has checked out
 *
 *returns a positive number indicating how many books are checked out 
 *        or PATRON_NOT_ENROLLED         
 */
int howmanybooksdoesPatronHaveCheckedOut(int patronid) {
	if (!patronEnrolled(patronid)) {
		return PATRON_NOT_ENROLLED;
	}
	return patrons[patronid].number_books_checked_out;
}

/* search through patrons container to see if patronid is there
 * if so returns the name associated with patronid in the variable name
 * 
 * returns SUCCESS found it and name in name
 *         PATRON_NOT_ENROLLED no patron with this patronid
 */
int whatIsPatronName(std::string &name, int patronid) {
	if (!patronEnrolled(patronid)) {
		return PATRON_NOT_ENROLLED;
	}
	return SUCCESS;
}

