/*************************************************************************************************
  ESP32 Web Server
  Ejemplo de creación de Web server 
  Basándose en los ejemplos de: 
  https://lastminuteengineers.com/creating-esp32-web-server-arduino-ide/
  https://electropeak.com/learn
**************************************************************************************************/
//************************************************************************************************
// Librerías
//************************************************************************************************
#include <WiFi.h>
#include <WebServer.h>
//************************************************************************************************
// Variables globales
//************************************************************************************************
// SSID & Password
const char* ssid = "ASUS_68";  // Enter your SSID here
const char* password = "notebook";  //Enter your Password here

WebServer server(80);  // Object of WebServer(HTTP port, 80 is defult)

//Variables
uint8_t dato = 0;
uint8_t espacio1 = 0;
uint8_t espacio2 = 0;
uint8_t espacio3 = 0;
uint8_t espacio4 = 0;
uint8_t cantidad = 0;
//************************************************************************************************
// Configuración
//************************************************************************************************
void setup() {
  Serial.begin(115200);
  Serial.println("Try Connecting to ");
  Serial.println(ssid);

  // Connect to your wi-fi modem
  WiFi.begin(ssid, password);

  // Check wi-fi is connected to wi-fi network
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected successfully");
  Serial.print("Got IP: ");
  Serial.println(WiFi.localIP());  //Show ESP32 IP on serial

  server.on("/", handle_OnConnect); // Directamente desde e.g. 192.168.0.8
  
  server.onNotFound(handle_NotFound);

  server.begin();
  Serial.println("HTTP server started");
  delay(100);
}
//************************************************************************************************
// loop principal
//************************************************************************************************
void loop() {
  server.handleClient();
 if (Serial.available() > 0) {
    dato =Serial.read();
    Serial.println(dato);
    //Para parqueo 1
    if (dato & 0x01){
      espacio1 = 1;
    }else {
      espacio1 = 0;
    }
    //Para parqueo 2
    if (dato & 0x02){
      espacio2 = 1;
    }else {
      espacio2 = 0;
    }
    //Para parqueo 3
    if (dato & 0x04){
      espacio3 = 1;
    }else {
      espacio3 = 0;
    }
    //Para parqueo 4
    if (dato & 0x08){
      espacio4 = 1;
    }else {
      espacio4 = 0;
    }
  }
}
//************************************************************************************************
// Handler de Inicio página
//************************************************************************************************
void handle_OnConnect() {
  Serial.println("GPIO2 Status: Conected");
  cantidad = -(espacio1 + espacio2 + espacio3 + espacio4 ) + 4 ;//Muestra la cantidad de parqueos disponibles
  server.send(200, "text/html", SendHTML2(espacio1, espacio2, espacio3, espacio4, cantidad));
}

