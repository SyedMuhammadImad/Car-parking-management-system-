# Car Parking Management System

A console-based C++ simulation of a multi-floor parking lot, built to demonstrate
practical use of **stacks** and **queues** together in one system.

## How It Works

- Each **floor** stores parked cars in a **stack** (last car in is the first one
  that would need to move to let an earlier car out — mimicking real single-lane parking).
- Incoming cars go through an **entry queue**, and are assigned to the first
  available floor (FIFO).
- When all floors are full, new cars are placed on an **overflow waitlist queue**
  and automatically assigned a spot as soon as one frees up.

## Features

- Park a car (auto-assigned to the first available floor)
- Remove/exit a car by ID from any floor
- Automatic promotion of waitlisted cars when space opens up
- Live status display: per-floor occupancy, entry queue, and waitlist

## Data Structures Used

- `stack<int>` — per-floor car storage
- `queue<int>` — entry queue and overflow waitlist

## How to Run

```bash
g++ main.cpp -o car_parking_system
./car_parking_system
```

Default configuration: 2 floors, 3 spots per floor (edit `ParkingLot parkingLot(2, 3)` in `main()` to change).

## Menu Options

```
1. Enter a Car
2. Exit a Car
3. Display Parking Lot Status
4. Exit Program
```

## Tech

- C++
- STL (`<queue>`, `<stack>`)
