#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QString>
#include <QHBoxLayout>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    QWidget *placeholder;
    QVBoxLayout *outerL;
    QHBoxLayout *inputR;
    QHBoxLayout *zeroOneR;
    QHBoxLayout *buttonR;
    QHBoxLayout *labelR;
    QPushButton *zeroButton;
    QPushButton *oneButton;
    QPushButton *clearButton;
    QPushButton *signMagButton;
    QLabel *resultLabel;
    QLineEdit *inputLineEdit;

    void createElements(); // this function will draw the graphical elements
    void setupLayouts(); // TODO: complete this function which will create the layouts and populate them with
                         // graphical elements

    void setupConnections(); // Sets up connections between buttons and slots

private slots:
    void writeOne();
    void writeZero();
    void clearInput();
    void signConvert();
};


#endif // MAINWINDOW_H
