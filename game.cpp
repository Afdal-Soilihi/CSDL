#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

const int ROWS = 15;
const int COLS = 40;

void printGrid(bool grid[ROWS][COLS]) {
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            cout << (grid[i][j] ? '+' : ' ') << ' ';
        }
        cout << endl;
    }
}

int countNeighbors(bool grid[ROWS][COLS], int row, int col) {
    int count = 0;
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if (!(i == 0 && j == 0)) {
                int r = (row + i + ROWS) % ROWS;
                int c = (col + j + COLS) % COLS;
                count += grid[r][c] ? 1 : 0;
            }
        }
    }
    return count;
}

void updateGrid(bool grid[ROWS][COLS]) {
    bool newGrid[ROWS][COLS];
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            int neighbors = countNeighbors(grid, i, j);
            if (grid[i][j]) {
                newGrid[i][j] = (neighbors == 2 || neighbors == 3);
            } else {
                newGrid[i][j] = (neighbors == 3);
            }
        }
    }
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            grid[i][j] = newGrid[i][j];
        }
    }
}

void randomizeGrid(bool grid[ROWS][COLS]) {
    srand(time(nullptr));
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            grid[i][j] = rand() % 2 == 0;
        }
    }
}

void loadGridFromFile(bool grid[ROWS][COLS], const string& filename) {
    ifstream file(filename);
    if (file.is_open()) {
        for (int i = 0; i < ROWS; ++i) {
            for (int j = 0; j < COLS; ++j) {
                char cell;
                file >> cell;
                grid[i][j] = (cell == '+');
            }
        }
        file.close();
    } else {
        cout << "Unable to open file: " << filename << endl;
    }
}

void saveGridToFile(bool grid[ROWS][COLS], const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        for (int i = 0; i < ROWS; ++i) {
            for (int j = 0; j < COLS; ++j) {
                file << (grid[i][j] ? '+' : ' ') << ' ';
            }
            file << endl;
        }
        file.close();
    } else {
        cout << "Unable to create file: " << filename << endl;
    }
}

int main() {
    bool grid[ROWS][COLS] = {false};

    char choice;
    do {
        cout << "Menu:" << endl;
        cout << "1. Start Game" << endl;
        cout << "2. Generate Random Population" << endl;
        cout << "3. Start Default Population" << endl;
        cout << "4. Load Population from File" << endl;
        cout << "5. Save Current Population to File" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case '1':
                while (true) {
                    printGrid(grid);
                    updateGrid(grid);
                    cout << string(50, '\n'); // Efface l'écran en imprimant 50 caractères de saut de ligne
                }
                break;
            case '2':
                randomizeGrid(grid);
                break;
            case '3':
                // Set the default population
                break;
            case '4': {
                string filename;
                cout << "Enter filename: ";
                cin >> filename;
                loadGridFromFile(grid, filename);
                break;
            }
            case '5': {
                string filename;
                cout << "Enter filename: ";
                cin >> filename;
                saveGridToFile(grid, filename);
                break;
            }
            case '6':
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != '6');

    return 0;
}