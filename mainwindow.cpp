#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // setCentralWidget(ui->openGLWidget);
    QCursor Cursor;
    Cursor.setShape(Qt::OpenHandCursor);
    setCursor(Cursor);
    __connectAll();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::__connectAll()
{
    // connect(this, &MainWindow::keySignal, ui->openGLWidget, &CSceneView::getKey);
}

void MainWindow::on_pushButton_clicked()
{

}

