#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "gameWidget.h"
//#include "grid.h"
#include <QTimer>
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private slots:
    void setSpeed(int speed);
    void startSimulation();
    void stopSimulation();
    void stepSimulation();
    void clearSimulation();

private:
    Ui::MainWindow *ui;
    GameWidget* game;
    QTimer *timer;
    static constexpr int STANDART_SPEED = 1000;
    static constexpr int GAME_WIDGET_STRETCH_FACTOR = 10;
    static constexpr int SETTINGS_WIDGET_STRETCH_FACTOR = 2;
    int speed = STANDART_SPEED;

};
#endif // MAINWINDOW_H
