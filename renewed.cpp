#include <iostream>
#include <string.h>
#include <iomanip>
#include <stdio.h>
#include <fstream>
using namespace std;
//Make sure to have less space and time complexity
struct carRental{
	string carNo;
	string carYear;
	string carModel;
	string carColor;
	string ownerFName;
	string ownerLName;
	string tenantPhoneNo;
	string addressOfTenant;
	string dateOfRental;
	string daysNo;
	string rentedOrNot;
	string payment;
	string howMuchCost;
}rawFile[150];
//Number trackers
int num = 100, numLL = 1;

struct node{
	carRental data;
	node *next;
}*head = NULL, *temp = NULL, *cur = NULL, *checker = NULL;
//readers and adders also with remover
void read();
void dataAdder(int j);
void add();
void remove(int n);

//Display
void display();

//search
void searchBy();//To choice if we search by name,vin....or something
void searchUsing(char searchBy);//To pick which method we want use if it's linear or binary
void linearSearch(char searchBy);
int binarySearch(char searchBy, string RorS);

//sort
void swapStruct();
void sortBy();//To choice if we sort by name,vin....or something
void sortUsing(char sortByL);//To pick which method we want use if it's selection or bubble
char ascendOrDescend();//To choice if ascending or descending
void selectionSort(char sortByUsing, char AorD, int ch);
void bubbleSort(char sortBy, char AorD);

//Main menu
int main(){
	if(numLL == 1){
	read();
	}
	cout<<numLL;
	system("pause");
	menu:
	system("cls");
	cout << endl <<setw(5) << "  " << "*******************************************************" << "Car Rental" << "*******************************************************\n\n";
	cout << "\n\t 1. Display" << endl;
	cout << "\n\t 2. Search" << endl;
	cout << "\n\t 3. Sort" << endl;
	cout << "\n\t 4. Add" << endl;
	cout << "\n\t 5. Remove" << endl;
	cout << "\n\t 6. Exit" << endl;
	int choice;
	cin >> choice;
	switch(choice){
		case 1:
			display();
			break;
		case 2:
			searchBy();
			break;
		case 3:
			sortBy();
			break;
		case 4:
			system("cls");
			add();
			break;
		case 5:
			system("cls");
			cout << "\n\t 1. By first name" << endl;
			cout << "\n\t 2. By VIN ID" << endl;
			cout << "\n\t 3. Exit" << endl;
			cin>>choice;
			remove(choice);
			break;
		case 6:
			exit(4);
			break;
		default:
			cout<<"Wrong choice\n";
	}
	
	goto menu;
	return 0;
}

void read(){
	ifstream File;
	File.open("carRental.txt");
	for(int i = 0;i < num;i++){
		File>>rawFile[i].carModel;
		File>>rawFile[i].carNo;
		File>>rawFile[i].carYear;
		File>>rawFile[i].carColor;
		File>>rawFile[i].ownerFName;
		File>>rawFile[i].ownerLName;
		File>>rawFile[i].tenantPhoneNo;
		File>>rawFile[i].addressOfTenant;
		File>>rawFile[i].dateOfRental;
		File>>rawFile[i].rentedOrNot;
		File>>rawFile[i].daysNo;
		File>>rawFile[i].payment;
		File>>rawFile[i].howMuchCost;
		dataAdder(i);
	}
	numLL = num;
	File.close();
}
void dataAdder(int n){
	temp = new node;
    temp->data = rawFile[n];
    temp->next = NULL;
	if(head == NULL){
			head = temp;
			head->next = NULL;
	}
	else if((head->next) == NULL){
			head->next = temp;
			temp->next = NULL;
			cur= temp;
	}
	else{
			cur->next = temp;
			temp->next = NULL;
			cur = temp;
	}
}
void add(){
	int n = numLL;
	for(int i = n;i < n + 1; i++){
		cout<<"Car model: ";
		cin>>rawFile[i].carModel;
		cout<<"Car number: ";
		cin>>rawFile[i].carNo;
		cout<<"Car year: ";
		cin>>rawFile[i].carYear;
		cout<<"Car color: ";
		cin>>rawFile[i].carColor;
		cout<<"First name:";
		cin>>rawFile[i].ownerFName;
		cout<<"Last name: ";
		cin>>rawFile[i].ownerLName;
		cout<<"Phone number: ";
		cin>>rawFile[i].tenantPhoneNo;
		cout<<"Address of tenant: ";
		cin>>rawFile[i].addressOfTenant;
		cout<<"Date of rent: ";
		cin>>rawFile[i].dateOfRental;
		cout<<"R or Not_R: ";
		cin>>rawFile[i].rentedOrNot;
		cout<<"How many days: ";
		cin>>rawFile[i].daysNo;
		cout<<"Payment : ";
		cin>>rawFile[i].payment;
		cout<<"Cost : ";
		cin>>rawFile[i].howMuchCost;
		dataAdder(i);
	}
	numLL = n + 1;
}

