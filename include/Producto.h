#ifndef PRODUCTO_H
#define PRODUCTO_H

#include <string>
#include "Pasta.h"
#include "Esmalte.h"

struct Dimensiones {
    double largo;
    double ancho;
    double altura;
    double grosor;
};

class Producto {
    public:
        Producto(int id, const Dimensiones& dimensiones, 
            Pasta& pasta, Esmalte& esmalte, double precio, const std::string& descripcion, int existencia);

        int getId() const;
        const Dimensiones& getDimensiones() const;
        Pasta getPasta() const;
        Esmalte getEsmalte() const;
        double getPrecio() const;
        const std::string& getDescripcion() const;
        int getExistencia() const;

        void setExistencia(int nuevaExistencia);

    private:
        int id;
        Dimensiones dimensiones;
        Pasta pasta;
        Esmalte esmalte;
        double precio;
        std::string descripcion;
        int existencia;
};

#endif // PRODUCTO_H
