#ifndef DEBUG
#define DEBUG

/*ESTE ARCHIVO SÓLO DEBE SER MODIFICADO DESDE SistemaConducciónJoystick
 * Hay enlace en GeneradorTextoSerial, pero es sólo para generar texto
 * realista que corresponda con el que genera el sistema real, aunque
 * sin conectar sensores ni actuadores.
 *
 */

// Constantes para Debugueo de funciones
#define DEBUG_JOYSTICK 1
#define DEBUG_POTS 0
#define DEBUG_POTS_ERROR 1

#define DEBUG_TIME 1
#define DEBUG_CONTROL 0

#define DEBUG_ACTUADORES_POS 1
#define DEBUG_ACTUADORES_CONTROL 1
#define DEBUG_ACTUADORES_BLOQUEOFRENO 1
#define DEBUG_BOTONES 0

#define DEBUG_COMUNICACION_NANO 0

#define DEBUG_VOLANTE 1
#define DEBUG_POS_VOLANTE 0
#define DEBUG_CONTROL_VOLANTE 0

#define DEBUG_PALANCA 1

#define DEBUG_CONTROL_VOLANTE_UMBRALES 0

#define DEBUG_ENCODER 0

#define DEBUG_SEGURIDAD 0 //Acerca de la conexión de los dispositivos.

#endif
