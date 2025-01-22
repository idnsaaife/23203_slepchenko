#include "gameWidget.h"
#include "factory.h"
#include "pattern.h"
#include <QPainter>
#include <QMouseEvent>

GameWidget::GameWidget(QWidget *parent) : QWidget(parent), grid(new Grid()) {
    grabGesture(Qt::PinchGesture);
}

GameWidget::~GameWidget() {
    delete grid;
}


QSize GameWidget::sizeHint() const
{
    return QSize(DEFAULT_SIZE, DEFAULT_SIZE);
}


void GameWidget::showNextGeneration() {

    grid->step();
    update();
}


void GameWidget::clearGrid()
{
    grid->clear();
    update();
}

bool GameWidget::event(QEvent *event)
{
    if (event->type() == QEvent::Gesture)
    {
        return gestureEvent(static_cast<QGestureEvent *>(event));
    }
    return QWidget::event(event);
}

bool GameWidget::gestureEvent(QGestureEvent *gestureEvent)
{
    if (QGesture *pinch = gestureEvent->gesture(Qt::PinchGesture))
    {
        pinchGesture(static_cast<QPinchGesture *>(pinch));
        return true;
    }
    return false;
}

void GameWidget::pinchGesture(QPinchGesture *gesture)
{
    if (gesture->state() == Qt::GestureStarted || gesture->state() == Qt::GestureUpdated)
    {
        scaleFactor *= gesture->scaleFactor();
        update();
    }
}

void GameWidget::paintEvent(QPaintEvent *)
{
    if (!grid)
        return;

    QPainter painter(this);

    int cellWidth = (width() / grid->getCols()) * scaleFactor;
    int cellHeight = (height() / grid->getRows()) * scaleFactor;

    for (size_t row = 0; row < grid->getRows(); row++)
    {
        for (size_t col = 0; col < grid->getCols(); col++)
        {
            QRect cellRect(col * cellWidth, row * cellHeight, cellWidth, cellHeight);
            painter.setBrush(grid->isCellAlive(row, col) ? Qt::black : Qt::white);
            painter.drawRect(cellRect);
        }
    }
}

void GameWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (!grid)
        return;

    int cellWidth = (width() / grid->getCols()) * scaleFactor;
    int cellHeight = (height() / grid->getRows()) * scaleFactor;

    size_t col = event->x() / cellWidth;
    size_t row = event->y() / cellHeight;

    if (row >= 0 && row < grid->getRows() && col >= 0 && col < grid->getCols())
    {
        grid->setCellState(row, col, !grid->isCellAlive(row, col));
        update();
    }
}

void GameWidget::setColsSize(int newCols)
{
    cols = newCols;
    updateGrid(grid->getRows(), cols);
    update();
}

void GameWidget::setRowsSize(int newRows)
{
    rows = newRows;
    updateGrid(rows, grid->getCols());
    update();
}

void GameWidget::updateGrid(int rows, int cols)
{

    delete grid;
    grid = new Grid(rows, cols);
    update();
}

void GameWidget::setPattern(const std::vector<std::vector<bool>>& pattern) {
    if (!grid)
        return;

    size_t rows = pattern.size();
    size_t cols = pattern[0].size();

    if (rows != grid->getRows() || cols != grid->getCols())
    {
        return;
    }

    for (size_t row = 0; row < rows; ++row)
    {
        for (size_t col = 0; col < cols; ++col)
        {
            grid->setCellState(row, col, pattern[row][col]);
        }

    }
    update();
}

void GameWidget::applyPattern(const QString &name) {
    auto PatternFactory = Factory<QString, Pattern>::getInstance();
    auto pattern = PatternFactory->createPatternByName(name);
    setPattern(pattern->createPattern(grid->getRows(), grid->getCols()));
}

