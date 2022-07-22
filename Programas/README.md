La carpeta **Arduino_(PlatformIO)** incluye el **código para el módulo de control**. Se utiliza **Qt Creator como IDE**, configurándolo para compilar el código con **PlatformIO**.




La carpeta **MonitorSerie_(Qt)** incluye el código para monitorear el sistema en tiempo real; sólo debe conectarse el módulo de control por USB. 

![Imagen de la interfaz del monitor serie](../assets/imgs/interfaz-monitor-serial.png)

Hay dos versiones, de 32 y 64 bits. 


# Instalar udev rules para tarjetas ST.
	curl -fsSL https://raw.githubusercontent.com/platformio/platformio-core/master/scripts/99-platformio-udev.rules | sudo tee /etc/udev/rules.d/99-platformio-udev.rules
	
	sudo cp /media/Ext4/Recursos/Electronica/Tarjetas_Desarrollo/ST/99-platformio-udev.rules /etc/udev/rules.d/99-platformio-udev.rules