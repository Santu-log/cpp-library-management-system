#include "Library.h"
#include <cassert>
#include <cstdio>
#include <iostream>
#include <stdexcept>
#include <string>

int main(){
    std::remove("test_books.txt");
    std::remove("test_members.txt");
    std::remove("test_loans.txt");
    {
    Library library("test_");
    library.addBook(Book(1,"The C++ Programming Language","Bjarne Stroustrup","ISBN-001",2));
    assert(library.bookCount()==1);
    assert(library.findBook(1)->getAvailableCopies()==2);
    assert(library.searchBooks("stroustrup").size()==1);
    assert(library.searchBooks("missing").empty());
    assert(library.updateBook(1,"C++ Programming","Bjarne Stroustrup","ISBN-001",3));
    assert(library.findBook(1)->getTotalCopies()==3);
    library.registerMember(7,"Ada Lovelace","ada@example.com");
    assert(library.memberCount()==1);
    int loan=library.issueBook(1,7);
    assert(library.activeLoanCount()==1);
    assert(library.findBook(1)->getAvailableCopies()==2);
    bool rejected=false; try{library.deleteBook(1);}catch(const std::runtime_error&){rejected=true;} assert(rejected);

    // Reopen the library to verify that book, member, and active loan state persists.
    Library reopened("test_");
    assert(reopened.bookCount()==1);
    assert(reopened.memberCount()==1);
    assert(reopened.activeLoanCount()==1);
    assert(reopened.findBook(1)->getAvailableCopies()==2);
    assert(reopened.findMember(7)!=nullptr);
    assert(reopened.returnBook(loan)>=0.0);
    assert(reopened.activeLoanCount()==0);
    assert(reopened.findBook(1)->getAvailableCopies()==3);
    rejected=false; try{reopened.returnBook(loan);}catch(const std::runtime_error&){rejected=true;} assert(rejected);
    assert(reopened.deleteBook(1)); assert(reopened.bookCount()==0);
    rejected=false; try{reopened.addBook(Book(2,"","Author","ISBN-2",1));}catch(const std::invalid_argument&){rejected=true;} assert(rejected);
    }
    std::remove("test_books.txt");
    std::remove("test_members.txt");
    std::remove("test_loans.txt");
    std::cout<<"All library tests passed.\n";
}
