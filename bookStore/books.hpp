#ifndef books_hpp
#define books_hpp

#include <iostream>
#include "Database.hpp"
#include <boost/date_time/posix_time/posix_time.hpp>
#include <stdio.h>
#include <string.h>

#define CON Database &db = Database::getInstance(); Connection *con = db.getConnection();

using namespace std;
using namespace boost::posix_time;
using namespace boost::gregorian;

class books {
    
    string ISBN;
    string name;
    string category;
    string language;
    string author;
    date publishing_date;
    
public:
    
    static int count (){
        CON;
        int counter = 0;
        if (con) {
            Statement *stmt = con->createStatement();
            ResultSet *rset = stmt->executeQuery("SELECT count(*) as cnt from TheStoreBooks");
            rset->first();
            counter = rset->getInt("cnt");
            delete con;
            delete rset;
            delete stmt;
        }
        return counter;
    }
    void inventory ();
    books* geByName(string name);
};


#endif /* books_hpp */
