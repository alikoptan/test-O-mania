#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "fstream"
#include "iostream"
#include "memory"
#include "stdexcept"
#include "string"
#include "array"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

}

MainWindow::~MainWindow() {
    delete ui;
}

std::string MainWindow::exec(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

std::string MainWindow::compile(std::string inputCode, std::string customInput) {
    std::fstream fileWriter;

    //clearing input.cpp
    fileWriter.open("input.cpp", std::ios::out | std::ios::trunc);
    fileWriter.close();

    //clearing in.txt
    fileWriter.open("in.txt", std::ios::out | std::ios::trunc);
    fileWriter.close();

    //clearing out.txt
    fileWriter.open("out.txt", std::ios::out | std::ios::trunc);
    fileWriter.close();

    //inserting file input & output code to use in.txt, out.txt in input.cpp
    size_t index = inputCode.find("main()");
    std::string fileInput = "\nfreopen(\"in.txt\", \"r\", stdin);\nfreopen(\"out.txt\", \"w\", stdout);";
    for (size_t i = index; i < inputCode.size(); i++) {
        if (inputCode[i] == '{') {
            inputCode.insert(i + 1, fileInput);
            break;
        }
    }

    //rewriting modifed code in input.cpp
    fileWriter.open("input.cpp", std::ios::out | std::ios::trunc);
    fileWriter << (inputCode);
    fileWriter.close();


   //writing custom input in in.txt
    fileWriter.open("in.txt", std::ios::out | std::ios::trunc);
    fileWriter << (customInput);
    fileWriter.close();

    //compiling via linux g++
    std:: string command = "g++ -o input input.cpp";
    std::string consoleResult = exec(command.c_str());

    if (consoleResult.size() != 0) { //means errors were thown in console (compilation error).
        ui->outputText->append(QString::fromStdString(consoleResult));
        return "NO";
    }else {
        command = "./input";
        std::string output = exec(command.c_str());
        return output;
    }
}
void MainWindow::on_compileButton_clicked() {
    ui->outputText->clear();
    std::string inputCode = ui->sourceCodeText->toPlainText().toUtf8().constData();
    std::string customInput = ui->inputText->toPlainText().toUtf8().constData();
    compile(inputCode, customInput);
    std::string outputString, line;
    std::ifstream fileReader("out.txt");
    if (fileReader.is_open()) {
        while(std::getline(fileReader, line)) {
            outputString += line;
            outputString += '\n';
        }
        fileReader.close();
    }
    ui->outputText->append(QString::fromStdString(outputString));
}

void MainWindow::on_exitButton_clicked() {
    this->close();
}

void MainWindow::on_clearButton_clicked() {
    ui->sourceCodeText->clear();
}
