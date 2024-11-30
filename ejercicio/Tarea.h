#ifndef TAREA_H
#define TAREA_H

#include <vector>

struct Tarea {
    char id;
    int duracion;
    std::vector<char> dependencias;
};

#endif // TAREA_H