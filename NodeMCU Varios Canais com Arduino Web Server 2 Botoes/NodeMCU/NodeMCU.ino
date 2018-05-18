  /* 
  Projeto original de Pedro Minatel.
  Retirado do site: http://pedrominatel.com.br/pt/arduino/web-server-com-esp8266-e-ide-arduino/
  */

  #include <ESP8266WiFi.h>
  
  IPAddress ip(192,168,0,111);
  IPAddress gateway(192,168,0,1);
  IPAddress subnet(255,255,255,0);
  
  WiFiServer server(8085);

  int status = 0 ;
  int status1 = 0 ;
    
  void setup() {

  WiFi.begin("Vitorelo", "setembro1309");
  WiFi.config(ip, gateway, subnet);  

  Serial.begin(9600);
  delay(10);
      
  conectar();
  }

  void conectar() {
  Serial.println();
  Serial.println();
  Serial.print("Connectando a ");
  while (WiFi.status() != WL_CONNECTED) {
  delay(500);
  Serial.print(".");
  Serial.println("");
  Serial.println("Conectado com sucesso na rede.");
  // Start the server
  server.begin();
  Serial.println("IP Obtido: ");
  Serial.print(WiFi.localIP());
  }}

  void loop() {


    char caracter = Serial.read();
    if(caracter == 'J'){
    status = 1;}
    if(caracter == 'j'){
    status = 0;}
    if(caracter == 'K'){
    status1 = 1;}
    if(caracter == 'k'){
    status1 = 0;}
     
  if (WiFi.status() != WL_CONNECTED) {conectar();}
  WiFiClient client = server.available();
  if (!client) { 
    return;}     
  
  String req = client.readStringUntil('\r');
  client.flush();

       if (req.indexOf("D0_on") != -1){
    Serial.println("A");
    status = 1;}
       if (req.indexOf("D0_off") != -1){
    Serial.println("a");
    status = 0;}
       if (req.indexOf("D1_on") != -1){
    Serial.println("B");
    status1 = 1;}
       if (req.indexOf("D1_off") != -1){
    Serial.println("b");
    status1 = 0;}

  String buf = "";

  buf += "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\n";
  buf += "<html lang=\"pt\"><head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1, user-scalable=no\"/>\r\n";
  buf += "<meta http-equiv='refresh' content='2;url=/'>";
  buf += "<link rel='icon' type='image/png' href='https://icon-icons.com/icons2/474/PNG/512/light-bulb_46866.png'/>";
  buf += "<body style=background-color:#000000>";
  buf += "<title>CONTROLE AUTOMA&Ccedil;&Atilde;O</title>";
  buf += "<style>body{text-align:center; font-family:verdana;}</style>";
  buf += "<p style= font-size:28px><b><font color=#0000FF>CONTROLE AUTOMA&Ccedil;&Atilde;O</font></p></b>";
  buf += "<hr align='center' width='100%' size='3' color='#FFFFFF'>"; // Cria uma Linha Horizontal.
  
  buf += "<p style= font-size:16px><b><font color=#FFFFFF>CANAL 01</font></p></b>";
  buf += "<style>.c{text-align: center;} div,input{padding:5px;font-size:1em;} input{width:80%;} body{text-align: center;font-family:verdana;} button{border:0;border-radius:0.3rem;background-color:#FFA500;color:#FFFFF;line-height:2.0rem;font-size:1.2rem;width:49%;} .q{float: right;width: 64px;text-align: right;}</style>";
  buf += "<a href=\"?function=D0_on\"><button><b>LIGA</b></button></a> <a href=\"?function=D0_off\"><button><b>DESLIGA</b></button></a></p>";
  if (status == 1){
  buf += "<p style= font-size:20px><b><font color=#008000>CANAL 01 LIGADO</font></p></b>";} // L&Acirc;MPADA LIGADA
  if (status == 0){
  buf += "<p style= font-size:20px><b><font color=#FF0000>CANAL 01 DESLIGADO</font></p></b>";} // L&Acirc;MPADA DESLIGADA
  buf += "<hr align='center' width='100%' size='3' color='#FFFFFF'>"; // Cria uma Linha Horizontal.
  
  buf += "<p style= font-size:16px><b><font color=#FFFFFF>CANAL 02</font></p></b>";
  buf += "<a href=\"?function=D1_on\"><button><b>LIGA</b></button></a> <a href=\"?function=D1_off\"><button><b>DESLIGA</b></button></a></p>";
  if (status1 == 1){
  buf += "<p style= font-size:20px><b><font color=#008000>CANAL 02 LIGADO</font></p></b>";} // L&Acirc;MPADA LIGADA
  if (status1 == 0){
  buf += "<p style= font-size:20px><b><font color=#FF0000>CANAL 02 DESLIGADO</font></p></b>";} // L&Acirc;MPADA DESLIGADA
  buf += "<hr align='center' width='100%' size='3' color='#FFFFFF'>"; // Cria uma Linha Horizontal.
   
  client.print(buf);
  delay(10);
  client.stop();
  }

