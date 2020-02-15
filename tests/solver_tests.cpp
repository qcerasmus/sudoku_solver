#include "gtest/gtest.h"
#include "solver.h"

#include <fstream>

TEST(solver_tests, possible_moves)
{
    std::vector<int> array = {0,0,0,0,0,0,0,0,0,
                              0,0,0,0,0,0,9,0,0,
                              9,7,0,3,0,0,0,0,0,
                              0,1,0,0,6,0,5,0,0,
                              0,0,4,7,0,8,0,0,2,
                              0,0,0,0,0,2,0,0,6,
                              0,3,1,0,0,4,0,0,0,
                              0,0,0,8,0,0,1,6,7,
                              0,8,7,0,0,0,0,0,0};

    solver s;
    s.load_puzzle(array);
    EXPECT_EQ(false, s.possible_move(8, 8, 1));
    EXPECT_EQ(true, s.solve_puzzle());
    std::cout << s << std::endl;
}

TEST(solver_tests, hard_puzzles_95)
{
    solver s;
    std::ifstream test_file;
    test_file.open("top95");
    if (test_file.is_open())
    {
        std::string line;
        std::vector<int> puzzle;
        auto i = 0;
        while (std::getline(test_file, line))
        {
            puzzle.clear();
            EXPECT_EQ(81, line.size());
            for (auto i = 0; i < 81; i++)
            {
                puzzle.push_back(line[i] - 48);
            }
            s.load_puzzle(puzzle);
            EXPECT_EQ(true, s.solve_puzzle());
            i++;
            std::cout << "Puzzle " << i << " of 95 completed\n";
        }
        test_file.close();
    }
}
