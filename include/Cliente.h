#ifndef CLIENTE_H
#define CLIENTE_H

#include <string>

class Cliente {
public:
    Cliente(int id, const std::string& nombre, const std::string& apellidos, const std::string& direccion);

    int getId() const;
    const std::string& getNombre() const;
    const std::string& getApellidos() const;
    const std::string& getDireccion() const;
    int getCantidadCompras() const;
    bool esAsiduo() const;

    void incrementarCompras();

private:
    int id;
    std::string nombre;
    std::string apellidos;
    std::string direccion;
    int cantidadCompras;
};

#endif // CLIENTE_H
