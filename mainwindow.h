#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QResizeEvent>
#include <QMainWindow>
#include <QTimer>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include "field.h"
#include "ball.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void on_startButton_clicked();
    void on_resetButton_clicked();
    void on_updateBallButton_clicked();
    void on_updateFieldButton_clicked();
    void updateBall();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QGraphicsEllipseItem *ballItem;
    QTimer *timer;
    Field *field;
    Ball *ball;
    bool isMoving;

    void resetBall();
    void checkRadiusInput();
    void checkSizeInput();
};

#endif // MAINWINDOW_H
