#include <iostream>
#include <algorithm>
#include <limits>

#include "AlmacenController.h"
#include "FileManager.h"
#include "SolicitudController.h"
#include "ClienteController.h"

AlmacenController::AlmacenController(SolicitudController* solicitudController, ClienteController* clienteController) {
    FileManager fileManager;

    inventario = fileManager.cargarProductosDesdeArchivo();

    this->solicitudController = solicitudController;
    this->clienteController = clienteController;
}

std::vector<Producto> AlmacenController::obtenerInventario() {
    return inventario;
}

void AlmacenController::agregarIngrediente() {
    FileManager fileManager;

    int id = fileManager.generarNuevoId("ingredientes"); 

    std::cout << "Ingrese el nombre del nuevo ingrediente: ";
    std::string nombre;
    std::cin.ignore();
    std::getline(std::cin, nombre);

    std::cout << "Ingrese la descripción del ingrediente: ";
    std::string descripcion;
    std::getline(std::cin, descripcion);

    Ingrediente nuevoIngrediente(id, nombre, descripcion);

    fileManager.guardarIngredienteEnArchivo(nuevoIngrediente);

    std::cout << "Ingrediente agregado y guardado exitosamente." << std::endl;
}

void AlmacenController::agregarEsmalte() {
    FileManager fileManager;
    int id;
    std::vector<Ingrediente> ingredientes;

    id = fileManager.generarNuevoId("esmaltes");

    std::cout << "Ingrese el color del esmalte: ";
    std::string color;
    std::cin >> color;

    std::vector<Ingrediente> ingredientesDisponibles = fileManager.cargarIngredientesDesdeArchivo();

    if (ingredientesDisponibles.empty()) {
        std::cout << "No hay ingredientes disponibles para seleccionar.\n";
        return;
    }

    char opcion;
    do {
        std::cout << "Ingredientes disponibles:\n";
        for (const auto& ingrediente : ingredientesDisponibles) { 
            std::cout << "ID: " << ingrediente.getId() << " - Nombre: " << ingrediente.getNombre() << "\n";
        }

        int idIngrediente;
        std::cout << "Seleccione el ID del ingrediente: ";
        std::cin >> idIngrediente;

        std::optional<Ingrediente> ingrediente = fileManager.obtenerIngredientePorId(ingredientesDisponibles, idIngrediente);

        if (ingrediente) {
            // Verificar si el ingrediente ya fue agregado
            auto it = std::find_if(ingredientes.begin(), ingredientes.end(), 
                [idIngrediente](const Ingrediente& ing) { return ing.getId() == idIngrediente; });

            if (it == ingredientes.end()) {
                ingredientes.push_back(*ingrediente);
                std::cout << "Ingrediente agregado.\n";
            } else {
                std::cout << "El ingrediente ya ha sido agregado.\n";
            }
        } else {
            std::cout << "Ingrediente no encontrado. Intente nuevamente.\n";
        }

        std::cout << "¿Desea agregar otro ingrediente? (s/n): ";
        std::cin >> opcion;
    } while (opcion == 's' || opcion == 'S');

    // Crear y guardar el nuevo esmalte
    Esmalte nuevoEsmalte(id, color, ingredientes);
    fileManager.guardarEsmalteEnArchivo(nuevoEsmalte);

    std::cout << "Esmalte agregado.\n";
}

void AlmacenController::agregarPasta() {
    FileManager fileManager;
    int id;
    std::string nombre, descripcion;

    id = fileManager.generarNuevoId("pastas");

    std::cout << "Ingrese el nombre de la pasta: ";
    std::cin.ignore();
    std::getline(std::cin, nombre);

    std::cout << "Ingrese la descripcion: ";
    std::getline(std::cin, descripcion);

    Pasta nuevaPasta(id, nombre, descripcion);
    fileManager.guardarPastaEnArchivo(nuevaPasta);

    std::cout << "Pasta agregada.\n";
}

