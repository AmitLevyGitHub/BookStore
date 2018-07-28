#include <iostream>
#include "Database.hpp"
#include "books.hpp"
#include "employees.hpp"
#include "supliers.hpp"
#include "customers.hpp"


int main(int argc, const char * argv[]) {
    
    Database &db = Database::getInstance();
    cout << books::count();
    //    books* book;
//    book->inventory();
    
}
