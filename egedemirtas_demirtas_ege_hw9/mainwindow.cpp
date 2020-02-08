#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    createElements();
    setupLayouts();
    setupConnections();
}

void MainWindow::createElements(){
    zeroButton = new QPushButton("0");
    zeroButton->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
    oneButton = new QPushButton("1");
    oneButton->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
    clearButton = new QPushButton("Clear");
    clearButton->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
    signMagButton = new QPushButton("Sign Magnitude");
    signMagButton->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
    resultLabel = new QLabel;
    inputLineEdit = new QLineEdit;
    inputLineEdit->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
    inputLineEdit->setReadOnly(true);
    resultLabel->setAlignment(Qt::AlignCenter);
    resultLabel->setText("Please enter a number to convert");
}

void MainWindow::setupLayouts(){
    outerL = new QVBoxLayout(this); // This is the outer Vertical layout; it will contain
                                    // all the other layouts
    inputR = new QHBoxLayout(this); // The first row; contains the inputLineEdit only
    zeroOneR = new QHBoxLayout(this); // Second row; contains the 0, 1, and Clear buttons
    buttonR = new QHBoxLayout(this); // Third row; contains the Sign Magnitude Button
    labelR = new QHBoxLayout(this); // Fourth row; contains the resultLabel label
    // TODO: add the graphical elements to the proper layouts and add the layouts to the outer layout
    // so that the final result is identical to the homework assignment's figures

    QHBoxLayout *horizontalLayout = new QHBoxLayout();//to create a horizontal layout to create such design ---> |0 | 1| Clear|
    horizontalLayout->addWidget(zeroButton);
    horizontalLayout->addWidget(oneButton);
    horizontalLayout->addWidget(clearButton);

    //add each widget one by one in correct order
    outerL->addWidget(inputLineEdit);
    outerL->addLayout(horizontalLayout);
    outerL->addWidget(signMagButton);
    outerL->addWidget(resultLabel);

    QWidget *parentWidget = new QWidget;
    parentWidget->setLayout(outerL);
    setCentralWidget(parentWidget);
}

void MainWindow::setupConnections(){
    QObject::connect(oneButton, SIGNAL(clicked()), this, SLOT(writeOne()));
    QObject::connect(zeroButton, SIGNAL(clicked()), this, SLOT(writeZero()));
    QObject::connect(clearButton, SIGNAL(clicked()),this, SLOT(clearInput()));
    QObject::connect(signMagButton, SIGNAL(clicked()), this, SLOT(signConvert()));
}

void MainWindow::writeOne(){
  //TODO: write a function that will append the character '1' to the
  // inputLineEdit
    inputLineEdit->insert("1");
}

void MainWindow::writeZero(){
  //TODO: write a function that will append the character '0' to the
  // inputLineEdit
    inputLineEdit->insert("0");
}

void MainWindow::clearInput(){
  //TODO: write a function that will set the text of inputLineEdit to ""
    inputLineEdit->setText("");
}

void MainWindow::signConvert(){
  //TODO: write a function that will convert the text in inputLineEdit
  // to a decimal number and print it in the QLabel resultLabel if the text is more than two bits long, otherwise
  // it will print the proper error.
  // If there are no bits in inputLineEdit print in result:
  // "Please enter a number in the input fields"
  // If there is only one bit in inputLineEdit print in result:
  // "Please enter at least two bits"
    int result = 0; //decimal value will be stored
    QString text = inputLineEdit->text(); //get the string in the qlineEdit to a qstring variable
    if(1 <= text.size() && text.size()< 2){
        resultLabel->setText( "Please enter at least two bits");
    }else if( text.size() == 0){
        resultLabel->setText( "Please enter a number in the input fields");
    }else{
        for(int i = text.size()-1; i>=0 ; i--){ //traverse from lsb to msb
            if( (i==0) && (text.at(i).digitValue()== 1 ) ){ //if the msb is 1, update the result as negative
                result = -result;
            }else{
                result = result + (text.at(i).digitValue() * pow(2,text.size()-1-i)); //turn the bit to decimal value and add to result
            }
        }
        resultLabel->setText(QString::number(result)); //show the decimal value
    }

}

MainWindow::~MainWindow()
{

}
