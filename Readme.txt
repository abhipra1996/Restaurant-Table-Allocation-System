
*****************Restaurant Table Allocation System********************

A restaurant table allocation is an arrangement made in advance to have a table available at a restaurant. 
While most restaurants in the vast majority of the world do not require a reservation, and some have no policy or simply any channel for making one, 
so-called higher-end restaurants mainly in overcrowded cities often require a reservation, and some may have tables booked for weeks in advance.
At particularly exclusive venues, it may be impossible to make a reservation on the same day as the planned visit.


I used the STL map to keep a collection of tables in the restaurant. 
Each item in the map is identified by the table number. Each table keeps the information of the number of seats, 
customer (if not assigned, this value would be NULL), and a status to indicate if the table is occupied or not. 
There would not be any table with the same number. When the program starts, we populate the map with an initial number of tables. 
All tables would not be occupied upon initialization.A text file might be used with the following format for this initialization where 
each line contains the table number and number of seats available.
I used a menu driven program to simulate the arrival of customers, assignment of tables, adding new tables, and customer leaving the restaurant. 
When a customer arrives, dynamically a customer object is created and is pushed to the deque containing the customers waiting to be assigned a table. 
A new customer would always be added to the end of the deque.To assign a table, we retrieved the first customer from the deque and search for an empty 
table in the map that has enough seats to assign the customer retrieved. If a table is available, we removed the customer from the deque, 
assign the customer to the map item with the available table number, and set the status of the table to occupied. 
If no table is available, we retrieve another customer record which might have a smaller number of people and searched for an available table. 
Basically, customers are assigned with tables using the first come first serve basis. However, if there is no available table with enough seats, 
then the next customer with a smaller number can be assigned first. We used the iterator to traverse the deque for this purpose. 
The user would allow for new tables to be added to the map. A new table added would always be initialized as an empty table with no customer assigned to it. 
When a customer leaves the restaurant, we searched the map for the table number. If found, we reset the customer to NULL and the status to unoccupied.



To run the code, one simply needs a gnu c++ compiler installed in their systems. Once installed, the program can simply 
be executed as any other c++ program (through an ide in Windows, terminal in Linux). We have initialized the tables with 
a set of data provided in a text file with the project package, this file can be modified by the end user in proper format.
The program is menu driven, that is, it will keep on asking for user input for selecting a choice from listed options, 
and the user will have to input those choices according to their needs. 

