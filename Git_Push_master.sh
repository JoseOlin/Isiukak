#!/bin/bash
git status

echo -e "\n\nEsos son los archivos que han sido modificados"
echo -e "\n¿Deseas agregarlos a Github (y/n)?"

read -n1 key 

if [[ $key == y ]];
then
	echo -e "\nSe presionó y"
	git add . 
	echo -e "\nEscribe el mensaje asociado al push: "
	read var_mensaje
	echo -e "\nTu mensaje es: "
	echo $var_mensaje
	git commit -m " $var_mensaje "
	git push -u origin master
else
	echo -e "\nSaliendo del script"
	exit 0
fi

#git add .
#git commit -m "Mensaje asociado a la actualización."
#git push -u origin master

#Username for github: JLuisGT
# Pass: Usar el token


