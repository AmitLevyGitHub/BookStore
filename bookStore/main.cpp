#include <iostream>
#include "Database.hpp"
#include "books.hpp"
#include "employees.hpp"
#include "suppliers.hpp"
#include "customers.hpp"

using namespace std;

int main(int argc, const char * argv[]) {
    
    Database &db = Database::getInstance();
        
    cout << "Welcome to our Book Store! \n" <<
    "What would you like to do?" << endl;
    
    while (1) {
        int choise;
        cout << "- In order to watch inventory, press 1" << endl
        << "- In order to watch Open Orders, press 2" << endl
        << "- In order to watch Customer List, press 3" << endl
        << "- In order to watch Supplier List, press 4" << endl
        << "- In order to watch Orders By Date, press 5" << endl
        << "- In order to watch All the Discounted Books, press 6" << endl
        << "- In order to search for specific Book, press 7" << endl
        << "- In order to search for suppliers of specific, press 8" << endl
        << "- In order to check how many copys of a specific book were sold since a specific date, press 9" << endl
        << "- In order to check how many Books a specific Customer Purchased since a specific date, press 10" << endl
        << "- In order to check how Who is the Customer who Purchased the most since a specific date, press 11" << endl
        << "- In order to watch details of the Supplier who supplied the most books since a specific date, press 12" << endl
        << "- In order to check Amount of Orders for specific range of dates, press 13" << endl
        << "- In order to check Amount of Purchases for specific range of dates, press 14" << endl
        << "- In order to check Amount of new Customerss for specific range of dates, press 17" << endl
        << "- In order to check purchases from specific Supplier in a specific range of dates, press 18" << endl
        << "- In order to check Sales for specific employee in a specific range of dates, press 19" << endl
        << "- In order to watch top 10 Books in a specific range of dates, press 20" << endl
        << "- For Exit, press 99" << endl;
        cin >> choise;
        
        switch (choise) {
            case 1:
                books::inventory();
                break;
            case 2:
                books::orders();
                break;
            case 3:
                customers::customerList();
                break;
            case 4:
                suppliers::SupplierList();
                break;
            case 5:
                books::ordersByDate();
                break;
            case 6:
                books::DiscuntedBooks();
                break;
            case 7:
                books::bookSearching();
                break;
            case 8:
                suppliers::searchingSupplierByBookName();
                break;
            case 9:
                books::booksSince();
                break;
            case 10:
                customers::howManyBooksForCustomer();
            case 11:
                customers::CustomerWhoPurchasedTheMost();
            case 12:
                suppliers::topSupllier();
                break;
            case 13:
                books::OrdersAmount();
                break;
            case 14:
                books::PhurchacesAmount();
                break;
            case 17:
                customers::newCustomers();
                break;
            case 18:
                suppliers::totalOrders();
                break;
            case 19:
                employees::totalSales();
                break;
            case 20:
                books::top10Books();
                break;
            case 99:
                cout << "Have a Great Day!" << endl;
                exit(1);
            default:
                cout << "Invalid choise, try again" << endl;
                break;
        }
    }
    
}