void remove(int n){
	int searchNum = -2;
	string remove;
	if(n == 1){
		cout<<"Enter the first name to remove from list: ";
		cin>>remove;
		searchNum = binarySearch('N', remove);
	}
	else if(n == 2){
		cout<<"Enter the VIN ID to remove from list: ";
		cin>>remove;
		searchNum = binarySearch('V', remove);
	}
	else{
		cout<<"Worng answer\n";
	}
	if(searchNum != -2){
		temp = head;
		if(searchNum == 0){
			cur = temp->next;
			head = cur;
			temp = NULL;
			cout<<"\n\t\tDeleted\n\n";
			numLL--;
		}
		else if(searchNum == 1){
			checker = temp;
			cur = temp->next;
			checker->next = cur->next;
			cur = NULL;
			cout<<"\n\t\tDeleted\n\n";
			numLL--;
		}
		else if(searchNum > 1){
			for(int i = 1;i < searchNum;i++){
				temp = temp->next;
				cur = temp->next;
			}
			temp->next = cur->next;
			cur = NULL;
			cout<<"\n\t\tDeleted\n\n";
			numLL--;
		}
		else{
			cout<<"NO FILE FOUND TO REMOVE!!";
		}
	}
	system("pause");
}

//Display
void display(){
	system("cls");
	temp = head;
	cout << "|" << setw(13) <<"Modle"<<"|"<<setw(20)<<"VIN"<<"|"<<setw(4)<<"Year"<<"|"<<setw(11)<<"Color"<<"|"<<setw(10)<<"First Name"<<"|"<<setw(12)<<"Last name"<<"|"<<setw(13)<<"Phone No."<<"|"<<setw(25)<<"Address"<<"|"<<setw(8)<<"R or Not"<<"|"<<setw(11)<<"Rented Date"<<"|"<<setw(7)<<"Day NO."<<"|"<<setw(9)<<"Payment"<<"|"<<setw(10)<<"Cost"<<"|"<<endl;
	if((temp->next) != NULL){
		while((temp->next) != NULL){
			cout << "|" << setw(13) <<temp->data.carModel<<"|"<<setw(20)<<temp->data.carNo<<"|"<<setw(4)<<temp->data.carYear<<"|"<<setw(11)<<temp->data.carColor<<"|"<<setw(10)<<temp->data.ownerFName<<"|"<<setw(12)<<temp->data.ownerLName<<"|"<<setw(13)<<temp->data.tenantPhoneNo<<"|"<<setw(25)<<temp->data.addressOfTenant<<"|"<<setw(8)<<temp->data.rentedOrNot<<"|"<<setw(11)<<temp->data.dateOfRental<<"|"<<setw(7)<<temp->data.daysNo<<"|"<<setw(9)<<temp->data.payment<<"|"<<setw(10)<<temp->data.howMuchCost<<"|"<<endl;
			temp = temp->next;
		}
	}
	if((temp->next) == NULL){
		cout << "|" << setw(13) <<temp->data.carModel<<"|"<<setw(20)<<temp->data.carNo<<"|"<<setw(4)<<temp->data.carYear<<"|"<<setw(11)<<temp->data.carColor<<"|"<<setw(10)<<temp->data.ownerFName<<"|"<<setw(12)<<temp->data.ownerLName<<"|"<<setw(13)<<temp->data.tenantPhoneNo<<"|"<<setw(25)<<temp->data.addressOfTenant<<"|"<<setw(8)<<temp->data.rentedOrNot<<"|"<<setw(11)<<temp->data.dateOfRental<<"|"<<setw(7)<<temp->data.daysNo<<"|"<<setw(9)<<temp->data.payment<<"|"<<setw(10)<<temp->data.howMuchCost<<"|"<<endl;
  		system("pause");
	}
}

