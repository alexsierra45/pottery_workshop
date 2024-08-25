#ifndef CLIENTE_CONTROLLER_H
#define CLIENTE_CONTROLLER_H

#include <vector>
#include "Cliente.h"

class ClienteController {
    public:
        ClienteController();

        void agregarCliente(const Cliente& cliente);
        std::vector<Cliente>& obtenerClientes();

    private:
        std::vector<Cliente> clientes;
};

#endif // CLIENTE_CONTROLLER_H
