# pla7iotActividad3
PLA7 Actividad 3 Curso iOT


Servidor ECHO

* Para instalar como servicio:

Damos permisos de ejecución al archivo:

chmod +x startserver.sh

Creamos el archivo:
``
/etc/systemd/system/echoserveriot.service
``
Con el contenido:
``
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
``

Cargamos el script con:

systemctl enable echoserveriot.service
systemctl daemon-reload

Lo arrancamos:

systemctl start echoserveriot.service

Vemos su status:

systemctl status echoserveriot.service