//search
//search choices
void searchBy(){
	system("cls");
	int ch;
	SearchMenu:
	cout << "\n\t 1. By Name " << endl;
	cout << "\n\t 2. By VIN" << endl;
	cout << "\n\t 3. Go back\n";
	cin>>ch;
	switch(ch){
		case 1:
			searchUsing('N');
			break;
		case 2:
			searchUsing('V');
			break;
		case 3:
			main();
			break;
		default:
			cout<<"Wrong choice\n";
			goto SearchMenu;
	}
}

void searchUsing(char searchBy){
	system("cls");
	int ch;
	searchByMenu:
	cout << "\n\t 1. Linear Search" << endl;
	cout << "\n\t 2. Binary Search" << endl;
	cout << "\n\t 3. Go Back\n";
	cin>>ch;
	switch(ch){
		case 1:
			linearSearch(searchBy);
			break;
		case 2:
			ch = binarySearch(searchBy, "S");
			break;
		case 3:
			main();
			break;
		default:
			cout<<"Wrong choice\n";
			goto searchByMenu;
	}
}
//Linear search and binary search
void linearSearch(char searchBy){
	string search;
	system("cls");
	switch(searchBy){
		case 'N':
			cout << "   Enter the First Name you want to be searched:";
			cin >> search;
			temp = head;
				while((temp->next) != NULL){
					if(temp->data.ownerFName.compare(search) == 0){
					system("cls");
					cout<<endl<<"\n   |"<<temp->data.carModel<<"  |"<<temp->data.carColor<<"  |"<<temp->data.carYear<<"  |"<<temp->data.carNo<<"  |"<<temp->data.ownerFName<<" "<<temp->data.ownerLName<<"  |"<<temp->data.addressOfTenant<<"  |"<<temp->data.tenantPhoneNo<<"  |"<<temp->data.dateOfRental<<"  |"<<temp->data.payment<<"  |"<<temp->data.howMuchCost<<"  |"<<endl;
					system("pause");
						goto end;
				}
					temp = temp->next;
			}
			if(((temp->next) == NULL) && (temp->data.ownerFName.compare(search) == 0)){
				system("cls");
					cout<<"\n   |"<<temp->data.carModel<<"  |"<<temp->data.carColor<<"  |"<<temp->data.carYear<<"  |"<<temp->data.carNo<<"  |"<<temp->data.ownerFName<<" "<<temp->data.ownerLName<<"  |"<<temp->data.addressOfTenant<<"  |"<<temp->data.tenantPhoneNo<<"  |"<<temp->data.dateOfRental<<"  |"<<temp->data.payment<<"  |"<<temp->data.howMuchCost<<"  |"<<endl;
					system("pause");
						goto end;
			}
			cout<<"\n   No same First Name to be found\n\n";
			system("pause");
			break;
		case 'V':
			cout << "   Enter the VIN ID you want to be searched:";
			cin >> search;
			temp = head;
			while((temp->next) != NULL){
				if(temp->data.carNo.compare(search) == 0){
					system("cls");
					cout<<endl<<"\n   |"<<temp->data.carModel<<"  |"<<temp->data.carColor<<"  |"<<temp->data.carYear<<"  |"<<temp->data.carNo<<"  |"<<temp->data.ownerFName<<" "<<temp->data.ownerLName<<"  |"<<temp->data.addressOfTenant<<"  |"<<temp->data.tenantPhoneNo<<"  |"<<temp->data.dateOfRental<<"  |"<<temp->data.payment<<"  |"<<temp->data.howMuchCost<<"  |"<<endl;
					system("pause");
						goto end;
				}
				temp = temp->next;
			}
			if(((temp->next) == NULL) && (temp->data.carNo.compare(search) == 0)){
				system("cls");
				cout<<"\n   |"<<temp->data.carModel<<"  |"<<temp->data.carColor<<"  |"<<temp->data.carYear<<"  |"<<temp->data.carNo<<"  |"<<temp->data.ownerFName<<" "<<temp->data.ownerLName<<"  |"<<temp->data.addressOfTenant<<"  |"<<temp->data.tenantPhoneNo<<"  |"<<temp->data.dateOfRental<<"  |"<<temp->data.payment<<"  |"<<temp->data.howMuchCost<<"  |"<<endl;
				system("pause");
				goto end;
			}
			cout<<"\n   No same VIN ID to be found\n\n";
			end:
			system("pause");
			break;
	}
}
int binarySearch(char searchBy, string RorS){
	cout<<RorS<<endl;
	system("pause");
	selectionSort(searchBy, 'A', 1);
 	string search;
 	temp = head;
	int low = 0, high = numLL - 1, mid, found = 0;
	switch(searchBy){
		case 'N':
			if(RorS == "S"){
   				cout << "\n   Enter the first Name:";
				cin >> search;
			}
			else{
				search = RorS;
			}
			do{
					cur = temp;
					mid = (low + high) / 2;
				for(int i = 0;i < mid;i++){
					cur = cur->next;
				}
				if(cur->data.ownerFName < search){
					low = mid + 1;
				}
				else if(cur->data.ownerFName > search){
					high = mid - 1;
				}
				else {
					if(RorS == "S"){
		   				cout<<"\n   |"<<cur->data.carModel<<"  |"<<cur->data.carColor<<"  |"<<cur->data.carYear<<"  |"<<cur->data.carNo<<"  |"<<cur->data.ownerFName<<" "<<cur->data.ownerLName<<"  |"<<cur->data.addressOfTenant<<"  |"<<cur->data.tenantPhoneNo<<"  |"<<cur->data.dateOfRental<<"  |"<<cur->data.payment<<"  |"<<cur->data.howMuchCost<<"  |"<<endl;
					}
					found = 1;
				}
			}while(!found && (low <= high));
			if(found == 0){
				if(RorS == "S"){
					cout<<"\nNO search found\n";
				}
			}
			system("pause");
			break;
		case 'V':
			if(RorS == "S"){
 				cout << "\n   Enter the VIN ID:";
				cin >> search;
			}
			else{
				search = RorS;
			}
			do{
				cur = temp;
				mid = (low + high) / 2;
				for(int i = 0;i < mid;i++){
					cur = cur->next;
				}
				if(cur->data.carNo < search){
					low = mid + 1;
				}
				else if(cur->data.carNo > search){
					high = mid - 1;
				}
				else {
					if(RorS == "S"){
		   				cout<<"\n   |"<<cur->data.carModel<<"  |"<<cur->data.carColor<<"  |"<<cur->data.carYear<<"  |"<<cur->data.carNo<<"  |"<<cur->data.ownerFName<<" "<<cur->data.ownerLName<<"  |"<<cur->data.addressOfTenant<<"  |"<<cur->data.tenantPhoneNo<<"  |"<<cur->data.dateOfRental<<"  |"<<cur->data.payment<<"  |"<<cur->data.howMuchCost<<"  |"<<endl;
					}
					found = 1;
				}
			}while(!found && (low <= high));
 			if(found == 0){
 				if(RorS == "S"){
				cout<<"\nNO search found\n";
				}
			}
			system("pause");
			break;
	}
	if(found == 1){
		return mid;
	}
	else{
		return -1;
	}
}

