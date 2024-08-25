#ifndef SOLICITUD_CONTROLLER_H
#define SOLICITUD_CONTROLLER_H

#include <vector>
#include "Solicitud.h"

class SolicitudController {
    public:
        SolicitudController();

        void agregarSolicitud(const Solicitud& solicitud);
        void eliminarSolicitud(int id);
        Solicitud* obtenerSolicitudPorId(int id);
        std::vector<Solicitud>& obtenerSolicitudes();
        void cambiarEstado(EstadoSolicitud nuevoEstado, int id);

    private:
        std::vector<Solicitud> solicitudes;
};

#endif // SOLICITUD_CONTROLLER_H
