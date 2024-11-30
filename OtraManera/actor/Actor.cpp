#include "Actor.h"

#include <iostream>

// Constructor básico
Worker::Worker(WorkerType workerType)
    : type(workerType), currentTask(nullptr), specific_task(false) {}

// Constructor con propiedad specific_task
Worker::Worker(WorkerType workerType, bool onlySpecificTask)
    : type(workerType), currentTask(nullptr), specific_task(onlySpecificTask) {}

// Obtener el tipo del trabajador
WorkerType Worker::getType() const {
    return type;
}

// Obtener el estado del trabajador (activo si tiene una tarea asignada)
bool Worker::getState() const {
    return currentTask != nullptr;
}

// Asignar una tarea al trabajador
bool Worker::assignTask(const std::shared_ptr<Task>& task) {
    if (!task) {
        std::cerr << "Error: Task cannot be null." << std::endl;

        return false;
    }

    if (task->getWorkerType() != type) {
        //std::cerr << "Error: Worker type does not match task requirements." << std::endl;

        return false;
    }

    if (getState()) {
        std::cerr << "Error: Worker already has a task assigned." << std::endl;

        return false;
    }

    currentTask = task;
    task->setWorker(this);
    return true;
}

// Actualizar el estado del trabajador (implementación futura)
void Worker::Update() {
    // Este método se implementará en el futuro según los requisitos.

    if (currentTask) {
        currentTask->Update();
    }

    if (currentTask && currentTask->isCompleted()) {
        currentTask = nullptr;
    }

}

// Mostrar información del trabajador
void Worker::displayWorkerInfo() const {
    std::cout << "Worker Type: ";
    switch (type) {
        case WorkerType::CEO: std::cout << "CEO"; break;
        case WorkerType::trabajador1: std::cout << "AGENCY"; break;
        case WorkerType::trabajador2: std::cout << "AGENCY"; break;
        case WorkerType::trabajador3: std::cout << "AGENCY"; break;
    }
    std::cout << std::endl;

    std::cout << "State: " << (getState() ? "Active" : "Inactive") << std::endl;

    std::cout << "Specific Task Only: " << (specific_task ? "Yes" : "No") << std::endl;

    if (currentTask) {
        std::cout << "Current Task: " << currentTask->getName() << std::endl;
    } else {
        std::cout << "No current task assigned." << std::endl;
    }
}

std::string Worker::get_type() const {
    switch (type) {
        case WorkerType::CEO: return "CEO";
        case WorkerType::trabajador1: std::cout << "AGENCY"; break;
        case WorkerType::trabajador2: std::cout << "AGENCY"; break;
        case WorkerType::trabajador3: std::cout << "AGENCY"; break;
        default: return "UNKNOWN";
    }
