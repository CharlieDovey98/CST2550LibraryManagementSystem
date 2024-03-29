// Library Management System, main.cpp

// Include all the libraries for the code to run.
#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <fstream>
#include <sstream>
#include <algorithm>
//Include the header files of the classes.
#include "person.h"
#include "book.h"
#include "member.h"
#include "librarian.h"

// declaring a global variable to check whether the books have been read in from the .csv file or not.
bool bookDataFileFound = false;

// A function to print out the librarian object Alexa.
void librarianPortal() {
    std::cout << "Librarian active: " << Alexa.getName() << ", ID:" << Alexa.getStaffID() << ".";
    std::cout << "\n------------------------------------------" << std::endl;
}

// A function to print out the main menu to the console.
int startMenu(int menuChoice) {
    std::cout << "\n-------------------Menu-------------------";
    std::cout << "\nPlease choose from the following options:"
              << "\n    [1] Add a member."
              << "\n    [2] View a member's borrowed books."
              << "\n    [3] Issue a book."
              << "\n    [4] Return a book."
              << "\n    [5] Exit the system." << std::endl;

    std::cout << "\nPlease enter your choice as a number: ";
    std::cin >> menuChoice;

    // A validation check using a while loop, guard statement.
    while (std::cin.fail() || menuChoice < 1 || menuChoice > 5) {// If the input is not an integer or is out of range get a new input from the user.
        std::cout << "Invalid choice. Please enter a number between 1 and 5." << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "\nPlease enter your choice as a number: ";
        std::cin >> menuChoice;
    }
    return menuChoice; // Once a correct input has been attained, return the input.
}

// A function to attain the .csv file, read in its data line by line, and create book objects from the data.
void attainTheLibraryInformationFile() {
    std::string fileName;
    std::ifstream inputFile;

    std::cout << "\nPlease enter the book data filename for the library management system (e.g. librarybooks.csv)" << std::endl;
    std::getline(std::cin, fileName);

    // A validation check using a while loop, guard statement.
    while (fileName.size() <= 4 || fileName.substr(fileName.size() - 4) != ".csv") { // Check if the filename has .csv file extension or is longer than length 4 (which is ".csv").
        std::cout << "Invalid file extension. Please ensure the file is a .csv file." << std::endl;
        std::cout << "Please enter the book data filename for the library management system (e.g. librarybooks.csv): ";
        std::getline(std::cin, fileName);
    }
    inputFile.open(fileName); // Attempt to open the filename provided.

    // A validation check using a while loop, guard statement.
    while (!inputFile.is_open()) { // If the file name specified cannot be opened, most likely due to the filename being incorrect or the file doesn't exist.
        std::cout << "Failed to open file: " << fileName << std::endl;
        std::cout << "Please check if the file exists in the current directory." << std::endl;
        std::cout << "Please enter the book data filename for the library management system (e.g. librarybooks.csv): ";
        std::getline(std::cin, fileName);
        inputFile.open(fileName);
    }
    
    bookDataFileFound = true;

    std::string line = "";
    std::getline(inputFile, line); // Attain the first line from the document, the cell headings.
    line = "";                     // Discard the first headings line, as we only want to add books to the book vector.

    while (std::getline(inputFile, line)) { // While there are still lines to be read in, within the .csv file, continue.
        int bookID;
        bool isIssued = false;
        std::string bookName;
        std::string pageCount;
        std::string authorFirstName;
        std::string authorLastName;
        std::string bookType;
        std::string temporaryString;

        std::stringstream inputString(line);

        getline(inputString, temporaryString, ','); // Allocating bookID to a temporary string.
        bookID = atoi(temporaryString.c_str());     // Converting bookId to an integer from the temporary string.
        getline(inputString, bookName, ',');
        getline(inputString, pageCount, ',');
        getline(inputString, authorFirstName, ',');
        getline(inputString, authorLastName, ',');
        getline(inputString, bookType, ',');

        std::string line = "";
        Book newBook(bookID, bookName, authorFirstName, authorLastName, isIssued);
        getBookList().push_back(newBook);
    }
    std::cout << "\nBooks added successfully\n";
}

// This function prints out each book that has been read in from the .csv file after the file has successfully been opened.
// This is not used in the main funcionality of the program. This function aids bug testing and marking of the program.
void printBooks() {
    const std::vector<Book> &books = getBookList(); // Use the getBookList() to access the vector of books.
    for (const Book &book : books) {                // For loop through to print each book for testing purposes. 
    
        std::cout << "Book ID: " << book.getBookID() << ", "
                  << book.getBookName() << ", "
                  << book.getAuthorFirstName() << ", "
                  << book.getAuthorLastName() << ", "
                  << book.isBookIssued() << std::endl;
    }
}

