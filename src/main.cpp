#include <iostream>

#include "ClienteController.h"
#include "SolicitudController.h"
#include "FileManager.h"
#include "AlmacenController.h"

void mostrarMenu() {
    std::cout << "===== Taller de Cerámica =====" << std::endl;
    std::cout << "1. Agregar Cliente" << std::endl;
    std::cout << "2. Agregar Solicitud" << std::endl;
    std::cout << "3. Mostrar Clientes" << std::endl;
    std::cout << "4. Mostrar Solicitudes" << std::endl;
    std::cout << "5. Mostrar Productos" << std::endl;
    std::cout << "6. Agregar Producto" << std::endl;
    std::cout << "7. Agregar Esmalte" << std::endl;
    std::cout << "8. Agregar Pasta" << std::endl;
    std::cout << "9. Agregar Ingrediente" << std::endl;
    std::cout << "10. Agregar existencia" << std::endl;
    std::cout << "11. Salir" << std::endl;
    std::cout << "Seleccione una opción: ";
}

int main() {
    ClienteController clienteController;
    SolicitudController solicitudController;
    AlmacenController almacenController;

    int opcion;

    do {
        mostrarMenu();
        std::cin >> opcion;

        switch (opcion) {
            case 1:
                clienteController.agregarCliente();
                break;
            case 2:
                solicitudController.agregarSolicitud();
                break;
            case 3: {
                const auto& clientes = clienteController.obtenerClientes();
                std::cout << "===== Clientes =====" << std::endl;
                for (const auto& cliente : clientes) {
                    std::cout << "ID: " << cliente.getId() << ", Nombre: " << cliente.getNombre() 
                    << " " << cliente.getApellidos() << " " << cliente.getDireccion() << std::endl;
                }
                break;
            }
            case 4: {
                const auto& solicitudes = solicitudController.obtenerSolicitudes();
                std::cout << "===== Solicitudes =====" << std::endl;
                for (const auto& solicitud : solicitudes) {
                    std::cout << "ID: " << solicitud.getId() << ", Cliente: " << solicitud.getCliente().getNombre() << std::endl;
                    std::cout << "Productos:" << std::endl;
                    for (const auto& pedido : solicitud.getItems()) {
                        std::cout << "    - " << pedido.producto.getDescripcion() << " " << pedido.cantidad << std::endl;
                    }
                }
                break;
            }
            case 5: {
                const auto& productos = almacenController.obtenerInventario();
                std::cout << "===== Productos =====" << std::endl;
                for (const auto& producto : productos) {
                    std::cout << "ID: " << producto.getId() << ", Descripción: " << producto.getDescripcion() 
                    << ", Precio: " << producto.getPrecio() << ", Existencia: " << producto.getExistencia() << std::endl;
                }
                break;
            }
            case 6: {
                almacenController.crearProducto();
                break;
            }
            case 7: {
                almacenController.agregarEsmalte();
                break;
            }
            case 8: {
                almacenController.agregarPasta();
                break;
            }
            case 9: {
                almacenController.agregarIngrediente();
                break;
            }
            case 10: {
                almacenController.agregarExistencia();
                break;
            }
            case 11:
                std::cout << "Saliendo del programa..." << std::endl;
                break;
            default: {
                std::cout << "Opción no válida. Intente de nuevo." << std::endl;
                break;
            }
        }

        std::cout << std::endl;
    } while (opcion != 11);

    return 0;
}