void AlmacenController::crearProducto() {
    FileManager fileManager;

    int id, existencia;
    double precio;
    std::string descripcion;
    Dimensiones dimensiones;
    int idPasta, idEsmalte;

    id = fileManager.generarNuevoId("productos");

    std::cout << "Ingrese dimensiones (largo, ancho, altura, grosor): ";
    std::cin >> dimensiones.largo >> dimensiones.ancho >> dimensiones.altura >> dimensiones.grosor;

    std::optional<Pasta> pasta = std::nullopt;
    std::vector<Pasta> pastas = fileManager.cargarPastasDesdeArchivo();
    while (!pasta) {
        std::cout << "Pastas disponibles:\n";
        for (const auto& pasta : pastas) {
            std::cout << "ID: " << pasta.getId() << " - Nombre: " << pasta.getNombre() << "\n";
        }

        std::cout << "Seleccione el ID de la pasta: ";
        int pastaId;
        std::cin >> pastaId;

        pasta = fileManager.obtenerPastaPorId(pastas, pastaId);
        if (!pasta) {
            std::cout << "Pasta no encontrada. Intente nuevamente." << std::endl;
        }
    }

    std::optional<Esmalte> esmalte = std::nullopt;
    std::vector<Esmalte> esmaltes = fileManager.cargarEsmaltesDesdeArchivo();
    while (!esmalte) {
        std::cout << "Esmaltes disponibles:\n";
        for (const auto& esmalte : esmaltes) {
            std::cout << "ID: " << esmalte.getId() << " - Color: " << esmalte.getColor() << "\n";
        }

        std::cout << "Seleccione el ID del esmalte: ";
        int esmalteId;
        std::cin >> esmalteId;

        esmalte = fileManager.obtenerEsmaltePorId(esmaltes, esmalteId);
        if (!esmalte) {
            std::cout << "Esmalte no encontrado. Intente nuevamente." << std::endl;
        }
    }

    std::cout << "Ingrese el precio: ";
    std::cin >> precio;

    std::cout << "Ingrese la descripcion: ";
    std::cin.ignore();
    std::getline(std::cin, descripcion);

    std::cout << "Ingrese la existencia: ";
    std::cin >> existencia;

    if (pasta && esmalte) {
        Producto producto(id, dimensiones, *pasta, *esmalte, precio, descripcion, existencia);
        inventario.push_back(producto);
        fileManager.guardarProductoEnArchivo(producto);
        std::cout << "Producto creado y agregado al inventario.\n";
    } else {
        std::cout << "Error: Pasta o esmalte no encontrados.\n";
    }
}

void mostrarProductos(std::vector<Producto> productos) {
    std::cout << "Productos disponibles:\n";
    for (const auto& producto : productos) {
        std::cout << "ID: " << producto.getId() 
                  << " - Descripción: " << producto.getDescripcion() 
                  << " - Precio: " << producto.getPrecio() 
                  << " - Existencia: " << producto.getExistencia() 
                  << std::endl;
    }
}

void AlmacenController::agregarExistencia() {
    FileManager fileManager;

    int productoId;
    std::vector<Producto> productos = inventario;
    std::cout << "Productos disponibles:\n";
    std::optional<Producto> producto = std::nullopt;
    while (!producto) {
        mostrarProductos(productos);
        std::cout << "Seleccione el ID del producto: ";
        std::cin >> productoId;

        producto = fileManager.obtenerProductoPorId(productos, productoId);
        if (!producto) {
            std::cout << "Producto no encontrado. Intente nuevamente." << std::endl;
        }
    }

    int cantidad;
    std::cout << "Ingrese la cantidad a agregar: ";
    std::cin >> cantidad;

    producto->setExistencia(producto->getExistencia() + cantidad);
    eliminarProducto(producto->getId());
    inventario.push_back(*producto);
    fileManager.guardarProductoEnArchivo(*producto);
    std::cout << "Existencia actualizada.\n";
}

void AlmacenController::eliminarProducto(int id) {
    auto it = std::remove_if(inventario.begin(), inventario.end(),
            [id](const Producto& producto) { return producto.getId() == id; });
    
    if (it != inventario.end()) {
        inventario.erase(it, inventario.end());

        FileManager fileManager;
        fileManager.guardarProductosEnArchivo(inventario);
    } else {
        std::cout << "Producto con ID " << id << " no encontrada.\n";
    }
}

