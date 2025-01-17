#include "ServerFunctions.h"

WebServer server(80);


 
// Funcion al recibir petición POST
// 192.168.0.200/cortina?CH=1&ACTION=U
void accionarSobreCortina() 
{
   // mostrar por puerto serie
   Serial.print(server.argName(0));
   Serial.print(": ");
   Serial.println(server.arg(0));

   Serial.print(server.argName(1));
   Serial.print(": ");
   Serial.println(server.arg(1));
   
   // devolver respuesta
   //server.send(200, "text/plain", String("POST ") + server.arg(String("Id")) + " " + server.arg(String("Status")));
      server.sendHeader("Location","/");        // Add a header to respond with a new location for the browser to go to the home page again
      server.send(200);
}

// Funcion al recibir petición POST
// 192.168.0.200/cortina?CH=1
void programarCortina() 
{
   // mostrar por puerto serie
   Serial.print(server.argName(0));
   Serial.print(": ");
   Serial.println(server.arg(0));

   Serial.print(server.argName(1));
   Serial.print(": ");
   Serial.println(server.arg(1));
   
   // devolver respuesta
   //server.send(200, "text/plain", String("POST ") + server.arg(String("Id")) + " " + server.arg(String("Status")));
      server.sendHeader("Location","/");        // Add a header to respond with a new location for the browser to go to the home page again
      server.send(200);
}


// Funcion que se ejecutara en la URI '/'
/*
void handleRoot() 
{
   server.send(200, "text/plain", "Hola mundo!");
}
*/


void handleNotFound() 
{
   server.send(404, "text/plain", "Not found");
}


void InitServer()
{
   // Ruteo para '/'
   //server.on("/", handleRoot);
 
   // Definimos dos routeos
   server.on("/cortina", HTTP_POST, accionarSobreCortina);
   server.on("/programacion", HTTP_POST, programarCortina);
   server.onNotFound(handleNotFound);        // When a client requests an unknown URI (i.e. something other than "/"), call function "handleNotFound"
 
 
   server.begin();
   Serial.println("HTTP server started");
}