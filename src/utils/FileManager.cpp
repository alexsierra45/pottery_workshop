#include "FileManager.h"
#include <fstream>
#include <sstream>
#include <iostream>

void FileManager::guardarProductoEnArchivo(const Producto& producto) {
    std::ofstream archivo("data/productos.txt", std::ios::app);

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

void FileManager::guardarProductosEnArchivo(const std::vector<Producto>& productos) {
    std::ofstream archivo("data/productos.txt", std::ios::out | std::ios::trunc);

    if (!archivo.is_open()) {
        std::cerr << "Error al abrir el archivo para guardar productos." << std::endl;
        return;
    }

    for (Producto producto : productos)
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
        std::optional<Pasta> pasta = obtenerPastaPorId(pastas, pastaId);

        std::getline(ss, token, ',');
        esmalteId = std::stoi(token);
        std::optional<Esmalte> esmalte = obtenerEsmaltePorId(esmaltes, esmalteId);

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
    std::ofstream archivo("data/clientes.txt", std::ios::app);

    if (!archivo.is_open()) {
        std::cerr << "Error al abrir el archivo para guardar clientes." << std::endl;
        return;
    }

    archivo << cliente.getId() << "," << cliente.getNombre() << "," << cliente.getApellidos() << ","
            << cliente.getDireccion() << "," << cliente.getCantidadCompras() << std::endl;

    archivo.close();
}

void FileManager::guardarClientesEnArchivo(const std::vector<Cliente>& clientes) {
    std::ofstream archivo("data/clientes.txt", std::ios::out | std::ios::trunc);

    if (!archivo.is_open()) {
        std::cerr << "Error al abrir el archivo para guardar Clientes." << std::endl;
        return;
    }

    for (Cliente cliente : clientes)
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
    std::ofstream archivo("data/solicitudes.txt", std::ios::app);

    if (!archivo.is_open()) {
        std::cerr << "Error al abrir el archivo para guardar solicitudes." << std::endl;
        return;
    }

    int estadoId;
    if (solicitud.getEstado() == EstadoSolicitud::CUMPLIDA) 
        estadoId = 0;
    else if (solicitud.getEstado() == EstadoSolicitud::PENDIENTE)
        estadoId = 1;
    else 
        estadoId = 2;

    archivo << solicitud.getId() << "," << solicitud.getCliente().getId() << ","
            << estadoId;

    for (const auto& item : solicitud.getItems()) {
        archivo << "," << item.producto.getId() << "," << item.cantidad;
    }

    archivo << std::endl;

    archivo.close();
}

void FileManager::guardarSolicitudesEnArchivo(const std::vector<Solicitud>& solicitudes) {
    std::ofstream archivo("data/solicitudes.txt", std::ios::out | std::ios::trunc);

    if (!archivo.is_open()) {
        std::cerr << "Error al abrir el archivo para guardar solicitudes." << std::endl;
        return;
    }

    for (Solicitud solicitud : solicitudes) {
            int estadoId;
        if (solicitud.getEstado() == EstadoSolicitud::CUMPLIDA) 
            estadoId = 0;
        else if (solicitud.getEstado() == EstadoSolicitud::PENDIENTE)
            estadoId = 1;
        else 
            estadoId = 2;

        archivo << solicitud.getId() << "," << solicitud.getCliente().getId() << ","
                << estadoId;

        for (const auto& item : solicitud.getItems()) {
            archivo << "," << item.producto.getId() << "," << item.cantidad;
        }

        archivo << std::endl;
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
        int solicitudId, clienteId, estadoId;
        char separador;

        // Leer la solicitud principal
        if (!(stream >> solicitudId >> separador >> clienteId >> separador >> estadoId)) {
            std::cerr << "Error al leer la solicitud desde la línea: " << linea << std::endl;
            continue;
        }

        // Buscar el cliente
        std::optional<Cliente> cliente = obtenerClientePorId(clientes, clienteId);
        if (cliente == std::nullopt) {
            std::cerr << "Cliente con ID " << clienteId << " no encontrado." << std::endl;
            continue;
        }

        // Determinar el estado de la solicitud
        EstadoSolicitud estado;
        if (estadoId == 0)
            estado = EstadoSolicitud::CUMPLIDA;
        else if (estadoId == 1)
            estado = EstadoSolicitud::PENDIENTE;
        else
            estado = EstadoSolicitud::PENDIENTE_ANTERIOR;

        std::vector<PedidoItem> items;

        // Leer los items dentro de la misma línea
        int productoId, cantidad;
        while (stream >> separador >> productoId >> separador >> cantidad) {
            std::optional<Producto> producto = obtenerProductoPorId(productos, productoId);
            if (producto == std::nullopt) {
                std::cerr << "Producto con ID " << productoId << " no encontrado." << std::endl;
                continue;
            }
            items.push_back(PedidoItem{*producto, cantidad});
        }

        // Crear la solicitud y agregarla a la lista
        Solicitud solicitud(solicitudId, *cliente, items, estado);
        solicitudes.push_back(solicitud);
    }

    archivo.close();
    return solicitudes;
}

void FileManager::guardarPastaEnArchivo(const Pasta& pasta) {
    std::ofstream archivo("data/pastas.txt", std::ios::app);

    if (!archivo.is_open()) {
        std::cerr << "Error al abrir el archivo para guardar pastas." << std::endl;
        return;
    }

    archivo << pasta.getId() << ","
            << pasta.getNombre() << ","
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
        std::istringstream ss(linea);
        std::string token;

        int id;
        std::string nombre, descripcion;

        std::getline(ss, token, ',');
        id = std::stoi(token);

        std::getline(ss, token, ',');
        nombre = token;

        std::getline(ss, token, ',');
        descripcion = token;

        Pasta pasta(id, nombre, descripcion);
        pastas.push_back(pasta);
    }

    archivo.close();

    return pastas;
}