//sort
void swapStruct(){
	string ch;
	ch = cur->data.addressOfTenant;
	cur->data.addressOfTenant = checker->data.addressOfTenant;
	checker->data.addressOfTenant = ch;
	ch = cur->data.carColor;
	cur->data.carColor = checker->data.carColor;
	checker->data.carColor = ch;
	ch = cur->data.carModel;
	cur->data.carModel = checker->data.carModel;
	checker->data.carModel = ch;
	ch = cur->data.carNo;
	cur->data.carNo = checker->data.carNo;
	checker->data.carNo = ch;
	ch = cur->data.carYear;
	cur->data.carYear = checker->data.carYear;
	checker->data.carYear = ch;
	ch = cur->data.dateOfRental;
	cur->data.dateOfRental = checker->data.dateOfRental;
	checker->data.dateOfRental = ch;
	ch = cur->data.daysNo;
	cur->data.daysNo = checker->data.daysNo;
	checker->data.daysNo = ch;
	ch = cur->data.howMuchCost;
	cur->data.howMuchCost = checker->data.howMuchCost;
	checker->data.howMuchCost = ch;
	ch = cur->data.ownerFName;
	cur->data.ownerFName = checker->data.ownerFName;
	checker->data.ownerFName = ch;
	ch = cur->data.ownerLName;
	cur->data.ownerLName = checker->data.ownerLName;
	checker->data.ownerLName = ch;
	ch = cur->data.payment;
	cur->data.payment = checker->data.payment;
	checker->data.payment = ch;
	ch = cur->data.rentedOrNot;
	cur->data.rentedOrNot = checker->data.rentedOrNot;
	checker->data.rentedOrNot = ch;
	ch = cur->data.tenantPhoneNo;
	cur->data.tenantPhoneNo = checker->data.tenantPhoneNo;
	checker->data.tenantPhoneNo = ch;
}
//sort choices
void sortBy(){
	system("cls");
	int ch;
	sortByMenu:
	cout << "\n\t 1. By Name \n";
	cout << "\n\t 2. By VIN\n";
	cout << "\n\t 4. Go back\n";
	cin>>ch;
	switch(ch){
		case 1:
			sortUsing('N');
			break;
		case 2:
			sortUsing('V');
			break;
		case 3:
			main();
			break;
		default:
			cout<<"Wrong choice\n";
			goto sortByMenu;
	}
}

