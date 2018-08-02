#include "suppliers.hpp"


int suppliers:: count (){
    CON;
    int counter = 0;
    if (con) {
        Statement *stmt = con->createStatement();
        ResultSet *rset = stmt->executeQuery("SELECT count(*) as cnt from Suppliers");
        rset->first();
        counter = rset->getInt("cnt");
        delete con;
        delete rset;
        delete stmt;
    }
    return counter;
}

void suppliers:: SupplierList(){
    CON;
    if (con) {
        Statement *stmt = con->createStatement();
        ResultSet *rset = stmt->executeQuery("SELECT * FROM Suppliers");
        cout << "\tID\t\t\t" << "Name\t\t\t" << "Incomes From Store\t\t" << "Added To Ststem Date\t\t\t" << endl;
        while (rset->next()){
            cout << "\t" << rset->getString(1) << "\t" <<
            rset->getString(2) << "\t" << rset->getString(3) << "\t\t\t" << rset->getString(4) << endl;
        }
        cout << "\n";
        delete con;
        delete rset;
        delete stmt;
    }
    
}

void suppliers::searchingSupplierByBookName(){
    CON;
    if (con) {

        string bookName;
        PreparedStatement *pstmt1 = con->prepareStatement("CREATE TABLE if not exists temp1 AS SELECT * FROM Suppliers natural join SuppliersBooks;");
        pstmt1->execute();
        PreparedStatement *pstmt2 = con->prepareStatement("CREATE TABLE if not exists temp2 AS select * from Books natural join TheStoreBooks;");
        pstmt2->execute();

        PreparedStatement *pstmt = con->prepareStatement("select Supp_Name,Supp_ID from temp1 inner join temp2 on temp1.ISBN=temp2.ISBN where Book_Name=?;");

        cout << "Please Enter Book Name > ";
        string temp;
        getline(cin, temp);
        getline(cin, bookName);
        pstmt->setString(1, bookName);
        ResultSet *rset = pstmt->executeQuery();
        
        

        if (rset->first()){
            rset->beforeFirst();
            cout << "\nSuppliers who holds '" << bookName << "':\n" << endl;
            cout<< "Supplier Name\t\t" << "Supplier ID\n" << endl;
            while (rset->next()){
                cout << rset->getString(1) << "\t\t" << rset->getString(2) << endl;
            }
            cout << "\n";
        }
        else
            cout << "\nInvalid Book Name\n" << endl;
        
    }
}

void suppliers::topSupllier(){
    CON;
    if (con) {
        
        string startDate;
        
        PreparedStatement *pstmt = con->prepareStatement("SELECT Supp_Name,supplied FROM Suppliment natural join Suppliers WHERE Order_Date >= ? ORDER BY supplied DESC;");
        
        cout << "Please Enter Start Date in the following format- YYYY-MM-DD > ";
        string temp;
        getline(cin, temp);
        getline(cin, startDate);
        pstmt->setString(1, startDate);
        
        ResultSet *rset = pstmt->executeQuery();
        
        if (rset->rowsCount() == 0) {
            cout << "Invaid Input Or orders in this range of dates " << endl;
            return;
        }
        
        rset->first();
        cout << "\nTop Supplier since " << startDate << " - " << rset->getString("Supp_Name") << " who Supplied "
        << rset->getString("supplied") << " Books" << endl;
        
        cout << "\n";
    }
}

void suppliers::totalOrders(){
    CON;
    if (con) {
        
        string startDate, endDate, suppID;
        
        PreparedStatement *pstmt = con->prepareStatement("SELECT Supp_Name, Incomes_From_Store FROM Suppliment natural join Suppliers WHERE Supp_ID=? AND Order_Date >= ? AND Order_Date <= ?;");
        
        cout << "Please Enter Supplier ID > ";
        string temp;
        getline(cin, temp);
        getline(cin, suppID);
        pstmt->setString(1, suppID);
        cout << "Please Enter Start Date in the following format- YYYY-MM-DD > ";
        getline(cin, startDate);
        pstmt->setString(2, startDate);
        cout << "Please Enter End Date in the following format- YYYY-MM-DD > ";
        getline(cin, endDate);
        pstmt->setString(3, endDate);
        
        ResultSet *rset = pstmt->executeQuery();
        
        if (rset->rowsCount() == 0) {
            cout << "Invaid Input Or orders in this range of dates " << endl;
            return;
        }
        
        rset->first();
        cout << "\nTotal price for purchases from " << rset->getString("Supp_Name") << ", ID number " << suppID << " Between " << startDate << " And " << endDate << " - " <<
        rset->getString("Incomes_From_Store") << endl;
        
        cout << "\n";
    }
}

