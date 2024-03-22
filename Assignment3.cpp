// ASU Spring 2024 CSE310 HW#3
// Name : Daniel Budavari
// CarID : 1224612207
// Email : dbudavar@asu.edu
// Description :This program displays a menu of choices to a user
//              and performs the chosen task. It will keep asking a user to
//              enter the next choice until the choice of 'Q' (Quit) is entered.
//				also contains heapsort function
#include "MaxHeap.h"
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

void printMenu();
void heapSort(MaxHeap* oneMaxHeap);

int main()
{
	char input1 = 'Z';
	int vin, newVIN;
	string model, make;
	double price;
	int capacity, index = -1;   //array capacity and index
	bool success = false;


	Car oneCar;
	Car* car;

	// instantiate an empty Heap
	MaxHeap* heap1 = nullptr;
	printMenu();

	do {
		cout << "\nWhat action would you like to perform?" << endl;
		cin.get(input1);
		input1 = toupper(input1);
		cin.ignore(20, '\n');	//flush the buffer

		// matches one of the cases
		switch (input1)
		{
		case 'C':	//create empty Heap with the relevant capacity
			cout << "Please enter the heap capacity: ";
			cin >> capacity;
			cin.ignore(20, '\n');	//flush the buffer
			heap1 = new MaxHeap(capacity);

			break;

		case 'D':	//delete the heap, call the destructor explicitly
			cout << "Delete the heap\n" << endl;
			
			heap1->~MaxHeap();
			heap1 = new MaxHeap(5);

			break;

		case 'E':	//Extract the maximum node
			
			if (heap1 == NULL) {
				cout << "\nEmpty heap, can NOT extract max" << endl;
				break;
			}
			else //if valid operation can occur, call function and display
			{
				cout << "Before extract heap max operation:" << endl;
				heap1->printHeap();
				heap1->extractHeapMax();
				cout << "\nAfter extract heap max operation:" << endl;
				heap1->printHeap();
			}
			break;

		case 'F':	//Find a Car
			cout << "Enter the car VIN you want to search: ";
			cin >> vin;
			cin.ignore(20, '\n');	//flush the buffer

			if (heap1->isFound(vin) == -1) {
				cout << "\nCar with VIN: " << vin << " is NOT found" << endl;
			}
			else {
				cout << "\nCar with VIN: " << vin << " is found" << endl;
			}

			break;

		case 'I':	//Insert a Car
			cout << "\nEnter the car model: ";
			cin >> model;

			cout << "\nEnter the car make: ";
			cin >> make;

			cout << "\nEnter the car VIN: ";
			cin >> vin;

			cout << "\nEnter the car price: ";
			cin >> price;
			cin.ignore(20, '\n');	//flush the buffer

			//Displays if car was added or not
			if (heap1->heapInsert(vin, model, make, price) == true) {
				cout << "Car " << "\"" << model << " " << make << "\"" <<  " is added\n" << endl;
			}
			else {
				cout << "Car " << "\"" << model << " " << make << "\"" << " is NOT added\n" << endl;
			}

			break;

		case 'K':	//increase the vin
			cout << "\nEnter the old car VIN you want to increase: ";
			cin >> vin;

			cout << "\nEnter the new car VIN: ";
			cin >> newVIN;

			cin.ignore(20, '\n');	//flush the buffer
			index = heap1->isFound(vin);

			//if the old vin is not in the heap or the new vin already is in the heap
			if (index == -1) {
				cout << "\nThe old VIN you try to increase does not exist\n" << endl;
				break;
			}
			if (heap1->isFound(newVIN) != -1) {
				cout << "\nThe new VIN you entered already exist, increase VIN operation failed\n" << endl;
				break;
			}

			if (vin > newVIN) {
				cout << "\nIncrease VIN error: new vin is smaller than current vin" << endl;
				break;
			}

			//if succesful it will display the list before and after the increase
			car = heap1->getCarArr();
			cout << "Before increase VIN operation:" << endl;
			heap1->printHeap();

			car[index].vin = newVIN;
			heap1->heapIncreaseVIN(index, car[index]);
			
			cout << "\nCar with old VIN: " << vin << " is increased to new VIN: " << newVIN << "\n" << endl;
			cout << "After increase VIN operation: " << endl;
			heap1->printHeap();
			
			break;

		case 'M':	//get maximum node

			//if heap is empty, break
			if (heap1->getSize() == 0) {
				cout << "Empty heap, can NOT get max node\n" << endl;
				break;
			}

			//display the max heap
			cout << "The maximum heap node is:" << endl;
			cout << left;
			cout << setw(8) << heap1->getHeapMax().vin
				<< setw(12) << heap1->getHeapMax().model
				<< setw(12) << heap1->getHeapMax().make
				<< setw(8) << fixed << setprecision(2) << heap1->getHeapMax().price << "\n" << endl;
			
			break;

		case 'P':	//Print heap contents

			if (heap1->getSize() == 0) {
				cout << "Empty heap, no elements\n" << endl;
				break;
			} 
			heap1->printHeap();

			break;

		case 'S':	//HeapSort
			
			cout << "\nHeap sort. Cars will be sorted in increasing order of their VINs" << endl;
			heapSort(heap1);

			break;

		case 'Q':	//Quit
			delete heap1;
			break;

		case '?':	//Display Menu
			printMenu();
			break;

		default:
			cout << "Unknown action\n";
			break;
		}
	} while (input1 != 'Q');
	return 0;
}

//*****************************************************
//Given a max heap, we want to sort it in increasing order according to Car VIN, put the
//sorting result inside another array and print it out
void heapSort(MaxHeap* oneMaxHeap)
{
	int tempSize = oneMaxHeap->getSize() - 1;
	Car printArr[25]; //temp array to hold our cars for printing in increasing order

	//heapsort algorithm
	for (int i = tempSize; i >= 0; i--) {
		printArr[i] = oneMaxHeap->getHeapMax();
		oneMaxHeap->extractHeapMax();
	}
	//if the last two nodes are out of order, switch them
	if(printArr[0].vin > printArr[1].vin) {
		swap(printArr[0], printArr[1]);
	}

	//print the cars in increasing order of VIN
	int nav = 0;
	while (nav <= tempSize) {
		cout << left;
		cout << setw(8) << printArr[nav].vin
			<< setw(12) << printArr[nav].model
			<< setw(12) << printArr[nav].make
			<< setw(8) << fixed << setprecision(2) << printArr[nav].price << endl;
		nav++;
	}

}

//**The function displays the menu to a user**
void printMenu()
{
	cout << "Choice\t\tAction\n";
	cout << "------\t\t------\n";
	cout << "C\t\tCreate a heap\n";
	cout << "D\t\tDelete the heap\n";
	cout << "E\t\tExtract max node\n";
	cout << "F\t\tFind a Car by VIN\n";
	cout << "I\t\tInsert a Car\n";
	cout << "K\t\tIncrease the VIN\n";
	cout << "M\t\tGet the max node\n";
	cout << "P\t\tPrint the heap\n";
	cout << "S\t\tHeap Sort\n";
	cout << "Q\t\tQuit\n";
	cout << "?\t\tDisplay Help\n\n";
}