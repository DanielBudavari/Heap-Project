// ASU Spring 2024 CSE310 HW#3
// Name : Daniel Budavari
// CarID : 1224612207
// Email : dbudavar@asu.edu
// Description : This header file contains the code to perform all operations in the heap,
//	   creating and destructing the heap, creating and reorganizing cars in the heap, and all helper functions,
//	   other functions like increaseVin, extractMax, and finally the helper functions for the main functions.
#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
using namespace std;

//Each Car will have a unique Vin
struct Car
{
	string model, make;
	int vin;        //Vehicle Identification Number
	double price;
};

//class MaxHeap represents a max heap that contains Car objects. The underline data structure
//is a one dimensional array of Cars.
class MaxHeap
{
private:
	struct Car* carArr;	//an array of Cars
	int capacity; //num of cars that can be stored
	int size;	//num of cars that are inside the heap actively

public:
	MaxHeap(int capacity);
	~MaxHeap();

	Car* getCarArr();
	int getSize();
	int getCapacity();
	int isFound(int aVin);
	bool heapIncreaseVIN(int index, Car oneCarWithNewVIN);
	bool heapInsert(int vin, string model, string make, double price);
	void heapify(int index);
	Car getHeapMax();
	void extractHeapMax();
	int leftChild(int parentIndex);
	int rightChild(int parentIndex);
	int parent(int childIndex);
	void printHeap();
};

//Constructor to dynamically allocate memory for a heap with the specified capacity
MaxHeap::MaxHeap(int capacity) {
	this->capacity = capacity;
	carArr = new Car[capacity];
	size = 0;
}

//Destructor
//Before termination, the destructor is called to free the associated memory occupied by the heap.
//and prints the number of nodes deleted by it.
MaxHeap::~MaxHeap() {
	int carCount = getSize();
	delete[] carArr;
	cout << "\nThe number of deleted cars is: " << carCount << endl;
}

//increase the Car's VIN located at the specific index
bool MaxHeap::heapIncreaseVIN(int index, Car oneCarWithNewVIN)
{
	if (getSize() <= index) {
		cout << "\nIncrease VIN error: index out of range" << endl;
		return false;
	}
	
	//Begin swapping, floating the proper Cars down
	carArr[index].vin = oneCarWithNewVIN.vin;
	carArr[index].model = oneCarWithNewVIN.model;
	carArr[index].make = oneCarWithNewVIN.make;
	carArr[index].price = oneCarWithNewVIN.price;
	while (index > 0 && carArr[parent(index)].vin < carArr[index].vin) {
		swap(carArr[index], carArr[parent(index)]);
		index = parent(index);
	}
	return true;
}

bool MaxHeap::heapInsert(int vin, string model, string make, double price) {
	
	if (isFound(vin) != -1 ) {
		cout << "\nDuplicated Car. Not added" << endl;
		return false;
	}

	struct Car newCar; 
	newCar.vin = vin;
	newCar.model = model;
	newCar.make = make;
	newCar.price = price;

	if (getCapacity() == getSize()) { //the heap is full so we need to double in size and dynamically allocate the memory
		
		capacity *= 2;
		Car* newCars = new Car[capacity]; //temp to copy over car objects
		
		// Copy existing elements to the new array
		for (int i = 0; i < getSize(); i++) {
			newCars[i] = carArr[i];
		}
		delete[] carArr;
		carArr = newCars;
		//increase size and calls increase vin to float down proper values and maxheapify the heap
		size++;
		carArr[size - 1].vin = -10000;
		heapIncreaseVIN(size - 1, newCar);
		
		cout << "Reach the capacity limit, double the capacity now." << endl;
		cout << "\nThe new capacity now is " << getCapacity() << "\n" << endl;
		return true;
	}
	else { //the car can be added as the heap is not full
		size++;
		carArr[size - 1].vin = -10000;
		heapIncreaseVIN(size - 1, newCar);
		return true;
	}
	return false;
}

void MaxHeap::heapify(int index) {
	int left = leftChild(index);
	int right = rightChild(index);
	int largest = isFound(getHeapMax().vin); //set to largest

	//if the left is larger
	if (left < getSize() - 1 && carArr[left].vin > carArr[index].vin) {
		largest = left;
	}
	else {
		largest = index;
	}
	//if the right is larger
	if (left <= getSize() - 1 && carArr[right].vin > carArr[largest].vin) {
		largest = right;
	}
	//if the current index is not the largest, swap and continue heapify-ing until it is
	if (largest != index) {
		swap(carArr[index], carArr[largest]);
		heapify(largest);
	}
}

void MaxHeap::extractHeapMax() {
	//heap is empty
	if (getSize() < 1 || getCapacity() == 0) {
		cout << "\nHeap Underflow." << endl;
	} 
	else {
		//obtain and store the max and remove it, then calling heapify to repair maxheap
		Car max = getHeapMax();
		carArr[0] = carArr[size - 1];
		size--;
		heapify(0);
	}
	
}
//Helper 'get' functions, mainly used for the main or our function 
Car MaxHeap::getHeapMax() {
	return carArr[0];
}

int MaxHeap::leftChild(int parentIndex) {
	return (2 * parentIndex + 1);
}

int MaxHeap::rightChild(int parentIndex) {
	return (2 * parentIndex + 2);
}

int MaxHeap::parent(int childIndex) { 
	return (childIndex - 1) / 2 ;
}

Car* MaxHeap::getCarArr() {
	return carArr;
}

int MaxHeap::getSize() {
	return size;
}

int MaxHeap::getCapacity() {
	return capacity;
}

int MaxHeap::isFound(int aVin) {

	for (int i = 0; i < getSize(); i++) { //searches array and compares vins, if found it returns the index the vin/car is at
		if (carArr[i].vin == aVin) {
			return i;
		}
	}
	//else, the car is not found and returns -1 (false)
	return -1;
}

void MaxHeap::printHeap() {
	//prints the car list 
	Car oneCar;
	//if empty
	if(getSize() == 0) {
		cout << "\nEmpty heap, no elements" << endl;
	}
	//if the heap has elements to print
	if (getSize() > 0) {
		cout << "\nHeap capacity = " << capacity << endl;
		cout << "\nHeap size = " << size << "\n" << endl;
	}
	
	int nav = 0;
	while (nav < size) {
		oneCar = carArr[nav];
		cout << left;
		cout << setw(8) << oneCar.vin
			<< setw(12) << oneCar.model
			<< setw(12) << oneCar.make
			<< setw(8) << fixed << setprecision(2) << oneCar.price << endl;
		nav++;
	} 
	
}