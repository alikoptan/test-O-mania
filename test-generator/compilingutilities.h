#ifndef COMPILINGUTILITIES_H
#define COMPILINGUTILITIES_H
#include "string"
#include "ui_mainwindow.h"

namespace Ui {
class compilingutilities;
}
class compilingutilities
{
public:
    compilingutilities();
    std::string exec(const char*);
    void compile(std::string);
};

#endif // COMPILINGUTILITIES_H
