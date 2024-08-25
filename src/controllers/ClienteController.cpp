#include "ClienteController.h"
#include <iostream>

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

    std::cout << "Cliente creado y guardado exitosamente." << std::endl;
}

std::vector<Cliente>& ClienteController::obtenerClientes() {
    return clientes;
}
