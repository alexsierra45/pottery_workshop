#ifndef SOLICITUD_H
#define SOLICITUD_H

#include <vector>
#include "Producto.h"
#include "Cliente.h"

struct PedidoItem {
    Producto producto;
    int cantidad;
};

enum class EstadoSolicitud {
    PENDIENTE,
    CUMPLIDA,
    PENDIENTE_ANTERIOR
};

class Solicitud {
    public:
        Solicitud(int id, const Cliente& cliente, const std::vector<PedidoItem>& items, EstadoSolicitud estado)
        : id(id), cliente(cliente), items(items), estado(estado) {}
        Solicitud(int id, Cliente& cliente, const std::vector<PedidoItem>& items, const EstadoSolicitud estado);

        int getId() const;
        Cliente getCliente() const;
        const std::vector<PedidoItem>& getItems() const;
        const EstadoSolicitud getEstado() const;
        void setEstado(EstadoSolicitud nuevoEstado);
        
    private:
        int id;
        Cliente cliente;
        std::vector<PedidoItem> items;
        EstadoSolicitud estado;
};

#endif // SOLICITUD_H