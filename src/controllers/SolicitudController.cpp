#include <algorithm>
#include <iostream>
#include <queue>

#include "SolicitudController.h"
#include "FileManager.h"

SolicitudController::SolicitudController() {
    FileManager fileManager;

    solicitudes = fileManager.cargarSolicitudesDesdeArchivo();
}

void mostrarClientesDisponibles(std::vector<Cliente> clientes) {
    std::cout << "Clientes disponibles:\n";
    for (const auto& cliente : clientes) {
        std::cout << "ID: " << cliente.getId() << " - Nombre: " << cliente.getNombre() << std::endl;
    }
}

void mostrarProductosDisponibles(std::vector<Producto> productos) {
    std::cout << "Productos disponibles:\n";
    for (const auto& producto : productos) {
        std::cout << "ID: " << producto.getId() 
                  << " - Descripción: " << producto.getDescripcion() 
                  << " - Precio: " << producto.getPrecio() 
                  << " - Existencia: " << producto.getExistencia() 
                  << std::endl;
    }
}

void SolicitudController::agregarSolicitud() {
    FileManager fileManager;

    std::optional<Cliente> cliente = std::nullopt;

    const auto& clientes = fileManager.cargarClientesDesdeArchivo();
    while (!cliente) {
        mostrarClientesDisponibles(clientes);
        std::cout << "Seleccione el ID del cliente: ";
        int clienteId;
        std::cin >> clienteId;

        cliente = fileManager.obtenerClientePorId(clientes, clienteId);
        if (!cliente) {
            std::cout << "Cliente no encontrado. Intente nuevamente." << std::endl;
        }
    }

    std::vector<PedidoItem> items;

    const auto& productos = fileManager.cargarProductosDesdeArchivo(); 
    char opcion;
    do {
        std::optional<Producto> producto = std::nullopt;
        while (!producto) {
            mostrarProductosDisponibles(productos);
            std::cout << "Seleccione el ID del producto: ";
            int productoId;
            std::cin >> productoId;

            producto = fileManager.obtenerProductoPorId(productos, productoId);
            if (!producto) {
                std::cout << "Producto no encontrado. Intente nuevamente." << std::endl;
            }
        }

        std::cout << "Ingrese la cantidad: ";
        int cantidad;
        std::cin >> cantidad;

        items.push_back(PedidoItem{ *producto, cantidad });

        std::cout << "¿Desea agregar otro producto a la solicitud? (s/n): ";
        std::cin >> opcion;
    } while (opcion == 's' || opcion == 'S');

    int nuevaSolicitudId = fileManager.generarNuevoId("solicitudes"); 
    Solicitud nuevaSolicitud(nuevaSolicitudId, *cliente, items, EstadoSolicitud::PENDIENTE);

    fileManager.guardarSolicitudEnArchivo(nuevaSolicitud);
    solicitudes.push(nuevaSolicitud);

    std::cout << "Solicitud creada y guardada exitosamente." << std::endl;
}

void SolicitudController::eliminarSolicitud(int id) {
    std::queue<Solicitud> auxiliar;

    Solicitud* it = nullptr;

    while (!solicitudes.empty()) {
        Solicitud primera = solicitudes.front();
        solicitudes.pop();

        if (primera.getId() == id) 
            it = &primera;
        else 
            auxiliar.push(primera);
    }

    solicitudes = auxiliar;
    // auto it = std::remove_if(solicitudes.begin(), solicitudes.end(),
    //             [id](const Solicitud& solicitud) { return solicitud.getId() == id; });
    
    if (it != nullptr) {
        // solicitudes.erase(it, solicitudes.end());

        FileManager fileManager;
        fileManager.guardarSolicitudesEnArchivo(solicitudes);
    } else {
        std::cout << "Solicitud con ID " << id << " no encontrada.\n";
    }
}

Solicitud* SolicitudController::obtenerSolicitudPorId(int id) {
    Solicitud* respuesta = nullptr;

    std::queue<Solicitud> auxiliar;

    while (!solicitudes.empty()) {
        Solicitud primera = solicitudes.front();
        auxiliar.push(primera);
        solicitudes.pop();

        if (primera.getId() == id) {
            respuesta = &primera;
        }
    }

    solicitudes = auxiliar;
    
    return respuesta;

    // for (auto& solicitud : solicitudes) {
    //     if (solicitud.getId() == id) {
    //         return &solicitud;
    //     }
    // }
    // return nullptr;
}

void SolicitudController::cambiarEstado(EstadoSolicitud nuevoEstado, int id) {
    Solicitud* solicitud = obtenerSolicitudPorId(id);
    Solicitud solicitudCpy(solicitud->getId(), solicitud->getCliente(), solicitud->getItems(), solicitud->getEstado());

    eliminarSolicitud(id);

    solicitudCpy.setEstado(nuevoEstado);

    FileManager fileManager;
    fileManager.guardarSolicitudEnArchivo(solicitudCpy);
    solicitudes.push(solicitudCpy);
}

std::queue<Solicitud>& SolicitudController::obtenerSolicitudes() {
    return solicitudes;
}
