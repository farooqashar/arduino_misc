String do_GET(float lat, float lon) {
  WiFiClient client;
  if (client.connect("https://iesc.io/608/S20/", 50)) { 
    client.println("GET /608dev-2/sandbox/afarooq/sandbox/getArea.py?x=" + String(lon) + "&y=" + String(lat) + " HTTP/1.1");
    client.println("Host: https://iesc.io/608/S20/");
    client.print("\r\n");
    unsigned long count = millis();
    while (client.connected()) { 
      String line = client.readStringUntil('\n');
      if (line == "\r") { 
        break;
      }
      if (millis() - count > 6500){
      break;
    }
  }
    count = millis();
    String outputPrepare; 
    while (client.available()) { 
      outputPrepare += (char)client.read();
    }
    client.stop();
    return outputPrepare;
    }else{
      client.stop();
    }
}

void wifi() {
  Wire.begin();
  if (imu.setupIMU(1)) {
    Serial.println("IMU Connected!");
  } else {
    Serial.println("IMU Not Connected :/");
    Serial.println("Restarting");
    ESP.restart(); // restart the ESP (proper way)
  }
  WiFi.begin(network, password); //attempt to connect to wifi
  uint8_t count = 0; //count used for Wifi check times
  Serial.print("Attempting to connect to ");
  Serial.println(network);
  while (WiFi.status() != WL_CONNECTED && count < 12) {
    Serial.print(".");
    count++;
  }
  if (WiFi.isConnected()) { //if we connected then print our IP, Mac, and SSID we're on
    Serial.println("CONNECTED!");
    Serial.println(WiFi.localIP().toString() + " (" + WiFi.macAddress() + ") (" + WiFi.SSID() + ")");
    
  } else { //if we failed to connect just Try again.
    Serial.println("Failed to Connect :/  Going to restart");
    Serial.println(WiFi.status());
    ESP.restart(); // restart the ESP (proper way)
  }
}
