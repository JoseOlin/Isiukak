#ifndef CONFIG_HPP
#define CONFIG_HPP

// Constantes para definición de los actuadores a utilizar
#define FRENO_ACTIVADO 1
#define ACELERADOR_ACTIVADO 1 //Para definir si se usará el actuador de acelerador
#define VOLANTE_ACTIVADO 1  //Para especificar que se controlará el volante.

enum TipoFeedback{ResistenciaVariable, EncoderIncremental};
//TipoFeedback ActuadorFreno_TipoFeedback = TipoFeedback::EncoderIncremental;
TipoFeedback ActuadorFreno_TipoFeedback = TipoFeedback::ResistenciaVariable;


#endif // CONFIG_HPP
