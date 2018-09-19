#include <iostream>
#include <vector>
#include <windows.h>

/*
 * Program works, but unfortunately in CLion game table is not printed correctly.
 * I know it works because in debugging mode everything is correct.
 */

using vec_vecb = std::vector<std::vector<bool>>;

void PrintWorld(const vec_vecb &world) {
    for (const auto x : world) {
        for (const auto y : x) {
            std::cout << y << " " << std::flush;
        }
        std::cout << std::endl << std::flush;
    }
}

// Counting number of neighbours of given point
unsigned count_neighbours(const vec_vecb &world, const int row, const int column, const int size) {
    // 3x3 rows
    unsigned counter = 0;
    for (int neighbourRow = row - 1; neighbourRow <= row + 1; ++neighbourRow) {
        // 3x3 columns
        if (neighbourRow < 0 || neighbourRow >= size)
            continue;
        for (int neighbourColumn = column - 1; neighbourColumn <= column + 1; ++neighbourColumn) {
            // Checking if in the array
            if (neighbourColumn >= 0 && neighbourColumn < size) {
                if (world[neighbourRow][neighbourColumn])
                    if (neighbourColumn != column || neighbourRow != row)
                        ++counter;
            }
        }
    }
    return counter;
}

void
checkIfShouldBeAlive(const vec_vecb &world, vec_vecb &temp, const unsigned counter, const int row, const int column) {
    if (world[row][column]) {
        if (counter != 2 && counter != 3)
            temp[row][column] = false;
    } else {
        if (counter == 3)
            temp[row][column] = true;
    }
}

// Main game loop
void game_loop(vec_vecb &world) {
    unsigned num_iter = 10;
    while (--num_iter) {
        vec_vecb temp = world;
        unsigned size = temp.size();
        // World rows
        for (unsigned row = 0; row < size; ++row)
            // World columns
            for (unsigned column = 0; column < size; ++column) {
                unsigned counter = count_neighbours(world, row, column, size);
                checkIfShouldBeAlive(world, temp, counter, row, column);
            }

        world = temp;
        std::cout << std::flush;
        Sleep(1000);
        std::cout << std::flush;
        system("cls");
        PrintWorld(world);
    }
}


int main() {
    unsigned size = 10;
    vec_vecb world(size);

    for (unsigned i = 0; i < size; ++i) {
        std::vector<bool> vec(size, false);
        world.at(i) = vec;
    }
    // three points that will transform into square
    world.at(0).at(0) = true;
    world.at(0).at(1) = true;
    world.at(1).at(0) = true;

    // rotate 3x1 to 1x3 and so on
    world.at(5).at(5) = true;
    world.at(5).at(6) = true;
    world.at(5).at(7) = true;

    // dunno how to call it
    world.at(1).at(5) = true;
    world.at(1).at(6) = true;
    world.at(1).at(7) = true;
    world.at(2).at(6) = true;
    world.at(2).at(7) = true;
    world.at(2).at(8) = true;

    PrintWorld(world);
    game_loop(world);
    return 0;
}