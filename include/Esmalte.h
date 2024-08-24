#ifndef ESMALTE_H
#define ESMALTE_H

#include <string>
#include <vector>
#include "Ingrediente.h"

class Esmalte {
    public:
        Esmalte(int id, const std::string& color, const std::vector<Ingrediente>& ingredientes)
            : id(id), color(color), ingredientes(ingredientes) {}

        int getId() const { return id; }
        std::string getColor() const { return color; }
        std::vector<Ingrediente> getIngredientes() const { return ingredientes; }

    private:
        int id;
        std::string color;
        std::vector<Ingrediente> ingredientes;
};

#endif // ESMALTE_H
