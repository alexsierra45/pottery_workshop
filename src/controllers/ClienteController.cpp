#include "include/ClienteController.h"
#include <iostream>

#include "include/FileManager.h"

ClienteController::ClienteController() {
    FileManager fileManager;

    clientes = fileManager.cargarClientesDesdeArchivo();
}

void ClienteController::agregarCliente(const Cliente& cliente) {
    FileManager fileManager;

    fileManager.guardarClienteEnArchivo(cliente);
}

std::vector<Cliente>& ClienteController::obtenerClientes() {
    return clientes;
}
