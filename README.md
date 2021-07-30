# Fibaro_RS485_ESP32

## RS485

- Baudrate: 4800
- Startbit: 0
- Data bits: 8 (less significant first)
- Parity: Odd
- Stop bit: 1

## Mensajes

- 100ms between two messages


| Byte Number | Name      | Value       | Descripcion                                                          |
|-------------|-----------|-------------|----------------------------------------------------------------------|
| 1           | MSG       | Ver Tabla   |                                                                      |
| 2           | LEN       | Ver tabla   |                                                                      |
| 3           | Reservado | 0x05 / 0x50 | 0x05 mensaje para RTS Transmitter 0x50 mensaje desde RTS transmitter |
| 4-6         | SRC@      |             | Si el emisor no es Somfy la dir debe ir entre FFFF00 y FFFFFE        |
| 7-9         | DEST@     |             | Ver en la etiqueta del producto. En formato LSBF                     |
| ...         | DATA      |             |                                                                      |
| Byte n-1    | CHECKSUM  |             | Complemento a 1 de la suma del byte 1 al byte n-2                    |
| Byte n      | CHECKSUM  |             |                                                                      |

## Comandos
### Move UP/DOWN

- MSG = CTRL_POSITION = 0x80
- LEN = 0x0D
- DATA Lenght = 2
- DATA Type = 8 bits
- DATA Value = 
    - 0 to 15 (RTS Channel)
    - 1 = UP | 2 = DOWN | 3 = STOP | 4 = Fav Position     


### Send PROG Comand

- MSG = SET_CHANNEL = 0x97
- LEN = 0x0
- DATA Lenght = 1
- DATA Type = 8 bits
- DATA Value = 
    - 0 to 15 (RTS Channel)

# Configuracion del código

Los archivos a modificar son:

1. *NetworkData.h* donde se debe modificar el SSID y clave de la red y la dirección IP (fija) elegida.
2. *Constants.h* donde se debe modificar el ID del Somfy RS485 en "RTS_ID_POS_0"

# ¿Como programo cortinas?

Esto se basa en que ya tengo un control programado para la cortina:

*Fuentes:*
- https://www.youtube.com/watch?v=t267sqvygBk (min 2:30)
- https://www.youtube.com/watch?v=i5wTanlfrbE

1. Primero debo enviar el comando de programación al motor. Esto se hace desde un control remotot ya programado situandome en el canal elegido (si el control es multicanal) y presionando el boton trasero (pequeño) por unos segundos hasta que la cortina suba y baje levemente.
2. Envio comando de PROG desde el RS485 con el canal en el cual quiero poner dicha cortina.
3. La cortina debería hacer "click-clack" (subir y bajar levemente) y dicha cortina quedo programada en el canal elegido.

# HTTP

Los POST a hacer son los siguientes:

- Obtener info de la config del canal. Este comando nos da respuesta por el puerto serie

```
POST [IP_ADDRESS]/channelmode?CH=1 
```

- Enviar comando de PROG

```
POST [IP_ADDRESS]/programacion?CH=1 
```

- Enviar comando de ACCION

```
POST [IP_ADDRESS]/cortina?CH=1&ACTION=U
```

Donde las acciones pueden ser:
- D: DOWN (bajar)
- U: UP (subir)
- S: STOP (parar)
- F: FAVORITE (posicion favorita)

## Home Center

1. Importar el dispositivo virtual adjunto.
2. Cambiarle el icono.
3. Elegir la habitación, la IP que tendrá asignada el ESP32, el puerto (80), ponerle "blinds" en tipo. 
4. Configurar el CH del POST.

Para enviarlo desde el Home Center de Fibaro, se debe enviar el CRLF forzadamente. Por lo que es al request hay que sumarle este HEX:

```
0x0D0x0A0x0D0x0A
```
Y quedaría asi:
```
POST /cortina?CH=1&ACTION=U HTTP/1.10x0D0x0A0x0D0x0A
```


 
