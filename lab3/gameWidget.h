#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include "grid.h"
#include "factory.h"
#include "pattern.h"
#include <QWidget>
#include <QPainter>
#include <QGestureEvent>
#include <QPinchGesture>
#include <QTimer>
#include <QString>

class GameWidget : public QWidget {
        Q_OBJECT

    public:
        GameWidget(QWidget *parent = nullptr);
        ~GameWidget();
        QSize sizeHint() const override;
        void updateGrid(int rows, int cols);
        bool event(QEvent *event) override;
        bool gestureEvent(QGestureEvent *gestureEvent);
        void pinchGesture(QPinchGesture *gesture);
        void setPattern(const std::vector<std::vector<bool>>& pattern);
        void showNextGeneration();
        void clearGrid();

    protected:
        void paintEvent(QPaintEvent *event) override;
        void mouseMoveEvent(QMouseEvent *event) override;


    public slots:
        void setColsSize(int newCols);
        void setRowsSize(int newRows);

        void applyPattern(const QString &name);

    private:
        Grid *grid = nullptr;
        static constexpr int DEFAULT_GRID_SIZE = 64;
        static constexpr int DEFAULT_CELL_SIZE = 10;
        static constexpr int DEFAULT_SIZE = 500;
        static constexpr double DEFAULT_SCALE_FACTOR = 1.0;
        int cellSize = DEFAULT_CELL_SIZE;
        int cols = DEFAULT_GRID_SIZE;
        int rows = DEFAULT_GRID_SIZE;
        double scaleFactor = DEFAULT_SCALE_FACTOR;


};

#endif
