#ifndef ALMACEN_CONTROLLER_H
#define ALMACEN_CONTROLLER_H

#include <vector>
#include "Producto.h"
#include "Solicitud.h"
#include "SolicitudController.h"
#include "ClienteController.h"

class AlmacenController {
public:
    AlmacenController(SolicitudController* solicitudController, ClienteController* clienteController);

    void crearProducto();
    void agregarExistencia();
    void eliminarProducto(int id);
    void agregarPasta();
    void agregarEsmalte();
    void agregarIngrediente();
    bool procesarSolicitud(Solicitud& solicitud);
    void procesarSolicitudesDiarias();
    std::vector<Producto> obtenerInventario();

private:
    std::vector<Producto> inventario;
    SolicitudController* solicitudController;
    ClienteController* clienteController;

    bool haySuficienteInventario(const PedidoItem& item);
    void actualizarInventario(const PedidoItem& item);
};

#endif // ALMACEN_CONTROLLER_H
