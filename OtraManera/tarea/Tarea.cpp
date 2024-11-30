#include "Tarea.h"
#include "../actor/Actor.h" // Incluye la definición de Worker y WorkerType
#include "../actor/ActorType.h"

#include <iostream>
#include <stdexcept> // Para manejar excepciones

// Constructor con WorkerType y múltiples dependencias
Task::Task(const std::string& taskName, int taskDuration, WorkerType workerType,
           const std::vector<std::shared_ptr<Task>>& dependencies)
    : name(taskName), duration(taskDuration), remaining_time(taskDuration),
      assigned_worker(nullptr), worker_type(workerType), dependencies(dependencies) {
    if (taskDuration <= 0) {
        std::cerr << "Error: Task duration must be greater than 0." << std::endl;
        duration = 1;
        remaining_time = 1;
    }
}

// Constructor con múltiples dependencias pero sin WorkerType (WorkerType::Generic por defecto)
Task::Task(const std::string& taskName, int taskDuration,
           const std::vector<std::shared_ptr<Task>>& dependencies)
    : Task(taskName, taskDuration, WorkerType::GENERIC, dependencies) {}

// Obtener el trabajador asignado
Worker* Task::getWorker() const {
    return assigned_worker;
}

// Configurar el trabajador asignado
void Task::setWorker(Worker* worker) {
    if (!worker) {
        throw std::runtime_error("Error: Worker cannot be null.");
    }

    if (worker->getType() != worker_type) {
        throw std::runtime_error("Error: Worker type does not match task requirements.");
    }

    assigned_worker = worker;
}

// Actualizar el tiempo restante de la tarea
void Task::Update() {
    if (remaining_time > 0) {
        remaining_time--; // Reducir el tiempo restante
    }
    else {
        std::cout << "Tarea: " << name << " - Completada" << std::endl;
    }
}

// Verificar si la tarea está completa
bool Task::isCompleted() const {
    return remaining_time <= 0;
}

// Verificar si la tarea puede realizarse (todas las dependencias completas)
bool Task::can_be_done() const {
    for (const auto& dep : dependencies) {
        if (!dep->isCompleted()) {
            return false; // Si alguna dependencia no está completa, no se puede realizar
        }
    }
    return true; // Todas las dependencias están completas
}

// Obtener el nombre de la tarea
std::string Task::getName() const {
    return name;
}

// Obtener la duración total de la tarea
int Task::getDuration() const {
    return duration;
}

// Obtener el tiempo restante de la tarea
int Task::getRemainingTime() const {
    return remaining_time;
}

// Obtener el tipo de trabajador requerido para esta tarea
WorkerType Task::getWorkerType() const {
    return worker_type;
}