#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ball.h"
#include "field.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    field = new Field(800, 600);
    ball = new Ball(25, 20, 45, field->getWidth(), field->getHeight());

    // Создаем объект QGraphicsRectItem для отображения границы площадки
    QGraphicsRectItem* fieldRect = scene->addRect(0, 0, field->getWidth(), field->getHeight(), QPen(Qt::red));
    fieldRect->setPen(QPen(Qt::red, 5)); // Устанавливаем толщину линии границы

    ballItem = scene->addEllipse(ball->getX() - ball->getRadius(),
                                 ball->getY() - ball->getRadius(),
                                 2 * ball->getRadius(), 2 * ball->getRadius(),
                                 QPen(Qt::black), QBrush(Qt::red));

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateBall);

    isMoving = false;
}

MainWindow::~MainWindow()
{
    delete ui;
    delete field;
    delete ball;
}

void MainWindow::on_startButton_clicked()
{
    if (!isMoving) {
        timer->start(10);
        isMoving = true;
    }
}

void MainWindow::on_resetButton_clicked()
{
    timer->stop();
    isMoving = false;
    resetBall();
}

void MainWindow::on_updateBallButton_clicked()
{
    if (!isMoving) {
        int radius = ui->radiusSpinBox->value();
        int speed = ui->speedSpinBox->value();
        int angle = ui->angleSpinBox->value();

        checkRadiusInput();

        if (radius <= qMin(ui->widthSpinBox->value(), ui->heightSpinBox->value()) / 2) {
            delete ball;
            ball = new Ball(radius, speed, angle, field->getWidth(), field->getHeight());

            resetBall();

            // Обновляем объект ballItem с новым радиусом
            scene->removeItem(ballItem);
            delete ballItem;
            ballItem = scene->addEllipse(ball->getX() - ball->getRadius(),
                                         ball->getY() - ball->getRadius(),
                                         2 * ball->getRadius(), 2 * ball->getRadius(),
                                         QPen(Qt::black), QBrush(Qt::red));
        }
    }
}

void MainWindow::checkRadiusInput()
{
    int radius = ui->radiusSpinBox->value();
    int maxRadius = qMin(ui->widthSpinBox->value(), ui->heightSpinBox->value()) / 2;

    if (radius > maxRadius) {
        QMessageBox::warning(this, "Ошибка", "Радиус шарика слишком большой для данного размера поля.");
        //ui->radiusSpinBox->setValue(maxRadius);
    }
}

void MainWindow::checkSizeInput()
{
    int width = ui->widthSpinBox->value();
    int height = ui->heightSpinBox->value();
    int max = ui->radiusSpinBox->value() * 2;

    if (width < max || height < max)
    {
        QMessageBox::warning(this, "Ошибка", "Размеры поля слишком малы для данного радиуса шарика.");
    }
}

void MainWindow::on_updateFieldButton_clicked()
{
    if (!isMoving) {
        int width = ui->widthSpinBox->value();
        int height = ui->heightSpinBox->value();

        checkSizeInput();

        if (width >= ui->radiusSpinBox->value() && height >= ui->radiusSpinBox->value()) {
            field->setWidth(width);
            field->setHeight(height);

            delete ball;
            ball = new Ball(25, 20, 45, field->getWidth(), field->getHeight());

            resetBall();
            this->resize(width, height);

            // Обновляем границу площадки после изменения размеров
            QList<QGraphicsItem*> items = scene->items();
            foreach (QGraphicsItem* item, items) {
                if (QGraphicsRectItem* rect = qgraphicsitem_cast<QGraphicsRectItem*>(item)) {
                    rect->setRect(0, 0, field->getWidth(), field->getHeight());
                    rect->setPen(QPen(Qt::red, 5));
                }
            }
        }
    }
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);
    scene->setSceneRect(0, 0, event->size().width(), event->size().height());
}

void MainWindow::updateBall()
{
    ball->move();
    if (field->checkCollision(*ball)) {
        ball->handleCollision();
    }
    ballItem->setRect(ball->getX() - ball->getRadius(),
                      ball->getY() - ball->getRadius(),
                      2 * ball->getRadius(), 2 * ball->getRadius());
}

void MainWindow::resetBall()
{
    int radius = ui->radiusSpinBox->value();
    int speed = ui->speedSpinBox->value();
    int angle = ui->angleSpinBox->value();

    delete ball;
    ball = new Ball(radius, speed, angle, field->getWidth(), field->getHeight());

    ballItem->setRect(ball->getX() - ball->getRadius(),
                      ball->getY() - ball->getRadius(),
                      2 * ball->getRadius(), 2 * ball->getRadius());
}
