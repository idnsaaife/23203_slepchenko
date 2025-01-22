#include "grid.h"

Grid::Grid(size_t rows, size_t cols) : rows(rows), cols(cols), cells(rows, std::vector<bool>(cols, false)) {}


Grid::Grid() : rows(INITIAL_SIZE), cols(INITIAL_SIZE), cells(rows, std::vector<bool>(cols, false)) {}

void Grid::clear()
{
    for (size_t j = 0; j < rows; j++) {
        for (size_t i = 0; i < cols; i++) {
            cells[j][i] = false;
        }
    }
}



size_t Grid::getRows() const
{
    return rows;
}

size_t Grid::getCols() const
{
    return cols;
}

size_t Grid::countNeighbors(size_t row, size_t col) const
{
    int count = 0;
    for (int i = -1; i <= 1; ++i)
    {
        for (int j = -1; j <= 1; ++j)
        {
            if (i == 0 && j == 0)
                continue;
            if ((row == 0 && i == -1) || (col == 0 && j == -1)) {
                continue;
            }
            size_t r = row + i;
            size_t c = col + j;
            if (r < rows && c < cols && cells[r][c])
                count++;
        }
    }
    return count;
}

void Grid::step()
{
    std::vector<std::vector<bool>> newCells = cells;
    for (size_t row = 0; row < rows; ++row)
    {
        for (size_t col = 0; col < cols; ++col)
        {
            size_t neighbors = countNeighbors(row, col);
            if (cells[row][col])
            { // cell alive
                newCells[row][col] = (neighbors == 2 || neighbors == 3);
            }
            else
            { // cell dead
                newCells[row][col] = (neighbors == 3);
            }
        }
    }
    cells = newCells;
}

bool Grid::isCellAlive(size_t row, size_t col) const
{
    return cells[row][col];
}

void Grid::setCellState(size_t row, size_t col, bool state)
{
    cells[row][col] = state;
}

void Grid::changeRowsSize(size_t newRows) {
    rows = newRows;

    cells.resize(rows);
    for (auto &col : cells) {
        col.resize(cols);
    }
}

void Grid::changeColsSize(size_t newCols){
    cols = newCols;
    for (auto &col : cells) {
        col.resize(cols);
    }
}
