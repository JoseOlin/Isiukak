#ifndef CONFIG_HPP
#define CONFIG_HPP


#define JOYSTICK_VIRTUAL 0

// Se activa para probar varias condiciones de operación directamente en el microcontrolador
#define TESTING_NATIVE 0
#define EMBEDDED_TESTING 0

// se toma de los pines analógicos o del arreglo PotenciometrosVirtuales_ValidacionConexion
#define TESTING_MODE 0  // Define si los valores de los pots para la validación de conexión

#define ENTRADAS_VIRTUALES 0

// Constantes para definición de los actuadores a utilizar
#define JOYSTICK_ACTIVADO 1
#define FRENO_ACTIVADO 0
#define ACELERADOR_ACTIVADO 0 //Para definir si se usará el actuador de acelerador
#define VOLANTE_ACTIVADO 0  //Para especificar que se controlará el volante.
#define PALANCA_ACTIVADA 0



// Constantes para despliegue de información.
#define INFO_JOYSTICK 1
#define INFO_BOTONES 1
#define INFO_ACTUADORES_POS 1
#define INFO_ACTUADORES_CONTROL 1
#define INFO_VOLANTE 1
#define INFO_PALANCA 0
#define INFO_TIME 1

#define VALIDAR_LIMITES_POTS 1
#define VALIDAR_LIMITES_ACTUADORES 1
#define VALIDAR_LIMITES_JOYSTICK 1
#define VALIDAR_MOVING 0

enum TipoFeedback{ ResistenciaVariable, EncoderIncremental };
//TipoFeedback ActuadorFreno_TipoFeedback = TipoFeedback::EncoderIncremental;
TipoFeedback ActuadorFreno_TipoFeedback = TipoFeedback::ResistenciaVariable;


#define ENCODER_ACTIVADO 0 //Para tener retroalimentación de posición del volante.
#define PUESTACERO 0


#endif // CONFIG_HPP
