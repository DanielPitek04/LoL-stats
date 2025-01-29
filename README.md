# Project: League of Legends Statistics

A program written in C that calculates statistics from LoL and displays them in the form of four tables and one SVG graph.

## Project Structure

The project consists of three C files, two header files, and one makefile:

- `lolstatsproj.c` – the file containing the main logic of the program

- `nacitat.h` – the header file defining structures, global variables, and methods for `nacitat.c`
- `nacitat.c` – the file responsible for loading and processing input data

- `html.h` – the header file containing the method for calculating statistics
- `html.c` – the file for generating the output HTML page

- `makefile` – the file for linking files and creating the executable

## Requirements

Before running the project, make sure you have the following tools installed:

- **GCC**: For compiling C files
- **Make**: For compiling the project

## Installation and Running

1. Open a terminal (bash)
2. Make sure all project files are in the same directory
3. Run the following command to compile the project:

    - make
    
   This will create an executable file named `lolstats`
   
4. To run the program, use the following command:
    
    - ./lolstats zaznamy.txt hraci.txt stats.html
    
   - `zaznamy.txt` – input file containing match records
   - `hraci.txt` – input file containing a list of players
   - `stats.html` – output file where the HTML report with statistics will be generated



