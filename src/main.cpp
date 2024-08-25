#include <iostream>
#include "AlmacenController.h"
#include "ClienteController.h"
#include "SolicitudController.h"
#include "FileManager.h"

int main() {
    // AlmacenController almacen;
    ClienteController clienteCtrl;
    // SolicitudController solicitudCtrl;

    clienteCtrl.agregarCliente();

    // // Crear clientes
    // Cliente cliente1(1, "Juan", "Perez", "Calle 123");
    // Cliente cliente2(2, "Ana", "Gomez", "Calle 456");
    // clienteCtrl.agregarCliente(cliente1);
    // clienteCtrl.agregarCliente(cliente2);

    // // Crear productos
    // Dimensiones dim = {10.0, 10.0, 5.0, 0.5};
    // Producto producto1(1, dim, 101, 201, 15.99, "Maceta pequeña para bonsái", 100);
    // Producto producto2(2, dim, 102, 202, 25.99, "Maceta mediana para bonsái", 50);
    // almacen.agregarProducto(producto1);
    // almacen.agregarProducto(producto2);

    // // Crear solicitudes
    // PedidoItem item1 = {producto1, 10};
    // PedidoItem item2 = {producto2, 5};
    // std::vector<PedidoItem> items = {item1, item2};

    // Solicitud solicitud1(1, cliente1, items);
    // Solicitud solicitud2(2, cliente2, items);

    // solicitudCtrl.agregarSolicitud(solicitud1);
    // solicitudCtrl.agregarSolicitud(solicitud2);

    // // Procesar solicitudes diarias desde el AlmacenController
    // almacen.procesarSolicitudesDiarias(solicitudCtrl.obtenerSolicitudes());

    return 0;
}
