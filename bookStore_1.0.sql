

 -- -------------- GeneralBooks-------------- -- 
 
 CREATE TABLE IF NOT EXISTS Books (				/*This Table will hold all the books in the "World". 1 from each kind. (just for having all books details in one table....)*/
	ISBN varchar(13) , 			
    Book_Name varchar(30) not null, 
    Category varchar(30) , 
    Book_Language varchar(30) ,
    Author varchar(30) ,
    Publishing_Year date,
    
	PRIMARY KEY (ISBN) 
 );
 
 
SELECT * FROM Books;
INSERT INTO Books (ISBN, Book_Name, Category, Book_Language, Author , Publishing_Year) VALUES ('456' , 'Enter The Matrix', 'SCF' , 'English' , 'Cohen', '1999-03-25');
 
 
 
 
 
 
 
 
 
 
 
 
 
  -- -------------- BooksStore-------------- -- 
 
 CREATE TABLE IF NOT EXISTS TheStoreBooks (		/*This table is having the Book's list of the store. the data of each book is in the general Books table*/
	ISBN varchar(13) ,
    Books_Amount int , 
    Price float , 
    
    PRIMARY KEY(ISBN),
    FOREIGN KEY (ISBN) REFERENCES Books(ISBN)
    
 );
 
SELECT * FROM TheStoreBooks;
INSERT INTO TheStoreBooks (ISBN, Books_Amount, Price) VALUES ('456' , '5', 170);

 
 
 CREATE TABLE IF NOT EXISTS CustomersOrders (		/*Purchases and Cancelled_Orderes will also be here. the way to find them is via the Order_Status*/
	Order_Number varchar(20),
    ISBN varchar(13) ,
    Amount int,
    Customer_ID varchar(10),
    Emp_ID varchar(10),
    Order_Status ENUM ('ordered', 'arrived', 'messageSent', 'Purchased' , 'Cancelled') ,
	Order_Date date,
    Actual_Price_PerOneBook float,
    
    PRIMARY KEY (Order_Number , ISBN),
    FOREIGN KEY (ISBN) REFERENCES Books(ISBN),
    FOREIGN KEY (Customer_ID) REFERENCES Customers(Customer_ID),
	FOREIGN KEY (Emp_ID) REFERENCES Employees(Emp_ID)

 );


SELECT * FROM CustomersOrders;
INSERT INTO CustomersOrders (Order_Number, ISBN, Amount) VALUES ('456' , '5', 170);











 -- -------------- Employees Relevant Tables -------------- -- 

CREATE TABLE IF NOT EXISTS Employees (
	Emp_ID varchar(10) , 
	Emp_Name varchar(30) ,
    Salary float , 
	JoiningToStoreDate date ,
    BooksSold_TotalMoneyAmount float , 
    
	PRIMARY KEY (Emp_ID)
) ; 

SELECT * FROM Employees;
INSERT INTO Employees (Emp_ID, Emp_Name, Salary, JoiningToStoreDate, BooksSold_TotalMoneyAmount) VALUES ('0000000001' , 'David Stein', 4500, '2016-04-12' , 0);



CREATE TABLE IF NOT EXISTS EmpPhone (
    Emp_ID varchar (10) ,
    Phone_ID varchar (10),
	Phone_Number  varchar (14), 
    
    PRIMARY KEY (Phone_ID),
    FOREIGN KEY (Emp_ID) REFERENCES Employees(emp_ID)
) ;

SELECT * FROM EmpPhone;
INSERT INTO EmpPhone (Emp_ID, Phone_ID, Phone_Number) VALUES ('0000000001' , '1' , '0525111111');














-- -------------- Suppliers Relevant Tables -------------- -- 

CREATE TABLE IF NOT EXISTS Suppliers (
	Supp_ID varchar(10) , 
	Supp_Name    varchar(30),
    Incomes_From_Store float ,
    Added_To_System_Date date ,
    
	PRIMARY KEY (Supp_ID)
);

SELECT * FROM Suppliers;
INSERT INTO Suppliers (Supp_ID, Supp_Name, Incomes_From_Store, Added_To_System_Date) VALUES ('11111' , 'john Gregory', 0 , '2001-09-05');


CREATE TABLE IF NOT EXISTS Supp_Phone (
    Supp_ID varchar (10) ,
    Phone_ID varchar (10),
	phone_number  varchar (14), 
    
    PRIMARY KEY (Phone_ID) , 
    FOREIGN KEY (Supp_ID) REFERENCES Suppliers (Supp_ID)
);

SELECT * FROM Supp_Phone;
INSERT INTO Supp_Phone (Supp_ID, Phone_ID, phone_number) VALUES ('11111' , '10', '052544444444');




CREATE TABLE IF NOT EXISTS Supplier_Books (		/*Only Books who can be find here are books that the *Store* can buy*/
	Supp_ID varchar(30),
    ISBN varchar(13) , 
    Amount int,
    Price float,

	PRIMARY KEY (Supp_ID , ISBN),
    FOREIGN KEY (ISBN) REFERENCES Books (ISBN),
    FOREIGN KEY (Supp_ID) REFERENCES Suppliers(Supp_ID)
);

SELECT * FROM Supplier_Books;
INSERT INTO Supplier_Books (Supp_ID, ISBN, Amount, Price) VALUES ('11111', '123' ,10, 100);












-- -------------- Customers Relevant Tables -------------- -- 

CREATE TABLE IF NOT EXISTS Customers (			
	Customer_ID varchar(30) ,
    Customer_Name varchar(30) ,
    Total_Money_Spent_On_Books float ,
    Added_To_System_Date date,
    
    PRIMARY KEY (Customer_ID)
);

SELECT * FROM Customers;
INSERT INTO Customers (Customer_ID, Customer_Name, Total_Money_Spent_On_Books, Added_To_System_Date) VALUES ('11001100' , 'Reuven Atar', 0 , '2015-10-01');




CREATE TABLE IF NOT EXISTS Customers_Books (			
	Customer_ID varchar(30) ,
    Order_Number varchar(10) , 
    ISBN varchar(30) ,
    Amount_Of_Books int,
    Price_PerOneBook_After_Discount float,
    
    PRIMARY KEY (Customer_ID, ISBN, Order_Number),
	FOREIGN KEY (Customer_ID) REFERENCES Customers(Customer_ID),
    FOREIGN KEY (ISBN) REFERENCES Books(ISBN),
    FOREIGN KEY (Order_Number) REFERENCES CustomersOrders(Order_Number)

);

SELECT * FROM Customers_Books;
INSERT INTO Customers_Books (Customer_ID, Order_Number, ISBN, Amount_Of_Books , Price_PerOneBook_After_Discount) VALUES (/*ADD VALUES HERE*/);




CREATE TABLE IF NOT EXISTS Customers_Phone (
	Customer_ID varchar(30), 
    Phone_ID varchar (10) ,
    Phone_number varchar(14),
    
    PRIMARY KEY (Phone_ID),
    FOREIGN KEY(Customer_ID) REFERENCES Customers(Customer_ID)
);


SELECT * FROM Customers_Phone;
INSERT INTO Customers_Phone (Customer_ID, Phone_ID, Phone_number) VALUES (/*ADD VALUES HERE*/);
