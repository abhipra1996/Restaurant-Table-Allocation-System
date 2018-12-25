#include <iostream>
#include <fstream>
#include <deque>
#include <map>
using namespace std;

class Customer{
	int id, people;
public:
	Customer(int=0,int=0);
	int getID(){ return id; }
	int getPeople(){ return people; }
};

Customer::Customer(int id, int people){
	this->id = id;
	this->people = people;
}

// For the data of Map "table"
struct Table{
	int seat, customer;
	string status;
};

typedef map<int, Table> maptype;        //dummy argument passing data structure.
typedef deque<Customer> dequetype;      //dummy argument passing data structure.

void addTable(maptype&, int, int);
void assignTable(maptype&, dequetype&);
void freeTable(maptype&, int);
void getStatus(maptype& table);
void getWaiting(dequetype& cust);

int max_ppl = INT_MIN;
map<int, int> cust_info;
int main(){
	map<int, Table> table;
	deque<Customer> cust;
	Customer *c;
	int id, people, tableNo, tablePpl;

	ifstream ins("table.txt");
	//If filename not found in the system. terminate the program
	if(!ins){
		cout << "File \"table.txt\" not found!" << endl;
		return 0;
	}
	//else read all the data from file to the program
	while(ins.good()){
		if(!ins.eof()){
			ins >> tableNo;
			ins >> tablePpl;
			max_ppl = max(max_ppl, tablePpl);
			addTable(table, tableNo, tablePpl);
		}
	}
	ins.close();

	int option;
	while(true){
		cout << endl << endl << endl;
		cout << "\t+++++++++++++++++++++++++++++++++" << endl
			<< "\t+\tRestaurant Management\t+" << endl
			<< "\t+++++++++++++++++++++++++++++++++" << endl;
		cout << "1. New customer" << endl
			<< "2. Assign table for customer" << endl
			<< "3. New table" << endl
			<< "4. Customer finish dining" << endl
			<< "5. Table Status" << endl
			<< "6. Customer Waiting Status" << endl
			<< "0. Exit" << endl;
		cout << "Option: ";
		cin >> option;
		switch(option){
			case 1: // New customer
				cout << "Customer ID: ";
				cin >> id;
				cout << "Customer people count: ";
				cin >> people;
				if(people > max_ppl) {
                    cout << "NOT Allowed. Sorry Maximum no of people permitted is " << max_ppl << endl;
                    break;
				}

				c = new Customer(id, people);
				cust.push_back(*c);
				cust_info[id] = people;
				delete[] c;
				break;
			case 2: // Assign Customer to table
				assignTable(table, cust);
				break;
			case 3: // Create new table
				cout << "Table Number: ";
				cin >> tableNo;
				cout << "Table Seat Capacity: ";
				cin >> tablePpl;
				addTable(table, tableNo, tablePpl);
				break;
			case 4: // Customer leaving
				cout << "Enter Table Number: ";
				cin >> tableNo;
				freeTable(table, tableNo);
				break;
            case 5: // Assign Customer to table
				getStatus(table);
				break;
            case 6: // Assign Customer to table
				getWaiting(cust);
				break;
			case 0: // Exit
				cout << "Program terminated." << endl << endl;
				return 0;
			default: // Input doesn't match one of the cases
				cout << "Wrong input, please try again."<< endl << endl;
		}
	}
}

// function to add table
void addTable(maptype& table, int tableNo, int tablePpl){
	pair< map<int, Table>::iterator, bool> retval;
	Table temp;
	temp.seat = tablePpl;
	temp.customer = 0;
	temp.status = "unoccupied";
	retval = table.insert(pair<int, Table>(tableNo, temp));
	if(retval.second == false){
		cout << "Sorry, Table " << tableNo << " exist. " << endl;
	} else {
	    max_ppl = max(max_ppl, tablePpl);
		cout << "Record Table " << tableNo << " successfully created." << endl;
	}
}
void getStatus(maptype& table) {
    map<int, Table>::iterator p = table.begin();
	map<int, Table>::iterator e = table.end();
    int i = 1;
    cout << endl<< "T.No" << "\t" << "Cap." << "\t" << "Status\t\tC.ID\tPeople" << endl;
	for(p; p!=e; p++){

	    cout << p->first << "\t" << p->second.seat << "\t" << p->second.status << "\t" << p->second.customer << "\t" << cust_info[p->second.customer]<< endl;

    }
}

void getWaiting(dequetype& cust)
{
    cout <<endl<< "Cust.ID" << "\t" << "People" << endl;
    for(int i=0; i<cust.size(); i++){
        cout << cust.at(i).getID() << "\t" << cust.at(i).getPeople() << endl;
    }

}
// function to assign customer to table
void assignTable(maptype& table, dequetype& cust){
	int validate=-1;
	map<int, Table>::iterator p = table.begin();
	map<int, Table>::iterator p1 = table.begin();
	map<int, Table>::iterator e = table.end();
	// In order to assign the first customer to any empty table first,
	// we looped the Customer deque before looping the table map.

	for(int i=0; i<cust.size(); i++){
        int ans = INT_MAX;
        int id;
        int flag = 0;

		for(p=p1; p!=e; p++){
			if(p->second.status == "unoccupied"){
				if(cust.at(i).getPeople() <= p->second.seat){
                        if(p->second.seat < ans) {
                            ans =  p->second.seat;
                            id = i;
                            p1 = p;
                        }
					flag = 1;

				}
			}
		}

		if (flag == 1) {
            p1->second.customer = cust.at(id).getID();
					p1->second.status = "Occupied";
					cust.erase(cust.begin() + id); // remove the customer from deque
					cout << "Table " << p1->first << ", " // Table Number
						<< p1->second.status // Table current status
						<< " by Customer ID: " << p1->second.customer << endl << endl; // Customer ID
					validate = 0;
		}
		// Every time call the function only assign one customer to table
		if (validate == 0){
			break;
		}
	}
	// To know what issue happened.

	switch(validate){
		case 1:
			cout << "Sorry, no customer suitable for current table." << endl << endl;
			break;
		case 2:
			cout << "Sorry, table is fully occupied." << endl << endl;
			break;
		case -1:
			cout << "Sorry, table full or no more customer." << endl << endl;
			break;
	}
}

// function to remove customer from table
void freeTable(maptype& table, int tableNo){
	map<int, Table>::iterator p = table.begin();

	while ( p != table.end()){
		if(p->first == tableNo){
			p->second.customer = 0;
			p->second.status = "unoccupied";
			break;
		}
		p++;
	}
}
