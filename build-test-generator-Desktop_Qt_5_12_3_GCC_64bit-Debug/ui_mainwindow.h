/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QLabel *sourceCodeLabel;
    QPushButton *compileButton;
    QPushButton *clearButton;
    QPushButton *exitButton;
    QLabel *customInputLabel;
    QTextEdit *inputText;
    QLabel *outputLabel;
    QTextEdit *outputText;
    QLabel *testCasesLabel;
    QTextBrowser *textCasesBrowser;
    QPushButton *generateTestCasesButton;
    QTextEdit *sourceCodeText;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(681, 447);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        sourceCodeLabel = new QLabel(centralWidget);
        sourceCodeLabel->setObjectName(QString::fromUtf8("sourceCodeLabel"));
        sourceCodeLabel->setGeometry(QRect(10, 0, 341, 17));
        compileButton = new QPushButton(centralWidget);
        compileButton->setObjectName(QString::fromUtf8("compileButton"));
        compileButton->setGeometry(QRect(10, 360, 131, 25));
        clearButton = new QPushButton(centralWidget);
        clearButton->setObjectName(QString::fromUtf8("clearButton"));
        clearButton->setGeometry(QRect(160, 360, 91, 25));
        exitButton = new QPushButton(centralWidget);
        exitButton->setObjectName(QString::fromUtf8("exitButton"));
        exitButton->setGeometry(QRect(270, 360, 91, 25));
        customInputLabel = new QLabel(centralWidget);
        customInputLabel->setObjectName(QString::fromUtf8("customInputLabel"));
        customInputLabel->setGeometry(QRect(380, 0, 111, 17));
        inputText = new QTextEdit(centralWidget);
        inputText->setObjectName(QString::fromUtf8("inputText"));
        inputText->setGeometry(QRect(380, 20, 291, 51));
        outputLabel = new QLabel(centralWidget);
        outputLabel->setObjectName(QString::fromUtf8("outputLabel"));
        outputLabel->setGeometry(QRect(380, 80, 54, 17));
        outputText = new QTextEdit(centralWidget);
        outputText->setObjectName(QString::fromUtf8("outputText"));
        outputText->setGeometry(QRect(380, 100, 291, 51));
        testCasesLabel = new QLabel(centralWidget);
        testCasesLabel->setObjectName(QString::fromUtf8("testCasesLabel"));
        testCasesLabel->setGeometry(QRect(380, 160, 71, 17));
        textCasesBrowser = new QTextBrowser(centralWidget);
        textCasesBrowser->setObjectName(QString::fromUtf8("textCasesBrowser"));
        textCasesBrowser->setGeometry(QRect(380, 180, 291, 171));
        generateTestCasesButton = new QPushButton(centralWidget);
        generateTestCasesButton->setObjectName(QString::fromUtf8("generateTestCasesButton"));
        generateTestCasesButton->setGeometry(QRect(380, 360, 291, 25));
        sourceCodeText = new QTextEdit(centralWidget);
        sourceCodeText->setObjectName(QString::fromUtf8("sourceCodeText"));
        sourceCodeText->setGeometry(QRect(10, 20, 351, 331));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 681, 22));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        sourceCodeLabel->setText(QApplication::translate("MainWindow", "Source Code: (only g++14 compilable code)", nullptr));
        compileButton->setText(QApplication::translate("MainWindow", "Compile and Run", nullptr));
        clearButton->setText(QApplication::translate("MainWindow", "Clear", nullptr));
        exitButton->setText(QApplication::translate("MainWindow", "Exit", nullptr));
        customInputLabel->setText(QApplication::translate("MainWindow", "Custom Input:", nullptr));
        outputLabel->setText(QApplication::translate("MainWindow", "Output:", nullptr));
        testCasesLabel->setText(QApplication::translate("MainWindow", "Test Cases:", nullptr));
        generateTestCasesButton->setText(QApplication::translate("MainWindow", "Generate Test Cases", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
