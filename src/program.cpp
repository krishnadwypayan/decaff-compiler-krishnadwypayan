#include "Headers/program.h"

Program::Program(string name) {
    this->className = std::move(name);
    cout << name << endl;
}