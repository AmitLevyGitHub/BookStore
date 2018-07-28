#include "Database.hpp"

Database *Database::instance = 0;

Database::Database() : driver(get_driver_instance()) {
    connection_properties["hostName"] = DB_HOST;
    connection_properties["port"] = DB_PORT;
    connection_properties["userName"] = DB_USER;
    connection_properties["password"] = DB_PASS;
    connection_properties["OPT_RECONNECT"] = true;
    
    // use database
    try {
        Connection *con = driver->connect(connection_properties);
        try {
            con->setSchema("BookStore");
        }
        catch (SQLException &e) {
            Statement *stmt = con->createStatement();
            stmt->execute("CREATE DATABASE IF NOT EXISTS BookStore");
            con->setSchema("BookStore");
            stmt->execute("CREATE TABLE IF NOT EXISTS Books ( "
                          "ISBN varchar(13), "
                          "Book_Name varchar(30) not null, "
                          "Category varchar(30), "
                          "Book_Language varchar(30), "
                          "Author varchar(30), "
                          "Publishing_Year varchar(4), "
                          "PRIMARY KEY (ISBN) "
                          ")");
            stmt->execute("CREATE TABLE IF NOT EXISTS TheStoreBooks ( "
                          "ISBN varchar(13), "
                          "Books_Amount INT, "
                          "Price FLOAT, "
                          "Global_Discount FLOAT,"
                          "PRIMARY KEY(ISBN), "
                          "FOREIGN KEY (ISBN) REFERENCES Books(ISBN) "
                          ");");
            stmt->execute("CREATE TABLE IF NOT EXISTS Employees ( "
                          "Emp_ID varchar(10), "
                          "Emp_Name varchar(30), "
                          "Salary FLOAT, "
                          "JoiningToStoreDate date, "
                          "BooksSold_TotalMoneyAmount FLOAT, "
                          "PRIMARY KEY (Emp_ID) "
                          ");");
            stmt->execute("CREATE TABLE IF NOT EXISTS EmployeesPhones ( "
                          "Emp_ID varchar (10), "
                          "Phone_Number varchar (14), "
                          "PRIMARY KEY (Emp_ID,Phone_Number), "
                          "FOREIGN KEY (Emp_ID) REFERENCES Employees(emp_ID) "
                          ");");
            stmt->execute("CREATE TABLE IF NOT EXISTS Suppliers ( "
                          "Supp_ID varchar(10), "
                          "Supp_Name varchar(30), "
                          "Incomes_From_Store float, "
                          "Added_To_System_Date date, "
                          "PRIMARY KEY (Supp_ID) "
                          ");");
            stmt->execute("CREATE TABLE IF NOT EXISTS SuppliersPhones ( "
                          "Supp_ID varchar (10), "
                          "phone_number varchar (14), "
                          "PRIMARY KEY (Supp_ID,phone_number), "
                          "FOREIGN KEY (Supp_ID) REFERENCES Suppliers (Supp_ID) "
                          ");");
            stmt->execute("CREATE TABLE IF NOT EXISTS SuppliersBooks ( "
                          "Supp_ID varchar(30), "
                          "ISBN varchar(13), "
                          "Amount int, "
                          "Price float, "
                          "PRIMARY KEY (Supp_ID , ISBN), "
                          "FOREIGN KEY (ISBN) REFERENCES Books (ISBN), "
                          "FOREIGN KEY (Supp_ID) REFERENCES Suppliers(Supp_ID) "
                          ");");
            stmt->execute("CREATE TABLE IF NOT EXISTS Customers ( "
                          "Customer_ID varchar(30), "
                          "Customer_Name varchar(30), "
                          "Total_Money_Spent_On_Books FLOAT, "
                          "Added_To_System_Date date, "
                          "PRIMARY KEY (Customer_ID) "
                          ");");
            stmt->execute("CREATE TABLE IF NOT EXISTS CustomersOrders ( "
                          "Order_Number varchar(20), "
                          "ISBN varchar(13), "
                          "Amount INT, "
                          "Customer_ID varchar(10), "
                          "Emp_ID varchar(10), "
                          "Order_Status ENUM ('ordered', 'arrived', 'messageSent', 'Purchased' , 'Cancelled'), "
                          "Order_Date date, "
                          "Total_Price FLOAT, "
                          "PRIMARY KEY (Order_Number , ISBN), "
                          "FOREIGN KEY (ISBN) REFERENCES Books(ISBN), "
                          "FOREIGN KEY (Customer_ID) REFERENCES Customers(Customer_ID), "
                          "FOREIGN KEY (Emp_ID) REFERENCES Employees(Emp_ID) "
                          ");");
            stmt->execute("CREATE TABLE IF NOT EXISTS CustomersBooks ( "
                          "Customer_ID varchar(30), "
                          "Order_Number varchar(10), "
                          "ISBN varchar(30), "
                          "Amount_Of_Books int, "
                          "Price_PerOneBook_After_Discount FLOAT, "
                          "PRIMARY KEY (Customer_ID, ISBN, Order_Number), "
                          "FOREIGN KEY (Customer_ID) REFERENCES Customers(Customer_ID), "
                          "FOREIGN KEY (ISBN) REFERENCES Books(ISBN), "
                          "FOREIGN KEY (Order_Number) REFERENCES CustomersOrders(Order_Number) "
                          ");");
            stmt->execute("CREATE TABLE IF NOT EXISTS CustomersPhones ( "
                          "Customer_ID varchar(30), "
                          "Phone_number varchar(14), "
                          "PRIMARY KEY (Customer_ID,Phone_number), "
                          "FOREIGN KEY (Customer_ID) REFERENCES Customers(Customer_ID) "
                          ")");
            addBooksToWorld();
            addBooksToStore();
            addCustomers();
            addCustomersPhones();
            addEmployees();
            addEmployeesPhones();
            addSuppliers();
            addSuppliersPhones();
            
            
            
            delete stmt;
        }
        
        delete con;
    }
    catch (SQLException &e) {
        cout << e.getErrorCode() << " " << e.what() << " " << e.getSQLState();
    }
}

