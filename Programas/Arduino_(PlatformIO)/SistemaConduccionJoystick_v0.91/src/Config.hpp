#ifndef CONFIG_HPP
#define CONFIG_HPP

// Constantes para definición de los actuadores a utilizar
#define FRENO_ACTIVADO 1
#define ACELERADOR_ACTIVADO 1 //Para definir si se usará el actuador de acelerador
#define VOLANTE_ACTIVADO 1  //Para especificar que se controlará el volante.
#define PALANCA_ACTIVADA 1
#define JOYSTICK_ACTIVADO 1
#define PCF_ACTIVADO 0


#define TESTING_ACTIVADO 0

// Constantes para despliegue de información.
#define INFO_JOYSTICK 1
#define INFO_BOTONES 1
#define INFO_ACTUADORES_POS 1
#define INFO_ACTUADORES_CONTROL 1
#define INFO_VOLANTE 1
#define INFO_PALANCA 1
#define INFO_TIME 1

#define VALIDAR_LIMITES_POTS 0
#define VALIDAR_LIMITES_ACTUADORES 0
#define VALIDAR_LIMITES_JOYSTICK 1
#define VALIDAR_MOVING 0



#define ENCODER_ACTIVADO 0 //Para tener retroalimentación de posición del volante.
#define PUESTACERO 0

enum TipoFeedback{ ResistenciaVariable, EncoderIncremental };
//TipoFeedback ActuadorFreno_TipoFeedback = TipoFeedback::EncoderIncremental;
TipoFeedback ActuadorFreno_TipoFeedback = TipoFeedback::ResistenciaVariable;

uint8_t periodoDeseado = 25; //ms Periodo de funcionamiento del sistema en ms.

#endif // CONFIG_HPP
