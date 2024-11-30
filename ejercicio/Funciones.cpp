#include "Funciones.h"
#include <queue>
#include <algorithm>
#include <iostream>
#include <iomanip>

bool sePuedeCompletarEnTiempo(const std::vector<Tarea>& tareas, int numPersonas, int tiempoMaximo) {
    std::unordered_map<char, int> gradoEntrada;
    std::unordered_map<char, std::vector<char>> listaAdyacencia;
    std::unordered_map<char, int> duracionTarea;

    inicializarMapas(tareas, gradoEntrada, listaAdyacencia, duracionTarea);

    std::queue<char> cola;
    for (const auto& tarea : tareas) {
        if (gradoEntrada[tarea.id] == 0) {
            cola.push(tarea.id);
        }
    }

    std::vector<int> tiempoPersona(numPersonas, 0);
    while (!cola.empty()) {
        char actual = cola.front();
        cola.pop();

        int personaMin = min_element(tiempoPersona.begin(), tiempoPersona.end()) - tiempoPersona.begin();
        tiempoPersona[personaMin] += duracionTarea[actual];

        for (const auto& vecino : listaAdyacencia[actual]) {
            gradoEntrada[vecino]--;
            if (gradoEntrada[vecino] == 0) {
                cola.push(vecino);
            }
        }
    }

    return *max_element(tiempoPersona.begin(), tiempoPersona.end()) <= tiempoMaximo;
}

void inicializarMapas(const std::vector<Tarea>& tareas, std::unordered_map<char, int>& gradoEntrada, std::unordered_map<char,std:: vector<char>>& listaAdyacencia, std::unordered_map<char, int>& duracionTarea) {
    for (const auto& tarea : tareas) {
        gradoEntrada[tarea.id] = 0;
        duracionTarea[tarea.id] = tarea.duracion;
    }

    for (const auto& tarea : tareas) {
        for (const auto& dep : tarea.dependencias) {
            listaAdyacencia[dep].push_back(tarea.id);
            gradoEntrada[tarea.id]++;
        }
    }
}

void calcularAsignaciones(const std::vector<Tarea>& tareas, int numPersonas, std::unordered_map<char, int>& asignacionTarea, std::unordered_map<char, int>& inicioTarea) {
    std::unordered_map<char, int> gradoEntrada;
    std::unordered_map<char, std::vector<char>> listaAdyacencia;
    std::unordered_map<char, int> duracionTarea;

    inicializarMapas(tareas, gradoEntrada, listaAdyacencia, duracionTarea);

    std:: queue<char> cola;
    for (const auto& tarea : tareas) {
        if (gradoEntrada[tarea.id] == 0) {
            cola.push(tarea.id);
        }
    }
    std::vector<int> tiempoPersona(numPersonas, 0);
    while (!cola.empty()) {
        char actual = cola.front();
        cola.pop();

        int personaMin = min_element(tiempoPersona.begin(), tiempoPersona.end()) - tiempoPersona.begin();
        inicioTarea[actual] = tiempoPersona[personaMin];
        tiempoPersona[personaMin] += duracionTarea[actual];
        asignacionTarea[actual] = personaMin;

        for (const auto& vecino : listaAdyacencia[actual]) {
            gradoEntrada[vecino]--;
            if (gradoEntrada[vecino] == 0) {
                cola.push(vecino);
            }
        }
    }
}

void imprimirResultados(const std::vector<Tarea>& tareas, int numPersonas, const std::unordered_map<char, int>& asignacionTarea, const std::unordered_map<char, int>& inicioTarea, int horaInicio, int minutoInicio) {

    bool menosDe100 = true;
    for (int i = 0; i < numPersonas; ++i) {
        std::cout << "Persona " << i + 1 << ":" << std::endl;
        std::cout << std::left << std::setw(10) << "Hora" << std::setw(10) << "Tarea" << std::setw(10) << "Duracion" << std::endl;
        std::cout << "-----------------------------" << std::endl;
        int tiempototal = 0;
        for (const auto& tarea : tareas) {
            if (asignacionTarea.at(tarea.id) == i) {
                int horaTarea = horaInicio + (inicioTarea.at(tarea.id) + minutoInicio) / 60;
                int minutoTarea = (inicioTarea.at(tarea.id) + minutoInicio) % 60;
                tiempototal += tarea.duracion;
                std::cout << std::setw(2) << std::setfill('0') << horaTarea << ":"
                     << std::setw(2) << std::setfill('0') << minutoTarea << std::setfill(' ') << "       "
                     << tarea.id << "       "
                     << tarea.duracion << " mins" << std::endl;
            }
        }
        if(tiempototal > 100) menosDe100 = false;
        std::cout <<"Total tiempo:       "<< tiempototal << " mins \n"<< std::endl;
    }
    int tiempototal2 = 0;
    std::cout << "Tabla de tareas por hora:" << std::endl;
    std::cout << std::left << std::setw(10) << "Hora" << std::setw(10) << "Tarea" << std::setw(10) << "Persona" << std::setw(10) << "Duracion" << std::endl;
    std::cout << "---------------------------------------" << std::endl;
    for (int t = 0; t <= 100; ++t) {
        for (const auto& tarea : tareas) {
            if (inicioTarea.at(tarea.id) == t) {
                int horaTarea = horaInicio + (t + minutoInicio) / 60;
                int minutoTarea = (t + minutoInicio) % 60;
                tiempototal2 += tarea.duracion;
                std::cout << std::setw(2) << std::setfill('0') << horaTarea << ":"
                     << std::setw(2) << std::setfill('0') << minutoTarea << std::setfill(' ') << "       "
                     << tarea.id << "          "
                     << asignacionTarea.at(tarea.id) + 1 << "      "
                     << tarea.duracion << " mins" << std::endl;
            }
        }
    }
    std::cout <<"Total tiempo:                 "<< tiempototal2 << " mins \n"<< std::endl;

    if (menosDe100)
    {
        std::cout<<"Se ha completado con exito la tarea en menos de 100 minutos\n";
    } else
    {
        std::cout<<"No se pudo completar la tarea en menos de 100 minutos\n";
    }
}