Database & Database::getInstance() {
    if (Database::instance == 0) {
        instance = new Database();
    }
    return *instance;
}

Connection * Database::getConnection() {
    try {
        Connection *con = driver->connect(connection_properties);
        con->setSchema(DB_NAME);
        return con;
    } catch (SQLException &e) {
        cout << e.what();
    }
    return 0;
}

void Database::addBooksToWorld(){
    Connection *con = driver->connect(connection_properties);
    con->setSchema(DB_NAME);
    Statement *stmt = con->createStatement();
    stmt->execute("insert into Books(ISBN,Book_Name,Category,Book_Language,Author,Publishing_Year)"
                  "VALUES('888147660-6','Medic Of The Banished','Adventure','English','Laurena Mee','2016'),"
                  "('623753193-9','Armies Of Agony','Drama','English','Kanya Stocken','1997'),"
                  "('161913965-0','Sounds Of The Maze','Drama','Franch','Aylmer Clemow', '2013'),"
                  "('561800464-X','Ogre Without Desire','Fantacy','English','Fletch Dormand','1990'),"
                  "('089179767-X','Vanish At The Past','Fantasy','English','Davey Dykins','1989'),"
                  "('374822624-1','Women Of The Evening','Romance','Franch','Markos Krebs','1993'),"
                  "('867529509-X','Careful Of Nature','Horor','Hebrew','Shellie Service','1998'),"
                  "('754692835-4','Bunnies Of Mystery','Children','English','Paxon Oxby','2017'),"
                  "('578859010-8','Revival In My Town','Mystery','English','Sherwood Patience','1990'),"
                  "('600789272-7','Songs With A Hat','Humor','Hebrew','Urbain Cescotti','1992'),"
                  "('250024852-6','Mutants Asking Questions','Horor','English','Drusilla Van De Cappelle','2018'),"
                  "('552547148-5','Patrons And Patrons','Drama','English','Constantin Jodrelle','2015'),"
                  "('119639776-7','Union Of The Stockades','Adventure','Italian','Erastus McBeath','1990'),"
                  "('126219423-7','Admiring The Light','Drama','Hindi','Rae Venton','1992'),"
                  "('095254332-X','Lust Of Hell','Romance','English','Clarissa Addionisio','1988');");
}

void Database::addBooksToStore(){
    Connection *con = driver->connect(connection_properties);
    con->setSchema(DB_NAME);
    Statement *stmt = con->createStatement();
    stmt->execute("insert into TheStoreBooks(ISBN,Books_Amount,Price,Global_Discount)"
                  "VALUES('888147660-6','12','39','0'),"
                  "('623753193-9','20','56','0.2'),"
                  "('561800464-X','10','49','0'),"
                  "('374822624-1','35','39','0.1'),"
                  "('867529509-X','25','59','0'),"
                  "('600789272-7','30','25','0'),"
                  "('250024852-6','15','49','0.3'),"
                  "('552547148-5','10','25','0'),"
                  "('119639776-7','40','39','0.2'),"
                  "('095254332-X','50','20','0');");
}

void Database::addCustomers(){
    Connection *con = driver->connect(connection_properties);
    con->setSchema(DB_NAME);
    Statement *stmt = con->createStatement();
    stmt->execute("insert into Customers(Customer_ID,Customer_Name,Total_Money_Spent_On_Books,Added_To_System_Date)"
                  "VALUES('201764949','Erik Hounsham',180,'2015-07-09'),"
                  "('201954912','Niels Strelitzer',819,'2017-02-21'),"
                  "('401795834','Cindelyn Labeuil',955,'1998-04-01'),"
                  "('503860353','Collete Thomerson',1990,'2004-12-15'),"
                  "('201943842','Andrea Ozintsev',485,'2016-01-25'),"
                  "('302993813','Pearla McOrkill',1843,'2011-12-21'),"
                  "('561038427','Chadd Kloska',1300,'2011-07-08'),"
                  "('354095689','Geri Tuftin',1663,'2015-11-25'),"
                  "('353941513','Danny Fourcade',55,'2010-02-07'),"
                  "('491756877','Tamara Perassi',998,'2009-08-03');");
}
    
