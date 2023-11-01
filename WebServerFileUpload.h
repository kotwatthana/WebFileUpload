#ifndef WebServerFileUpload_h
#define WebServerFileUpload_h

#include <FS.h>
#include <ESPAsyncWebServer.h>

class WebServerFileUpload {
public:
  WebServerFileUpload(); // Constructor
  void begin(AsyncWebServer &server); // Method to set up the server
private:
  // You can define private member variables or helper functions here.
};

#endif