//************************************************************************************************
// Procesador de HTML
//************************************************************************************************
String SendHTML2(uint8_t parq_1, uint8_t parq_2, uint8_t parq_3, uint8_t parq_4, uint8_t cantidad) {
  String ptr = "<html>\n";
ptr +="<!doctype html>\n";
ptr +="<html lang=\"en\">\n";
ptr +="  <head>\n";
ptr += "<style>html { font-family: Helvetica; display: inline-block; margin: 50px auto; text-align: center;}\n";
ptr += ".column {float: left ; width: 25%; pading: 10px}\n";
ptr += "row:after {content:""; display: table; clear: both}\n";
ptr += "</style>\n";
ptr +="    <meta charset=\"utf-8\">\n";
ptr +="    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\n";
ptr +="    <link href=\"https://cdn.jsdelivr.net/npm/bootstrap@5.0.1/dist/css/bootstrap.min.css\" rel=\"stylesheet\" integrity=\"sha384-+0n0xVW2eSR5OomGNYDnhzAbDsOXxcvSN1TPprVMTNDbiYZCxYbOOl7+AMvyTG2x\" crossorigin=\"anonymous\">\n";
ptr +="    <title>Proyecto#4</title>\n";
ptr +="  </head>\n";
ptr +="  <body>\n";
ptr +="    <h1>Parqueo-Matic &#128664</h1>    \n";
ptr +="    <h3>Control de registro de parqueos</h3>    \n";
ptr +="    <h1>.</h1>    \n";
ptr +="    <table style=\"text-align:center;\"; class=\"table table-hover\">\n";


if (espacio1 == 1){
  ptr +="    <th scope=\"row\">Parqueo 01</th>\n";
  ptr +="    <td class=\"table table-hover\">Ocupado   &#10060</td>\n";
  ptr +="    </tr>\n";
  ptr +="    <tr>\n";
}else {
  ptr +="    <th scope=\"row\">Parqueo 01</th>\n";
  ptr +="    <td class=\"table table-hover\">Disponible &#9989</td>\n";
  ptr +="    </tr>\n";
  ptr +="    <tr>\n";
}

if (espacio2 == 1){
  ptr +="    <th scope=\"row\">Parqueo 02</th>\n";
  ptr +="    <td class=\"table table-hover\">Ocupado   &#10060</td>\n";
  ptr +="    </tr>\n";
  ptr +="    <tr>\n";
}else {
  ptr +="    <th scope=\"row\">Parqueo 02</th>\n";
  ptr +="    <td class=\"table table-hover\">Disponible &#9989</td>\n";
  ptr +="    </tr>\n";
  ptr +="    <tr>\n";
}
if (espacio3 == 1){
  ptr +="      <th scope=\"row\">Parqueo 03</th>\n";
  ptr +="      <td class=\"table table-hover\">Ocupado   &#10060</td>\n";
  ptr +="    </tr>\n";
  ptr +="    <tr>\n";
}else {
  ptr +="      <th scope=\"row\">Parqueo 03</th>\n";
  ptr +="      <td class=\"table table-hover\">Disponible &#9989</td>\n";
  ptr +="    </tr>\n";
  ptr +="    <tr>\n";
}
if (espacio4 == 1){
  ptr +="      <th scope=\"row\">Parqueo 04</th>\n";
  ptr +="      <td class=\"table table-hover\">Ocupado   &#10060</td>\n";
  ptr +="    </tr>\n";
  ptr +="    <tr>\n";
}else {
  ptr +="      <th scope=\"row\">Parqueo 04</th>\n";
  ptr +="      <td class=\"table table-hover\">Disponible &#9989</td>\n";
  ptr +="    </tr>\n";
  ptr +="    <tr>\n";
}

ptr +="  </tbody>\n";
ptr +="  </tfoot>\n";
ptr +="  \t<tr>\n";
ptr += "<th class=table-active scope=row>Parqueos Disponible</th>\n";
ptr += "<td class=table-info>";
ptr += (int) cantidad;
ptr += "</td>\n";
ptr +="    </tr>\n";
ptr +="  </tfoot>\n";
ptr +="</table>\n";
ptr +="<script>\n";
ptr +="function timedRefresh(timeoutPeriod) {\n";
ptr +="\tsetTimeout(\"location.reload(true);\",timeoutPeriod);}\n";
ptr +="window.onload = timedRefresh(1000);\n";
ptr +="</script>\n";
ptr +="    <script src=\"https://cdn.jsdelivr.net/npm/bootstrap@5.0.1/dist/js/bootstrap.bundle.min.js\" integrity=\"sha384-gtEjrD/SeCtmISkJkNUaaKMoLD0//ElJ19smozuHV6z3Iehds+3Ulb9Bn9Plx0x4\" crossorigin=\"anonymous\"></script>\n";
ptr +="    <script src=\"https://cdn.jsdelivr.net/npm/@popperjs/core@2.9.2/dist/umd/popper.min.js\" integrity=\"sha384-IQsoLXl5PILFhosVNubq5LC7Qb9DXgDA9i+tQ8Zj3iwWAwPtgFTxbJ8NT4GN1R8p\" crossorigin=\"anonymous\"></script>\n";
ptr +="    <script src=\"https://cdn.jsdelivr.net/npm/bootstrap@5.0.1/dist/js/bootstrap.min.js\" integrity=\"sha384-Atwg2Pkwv9vp0ygtn1JAojH0nYbwNJLPhwyoVbhoPwBhjQPR5VtM2+xf0Uwh9KtT\" crossorigin=\"anonymous\"></script>\n";
ptr +="  </body>\n";
ptr +="</html>";

return ptr;
}

//************************************************************************************************
// Handler de not found
//************************************************************************************************
void handle_NotFound() {
  server.send(404, "text/plain", "Not found");
}
