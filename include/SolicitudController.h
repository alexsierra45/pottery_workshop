#ifndef SOLICITUD_CONTROLLER_H
#define SOLICITUD_CONTROLLER_H

#include <queue>
#include "Solicitud.h"

class SolicitudController {
    public:
        SolicitudController();

        void agregarSolicitud();
        void eliminarSolicitud(int id);
        Solicitud* obtenerSolicitudPorId(int id);
        std::queue<Solicitud>& obtenerSolicitudes();
        void cambiarEstado(EstadoSolicitud nuevoEstado, int id);

    private:
        std::queue<Solicitud> solicitudes;
};

#endif // SOLICITUD_CONTROLLER_H
