#include "Solicitud.h"

Solicitud::Solicitud(int id, Cliente& cliente, const std::vector<PedidoItem>& items, EstadoSolicitud estado = EstadoSolicitud::PENDIENTE)
    : id(id), cliente(cliente), items(items), estado(estado) {}

int Solicitud::getId() const {
    return id;
}

Cliente Solicitud::getCliente() const {
    return cliente;
}

const std::vector<PedidoItem>& Solicitud::getItems() const {
    return items;
}

const EstadoSolicitud Solicitud::getEstado() const { return estado; }

void Solicitud::setEstado(EstadoSolicitud nuevoEstado) { estado = nuevoEstado; }