void Database::addCustomersPhones(){
    Connection *con = driver->connect(connection_properties);
    con->setSchema(DB_NAME);
    Statement *stmt = con->createStatement();
    stmt->execute("insert into CustomersPhones(Customer_ID,Phone_number)"
                  "VALUES('201764949','(504) 8008524'),"
                  "('201954912','(965) 9821447'),"
                  "('401795834','(339) 3047428'),"
                  "('503860353','(339) 3047428'),"
                  "('201943842','(420) 2437829'),"
                  "('201943842','(846) 3771753'),"
                  "('302993813','(697) 6491263'),"
                  "('561038427','(432) 1211491'),"
                  "('354095689','(755) 8739067'),"
                  "('353941513','(164) 6929417'),"
                  "('353941513','(319) 1754773'),"
                  "('491756877','(149) 6587422');");
}

void Database::addEmployees(){
    Connection *con = driver->connect(connection_properties);
    con->setSchema(DB_NAME);
    Statement *stmt = con->createStatement();
    stmt->execute("insert into Employees(Emp_ID,Emp_Name,Salary,JoiningToStoreDate,BooksSold_TotalMoneyAmount)"
                  "VALUES('079727787','Kala Rollins',4752,'2018-07-19','110'),"
                  "('569422207','Barry Henrichsen','9235','2018-04-22','710'),"
                  "('499263433','Yorgos Meredyth','8869','2015-02-09','820'),"
                  "('392704018','Helga Longhirst','5044','2016-01-15','560'),"
                  "('823213354','Rafe Newlands','5718','2015-07-06','780'),"
                  "('403252037','Morty Assandri','6514','2017-09-13','290'),"
                  "('157438974','Kikelia Mahaddy','5799','2016-10-06','950'),"
                  "('582039536','Mahmud Blaise','9062','2017-07-11','500'),"
                  "('534971565','Kikelia Mahaddy','5799','2016-10-06','950'),"
                  "('652444153','Ynes St. Paul','4712','2017-07-19','590'),"
                  "('382224948','Armand Berthouloume','8555','2017-11-20','790');");
}

void Database::addEmployeesPhones(){
    Connection *con = driver->connect(connection_properties);
    con->setSchema(DB_NAME);
    Statement *stmt = con->createStatement();
    stmt->execute("insert into EmployeesPhones(Emp_ID,Phone_number)"
                  "VALUES('079727787','(419) 8717088'),"
                  "('569422207','(604) 4280875'),"
                  "('499263433','(687) 5190471'),"
                  "('392704018','(878) 7121872'),"
                  "('823213354','(371) 3050646'),"
                  "('403252037','(251) 9554452'),"
                  "('157438974','(784) 5712861'),"
                  "('582039536','(432) 1211491'),"
                  "('534971565','(620) 7515862'),"
                  "('652444153','(287) 8807580'),"
                  "('382224948','(716) 5155960');");
}

void Database::addSuppliers(){
    Connection *con = driver->connect(connection_properties);
    con->setSchema(DB_NAME);
    Statement *stmt = con->createStatement();
    stmt->execute("insert into Suppliers(Supp_ID,Supp_Name,Incomes_From_Store,Added_To_System_Date)"
                  "VALUES('6256327977', 'Harvey Winkle', 539, '2015-12-18'),"
                  "('721276415', 'Giralda Boddice', 7989, '2015-01-26'),"
                  "('839113642', 'Winn Shutte', 3453, '2014-09-01'),"
                  "('349686016', 'Seth Joesbury', 3042, '2017-06-22'),"
                  "('288423058', 'Scarlett Dibb', 2231, '2015-01-09'),"
                  "('015129428', 'Shari Besant', 8600, '2015-08-23'),"
                  "('631483430', 'Val Standrin', 1546, '2017-11-15'),"
                  "('412616694', 'Lari Bartolomeu', 4023, '2017-06-22'),"
                  "('809995153', 'Mommy Chilcott', 8893, '2018-03-21'),"
                  "('124425982', 'Grover Goozee', 9082, '2016-02-24'),"
                  "('935903924', 'Flossi Ricciardiello', 8242, '2017-08-10');");
}

void Database::addSuppliersPhones(){
    Connection *con = driver->connect(connection_properties);
    con->setSchema(DB_NAME);
    Statement *stmt = con->createStatement();
    stmt->execute("insert into SuppliersPhones(Supp_ID,phone_number)"
                  "VALUES('6256327977','(251) 9236825'),"
                  "('721276415','(780) 7426268'),"
                  "('839113642','(992) 7678403'),"
                  "('349686016','(878) 3950699'),"
                  "('288423058','(798) 4668310'),"
                  "('015129428','(231) 8339530'),"
                  "('631483430','(632) 7303280'),"
                  "('631483430','(904) 2061602'),"
                  "('412616694','(278) 8631288'),"
                  "('809995153','(933) 5318535'),"
                  "('124425982','(893) 6377544'),"
                  "('935903924','(808) 3284963');");
}
