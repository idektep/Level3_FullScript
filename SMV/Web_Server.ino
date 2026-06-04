const char *htmlHomePage PROGMEM = R"HTMLHOMEPAGE(
<!DOCTYPE html>
<html>
  <head>
  <meta name="viewport" content="width=device-width, height=device-height, target-densitydpi=device-dpi, initial-scale=1, minimum-scale=1, maximum-scale=1, user-scalable=no">
    <style>
    .arrows { font-size:45px; color:AliceBlue; }
    .circularArrows { font-size:35px; color:Cornsilk; }
    td {
      width: 100px; height: 70px; font-size: 16px;
      background-color:pink; border-radius:35%; box-shadow: 5px 5px #888888;
    }
    td:active { transform: translate(5px,5px); box-shadow: none; }
    .noselect {
      touch-action: manipulation; -webkit-touch-callout: none;
      -webkit-user-select: none; -khtml-user-select: none;
      -moz-user-select: none; -ms-user-select: none; user-select: none;
    }
    </style>
  </head>

  <body class="noselect" align="center" style="background-color:white">
    <h3 style="color: teal;text-align:center;">MRV Web Controller</h3>      
    <div class="sensor">Temperature &#127777;:  <span id="tempValue">50</span></div>
    <div class="sensor">Humidity &#127783;: <span id="humiValue">100</span></div>
    <div class="sensor">Light &#9728;: <span id="ldrValue">100</span> Ultra &#128677;: <span id="UltraValue">100</span></div>
    
    <table id="mainTable" style="width:500;margin:auto;table-layout:fixed" CELLSPACING=8>
      <tr>
        <td ontouchstart='toggleCheckbox("TURN_RIGHT_RM")' ontouchend='toggleCheckbox("H_OFF")'>TR_RBA</span></td>
        <td ontouchstart='toggleCheckbox("EXTEND")' ontouchend='toggleCheckbox("H_OFF")'>EXTEND</span></td>
        <td ontouchstart='toggleCheckbox("UPPER")' ontouchend='toggleCheckbox("H_OFF")'>UPPER</span></td>
      </tr>
      <tr>
        <td ontouchstart='toggleCheckbox("TURN_LEFT_RM")' ontouchend='toggleCheckbox("H_OFF")'>TL_RBA</span></td>
        <td ontouchstart='toggleCheckbox("RESTACK")' ontouchend='toggleCheckbox("H_OFF")'>RESTACK</span></td>  
        <td ontouchstart='toggleCheckbox("LOWER")' ontouchend='toggleCheckbox("H_OFF")'>LOWER</span></td>   
      </tr>
      <tr>
        <td ontouchstart='toggleCheckbox("UPPER_G")' ontouchend='toggleCheckbox("H_OFF")'>UPPER_G</span></td>
        <td style="background-color:white; box-shadow:none;height:10px;width:10px;">RBA Control &#129470;</td>
        <td ontouchstart='toggleCheckbox("GRIP")' ontouchend='toggleCheckbox("H_OFF")'>GRIP</span></td>
      </tr>
      <tr>
        <td ontouchstart='toggleCheckbox("LOWER_G")' ontouchend='toggleCheckbox("H_OFF")'>LOWER_G</span></td>
        <td style="background-color:#95F5E7;"><h5 style="color: DarkMagenta;text-align:center;" ontouchstart='toggleCheckbox("home")' ontouchend='toggleCheckbox("H_OFF")'> HOME POSITION</h5></td>
        <td ontouchstart='toggleCheckbox("UN_GRIP")' ontouchend='toggleCheckbox("H_OFF")'>UN_GRIP</span></td>
      </tr>
      <tr></tr>
      <tr>
      <td ontouchstart='onTouchStartAndEnd("5")' ontouchend='onTouchStartAndEnd("0")'><span class="arrows" >&#11017;</span></td>
      <td ontouchstart='onTouchStartAndEnd("1")' ontouchend='onTouchStartAndEnd("0")'><span class="arrows" >&#8679;</span></td>
      <td ontouchstart='onTouchStartAndEnd("6")' ontouchend='onTouchStartAndEnd("0")'><span class="arrows" >&#11016;</span></td>
      </tr>
      <tr>
        <td ontouchstart='onTouchStartAndEnd("9")' ontouchend='onTouchStartAndEnd("0")'><span class="arrows" >&#8634;</span></td>
        <td ontouchstart='onTouchStartAndEnd("11")' ontouchend='onTouchStartAndEnd("12")'style="background-color:white;box-shadow:none">AGV Control &#128663;</td>
        <td ontouchstart='onTouchStartAndEnd("10")' ontouchend='onTouchStartAndEnd("0")'><span class="arrows" >&#8635;</span></td>
      </tr>
      <tr>
      <td ontouchstart='onTouchStartAndEnd("7")' ontouchend='onTouchStartAndEnd("0")'><span class="arrows" >&#11019;</span></td>
      <td ontouchstart='onTouchStartAndEnd("2")' ontouchend='onTouchStartAndEnd("0")'><span class="arrows" >&#8681;</span></td>
      <td ontouchstart='onTouchStartAndEnd("8")' ontouchend='onTouchStartAndEnd("0")'><span class="arrows" >&#11018;</span></td>
      </tr>    
    </table>
    
   <script>
      var webSocketUrl = "ws:\/\/" + window.location.hostname + "/ws";
      var websocket;
      
      function initWebSocket() {
        websocket = new WebSocket(webSocketUrl);
        websocket.onopen    = function(event){};
        websocket.onclose   = function(event){setTimeout(initWebSocket, 2000);};
        websocket.onmessage = function(event){};
      }

      function onTouchStartAndEnd(value) { websocket.send(value); }
  
     function toggleCheckbox(x) {
       var xhr = new XMLHttpRequest();
       xhr.open("GET", "/" + x, true);
       xhr.send(); 
     }
      function updateHumidity(value) { document.getElementById('humiValue').innerText = value; }
      function updateTemperature(value) { document.getElementById('tempValue').innerText = value; }
      function updateLight(value) { document.getElementById('ldrValue').innerText = value; }
      function updateUltra(value) { document.getElementById('UltraValue').innerText = value; }
      
      setInterval(function () {
        var tempXhr = new XMLHttpRequest();
        tempXhr.onreadystatechange = function () {
          if (tempXhr.readyState == 4 && tempXhr.status == 200) { updateTemperature(parseFloat(tempXhr.responseText)); }
        };
        tempXhr.open("GET", "/temperature", true); tempXhr.send();

        var humiXhr = new XMLHttpRequest();
        humiXhr.onreadystatechange = function () {
          if (humiXhr.readyState == 4 && humiXhr.status == 200) { updateHumidity(parseFloat(humiXhr.responseText)); }
        };
        humiXhr.open("GET", "/humidity", true); humiXhr.send();

        var ldrXhr = new XMLHttpRequest();
        ldrXhr.onreadystatechange = function () {
          if (ldrXhr.readyState == 4 && ldrXhr.status == 200) { updateLight(parseFloat(ldrXhr.responseText)); }
        };
        ldrXhr.open("GET", "/light", true); ldrXhr.send();
        
        var UltraXhr = new XMLHttpRequest();
        UltraXhr.onreadystatechange = function () {
          if (UltraXhr.readyState == 4 && UltraXhr.status == 200) { updateUltra(parseFloat(UltraXhr.responseText)); }
        };
        UltraXhr.open("GET", "/Ultra", true); UltraXhr.send();
        
      }, 500);
    window.onload = initWebSocket;
      document.getElementById("mainTable").addEventListener("touchend", function(event){ event.preventDefault() });
    </script>
  </body>
