#include "include/Solicitud.h"

Solicitud::Solicitud(int id, Cliente& cliente, const std::vector<PedidoItem>& items)
    : id(id), cliente(cliente), items(items), cumplida(false) {}

int Solicitud::getId() const {
    return id;
}

Cliente& Solicitud::getCliente() const {
    return cliente;
}

const std::vector<PedidoItem>& Solicitud::getItems() const {
    return items;
}

bool Solicitud::esCumplida() const {
    return cumplida;
}

void Solicitud::marcarCumplida() {
    cumplida = true;
}
