#include <WiFi.h>
#include <WebServer.h>

// Wi-Fi credentials
const char* ssid = "RFID";
const char* password = "30678921";

// Pin where the buzzer is connected
#define BUZZER_PIN 14

// Note frequencies (in Hz) for 25 keys (C4 to C6)
const int NOTE_FREQUENCIES[] = {
  261,  // C4
  277,  // C#4
  293,  // D4
  311,  // D#4
  329,  // E4
  349,  // F4
  370,  // F#4
  392,  // G4
  415,  // G#4
  440,  // A4
  466,  // A#4
  493,  // B4
  523,  // C5
  554,  // C#5
  587,  // D5
  622,  // D#5
  659,  // E5
  698,  // F5
  740,  // F#5
  784,  // G5
  831,  // G#5
  880,  // A5
  932,  // A#5
  987,  // B5
  1046  // C6
};

// Create a web server object
WebServer server(80);

// Function to play the tone
void playTone(int frequency, int duration) {
  tone(BUZZER_PIN, frequency); // Start playing the tone
  delay(duration);
  noTone(BUZZER_PIN); // Stop the tone
}

// Function to handle root URL ("/")
void handleRoot() {
  String html = "<html><head>";
  html += "<style>";
  html += "body { display: flex; justify-content: center; align-items: flex-end; height: 100vh; background: #333; margin: 0; overflow: hidden; }";
  html += ".key { width: 50px; height: 250px; margin: 0 1px; background: white; border: 1px solid #000; position: relative; }";
  html += ".key.black { width: 30px; height: 150px; background: black; position: absolute; left: 35px; z-index: 1; margin-left: -15px; }";
  html += ".key:hover { background: #ddd; }";
  html += ".key.black:hover { background: #444; }";

  // Media queries for responsive design
  html += "@media (max-width: 600px) {";
  html += ".key { width: 40px; height: 200px; }";
  html += ".key.black { width: 25px; height: 120px; }";
  html += "}";
  html += "@media (max-width: 400px) {";
  html += ".key { width: 30px; height: 180px; }";
  html += ".key.black { width: 20px; height: 100px; }";
  html += "}";
  
  html += "</style></head><body>";

  // Add buttons for each note (white keys)
  for (int i = 0; i < 25; i++) {
    html += "<div class='key' onclick='playNote(" + String(i) + ")'></div>"; // White key
    // Add black keys where appropriate
    if (i % 7 == 2 || i % 7 == 5 || i % 7 == 9 || i % 7 == 12 || i % 7 == 16) {
      html += "<div class='key black' onclick='playNote(" + String(i) + ")'></div>"; // Black key
    }
  }
  
  html += "<script>";
  html += "function playNote(note) { fetch('/play?note=' + note); }"; // JavaScript function to play note
  html += "</script>";
  
  html += "</body></html>";
  
  server.send(200, "text/html", html);
}

// Function to handle note playback via URL
void handlePlayNote() {
  if (server.hasArg("note")) {
    int noteIndex = server.arg("note").toInt();
    
    if (noteIndex >= 0 && noteIndex < 25) {
      int frequency = NOTE_FREQUENCIES[noteIndex];
      playTone(frequency, 500); // Play the note for 500ms
    }
  }
  server.send(200, "text/plain", "Note played");
}

void setup() {
  // Initialize serial communication
  Serial.begin(115200);
  
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to Wi-Fi...");
  }
  
  Serial.println("Connected to Wi-Fi");
  Serial.println(WiFi.localIP()); // Print the local IP address
  
  // Setup the web server
  server.on("/", handleRoot);
  server.on("/play", handlePlayNote);
  server.begin();
}

void loop() {
  // Handle incoming client requests
  server.handleClient();
}