</html>
)HTMLHOMEPAGE";

void handleRoot(AsyncWebServerRequest *request) {
  request->send_P(200, "text/html", htmlHomePage);
}

void setupWebServer() {
  server.on("/", HTTP_GET, handleRoot);
  server.onNotFound([](AsyncWebServerRequest *request){ request->send(404, "text/plain", "File Not Found"); });

  server.on("/temperature", HTTP_GET, [](AsyncWebServerRequest *request) { request->send(200, "text/plain", String(temp)); });
  server.on("/humidity", HTTP_GET, [](AsyncWebServerRequest *request) { request->send(200, "text/plain", String(humi)); });
  server.on("/light", HTTP_GET, [](AsyncWebServerRequest *request) { request->send(200, "text/plain", String(ldr)); });
  server.on("/Ultra", HTTP_GET, [](AsyncWebServerRequest *request) { request->send(200, "text/plain", String(Ultra)); });

  // ส่งคำสั่งผ่าน ESP-NOW ไปหาบอร์ดแขนกลแทน
  server.on("/TURN_RIGHT_RM", HTTP_GET, [](AsyncWebServerRequest *request) { sendCmdViaESPNow("TURN_RIGHT_RM"); request->send(200, "text/plain", "ok"); });
  server.on("/TURN_LEFT_RM", HTTP_GET, [](AsyncWebServerRequest *request) { sendCmdViaESPNow("TURN_LEFT_RM"); request->send(200, "text/plain", "ok"); });
  server.on("/EXTEND", HTTP_GET, [](AsyncWebServerRequest *request) { sendCmdViaESPNow("EXTEND"); request->send(200, "text/plain", "ok"); });
  server.on("/RESTACK", HTTP_GET, [](AsyncWebServerRequest *request) { sendCmdViaESPNow("RESTACK"); request->send(200, "text/plain", "ok"); });
  server.on("/UPPER", HTTP_GET, [](AsyncWebServerRequest *request) { sendCmdViaESPNow("UPPER"); request->send(200, "text/plain", "ok"); });
  server.on("/LOWER", HTTP_GET, [](AsyncWebServerRequest *request) { sendCmdViaESPNow("LOWER"); request->send(200, "text/plain", "ok"); });
  server.on("/UPPER_G", HTTP_GET, [](AsyncWebServerRequest *request) { sendCmdViaESPNow("UPPER_G"); request->send(200, "text/plain", "ok"); });
  server.on("/LOWER_G", HTTP_GET, [](AsyncWebServerRequest *request) { sendCmdViaESPNow("LOWER_G"); request->send(200, "text/plain", "ok"); });
  server.on("/GRIP", HTTP_GET, [](AsyncWebServerRequest *request) { sendCmdViaESPNow("GRIP"); request->send(200, "text/plain", "ok"); });
  server.on("/UN_GRIP", HTTP_GET, [](AsyncWebServerRequest *request) { sendCmdViaESPNow("UN_GRIP"); request->send(200, "text/plain", "ok"); });
  server.on("/home", HTTP_GET, [](AsyncWebServerRequest *request) { sendCmdViaESPNow("home"); request->send(200, "text/plain", "ok"); });
  server.on("/H_OFF", HTTP_GET, [](AsyncWebServerRequest *request) { sendCmdViaESPNow("H_OFF"); request->send(200, "text/plain", "ok"); });

  ws.onEvent([](AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len) {
    switch (type) {
      case WS_EVT_CONNECT:
        Serial.printf("WebSocket client #%u connected\n", client->id());
        break;
      case WS_EVT_DISCONNECT:
        Serial.printf("WebSocket client #%u disconnected\n", client->id());
        processAGVMovement("0"); // สั่งรถหยุดเมื่อหลุดการเชื่อมต่อ
        break;
      case WS_EVT_DATA:
        AwsFrameInfo *info = (AwsFrameInfo *)arg;
        if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) {
          std::string myData = "";
          myData.assign((char *)data, len);
          processAGVMovement(myData.c_str()); // สั่งรถขยับตามข้อมูล WebSocket
        }
        break;
    }
  });
  server.addHandler(&ws);
}