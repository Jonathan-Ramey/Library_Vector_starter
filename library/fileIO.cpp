//J.D. Ramey
//Project 3
#include <iostream>
#include <fstream>
#include <sstream>
#include "../includes_usr/fileIO.h"
using namespace std;
/* clears, then loads books from the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * 			NO_BOOKS_IN_LIBRARY if there are 0 entries in books
 * 			SUCCESS if all data is loaded
 * */
int loadBooks(std::vector<book> &books, const char *filename) {
	fstream inBooks;
	inBooks.open(filename);
	if (!inBooks.is_open()) {
		cout << "CANTOPENFILE" << endl;
		return COULD_NOT_OPEN_FILE;
	}
	string tempLine, tempstring;

	while (getline(inBooks, tempLine)) {
		book newBook;
		stringstream ss;
		ss.str(tempLine);
		getline(ss, tempstring, ',');
		newBook.book_id = stoi(tempstring);
		getline(ss, tempstring, ',');
		newBook.title = tempstring;
		getline(ss, tempstring, ',');
		newBook.author = tempstring;
		getline(ss, tempstring, ',');
		if (stoi(tempstring) == 1)
			newBook.state = IN;
		else
			newBook.state = OUT;
		getline(ss, tempstring, ',');
		newBook.loaned_to_patron_id = stoi(tempstring);
		books.push_back(newBook);
	}
	if (books.empty()) {
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
	ofstream outBooks;
	outBooks.open(filename);
	if (!outBooks.is_open()) {
		cout << "FILEWONTOPEN" << endl;
		return COULD_NOT_OPEN_FILE;
	}
	if (books.empty()) {
		cout << "EMPTY BOOKS" << endl;
		return NO_BOOKS_IN_LIBRARY;
	}
	for (int i = 0; i < books.size(); i++) {
		outBooks << books.at(i).book_id << ',' << books.at(i).title << ','
				<< books.at(i).author << ',' << books.at(i).state << ','
				<< books.at(i).loaned_to_patron_id << endl;
	}
	return SUCCESS;
}

/* clears, then loads patrons from the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * 			NO_PATRONS_IN_LIBRARY if there are 0 entries in patrons
 * 			SUCCESS if all data is loaded
 * */
int loadPatrons(std::vector<patron> &patrons, const char *filename) {
	fstream inPatrons;
	inPatrons.open(filename);
	if (!inPatrons.is_open()) {
		return COULD_NOT_OPEN_FILE;
	}

	string tempLine, tempstring;

	while (getline(inPatrons, tempLine)) {
		stringstream ss;
		patron newPatron;
		ss.str(tempLine);
		getline(ss, tempstring, ',');
		newPatron.patron_id = stoi(tempstring);
		getline(ss, tempstring, ',');
		newPatron.name = tempstring;
		getline(ss, tempstring, ',');
		newPatron.number_books_checked_out = stoi(tempstring);
		patrons.push_back(newPatron);
	}
	if (patrons.empty()) {
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
	ofstream outPatrons;
	outPatrons.open(filename);
	if (!outPatrons.is_open()) {
		return COULD_NOT_OPEN_FILE;
	}
	if (patrons.empty()) {
		return NO_PATRONS_IN_LIBRARY;
	}
	for (int i = 0; i < patrons.size(); i++) {
		outPatrons << patrons.at(i).patron_id << ',' << patrons.at(i).name
				<< ',' << patrons.at(i).number_books_checked_out << endl;
	}
	return SUCCESS;
}
