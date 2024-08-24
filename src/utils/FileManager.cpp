#include "include/FileManager.h"
#include <fstream>
#include <sstream>
#include <iostream>

void FileManager::guardarProductoEnArchivo(const Producto& producto) {
    std::ofstream archivo("data/productos.txt");

    if (!archivo.is_open()) {
        std::cerr << "Error al abrir el archivo para guardar productos." << std::endl;
        return;
    }

    archivo << producto.getId() << "," << producto.getDimensiones().largo << "," << producto.getDimensiones().ancho
            << "," << producto.getDimensiones().altura << "," << producto.getDimensiones().grosor << ","
            << producto.getPasta().getId() << "," << producto.getEsmalte().getId() << "," << producto.getPrecio() << ","
            << producto.getDescripcion() << "," << producto.getExistencia() << std::endl;
    
    archivo.close();
}

std::vector<Producto> FileManager::cargarProductosDesdeArchivo() {
    std::vector<Producto> productos;
    std::ifstream archivo("data/productos.txt");

    if (!archivo.is_open()) {
        std::cerr << "Error al abrir el archivo para cargar productos." << std::endl;
        return productos;
    }

    std::vector<Pasta> pastas = cargarPastasDesdeArchivo();
    std::vector<Esmalte> esmaltes = cargarEsmaltesDesdeArchivo();

    std::string linea;
    while (std::getline(archivo, linea)) {
        std::istringstream ss(linea);
        std::string token;

        int id, pastaId, esmalteId, existencia;
        double largo, ancho, altura, grosor, precio;
        std::string descripcion;

        std::getline(ss, token, ',');
        id = std::stoi(token);

        std::getline(ss, token, ',');
        largo = std::stod(token);

        std::getline(ss, token, ',');
        ancho = std::stod(token);

        std::getline(ss, token, ',');
        altura = std::stod(token);

        std::getline(ss, token, ',');
        grosor = std::stod(token);

        std::getline(ss, token, ',');
        pastaId = std::stoi(token);
        Pasta* pasta = obtenerPastaPorId(pastas, pastaId);

        std::getline(ss, token, ',');
        esmalteId = std::stoi(token);
        Esmalte* esmalte = obtenerEsmaltePorId(esmaltes, esmalteId);

        std::getline(ss, token, ',');
        precio = std::stod(token);

        std::getline(ss, token, ',');
        descripcion = token;

        std::getline(ss, token, ',');
        existencia = std::stoi(token);

        Producto producto(id, {largo, ancho, altura, grosor}, *pasta, *esmalte, precio, descripcion, existencia);
        productos.push_back(producto);
    }

    archivo.close();
    return productos;
}

void FileManager::guardarClienteEnArchivo(const Cliente& cliente) {
    std::ofstream archivo("data/clientes.txt");

    if (!archivo.is_open()) {
        std::cerr << "Error al abrir el archivo para guardar clientes." << std::endl;
        return;
    }

    archivo << cliente.getId() << "," << cliente.getNombre() << "," << cliente.getApellidos() << ","
            << cliente.getDireccion() << "," << cliente.getCantidadCompras() << std::endl;

    archivo.close();
}

std::vector<Cliente> FileManager::cargarClientesDesdeArchivo() {
    std::vector<Cliente> clientes;
    std::ifstream archivo("data/clientes.txt");

    if (!archivo.is_open()) {
        std::cerr << "Error al abrir el archivo para cargar clientes." << std::endl;
        return clientes;
    }

    std::string linea;
    while (std::getline(archivo, linea)) {
        std::istringstream ss(linea);
        std::string token;

        int id, cantidadCompras;
        std::string nombre, apellidos, direccion;

        std::getline(ss, token, ',');
        id = std::stoi(token);

        std::getline(ss, token, ',');
        nombre = token;

        std::getline(ss, token, ',');
        apellidos = token;

        std::getline(ss, token, ',');
        direccion = token;

        std::getline(ss, token, ',');
        cantidadCompras = std::stoi(token);

        Cliente cliente(id, nombre, apellidos, direccion);
        for (int i = 0; i < cantidadCompras; ++i) {
            cliente.incrementarCompras();
        }

        clientes.push_back(cliente);
    }

    archivo.close();
    return clientes;
}

void FileManager::guardarSolicitudEnArchivo(const Solicitud& solicitud) {
    std::ofstream archivo("data/solicitudes.txt");

    if (!archivo.is_open()) {
        std::cerr << "Error al abrir el archivo para guardar solicitudes." << std::endl;
        return;
    }

    archivo << solicitud.getId() << "," << solicitud.getCliente().getId() << ","
            << solicitud.esCumplida() << std::endl;

    for (const auto& item : solicitud.getItems()) {
        archivo << item.producto.getId() << "," << item.cantidad << std::endl;
    }

    archivo.close();
}

std::vector<Solicitud> FileManager::cargarSolicitudesDesdeArchivo() {
    std::vector<Solicitud> solicitudes;
    std::ifstream archivo("data/solicitudes.txt");

    if (!archivo.is_open()) {
        std::cerr << "Error al abrir el archivo para cargar solicitudes." << std::endl;
        return solicitudes;
    }

    std::vector<Cliente> clientes = cargarClientesDesdeArchivo();
    std::vector<Producto> productos = cargarProductosDesdeArchivo();

    std::string linea;
    while (std::getline(archivo, linea)) {
        std::istringstream stream(linea);
        int solicitudId, clienteId;
        stream >> solicitudId >> clienteId;

        Cliente* cliente = obtenerClientePorId(clientes, clienteId);
        if (cliente == nullptr) {
            std::cerr << "Cliente con ID " << clienteId << " no encontrado." << std::endl;
            continue;
        }

        std::vector<PedidoItem> items;
        int productoId, cantidad;
        while (stream >> productoId >> cantidad) {
            Producto* producto = obtenerProductoPorId(productos, productoId);
            if (producto == nullptr) {
                std::cerr << "Producto con ID " << productoId << " no encontrado." << std::endl;
                continue;
            }
            items.push_back(PedidoItem{*producto, cantidad});
        }

        Solicitud solicitud(solicitudId, *cliente, items);
        solicitudes.push_back(solicitud);
    }

    archivo.close();
    return solicitudes;
}

