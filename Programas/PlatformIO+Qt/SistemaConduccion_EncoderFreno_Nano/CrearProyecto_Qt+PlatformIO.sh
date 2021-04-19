## Para Arduino Nano ATmega328
platformio init --ide qtcreator --board nanoatmega328

##Para Arduino UNO
#platformio init --ide qtcreator --board uno

##Para Arduino Mega
#platformio init --ide qtcreator --board megaatmega2560

## Otras tarjetas
#https://docs.platformio.org/en/latest/boards/index.html

##Una vez creado el proyecto, modificar la configuración del proyecto.
#Build directory: El directorio donde esté platform.ini
#Buils Steps. Borrar todos los items
#Build steps → Custom Process Step.
#    • Command: platformio
#    • Arguments: -f -c qtcreator run
#    • Working directory: %{buildDir}
#
#Clean Steps. Borrar todos los items
#Add clean step → Custom Process step
#    • Command:			platformio
#    • Arguments:			-f -c qtcreator run --target clean
#    • Working directory:		%{buildDir}

#Configuración de Qt para subir el código
#Project → Run → Deploy configuration → Add Deploy Step → Custom Process Step
#    • Command: 			platformio
#    • Arguments:		 	run --target upload
#    • Working directory: 		%{buildDir}
#
#Es probable que tenga que copiarse el archivo de 99-platformio-udev.rules a /etc/udev/rules.d