// Procesar una solicitud para verificar si puede ser cumplida
bool AlmacenController::procesarSolicitud(Solicitud& solicitud) {
    std::ostringstream mensaje;

    // Verificar si hay suficiente inventario para cada item
    for (const auto& item : solicitud.getItems()) {
        if (!haySuficienteInventario(item)) {
            solicitudController->cambiarEstado(EstadoSolicitud::PENDIENTE_ANTERIOR, solicitud.getId());
            mensaje << "La solicitud con ID " << solicitud.getId() 
                << " no pudo ser procesada debido a falta de inventario para el producto con ID " << item.producto.getId() << ".\n";
            std::cout << mensaje.str();
            return false;  // Si falta inventario para algún item, la solicitud no puede ser cumplida
        }
    }

    // Si todos los items tienen suficiente inventario, actualizar inventario
    for (const auto& item : solicitud.getItems()) {
        actualizarInventario(item);
    }

    solicitudController->cambiarEstado(EstadoSolicitud::CUMPLIDA, solicitud.getId());
    bool descuento = solicitud.getCliente().esAsiduo();
    double precio = 0;
    for(auto item : solicitud.getItems()) {
        precio += item.producto.getPrecio() * (descuento ? 0.95 : 1) * item.cantidad;
    }
    clienteController->agregarCompra(solicitud.getCliente().getId());
    mensaje << "La solicitud con ID " << solicitud.getId() << " ha sido procesada exitosamente.\n";
    mensaje << "El cliente " << solicitud.getCliente().getNombre() << " pago un total de " << precio
        << (descuento ? " recibiendo un descuento del 5%." : ".") << "\n";
    std::cout << mensaje.str();
    
    return true;
}

// Procesar todas las solicitudes diarias
void AlmacenController::procesarSolicitudesDiarias() {
    std::queue<Solicitud>& solicitudes = solicitudController->obtenerSolicitudes();
    std::queue<Solicitud> auxiliar;

    std::vector<Solicitud> solicitudesAnteriores;

    std::vector<Solicitud> solicitudesAsiduos;
    std::vector<Solicitud> solicitudesNuevos;

    // Separar las solicitudes de clientes asiduos y nuevos
    // for (auto& solicitud : solicitudes) {
    while (!solicitudes.empty()) {
        Solicitud solicitud = solicitudes.front();
        solicitudes.pop();
        auxiliar.push(solicitud);

        if (solicitud.getEstado() == EstadoSolicitud::PENDIENTE) {
            if (solicitud.getCliente().esAsiduo()) {
                solicitudesAsiduos.push_back(solicitud);
            } else {
                solicitudesNuevos.push_back(solicitud);
            }
        }
        else if (solicitud.getEstado() == EstadoSolicitud::PENDIENTE_ANTERIOR) {
            solicitudesAnteriores.push_back(solicitud);
        }
    }

    solicitudes = auxiliar;

    for (auto& solicitud : solicitudesAnteriores) {
        procesarSolicitud(solicitud);
    }

    std::vector<Solicitud> solicitudesOrdenadas;
    size_t indexAsiduos = 0, indexNuevos = 0;
    int contadorAsiduos = 0;

    // Intercalar solicitudes: 2 de asiduos por 1 de nuevos
    while (indexAsiduos < solicitudesAsiduos.size() || indexNuevos < solicitudesNuevos.size()) {
        if ((contadorAsiduos < 2 && indexAsiduos < solicitudesAsiduos.size()) || indexNuevos == solicitudesNuevos.size()) {
            solicitudesOrdenadas.push_back(solicitudesAsiduos[indexAsiduos++]);
            contadorAsiduos++;
        } else if (indexNuevos < solicitudesNuevos.size()) {
            solicitudesOrdenadas.push_back(solicitudesNuevos[indexNuevos++]);
            contadorAsiduos = 0; // Resetear el contador después de agregar un nuevo
        }
    }

    // Procesar las solicitudes ordenadas
    for (auto& solicitud : solicitudesOrdenadas) {
        procesarSolicitud(solicitud);
    }
}

// Verificar si hay suficiente inventario para un item específico
bool AlmacenController::haySuficienteInventario(const PedidoItem& item) {
    for (const auto& prod : inventario) {
        if (prod.getId() == item.producto.getId()) {
            return prod.getExistencia() >= item.cantidad;
        }
    }
    return false;
}

// Actualizar el inventario después de procesar un item
void AlmacenController::actualizarInventario(const PedidoItem& item) {
    for (auto& producto : inventario) {
        if (producto.getId() == item.producto.getId()) {
            Producto productoCpy(producto.getId(), 
                producto.getDimensiones(), 
                producto.getPasta(), 
                producto.getEsmalte(),
                producto.getPrecio(), 
                producto.getDescripcion(), 
                producto.getExistencia() - item.cantidad);

            eliminarProducto(producto.getId());

            FileManager fileManager;
            fileManager.guardarProductoEnArchivo(productoCpy);
            inventario.push_back(productoCpy);

            break;
        }
    }
}