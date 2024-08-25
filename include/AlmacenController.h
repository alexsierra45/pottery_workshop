#ifndef ALMACEN_CONTROLLER_H
#define ALMACEN_CONTROLLER_H

#include <vector>
#include "Producto.h"
#include "Solicitud.h"

class AlmacenController {
public:
    AlmacenController();

    void crearProducto();
    void agregarExistencia();
    void eliminarProducto(int id);
    void agregarPasta();
    void agregarEsmalte();
    void agregarIngrediente();
    bool procesarSolicitud(Solicitud& solicitud);
    void procesarSolicitudesDiarias(std::vector<Solicitud>& solicitudes);

private:
    std::vector<Producto> inventario;

    bool haySuficienteInventario(const PedidoItem& item);
    void actualizarInventario(const PedidoItem& item);
};

#endif // ALMACEN_CONTROLLER_H