void FileManager::guardarIngredienteEnArchivo(const Ingrediente& ingrediente) {
    std::ofstream archivo("data/ingredientes.txt", std::ios::app);

    if (!archivo.is_open()) {
        std::cerr << "Error al abrir el archivo para guardar ingredientes." << std::endl;
        return;
    }

    archivo << ingrediente.getId() << ","
            << ingrediente.getNombre() << ","
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
        std::istringstream ss(linea);
        std::string token;

        int id;
        std::string nombre, descripcion;

        std::getline(ss, token, ',');
        id = std::stoi(token);

        std::getline(ss, token, ',');
        nombre = token;

        std::getline(ss, token, ',');
        descripcion = token;

        Ingrediente ingrediente(id, nombre, descripcion);
        ingredientes.push_back(ingrediente);
    }

    archivo.close();

    return ingredientes;
}

void FileManager::guardarEsmalteEnArchivo(const Esmalte& esmalte) {
    std::ofstream archivo("data/esmaltes.txt", std::ios::app);

    if (!archivo.is_open()) {
        std::cerr << "Error al abrir el archivo para guardar esmaltes." << std::endl;
        return;
    }

    archivo << esmalte.getId() << ","
            << esmalte.getColor();

    for (const Ingrediente& ingrediente : esmalte.getIngredientes()) {
        archivo << "," << ingrediente.getId();
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

    std::vector<Ingrediente> ingredientesDisponibles = cargarIngredientesDesdeArchivo();

    std::string linea;
    while (std::getline(archivo, linea)) {
        std::istringstream stream(linea);
        int id;
        std::string color;
        std::vector<Ingrediente> ingredientes;

        // Leer ID
        if (!(stream >> id)) {
            std::cerr << "Error al leer el ID desde la línea: " << linea << std::endl;
            continue;
        }

        // Leer el separador después del ID
        if (stream.peek() == ',') {
            stream.ignore();
        }

        // Leer color
        if (!std::getline(stream, color, ',')) {
            std::cerr << "Error al leer el color desde la línea: " << linea << std::endl;
            continue;
        }

        // Leer IDs de ingredientes
        int ingredienteId;
        while (stream >> ingredienteId) {
            std::optional<Ingrediente> ingrediente = obtenerIngredientePorId(ingredientesDisponibles, ingredienteId);
            if (ingrediente) {
                ingredientes.push_back(*ingrediente);
            } else {
                std::cerr << "Ingrediente con ID " << ingredienteId << " no encontrado." << std::endl;
            }

            // Ignorar la coma después del ID del ingrediente
            if (stream.peek() == ',') {
                stream.ignore();
            }
        }

        Esmalte esmalte(id, color, ingredientes);
        esmaltes.push_back(esmalte);
    }

    archivo.close();
    return esmaltes;
}

std::optional<Cliente> FileManager::obtenerClientePorId(const std::vector<Cliente>& clientes, int id) {
    for (const Cliente& cliente : clientes) {
        if (cliente.getId() == id) {
            return cliente;
        }
    }
    return std::nullopt;
}

std::optional<Producto> FileManager::obtenerProductoPorId(const std::vector<Producto>& productos, int id) {
    for (const Producto& producto : productos) {
        if (producto.getId() == id) {
            return producto;
        }
    }
    return std::nullopt;
}

std::optional<Pasta> FileManager::obtenerPastaPorId(const std::vector<Pasta>& pastas, int id) {
    for (const Pasta& pasta : pastas) {
        if (pasta.getId() == id) {
            return pasta;
        }
    }
    return std::nullopt;
}

int FileManager::generarNuevoId(const std::string& entidad) {

    int ultimoId = FileManager::obtenerUltimoId(entidad);
    FileManager::actualizarUltimoId(entidad, ultimoId + 1);

    return ultimoId;
}

std::optional<Esmalte> FileManager::obtenerEsmaltePorId(const std::vector<Esmalte>& esmaltes, int id) {
    for (const Esmalte& esmalte : esmaltes) {
        if (esmalte.getId() == id) {
            return esmalte;
        }
    }
    return std::nullopt;
}

std::optional<Ingrediente> FileManager::obtenerIngredientePorId(const std::vector<Ingrediente>& ingredientes, int id) {
    for (const Ingrediente& ingrediente : ingredientes) {
        if (ingrediente.getId() == id) {
            return ingrediente;
        }
    }
    return std::nullopt;
}

Json::Value FileManager::leerJsonDesdeArchivo() {
    std::ifstream archivo(archivoIds, std::ifstream::binary);
    Json::Value root;

    if (archivo.is_open()) {
        archivo >> root;
        archivo.close();
    } else {
        std::cerr << "No se pudo abrir el archivo JSON. Creando uno nuevo." << std::endl;
    }

    return root;
}

void FileManager::escribirJsonEnArchivo(const Json::Value& root) {
    std::ofstream archivo(archivoIds, std::ofstream::binary);

    if (archivo.is_open()) {
        archivo << root;
        archivo.close();
    } else {
        std::cerr << "No se pudo abrir el archivo para escribir el JSON." << std::endl;
    }
}

int FileManager::obtenerUltimoId(const std::string& entidad) {
    Json::Value root = leerJsonDesdeArchivo();
    return root.get(entidad, 0).asInt(); 
}

void FileManager::actualizarUltimoId(const std::string& entidad, int nuevoId) {
    Json::Value root = leerJsonDesdeArchivo();
    root[entidad] = nuevoId;
    escribirJsonEnArchivo(root);
}