# pla7iotActividad3
PLA7 Actividad 3 Curso iOT

Este repositorio contiene el código necesario para la Actividad 3 del pla7 del Curso IOT UOC2019.

Para comenzar a utilizarlo clonar el repositorio en la carpeta del servidor del grupo.
````
/var/pla7iotActividad3
````

## Servidor TCP ECHO

### Instalando el servidor como servicio de sistema en Ubuntu 18.04LTS

Damos permisos de ejecución al archivo:
````
chmod +x startserver.sh
````

Creamos el archivo:
````
/etc/systemd/system/echoserveriot.service
````

Con el contenido:
````
[Unit]
Description=IOT Course Echo Server
After=syslog.target

[Service]
Type=simple
User=root
Group=root
WorkingDirectory=/var/pla7iotActividad3
ExecStart=/var/pla7iotActividad3/startserver.sh
StandardOutput=syslog
StandardError=syslog

[Install]
WantedBy=multi-user.target
````

Cargamos el nuevo servicio en el gestor del sistema:
````
systemctl enable echoserveriot.service
systemctl daemon-reload
````

Lo arrancamos:
````
systemctl start echoserveriot.service
````

Podemos comprobar su estado con:
````
systemctl status echoserveriot.service
````
