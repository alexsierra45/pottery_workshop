#ifndef SOLICITUD_H
#define SOLICITUD_H

#include <vector>
#include "Producto.h"
#include "Cliente.h"

struct PedidoItem {
    Producto producto;
    int cantidad;
};

class Solicitud {
public:
    Solicitud(int id, Cliente& cliente, const std::vector<PedidoItem>& items);

    int getId() const;
    Cliente& getCliente() const;
    const std::vector<PedidoItem>& getItems() const;
    bool esCumplida() const;
    void marcarCumplida();
    
private:
    int id;
    Cliente& cliente;
    std::vector<PedidoItem> items;
    bool cumplida;
};

#endif // SOLICITUD_H
