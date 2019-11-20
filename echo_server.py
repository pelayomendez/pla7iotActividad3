# TCP Simple echo server
# iOT PQTM19
# Pelayo Méndez

import socket

# Creamos un socket TCP
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Asignamos al socket una dirección y a un puerto para poder comunicarnos con el
server_address = ('0.0.0.0', 12321)
print("Servidor TCP Echo funcionando en: ", server_address[0] , ":", server_address[1])
sock.bind(server_address)

# Ponemos el punto de conexión en modo servidor y esperamos solo un cliente en la cola:
sock.listen(1)

# Creamos un loop para esperar las conexiones:
try:
    while True:
        # El metódo accept() nos permite esperar a que se realice alguna conexión
        print("Esperando una conexión... ")
        client_socket, client_address = sock.accept()

        while True:
            # Una vez creada la conexión recibimos los datos del cliente:
            data = client_socket.recv(1024)
            stringdata = data.decode('utf-8')
            print("Mensaje recibido: ", stringdata)
            if data:
                # Volvemos a enviar al cliente los datos que nos ha enviado:
                print("Mensaje enviado: ", stringdata)
                client_socket.sendall(stringdata.encode('utf-8'))
            else:
                # Volvemos al estado de espera:
                print("No hay mas datos del cliente. ")
                break

finally:
    # Si se interrumpe el prgrama cerramos la conexión:
    print("Cerrando la conexion. Bye bye.")
    sock.close()

