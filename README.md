# C Programming - Formative Project 1
This project contains four programming problems implemented in C and C++ (for Arduino), which demonstrates core concepts of programming, hardware interaction, and algorithm design.

## Repository Structure
The project is divided into four main sections (Questions 1-4). Each directory contains the source code and documentation detailing the proof of concept (PoC), requirements, and analysis.

### Q1-WaterQuality/: 
A C program modeling the processing step of a water quality device monitor. It takes temperature and turbidity readings, calculates a water quality index, and classifies the water status. Includes an explanation of the C compilation lifecycle and error analysis.

### Q2-TransactionProcess/:
A C program simulating a mobile money transaction system terminal. It handles deposits, withdrawals, and balance checks while demonstrating the usage of loops, conditionals, break, and continue statements.

### Q3-DeliveryAnalysis/: 
A C program for a logistics company to analyze delivery routes. It calculates total distance, average distance, longest route, and counts routes above a limit. This section specifically emphasizes array manipulation and recursive problem-solving.

### Q4-SmartParking/: 
An Arduino (.ino) smart parking system project using an ultrasonic sensor to detect vehicle occupancy and control indicators (LEDs and a buzzer).

## Directions & Instructions

### Exploring the Documentation
Each sub-folder contains a docs/ directory. For a comprehensive explanation of how each program works, its design decisions, and its real-world applications, please refer to the PoC-*.md documents located inside the docs/ folder of the respective question.

### Running the C Programs (Q1, Q2, Q3)
To compile and run the standard C programs (Q1-WaterQuality, Q2-TransactionProcess, Q3-DeliveryAnalysis), you will need a C compiler such as gcc.

Navigate to the directory of the program you wish to run and use the following commands in your terminal:

# Example for Q1-WaterQuality
cd q1-water_quality

# Compile the code
gcc water_quality.c -o water_quality

# Run the executable
./water_quality
Repeat the same pattern for the others too


# Authored by Gilbert NTIVUNWA