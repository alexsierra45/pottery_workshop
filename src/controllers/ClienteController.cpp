#include <iostream>
#include <algorithm>

#include "ClienteController.h"
#include "FileManager.h"

ClienteController::ClienteController() {
    FileManager fileManager;

    clientes = fileManager.cargarClientesDesdeArchivo();
}

void ClienteController::agregarCliente() {
    FileManager fileManager;

    std::cout << "Ingrese el nombre del cliente: ";
    std::string nombre;
    std::cin >> nombre;

    std::cout << "Ingrese los apellidos del cliente: ";
    std::string apellidos;
    std::cin.ignore(); 
    std::getline(std::cin, apellidos);

    std::cout << "Ingrese la dirección del cliente: ";
    std::string direccion;
    std::cin.ignore(); 
    std::getline(std::cin, direccion);

    int nuevoClienteId = fileManager.generarNuevoId("clientes");  

    Cliente nuevoCliente(nuevoClienteId, nombre, apellidos, direccion);

    fileManager.guardarClienteEnArchivo(nuevoCliente);
    clientes.push_back(nuevoCliente);

    std::cout << "Cliente creado y guardado exitosamente." << std::endl;
}

std::vector<Cliente>& ClienteController::obtenerClientes() {
    return clientes;
}

Cliente* ClienteController::obtenerClientePorId(int id) {
    for (auto& cliente : clientes) {
        if (cliente.getId() == id) {
            return &cliente;
        }
    }
    return nullptr;
}

void ClienteController::eliminarCliente(int id) {
    auto it = std::remove_if(clientes.begin(), clientes.end(),
                [id](const Cliente& cliente) { return cliente.getId() == id; });
    
    if (it != clientes.end()) {
        clientes.erase(it, clientes.end());

        FileManager fileManager;
        fileManager.guardarClientesEnArchivo(clientes);
    } else {
        std::cout << "Solicitud con ID " << id << " no encontrada.\n";
    }
}

void ClienteController::agregarCompra(int id) {
    Cliente* cliente = obtenerClientePorId(id);
    std::cout << cliente->getCantidadCompras() << std::endl;
    Cliente clienteCpy(cliente->getId(), cliente->getNombre(), cliente->getApellidos(), cliente->getDireccion());
    for (int i = 0; i < cliente->getCantidadCompras(); ++i) {
            clienteCpy.incrementarCompras();
    }

    eliminarCliente(id);

    clienteCpy.incrementarCompras();

    FileManager fileManager;
    fileManager.guardarClienteEnArchivo(clienteCpy);
    clientes.push_back(clienteCpy);
}