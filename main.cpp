#include <iostream>
#include <fstream>
#include <vector>

#include "solver.h"

int main()
{
    std::string puzzle_name = "puzzle.txt";

    std::cout << "Enter a puzzle name\n";
    std::cin >> puzzle_name;

    solver s;
    s.load_puzzle(puzzle_name);

    s.solve_puzzle();
}
