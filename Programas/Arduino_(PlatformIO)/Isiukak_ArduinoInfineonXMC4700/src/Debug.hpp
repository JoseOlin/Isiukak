#ifndef DEBUG
#define DEBUG

/* ESTE ARCHIVO SÓLO DEBE SER MODIFICADO DESDE SistemaConducciónJoystick. */

// Constantes para Debugueo de funciones

#define DEBUG_POTS_VALUES 0 // Show the value of the pot on connection checking
#define DEBUG_POTS_ERROR 0
#define DEBUG_POTS_ERROR_VALUES 1 // Show the value of the pot on connection checking only if it were errors.
#define DEBUG_POTS_ERROR_VALUES_EVERY_PERIOD 0

#define DEBUG_BOOT 0

#define DEBUG_CONTROL 0
#define DEBUG_ACTUATORS_CONTROL 0
#define DEBUG_ACTUATORS_RANGE 0

#define DEBUG_ACTUADORES_BLOQUEOFRENO 0

#define DEBUG_VOLANTE 0
#define DEBUG_CONTROL_VOLANTE 0

#define DEBUG_PAROEMERGENCIA 0

#define DEBUG_COMUNICACION_NANO 0
//#define DEBUG_WIRE 0 // Para el i2c

#define DEBUG_SEGURIDAD 0 //Acerca de la conexión de los dispositivos.

#endif
