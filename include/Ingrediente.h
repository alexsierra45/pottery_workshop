#ifndef INGREDIENTE_H
#define INGREDIENTE_H

#include <string>

class Ingrediente {
    public:
        Ingrediente(int id, const std::string& nombre, const std::string& descripcion)
            : id(id), nombre(nombre), descripcion(descripcion) {}

        int getId() const { return id; }
        std::string getNombre() const { return nombre; }
        std::string getDescripcion() const { return descripcion; }

    private:
        int id;
        std::string nombre;
        std::string descripcion;
};

#endif // INGREDIENTE_H
