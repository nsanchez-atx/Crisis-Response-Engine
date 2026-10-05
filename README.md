# Crisis Response Engine

A C++ command-line simulation for prioritizing patients and managing vaccine supplies during a regional outbreak.

## Overview

The program models three connected Texas regions—Austin, Dallas, and Houston—and allows a user to add patients, simulate changing outbreak conditions, rank patients by risk, and move vaccine supplies between connected regions.

## Features

- Stores regional data using `std::map`
- Stores patients with custom `Person` and `Region` structs
- Calculates patient risk using age, health status, essential-worker status, exposure level, and regional outbreak level
- Uses `std::priority_queue` to rank patients by risk score
- Represents transportation connections between regions with an adjacency-list graph
- Simulates crises by increasing outbreak levels and reducing vaccine supplies
- Validates menu and numeric input
- Transfers vaccines only between connected regions with sufficient supply

## Menu

The application supports:

1. Add Patient
2. View Regions
3. Generate Crisis
4. Show Priority Queue
5. Transfer Vaccines
6. Exit

## Build and Run

Compile with a C++11-compatible compiler:

```bash
g++ -std=c++11 CrisisResponseEngine.cpp -o crisis_response
./crisis_response
```

## Concepts Used

- C++ structs
- Maps and vectors
- Priority queues and custom comparators
- Graph representation
- Random simulation
- Input validation
- Command-line application design
