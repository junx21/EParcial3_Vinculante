#ifndef WORKER_H
#define WORKER_H

#include <string>
#include <memory>
#include "../tarea/Tarea.h" // Incluye la definición de la clase Task
#include "ActorType.h" // Incluye la definición de WorkerType

class Task; // Declaración anticipada para evitar dependencias circulares

// Enumeración para los tipos de trabajadores


class Worker {
private:
    WorkerType type;                       // Tipo de trabajador (inmutable)
    std::shared_ptr<Task> currentTask;     // Tarea actual (puntero inteligente)
    bool specific_task;                    // Indica si el trabajador solo acepta tareas específicas

public:
    // Constructores
    Worker(WorkerType workerType);                               // Constructor básico
    Worker(WorkerType workerType, bool onlySpecificTask);        // Constructor con propiedad specific_task

    // Métodos para obtener el tipo del trabajador
    WorkerType getType() const;

    // Métodos relacionados con tareas
    bool getState() const;                 // Activo solo si tiene tarea
    bool assignTask(const std::shared_ptr<Task>& task);

    // Actualizar el estado del trabajador (vacío por ahora)
    void Update();

    // Mostrar información del trabajador
    void displayWorkerInfo() const;

    std::string get_type() const;

};




#endif //WORKER_H