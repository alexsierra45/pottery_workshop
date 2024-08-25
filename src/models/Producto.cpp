#include "Producto.h"

Producto::Producto(int id, const Dimensiones& dimensiones, Pasta& pasta, Esmalte& esmalte, double precio, const std::string& descripcion, int existencia)
    : id(id), dimensiones(dimensiones), pasta(pasta), esmalte(esmalte), precio(precio), descripcion(descripcion), existencia(existencia) {}

int Producto::getId() const {
    return id;
}

const Dimensiones& Producto::getDimensiones() const {
    return dimensiones;
}

Pasta Producto::getPasta() const {
    return pasta;
}

Esmalte Producto::getEsmalte() const {
    return esmalte;
}

double Producto::getPrecio() const {
    return precio;
}

const std::string& Producto::getDescripcion() const {
    return descripcion;
}

int Producto::getExistencia() const {
    return existencia;
}

void Producto::setExistencia(int nuevaExistencia) {
    existencia = nuevaExistencia;
}
