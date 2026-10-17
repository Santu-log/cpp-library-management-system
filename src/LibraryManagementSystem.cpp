#include "LibraryManagementSystem.h"
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>

int LibraryManagementSystem::readInt(const std::string& prompt) {
    while(true){std::cout<<prompt;std::string line;if(!std::getline(std::cin,line)) throw std::runtime_error("Input stream closed.");try{std::size_t used=0;int value=std::stoi(line,&used);if(used==line.size())return value;}catch(const std::exception&){}std::cout<<"Invalid input. Please enter a whole number.\n";}
}
std::string LibraryManagementSystem::readLine(const std::string& prompt){std::cout<<prompt;std::string value;if(!std::getline(std::cin,value))throw std::runtime_error("Input stream closed.");return value;}
void LibraryManagementSystem::showMenu() const {
 std::cout<<"\n========== LIBRARY MANAGEMENT SYSTEM ==========\n"
 <<"1. Add book                 2. Display all books\n3. Search books              4. Update book\n5. Delete book               6. Register member\n7. Display members           8. Remove member\n9. Issue book               10. Return book\n11. Display active loans    12. Display all loans\n13. Library statistics       0. Exit\n";
}
void LibraryManagementSystem::addBook(){int id=readInt("Book ID: ");auto title=readLine("Title: ");auto author=readLine("Author: ");auto isbn=readLine("ISBN: ");int copies=readInt("Number of copies: ");library_.addBook(Book(id,title,author,isbn,copies));std::cout<<"Book added.\n";}
void LibraryManagementSystem::updateBook(){int id=readInt("Book ID to update: ");auto title=readLine("New title: ");auto author=readLine("New author: ");auto isbn=readLine("New ISBN: ");int copies=readInt("New total copies: ");if(library_.updateBook(id,title,author,isbn,copies))std::cout<<"Book updated.\n";else std::cout<<"Book not found.\n";}
void LibraryManagementSystem::deleteBook(){int id=readInt("Book ID to delete: ");std::cout<<(library_.deleteBook(id)?"Book deleted.\n":"Book not found.\n");}
void LibraryManagementSystem::searchBooks() const {auto q=readLine("Search by title, author, or ISBN: ");auto matches=library_.searchBooks(q);if(matches.empty())std::cout<<"No matches found.\n";else for(auto b:matches)b->display();}
void LibraryManagementSystem::registerMember(){int id=readInt("Member ID: ");auto name=readLine("Name: ");auto email=readLine("Email: ");library_.registerMember(id,name,email);std::cout<<"Member registered.\n";}
void LibraryManagementSystem::removeMember(){int id=readInt("Member ID to remove: ");std::cout<<(library_.removeMember(id)?"Member removed.\n":"Member not found.\n");}
void LibraryManagementSystem::issueBook(){int b=readInt("Book ID: ");int m=readInt("Member ID: ");std::cout<<"Book issued. Loan ID: "<<library_.issueBook(b,m)<<" (14-day loan).\n";}
void LibraryManagementSystem::returnBook(){int id=readInt("Loan ID to return: ");double fine=library_.returnBook(id);std::cout<<"Book returned. Fine due: Rs "<<fine<<'\n';}
void LibraryManagementSystem::handleChoice(int c){switch(c){case 1:addBook();break;case 2:library_.displayBooks();break;case 3:searchBooks();break;case 4:updateBook();break;case 5:deleteBook();break;case 6:registerMember();break;case 7:library_.displayMembers();break;case 8:removeMember();break;case 9:issueBook();break;case 10:returnBook();break;case 11:library_.displayLoans(true);break;case 12:library_.displayLoans();break;case 13:library_.displayStatistics();break;case 0:running_=false;std::cout<<"Goodbye!\n";break;default:std::cout<<"Choose a listed menu option.\n";}}
void LibraryManagementSystem::run() {
    std::cout << "Welcome to the Library Management System.\n"
              << "Saved records will be loaded from books.txt, members.txt, and loans.txt.\n";
    while (running_) {
        try {
            showMenu();
            handleChoice(readInt("Choice: "));
        } catch (const std::runtime_error& e) {
            if (!std::cin) {
                std::cout << "\nInput closed. Exiting.\n";
                break;
            }
            std::cout << "Error: " << e.what() << '\n';
        } catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << '\n';
        }
    }
}
