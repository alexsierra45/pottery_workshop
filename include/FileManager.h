#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <vector>
#include <queue>
#include <string>
#include <optional>
#include </usr/include/jsoncpp/json/json.h>

#include "Producto.h"
#include "Cliente.h"
#include "Solicitud.h"
#include "Pasta.h"
#include "Ingrediente.h"
#include "Esmalte.h"

class FileManager {
    public:
        static void guardarProductosEnArchivo(const std::vector<Producto>& productos);
        static void guardarProductoEnArchivo(const Producto& producto);
        static std::vector<Producto> cargarProductosDesdeArchivo();

        static void guardarClientesEnArchivo(const std::vector<Cliente>& clientes);
        static void guardarClienteEnArchivo(const Cliente& cliente);
        static std::vector<Cliente> cargarClientesDesdeArchivo();

        static void guardarSolicitudesEnArchivo(std::queue<Solicitud>& solicitudes);
        static void guardarSolicitudEnArchivo(const Solicitud& solicitud);
        static std::queue<Solicitud> cargarSolicitudesDesdeArchivo();

        static void guardarPastaEnArchivo(const Pasta& pasta);
        static std::vector<Pasta> cargarPastasDesdeArchivo();

        static void guardarEsmalteEnArchivo(const Esmalte& esmalte);
        static std::vector<Esmalte> cargarEsmaltesDesdeArchivo();

        static void guardarIngredienteEnArchivo(const Ingrediente& ingrediente);
        static std::vector<Ingrediente> cargarIngredientesDesdeArchivo();

        int generarNuevoId(const std::string& entidad);
        int obtenerUltimoId(const std::string& entidad);
        void actualizarUltimoId(const std::string& entidad, int nuevoId);

        static std::optional<Cliente> obtenerClientePorId(const std::vector<Cliente>& clientes, int id);
        static std::optional<Producto> obtenerProductoPorId(const std::vector<Producto>& productos, int id);
        static std::optional<Pasta> obtenerPastaPorId(const std::vector<Pasta>& pastas, int id);
        static std::optional<Ingrediente> obtenerIngredientePorId(const std::vector<Ingrediente>& ingredientes, int id);
        static std::optional<Esmalte> obtenerEsmaltePorId(const std::vector<Esmalte>& esmaltes, int id);

    private:
        const std::string archivoIds = "data/ultimos_ids.json";
        Json::Value leerJsonDesdeArchivo();
        void escribirJsonEnArchivo(const Json::Value& root);
};

#endif // FILE_MANAGER_H
