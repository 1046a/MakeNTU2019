const char ssid[] = "MakeNTU2019-B-5G";
const char pass[] = "lazy_tech";

byte wait = 0;
WiFiManager wifiManager;

void wificonnection(){
  WiFi.begin(ssid, pass);
  Serial.print("Connecting to ");
  Serial.println(ssid);

  while(WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(500);
    wait++;
    if (wait >= 20)
      //wifiManager.setAPCallback(configModeCallback);
      //wifiManager.autoConnect("SLAMISAWESOME", "connectme");
      wifiManager.autoConnect("MakeNTU_1046A");
  }
  Serial.println();

  Serial.println("WiFi Connected!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void serverSetup(){
  server.begin();

  server.on("/", []()
  {
    server.send(200, "text/html", prepareHtmlPage());
  });
}

String prepareHtmlPage()
{
  String page =
     String("HTTP/1.1 200 OK\r\n") +
            "Content-Type: text/html\r\n" +
            "Connection: close\r\n" +  // the connection will be closed after completion of the response
            "Refresh: 1\r\n" +  // refresh the page automatically every 5 sec
            "\r\n" +
            "<!DOCTYPE HTML>" +
            "<html>" +
            "<body>" +
            "<h1>hello MakeNTU</h1>"
            "</body>" +
            "</html>" +
            "\r\n";
  return page;
}
