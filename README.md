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


# ¿Como programo cortinas?

Esto se basa en que ya tengo un control programado para la cortina:

*Fuentes:*
- https://www.youtube.com/watch?v=t267sqvygBk (min 2:30)
- https://www.youtube.com/watch?v=i5wTanlfrbE

1. Primero debo enviar el comando de programación al motor. Esto se hace desde el control ya programado situandome en el canal elegido (si el control es multicanal) y presionando el boton trasero (pequeño) por unos segundos hasta que la cortina suba y baje levemente.
2. Envio comando de PROG desde el RS485 con el canal en el cual quiero poner dicha cortina.
3. La cortina debería hacer "click-clack" (subir y bajar levemente)


    
