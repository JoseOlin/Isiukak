#ifndef DEBUG
#define DEBUG

/*ESTE ARCHIVO SÓLO DEBE SER MODIFICADO DESDE SistemaConducciónJoystick
 * Hay enlace en GeneradorTextoSerial, pero es sólo para generar texto
 * realista que corresponda con el que genera el sistema real, aunque
 * sin conectar sensores ni actuadores.
 *
 */

// Constantes para Debugueo de funciones

#define DEBUG_POTS 0
#define DEBUG_POTS_ERROR 1

#define DEBUG_CONTROL 0

#define DEBUG_ACTUADORES_BLOQUEOFRENO 1

#define DEBUG_COMUNICACION_NANO 0
#define DEBUG_WIRE 0 // Para el i2c


#define DEBUG_POS_VINFO_VOLANTE
#define DEBUG_CONTROL_VOLANTE 0

#define DEBUG_CONTROL_VOLANTE_UMBRALES 0

#define DEBUG_ENCODER 0

#define DEBUG_SEGURIDAD 0 //Acerca de la conexión de los dispositivos.

#endif
