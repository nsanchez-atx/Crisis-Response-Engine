# Crisis Response Engine

A C++ command-line simulation for prioritizing patients and managing vaccine supplies during a regional outbreak.

## Overview

The Crisis Response Engine models three connected Texas regions: Austin, Dallas, and Houston.

Users can add patients, simulate changing outbreak conditions, rank patients based on medical and regional risk factors, and transfer vaccine supplies between connected cities.

## Features

- Stores regional data using `std::map`
- Stores patients using custom `Person` and `Region` structs
- Uses an adjacency-list graph to represent connections between regions
- Calculates patient risk using:
  - Age
  - Immunocompromised status
  - Essential-worker status
  - Exposure level
  - Regional outbreak level
- Uses `std::priority_queue` with a custom comparator to rank patients by risk
- Simulates changing outbreak conditions and vaccine shortages
- Transfers vaccine supplies between connected regions
- Validates numeric and menu input

## Program Menu

The program allows users to:

1. Add Patient
2. View Regions
3. Generate Crisis
4. Show Priority Queue
5. Transfer Vaccines
6. Exit

## Example Output

```text
-REGION CONNECTIONS-
Austin connected to: Dallas Houston
Dallas connected to: Houston
Houston connected to: Austin

1. Add Patient
2. View Regions
3. Generate Crisis
4. Show Priority Queue
5. Transfer Vaccines
6. Exit
Choice:
```

## Technologies and Concepts

- C++
- Data Structures
- Graphs
- Priority Queues
- Maps
- Vectors
- Custom Comparators
- Structs
- Random Simulation
- Input Validation

## Build and Run

Compile using a C++11-compatible compiler:

```bash
g++ -std=c++11 CrisisResponseEngine.cpp -o crisis_response
```

Run the program:

```bash
./crisis_response
```

## Purpose

This project was created to practice applying data structures to a simulated real-world problem involving resource allocation, risk prioritization, and connections between regions.