void FileManager::guardarPastaEnArchivo(const Pasta& pasta) {
    std::ofstream archivo("data/pastas.txt");

    if (!archivo.is_open()) {
        std::cerr << "Error al abrir el archivo para guardar pastas." << std::endl;
        return;
    }

    archivo << pasta.getId() << " "
            << pasta.getNombre() << " "
            << pasta.getDescripcion() << std::endl;

    archivo.close();
}

std::vector<Pasta> FileManager::cargarPastasDesdeArchivo() {
    std::vector<Pasta> pastas;
    std::ifstream archivo("data/pastas.txt");

    if (!archivo.is_open()) {
        std::cerr << "Error al abrir el archivo para cargar pastas." << std::endl;
        return pastas;
    }

    std::string linea;
    while (std::getline(archivo, linea)) {
        std::istringstream stream(linea);
        int id;
        std::string nombre, descripcion;

        stream >> id >> nombre >> descripcion;
        Pasta pasta(id, nombre, descripcion);
        pastas.push_back(pasta);
    }

    archivo.close();
}

void FileManager::guardarIngredienteEnArchivo(const Ingrediente& ingrediente) {
    std::ofstream archivo("data/ingredientes.txt");

    if (!archivo.is_open()) {
        std::cerr << "Error al abrir el archivo para guardar ingredientes." << std::endl;
        return;
    }

    archivo << ingrediente.getId() << " "
            << ingrediente.getNombre() << " "
            << ingrediente.getDescripcion() << std::endl;

    archivo.close();
}

std::vector<Ingrediente> FileManager::cargarIngredientesDesdeArchivo() {
    std::vector<Ingrediente> ingredientes;
    std::ifstream archivo("data/ingredientes.txt");

    if (!archivo.is_open()) {
        std::cerr << "Error al abrir el archivo para cargar ingredientes." << std::endl;
        return ingredientes;
    }

    std::string linea;
    while (std::getline(archivo, linea)) {
        std::istringstream stream(linea);
        int id;
        std::string nombre, descripcion;

        stream >> id >> nombre >> descripcion;
        Ingrediente ingrediente(id, nombre, descripcion);
        ingredientes.push_back(ingrediente);
    }

    archivo.close();
}

void FileManager::guardarEsmalteEnArchivo(const Esmalte& esmalte) {
    std::ofstream archivo("data/esmaltes.txt");

    if (!archivo.is_open()) {
        std::cerr << "Error al abrir el archivo para guardar esmaltes." << std::endl;
        return;
    }

    archivo << esmalte.getId() << " "
            << esmalte.getColor() << " ";
    
    for (const Ingrediente& ingrediente : esmalte.getIngredientes()) {
        archivo << ingrediente.getId() << " ";
    }

    archivo << std::endl;

    archivo.close();
}

std::vector<Esmalte> FileManager::cargarEsmaltesDesdeArchivo() {
    std::vector<Esmalte> esmaltes;
    std::ifstream archivo("data/esmaltes.txt");

    if (!archivo.is_open()) {
        std::cerr << "Error al abrir el archivo para cargar esmaltes." << std::endl;
        return esmaltes;
    }

    std::vector<Ingrediente> ingredientes;

    std::string linea;
    while (std::getline(archivo, linea)) {
        std::istringstream stream(linea);
        int id;
        std::string color;
        std::vector<Ingrediente> ingredientes;

        stream >> id >> color;

        int ingredienteId;
        while (stream >> ingredienteId) {
            Ingrediente* ingrediente = obtenerIngredientePorId(ingredientes, ingredienteId);
            if (ingrediente) {
                ingredientes.push_back(*ingrediente);
            }
        }

        Esmalte esmalte(id, color, ingredientes);
        esmaltes.push_back(esmalte);
    }

    archivo.close();
}

Cliente* FileManager::obtenerClientePorId(std::vector<Cliente> clientes, int id) {
    for (Cliente& cliente : clientes) {
        if (cliente.getId() == id) {
            return &cliente;
        }
    }
    return nullptr;
}

Producto* FileManager::obtenerProductoPorId(std::vector<Producto> productos, int id) {
    for (Producto& producto : productos) {
        if (producto.getId() == id) {
            return &producto;
        }
    }
    return nullptr;
}

Pasta* FileManager::obtenerPastaPorId(std::vector<Pasta> pastas, int id) {
    for (Pasta& pasta : pastas) {
        if (pasta.getId() == id) {
            return &pasta;
        }
    }
    return nullptr;
}

Esmalte* FileManager::obtenerEsmaltePorId(std::vector<Esmalte> esmaltes, int id) {
    for (Esmalte& esmalte : esmaltes) {
        if (esmalte.getId() == id) {
            return &esmalte;
        }
    }
    return nullptr;
}

Ingrediente* FileManager::obtenerIngredientePorId(std::vector<Ingrediente> ingredientes, int id) {
    for (Ingrediente& ingrediente : ingredientes) {
        if (ingrediente.getId() == id) {
            return &ingrediente;
        }
    }
    return nullptr;
}