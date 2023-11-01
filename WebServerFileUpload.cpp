#include "WebServerFileUpload.h"
#include "webpages.h" // Include your webpages.h if needed

WebServerFileUpload::WebServerFileUpload() {
  // Constructor (if you need to initialize any member variables)
}

void handleRoot(AsyncWebServerRequest *request) {
  request->send_P(200, "text/html", reinterpret_cast<const char*>(FILEUP_HTML));
}

void WebServerFileUpload::begin(AsyncWebServer &server) {
  // Web server setup
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    
    request->send(200, "text/plain", "pls. to ip/upload");
    });
  server.on("/upload", HTTP_GET, handleRoot);
  server.on("/upload", HTTP_POST, [](AsyncWebServerRequest *request) {
    // Handle file upload request
    AsyncWebServerResponse *response = request->beginResponse(200, "text/plain", "File uploaded successfully!");
    request->send(response);
  }, [](AsyncWebServerRequest *request, String filename, size_t index, uint8_t *data, size_t len, bool final) {
    // Handle file upload data
    if (!index) {
      Serial.printf("Start: %s\n", filename.c_str());
      File fsUploadFile = SPIFFS.open(filename, "w");
      if (!fsUploadFile) {
        Serial.println("Opening file for writing failed");
        return;
      }
    }
    Serial.printf("Writing to: %s\n", filename.c_str());
    File fsUploadFile = SPIFFS.open(filename, "a");
    if (fsUploadFile) {
      fsUploadFile.write(data, len);
    }
    if (final) {
      Serial.printf("End: %s, %u B\n", filename.c_str(), index + len);
    }
  });

  server.onNotFound([](AsyncWebServerRequest *request) {
    // Handle not found (404) requests
    request->send(404, "text/plain", "Not Found");
  });
  server.begin();
}
