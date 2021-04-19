#ifndef DEBUG
#define DEBUG

/*ESTE ARCHIVO SÓLO DEBE SER MODIFICADO DESDE SistemaConducciónJoystick
 * Hay enlace en GeneradorTextoSerial, pero es sólo para generar texto
 * realista que corresponda con el texto que genera el sistema real, pero
 * sin conectar sensores ni actuadores.
 *
 */

// Constantes para definición de los actuadores a utilizar
#define FRENO_ACTIVADO 1
#define ACELERADOR_ACTIVADO 1 //Para definir si se usará el actuador de acelerador


// Constantes para Debugueo de funciones
#define DEBUG_JOYSTICK 1
#define DEBUG_POTS 0
#define DEBUG_POTS_ERROR 1

#define DEBUG_TIME 0
#define DEBUG_CONTROL 0

#define DEBUG_ACTUADORES_POS 0
#define DEBUG_ACTUADORES_CONTROL 0
#define DEBUG_EXTENSOR 0


#define DEBUG_VOLANTE 0
#define DEBUG_POS_VOLANTE 0
#define DEBUG_CONTROL_VOLANTE 0

#define DEBUG_CONTROL_VOLANTE_UMBRALES 0

#define DEBUG_ENCODER 0

#define DEBUG_SEGURIDAD 0 //Acerca de la conexión de los dispositivos.

#endif