void sortUsing(char sortByL){
	system("cls");
	int ch;
	char AorD;
	sortUsingMenu:
	cout << "\n\t 1. selection Sort" << endl;
	cout << "\n\t 2. Bubble Sort" << endl;
	cout << "\n\t 3. Go Back\n";
	cin>>ch;
	switch(ch){
		case 1:
			system ("cls");
 		    AorD = ascendOrDescend();
			selectionSort(sortByL, AorD, 0);
			break;
		case 2:
			system ("cls");
			AorD = ascendOrDescend();
			bubbleSort(sortByL, AorD);
			break;
		case 3:
			system ("cls");
			sortBy();
			break;
		default:
			cout<<"Wrong choice\n";
			goto sortUsingMenu;
	}
}
char ascendOrDescend(){
	system("cls");
	int ch;
	cout << "\n\t 1. ascending sort" << endl;
	cout << "\n\t 2. Descending sort" << endl;
	cout << "\n\t 3. Go Back\n";
	cin>>ch;
	switch(ch){
		case 1:
			system ("cls");
			return 'A';
			break;
		case 2:
			system ("cls");
			return 'D';
			break;
		case 3:
			system ("cls");
   			main();
			break;
		default:
			cout<<"Wrong choice\n";
	}
}
//selection and bubble sort
void selectionSort(char sortByUsing, char AorD, int ch){
	system("cls");
	temp = head;
	switch(AorD){
		case 'A':
			switch(sortByUsing){
				case 'N':
					for(int i= 0;i< numLL - 1;i++){
					cur = temp;
					checker = temp->next;
					for(int j= i + 1;j< numLL;j++){
						if(cur->data.ownerFName > checker->data.ownerFName){
							cur =	checker;
						}
						checker = checker->next;
					}
					if(temp != cur){
						checker = temp;
					swapStruct();
					}
					temp = temp->next;
				}
				if(ch == 0){
				display();
				}
				break;
				case 'V':
							for(int i= 0;i< numLL - 1;i++){
					cur = temp;
					checker = temp->next;
					for(int j= i + 1;j< numLL;j++){
						if(cur->data.carNo > checker->data.carNo){
							cur =	checker;
						}
						checker = checker->next;
					}
					if(temp != cur){
						checker = temp;
					swapStruct();
					}
					temp = temp->next;
				}
				if(ch == 0){
				display();
				}
				break;
			}
		break;
		case 'D':
				switch(sortByUsing){
				case 'N':
					for(int i= 0;i< numLL - 1;i++){
					cur = temp;
					checker = temp->next;
					for(int j= i + 1;j< numLL;j++){
						if(cur->data.ownerFName < checker->data.ownerFName){
							cur =	checker;
						}
						checker = checker->next;
					}
					if(temp != cur){
						checker = temp;
					swapStruct();
					}
					temp = temp->next;
				}
				if(ch == 0){
				display();
				}
					break;
				case 'V':
							for(int i= 0;i< numLL - 1;i++){
					cur = temp;
					checker = temp->next;
					for(int j= i + 1;j< numLL;j++){
						if(cur->data.carNo < checker->data.carNo){
							cur =	checker;
						}
						checker = checker->next;
					}
					if(temp != cur){
						checker = temp;
					swapStruct();
					}
					temp = temp->next;
				}
				if(ch == 0){
				display();
				}
					break;
			}
		break;
	}
}

