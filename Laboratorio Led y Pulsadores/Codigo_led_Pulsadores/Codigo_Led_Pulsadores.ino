// Declaración de pines
const int LED_PIN = 13;
const int BUTTON_PIN = 2;

// Variables para el estado del LED
bool ledState = false;

// Variables para el debounce
bool lastButtonState = HIGH;
bool currentButtonState;
bool reading;

// Tiempos para el debounce (en milisegundos)
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 50;  // Aumentado a 50ms para mayor seguridad

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  digitalWrite(LED_PIN, LOW);
}

void loop() {
  // Leer el estado del botón
  reading = digitalRead(BUTTON_PIN);
  
  // Si cambió el estado, reiniciar el contador de tiempo
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }
  
  // Esperar a que pase el tiempo de debounce
  if ((millis() - lastDebounceTime) > debounceDelay) {
    // Si el estado es diferente al actual, cambiar
    if (reading != currentButtonState) {
      currentButtonState = reading;
      
      // Solo actuar cuando el botón se PRESIONA (cambio de HIGH a LOW)
      if (currentButtonState == LOW) {
        // Cambiar estado del LED
        ledState = !ledState;
        digitalWrite(LED_PIN, ledState ? HIGH : LOW);
      }
    }
  }
  
  // Guardar el estado actual para la próxima iteración
  lastButtonState = reading;
}
