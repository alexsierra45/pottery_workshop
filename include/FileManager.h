#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <vector>
#include <string>
#include "Producto.h"
#include "Cliente.h"
#include "Solicitud.h"
#include "Pasta.h"
#include "Ingrediente.h"
#include "Esmalte.h"

class FileManager {
    public:
        static void guardarProductoEnArchivo(const Producto& producto);
        static std::vector<Producto> cargarProductosDesdeArchivo();

        static void guardarClienteEnArchivo(const Cliente& cliente);
        static std::vector<Cliente> cargarClientesDesdeArchivo();

        static void guardarSolicitudEnArchivo(const Solicitud& solicitud);
        static std::vector<Solicitud> cargarSolicitudesDesdeArchivo();

        static void guardarPastaEnArchivo(const Pasta& pasta);
        static std::vector<Pasta> cargarPastasDesdeArchivo();

        static void guardarEsmalteEnArchivo(const Esmalte& esmalte);
        static std::vector<Esmalte> cargarEsmaltesDesdeArchivo();

        static void guardarIngredienteEnArchivo(const Ingrediente& ingrediente);
        static std::vector<Ingrediente> cargarIngredientesDesdeArchivo();

    private:
        static Cliente* obtenerClientePorId(std::vector<Cliente> clientes, int id);
        static Producto* obtenerProductoPorId(std::vector<Producto> productos, int id);
        static Pasta* obtenerPastaPorId(std::vector<Pasta> pastas, int id);
        static Ingrediente* obtenerIngredientePorId(std::vector<Ingrediente> ingredientes, int id);
        static Esmalte* obtenerEsmaltePorId(std::vector<Esmalte> esmaltes, int id);
};

#endif // FILE_MANAGER_H
