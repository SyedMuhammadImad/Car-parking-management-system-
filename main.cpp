// Car Parking Management System
// Simulates a multi-floor parking lot using stacks (per-floor parking)
// and queues (entry queue + overflow waitlist).

#include <iostream>
#include <queue>
#include <stack>
using namespace std;

class Car {
public:
    int carId, floorNo, position;
    Car() : carId(-1), floorNo(-1), position(-1) {}
    Car(int id, int floor, int pos) : carId(id), floorNo(floor), position(pos) {}
};

class Floor {
public:
    int floorNo;
    int capacity;
    stack<int> parkedCars;

    Floor() : floorNo(0), capacity(0) {}
    Floor(int floorNum, int cap) : floorNo(floorNum), capacity(cap) {}

    bool addCar(int carId) {
        if (parkedCars.size() < capacity) {
            parkedCars.push(carId);
            return true;
        }
        return false;
    }

    bool removeCar(int carId) {
        stack<int> tempStack;
        bool found = false;

        while (!parkedCars.empty()) {
            int topCar = parkedCars.top();
            parkedCars.pop();

            if (topCar == carId) {
                found = true;
                break;
            }
            tempStack.push(topCar);
        }
        while (!tempStack.empty()) {
            parkedCars.push(tempStack.top());
            tempStack.pop();
        }
        return found;
    }

    bool isFull() {
        return parkedCars.size() == capacity;
    }

    int getAvailableSlots() {
        return capacity - parkedCars.size();
    }
};

class ParkingLot {
private:
    int floorCapacity, numFloors;
    queue<int> entryQueue;
    queue<int> overflowWaitlist;
    Floor *floors;
    Car *parkedCars;
    int parkedCount;

public:
    ParkingLot(int numFloors, int floorCap) : numFloors(numFloors), floorCapacity(floorCap) {
        floors = new Floor[numFloors];
        for (int i = 0; i < numFloors; i++) {
            floors[i] = Floor(i + 1, floorCap);
        }
        parkedCars = new Car[numFloors * floorCap];
        parkedCount = 0;
    }

    ~ParkingLot() {
        delete[] floors;
        delete[] parkedCars;
    }

    void enterCar(int carId) {
        entryQueue.push(carId);
        assignCarToFloor();
    }

    void assignCarToFloor() {
        while (!entryQueue.empty()) {
            int carId = entryQueue.front();
            bool parked = false;

            for (int i = 0; i < numFloors; i++) {
                if (!floors[i].isFull()) {
                    floors[i].addCar(carId);
                    parkedCars[parkedCount++] = Car(carId, i + 1, floors[i].parkedCars.size());
                    cout << "Car " << carId << " parked on Floor " << (i + 1) << ".\n";
                    entryQueue.pop();
                    parked = true;
                    break;
                }
            }

            if (!parked) {
                overflowWaitlist.push(carId);
                entryQueue.pop();
                cout << "Parking Full! Car " << carId << " added to waitlist.\n";
            }
        }
    }

    void exitCar(int carId) {
        for (int i = 0; i < parkedCount; i++) {
            if (parkedCars[i].carId == carId) {
                int floorNum = parkedCars[i].floorNo - 1;
                if (floors[floorNum].removeCar(carId)) {
                    cout << "Car " << carId << " exited from Floor " << (floorNum + 1) << ".\n";
                    parkedCars[i] = parkedCars[--parkedCount];
                    assignCarFromWaitlist();
                    return;
                }
            }
        }
        cout << "Car " << carId << " not found in parking lot.\n";
    }

    void assignCarFromWaitlist() {
        if (!overflowWaitlist.empty()) {
            int carId = overflowWaitlist.front();
            overflowWaitlist.pop();
            entryQueue.push(carId);
            assignCarToFloor();
        }
    }

    void displayStatus() {
        cout << "\n==== Parking Lot Status ====\n";
        for (int i = 0; i < numFloors; i++) {
            cout << "Floor " << (i + 1) << " (Capacity: " << floors[i].capacity << " | Available: " << floors[i].getAvailableSlots() << "): ";
            stack<int> temp = floors[i].parkedCars;
            if (temp.empty()) {
                cout << "[Empty]\n";
            } else {
                while (!temp.empty()) {
                    cout << temp.top() << " ";
                    temp.pop();
                }
                cout << "\n";
            }
        }

        cout << "Entry Queue (" << entryQueue.size() << " cars): ";
        queue<int> tempQueue = entryQueue;
        while (!tempQueue.empty()) {
            cout << tempQueue.front() << " ";
            tempQueue.pop();
        }
        cout << "\nOverflow Waitlist (" << overflowWaitlist.size() << " cars): ";
        queue<int> tempWaitlist = overflowWaitlist;
        while (!tempWaitlist.empty()) {
            cout << tempWaitlist.front() << " ";
            tempWaitlist.pop();
        }
        cout << "\n";
    }
};

int main() {
    ParkingLot parkingLot(2, 3);

    int choice, carId;
    do {
        cout << "\n======= Parking Lot Menu =======\n";
        cout << "1. Enter a Car\n";
        cout << "2. Exit a Car\n";
        cout << "3. Display Parking Lot Status\n";
        cout << "4. Exit Program\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter Car ID to park: ";
                cin >> carId;
                parkingLot.enterCar(carId);
                break;

            case 2:
                cout << "Enter Car ID to remove: ";
                cin >> carId;
                parkingLot.exitCar(carId);
                break;

            case 3:
                parkingLot.displayStatus();
                break;

            case 4:
                cout << "Exiting the program. Thank you!\n";
                break;

            default:
                cout << "Invalid choice! Please enter a valid option.\n";
        }
    } while (choice != 4);

    return 0;
}
