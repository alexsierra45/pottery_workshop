#include <iostream>
#include <algorithm>
#include <limits>

#include "AlmacenController.h"
#include "FileManager.h"

AlmacenController::AlmacenController() {
    FileManager fileManager;

    inventario = fileManager.cargarProductosDesdeArchivo();
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

        // std::cout << "Producto actualizado correctamente.\n";
    } else {
        std::cout << "Producto con ID " << id << " no encontrada.\n";
    }
}

// Procesar una solicitud para verificar si puede ser cumplida
bool AlmacenController::procesarSolicitud(Solicitud& solicitud) {
    for (const auto& item : solicitud.getItems()) {
        if (!haySuficienteInventario(item)) {
            return false;  // Si falta inventario para algún item, la solicitud no puede ser cumplida
        }
    }

    // Si todos los items tienen suficiente inventario, actualizar inventario
    for (const auto& item : solicitud.getItems()) {
        actualizarInventario(item);
    }

    solicitud.setEstado(EstadoSolicitud::CUMPLIDA);
    return true;
}

// Procesar todas las solicitudes diarias
void AlmacenController::procesarSolicitudesDiarias(std::vector<Solicitud>& solicitudes) {
    for (auto& solicitud : solicitudes) {
        if (solicitud.getEstado() == EstadoSolicitud::PENDIENTE) {
            procesarSolicitud(solicitud);
        }
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
    for (auto& prod : inventario) {
        if (prod.getId() == item.producto.getId()) {
            prod.setExistencia(prod.getExistencia() - item.cantidad);
            break;
        }
    }
}
