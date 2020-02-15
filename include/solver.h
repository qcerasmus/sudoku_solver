#pragma once
#include <iostream>
#include <fstream>
#include <vector>

/**
 * @brief This class is used to solve sudoku puzzles.
 * It will give all possible solutions to a puzzle.
 */
class solver
{
public:
    solver() = default;
    ~solver() = default;

    /**
     * @brief SUDOKU_PUZZLE_SIZE Defines the size of the
     * puzzle. Most puzzles are 9x9.
     */
    constexpr static int SUDOKU_PUZZLE_SIZE = 9;

    /**
     * @brief puzzle A 2 dimentional array to keep the values
     * of the puzzle in.
     */
    int puzzle[SUDOKU_PUZZLE_SIZE][SUDOKU_PUZZLE_SIZE];

    /**
     * @brief operator << Easy way to output the puzzle.
     * @param output The stream to write to.
     * @param solver The instance of the class.
     * @return The output stream after writing to it.
     */
    friend std::ostream& operator<<(std::ostream& output, const solver& solver)
    {
        for (auto i = 0; i < 9; i++)
        {
            for (auto j = 0; j < 9; j++)
            {
                output << solver.puzzle[i][j];
            }
            output << '\n';
        }

        return output;
    }

    /**
     * @brief load_puzzle Loads a puzzle from the given filename.
     * The file must have 9x9 values. Empty values are represented with
     * a 0 value.
     * @param file_name The name of the file that contains the puzzle.
     */
    void load_puzzle(const std::string& file_name)
    {
        std::ifstream in_file;
        in_file.open(file_name);
        if (in_file.is_open())
        {
            char line[SUDOKU_PUZZLE_SIZE + 1];
            int line_number = 0;
            while (in_file.getline(line, SUDOKU_PUZZLE_SIZE + 1))
            {
                if (line_number >= SUDOKU_PUZZLE_SIZE)
                    break;

                for (auto i = 0; i < SUDOKU_PUZZLE_SIZE; i++)
                    puzzle[line_number][i] = line[i] - 48; //Reading chars, convert to numbers.

                ++line_number;
            }
            in_file.close();
        }
    }

    /**
     * @brief load_puzzle Overload for if you really want to send
     * the array. In this case the puzzle is all one line which
     * is converted to a 2D array.
     * @param temp_puzzle The puzzle to test on.
     */
    void load_puzzle(std::vector<int> temp_puzzle)
    {
        for (auto i = 0; i < SUDOKU_PUZZLE_SIZE * SUDOKU_PUZZLE_SIZE; i++)
        {
            puzzle[i / SUDOKU_PUZZLE_SIZE][i % SUDOKU_PUZZLE_SIZE] = temp_puzzle[i];
        }
    }

    /**
     * @brief solve_puzzle Solves the puzzle using recursion.
     * It will first find an empty spot and then try all possible values
     * at the x,y coordinate.
     *
     * After a possible number is found, we will recurse.
     * If we find no further empty spaces, a solution was found.
     *
     * If we didn't find a possible value further down, we will reset
     * the puzzle and try the next possible value.
     */
    bool solve_puzzle()
    {
        bool result = false;
        for (auto x = 0; x < SUDOKU_PUZZLE_SIZE; x++)
        {
            for (auto y = 0; y < SUDOKU_PUZZLE_SIZE; y++)
            {
                if (puzzle[x][y] == 0) //Empty space
                {
                    for (int number_to_test = 1; number_to_test < SUDOKU_PUZZLE_SIZE + 1; number_to_test++)
                    {
                        if (possible_move(x, y, number_to_test))
                        {
                            puzzle[x][y] = number_to_test;
                            result = solve_puzzle();
                            if (result)
                                return true;
                            puzzle[x][y] = 0;
                        }
                    }

                    return result;
                }
            }
        }
        return true;
    }

    /**
     * @brief possible_move Checks if a value is possible in the
     * position given.
     * @param x The x coordinate to check.
     * @param y The y coordinate to check.
     * @param number_to_test The number to test at the x,y position.
     * @return true if the move is possible.
     */
    bool possible_move(int x, int y, int number_to_test)
    {
        if (x >= SUDOKU_PUZZLE_SIZE || y >= SUDOKU_PUZZLE_SIZE ||
            x < 0 || y < 0)
            return false;

        for (auto i = 0; i < SUDOKU_PUZZLE_SIZE; i++)
        {
            if (puzzle[x][i] == number_to_test)
                return false;
            if (puzzle[i][y] == number_to_test)
                return false;
        }

        x = (x / 3) * 3;
        y = (y / 3) * 3;

        for (auto i = 0; i < 3; i++)
        {
            for (auto j = 0; j < 3; j++)
            {
                if (puzzle[x+i][y+j] == number_to_test)
                    return false;
            }
        }

        return true;
    }
};
