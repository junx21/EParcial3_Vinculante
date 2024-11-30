#ifndef CRUD_H
#define CRUD_H

#include <vector>
#include <stdexcept>
#include <iostream> // Para posibles mensajes de error

template <typename T>
class CRUD {
private:
    std::vector<T>& db; // Referencia al vector externo que actúa como base de datos

public:
    // Constructor que inicializa la base de datos
    explicit CRUD(std::vector<T>& database) : db(database) {}

    // Método para crear un nuevo registro
    void crear(const T& item) {
        db.push_back(item); // Agrega el nuevo elemento al vector
    }

    // Método para leer un registro por su ID
    T leer(size_t id) const {
        if (id < db.size()) {
            return db[id]; // Devuelve el objeto en la posición indicada
        } else {
            throw std::out_of_range("ID no válido"); // Lanza una excepción si el ID es inválido
        }
    }

    // Método para actualizar un registro existente
    void actualizar(size_t id, const T& nuevoItem) {
        if (id < db.size()) {
            db[id] = nuevoItem; // Actualiza el objeto en la posición indicada
        } else {
            throw std::out_of_range("ID no válido"); // Lanza una excepción si el ID es inválido
        }
    }

    // Método para borrar un registro por su ID
    void borrar(size_t id) {
        if (id < db.size()) {
            db.erase(db.begin() + id); // Borra el objeto en la posición indicada
        } else {
            throw std::out_of_range("ID no válido"); // Lanza una excepción si el ID es inválido
        }
    }

    // Método para listar todos los registros
    std::vector<T> listar() const {
        return db; // Devuelve una copia del vector completo
    }
};

#endif // CRUD_H