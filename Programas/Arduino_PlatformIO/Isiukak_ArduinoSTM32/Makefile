all:
	platformio -c qtcreator run
buildNucleo:
	platformio -c qtcreator run --environment nucleo_f401re
buildXMC:
	platformio -c qtcreator run --environment xmc4700_relax_kit

deploy: 
	platformio run --target upload
deployNucleo:
	platformio run --target upload --environment nucleo_f401re
deployXMC:
	platformio run --target upload --environment xmc4700_relax_kit


# regenerate project files to reflect platformio.ini changes
project-update:
	@echo "This will overwrite project metadata files.  Are you sure? [y/N] " \
	    && read ans && [ $${ans:-'N'} = 'y' ]
	platformio project init --ide qtcreator

# forward any other target (clean, build, etc.) to pio run
%:
	platformio -c qtcreator run --target $*
