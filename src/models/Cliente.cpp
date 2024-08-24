#include "include/Cliente.h"

Cliente::Cliente(int id, const std::string& nombre, const std::string& apellidos, const std::string& direccion)
    : id(id), nombre(nombre), apellidos(apellidos), direccion(direccion), cantidadCompras(0) {}

int Cliente::getId() const {
    return id;
}

const std::string& Cliente::getNombre() const {
    return nombre;
}

const std::string& Cliente::getApellidos() const {
    return apellidos;
}

const std::string& Cliente::getDireccion() const {
    return direccion;
}

int Cliente::getCantidadCompras() const {
    return cantidadCompras;
}

bool Cliente::esAsiduo() const {
    return cantidadCompras >= 3;
}

void Cliente::incrementarCompras() {
    cantidadCompras++;
}
