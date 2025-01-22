#ifndef GRID_H
#define GRID_H

#include <vector>

class Grid
{
public:
    Grid();
    Grid(size_t rows, size_t cols);
    void clear();
    void step();
    size_t getRows() const;
    size_t getCols() const;
    bool isCellAlive(size_t row, size_t col) const;
    void setCellState(size_t row, size_t col, bool state);
    void changeColsSize(size_t newCols);
    void changeRowsSize(size_t newRows);

private:
    size_t rows, cols;
    std::vector<std::vector<bool>> cells;
    static constexpr size_t INITIAL_SIZE = 64;
    size_t countNeighbors(size_t row, size_t col) const;
};

#endif // GRID_H
