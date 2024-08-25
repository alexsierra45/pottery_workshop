#include "include/SolicitudController.h"
#include <algorithm>

#include "include/FileManager.h"

SolicitudController::SolicitudController() {
    FileManager fileManager;

    solicitudes = fileManager.cargarSolicitudesDesdeArchivo();
}

void SolicitudController::agregarSolicitud(const Solicitud& solicitud) {
    FileManager fileManager;

    fileManager.guardarSolicitudEnArchivo(solicitud);
}

void SolicitudController::eliminarSolicitud(int id) {
    solicitudes.erase(std::remove_if(solicitudes.begin(), solicitudes.end(),
                                     [id](const Solicitud& solicitud) { return solicitud.getId() == id; }),
                      solicitudes.end());
}

Solicitud* SolicitudController::obtenerSolicitudPorId(int id) {
    for (auto& solicitud : solicitudes) {
        if (solicitud.getId() == id) {
            return &solicitud;
        }
    }
    return nullptr;
}

void SolicitudController::cambiarEstado(EstadoSolicitud nuevoEstado, int id) {
    Solicitud* solicitud = obtenerSolicitudPorId(id);

    eliminarSolicitud(id);

    solicitud->setEstado(nuevoEstado);

    FileManager fileManager;
    fileManager.guardarSolicitudEnArchivo(*solicitud);
}

std::vector<Solicitud>& SolicitudController::obtenerSolicitudes() {
    return solicitudes;
}
