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

    if (s.solve_puzzle())
	    std::cout << "Puzzle solved!\n" << s << '\n';
    else
	    std::cout << "Puzzle could not be solved\n";

}