void bubbleSort(char sortBy, char AorD ){
	system("cls");
	int changed = 1, i = 0;
	temp = head;
	switch(AorD){
	case 'A':
		switch(sortBy){
			case 'N':
			while((i < (numLL - 1) && (changed))){
					changed = 0;
					cur = temp;
					for(int j= 0;j < numLL - (i + 1);j++){
						checker = cur->next;
						if(cur->data.ownerFName > checker->data.ownerFName){
							swapStruct();
							changed = 1;
						}
						cur = cur->next;
					}
					i++;
				}
					display();
				break;
			case 'V':
					while((i< (numLL - 1) && (changed))){
					changed = 0;
					cur = temp;
					for(int j= 0;j< numLL -(i+1);j++){
						checker = cur->next;
						if(cur->data.carNo > checker->data.carNo){
							swapStruct();
							changed = 1;
						}
						cur = cur->next;
					}
					i++;
				}
					display();
				break;
			}
				break;
	case 'D':
			switch(sortBy){
			case 'N':
					while((i< (numLL - 1) && (changed))){
					changed = 0;
					cur = temp;
					for(int j= 0;j< numLL -(i+1);j++){
						checker = cur->next;
						if(cur->data.ownerFName < checker->data.ownerFName){
							swapStruct();
							changed = 1;
						}
						cur = cur->next;
					}
					i++;
				}
					display();
				break;
			case 'V':
				while((i< (numLL - 1) && (changed))){
					changed = 0;
					cur = temp;
					for(int j= 0;j< numLL -(i+1);j++){
						checker = cur->next;
						if(cur->data.carNo < checker->data.carNo){
							swapStruct();
							changed = 1;
						}
						cur = cur->next;
					}
					i++;
				}
					display();
				break;
			}
		break;
	}
}