// The main function of my code.
int main(void) {
    while (true) { // A while loop to loop on the main code.

        int menuChoice;
        std::cout << "\nLibrary Management System V1.\n"
                  << std::endl;
        librarianPortal();

        if (bookDataFileFound == false){
            // A call the to the function to attain the library's book information.
            attainTheLibraryInformationFile();
            // A call to the function printBooks to print the now attained books the library system has in stock.
            // printBooks();
        }

        menuChoice = startMenu(menuChoice);
        const int ADD_MEMBER = 1;
        const int BORROWED_BOOKS = 2;
        const int ISSUE_BOOK = 3;
        const int RETURN_BOOK = 4;
        const int EXIT_SYSTEM = 5;

        // A switch case on the user input menuChoice to run the part of the program the user has selected.
        switch (menuChoice){

        case ADD_MEMBER:      // Add a member functionality.
            Alexa.addMember(); // Using librarian Alexa to add a new member.
            std::cout << "\n-----------Returning to the menu----------";
            break;

        case BORROWED_BOOKS: // View a members borrowed books functionality.
            int memberIDForBorrowedBooks;

            std::cout << "Please enter the member's ID to view their currently borrowed books: ";
            std::cin >> memberIDForBorrowedBooks;

            // A validation check using a while loop, guard statement.
            while (std::cin.fail() || Alexa.findMember(memberIDForBorrowedBooks) == nullptr){ // If memberID doesn't exist or std::cin fails.
                std::cout << "Invalid memberID. Please enter the memberID in numbers, of a registered member." << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Please enter the member's ID to view their currently borrowed books: ";
                std::cin >> memberIDForBorrowedBooks;
            }
            Alexa.displayBorrowedBooks(memberIDForBorrowedBooks);
            std::cout << "\n-----------Returning to the menu----------";
            break;

        case ISSUE_BOOK: // Issue a book to a member functionality.
            int memberIDToIssueABook, bookIDToIssueABook;
            bool memberIDIssueBoolean, bookIDIssueBoolean;

            std::cout << "Please enter the memberID of the member that wants to borrow a book: ";
            std::cin >> memberIDToIssueABook;

            // A validation check using a while loop, guard statement.
            while (std::cin.fail() || Alexa.findMember(memberIDToIssueABook) == nullptr){ // If memberID doesn't exist or std::cin fails.
                std::cout << "Invalid memberID. Please enter the memberID in numbers, of a registered member." << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Please enter the memberID of the member that wants to borrow a book: ";
                std::cin >> memberIDToIssueABook;
            }
            memberIDIssueBoolean = true;

            std::cout << "Please enter the bookID of the book that is being issued out: ";
            std::cin >> bookIDToIssueABook;

            // A validation check using a while loop, guard statement.
            while (std::cin.fail() || Alexa.findBook(bookIDToIssueABook) == nullptr){ // If bookID doesn't exist or std::cin fails.
                std::cout << "Invalid bookID. Please enter the bookID in numbers, of a in stock library book." << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Please enter the bookID of the book that is being issued out: ";
                std::cin >> bookIDToIssueABook;
            }

            bookIDIssueBoolean = true;

            if (memberIDIssueBoolean && bookIDIssueBoolean){
                Alexa.issueBook(memberIDToIssueABook, bookIDToIssueABook);
            }
            std::cout << "\n-----------Returning to the menu----------";
            break;

        case RETURN_BOOK: // Return a book from a member functionality.
            int memberIDToReturnABook, bookIDToReturnABook;
            bool memberIDReturnBoolean, bookIDReturnBoolean;

            std::cout << "Please enter the memberID of the member that wants to return a book: ";
            std::cin >> memberIDToReturnABook;

            // A validation check using a while loop, guard statement.
            while (std::cin.fail() || Alexa.findMember(memberIDToReturnABook) == nullptr){ // If memberID doesn't exist or std::cin fails.
                std::cout << "Invalid memberID. Please enter the memberID in numbers, of a registered member." << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Please enter the memberID of the member that wants to return a book: ";
                std::cin >> memberIDToReturnABook;
            }
            memberIDReturnBoolean = true;

            std::cout << "Please enter the bookID of the book that is being returned: ";
            std::cin >> bookIDToReturnABook;

            // A validation check using a while loop, guard statement.
            while (std::cin.fail() || Alexa.findBook(bookIDToReturnABook) == nullptr){ // If bookID doesn't exist or std::cin fails.
                std::cout << "Invalid bookID. Please enter the bookID in numbers, of a in stock library book." << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Please enter the bookID of the book that is being returned: ";
                std::cin >> bookIDToReturnABook;
            }

            bookIDReturnBoolean = true;

            if (memberIDReturnBoolean && bookIDReturnBoolean){
                Alexa.returnBook(memberIDToReturnABook, bookIDToReturnABook);
            }
            std::cout << "\n-----------Returning to the menu----------";
            break;

        case EXIT_SYSTEM: // Exit the system functionality.
            std::cout << "-----------System Exiting-----------" << std::endl;
            exit(0);
            break;
        }
    }
}