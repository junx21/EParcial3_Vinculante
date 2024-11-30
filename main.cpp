#include "ejercicio/Funciones.h"
#include "ejercicio/Tarea.h"
#include <iostream>
#include <vector>
#include <unordered_map>


int main() {
    std::vector<Tarea> tareas;
    tareas = {

        {'A', 20, {}},
        {'B', 5, {}},
        {'J', 25, {}},
        {'I', 35, {}},
        {'D', 10, {'A'}},
        {'C', 40, {'B'}},
        {'E', 5, {'D'}},
        {'F', 10, {'E'}},
        {'G', 20, {'C'}},
        {'H', 25, {'G'}},
        {'K', 15, {'I'}},
        {'L', 5, {'K'}},
        {'M', 25, {'H', 'L', 'F', 'J'}},
    };

    int numPersonas = 1;
    while (!sePuedeCompletarEnTiempo(tareas, numPersonas, 100)) {
        numPersonas++;
    }

    std::cout << "\nNumero minimo de personas necesarias: " << numPersonas << " personas\n" << std::endl;

    std::unordered_map<char, int> asignacionTarea;
    std::unordered_map<char, int> inicioTarea;
    calcularAsignaciones(tareas, numPersonas, asignacionTarea, inicioTarea);

    int horaFinal = 19;
    int minutoFinal = 10;
    int minutosTotales = horaFinal * 60 + minutoFinal - 100;
    int horaInicio = minutosTotales / 60;
    int minutoInicio = minutosTotales % 60;

    imprimirResultados(tareas, numPersonas, asignacionTarea, inicioTarea, horaInicio, minutoInicio);

    return 0;
}