#include "gameWidget.h"
#include "grid.h"
#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QVBoxLayout>
#include <string>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow),

    game(new GameWidget(this)),
    timer(new QTimer(this))
{
    ui->setupUi(this);


    connect(ui->applyPatternButton, &QPushButton::clicked, game, [this]() {
        game->applyPattern(ui->patternComboBox->currentText());
    });

    connect(ui->startButton, &QPushButton::clicked, this, &MainWindow::startSimulation);
    connect(ui->stopButton, &QPushButton::clicked, this, &MainWindow::stopSimulation);
    connect(ui->clearButton, &QPushButton::clicked, this, &MainWindow::clearSimulation);
    connect(ui->stepButton, &QPushButton::clicked, this, &MainWindow::stepSimulation);
    connect(ui->speedSlider, &QSlider::valueChanged, this, &MainWindow::setSpeed);
    connect(ui->colsSize, &QSpinBox::valueChanged, game, &GameWidget::setColsSize);
    connect(ui->rowsSize, &QSpinBox::valueChanged, game, &GameWidget::setRowsSize);
    connect(timer, &QTimer::timeout, this, &MainWindow::stepSimulation);

    ui->mainLayout->setStretchFactor(ui->gameLayout, GAME_WIDGET_STRETCH_FACTOR);
    ui->mainLayout->setStretchFactor(ui->settingsLayout, SETTINGS_WIDGET_STRETCH_FACTOR);
    ui->gameLayout->addWidget(game);
}

void MainWindow::setSpeed(int newSpeed) {
    speed = STANDART_SPEED - newSpeed;
    if (timer->isActive()) {
        timer->start(speed);
    }
}

void MainWindow::startSimulation()
{
    timer->start(speed);
    game->showNextGeneration();
}

void MainWindow::stopSimulation()
{
    timer->stop();
}

void MainWindow::stepSimulation()
{
    game->showNextGeneration();
}

void MainWindow::clearSimulation()
{
    timer->stop();
    game->clearGrid();
}


