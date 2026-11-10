#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>

// Definir pines para el lector RFID
constexpr uint8_t RST_PIN = 9;  // Pin de reset
constexpr uint8_t SS_PIN = 10;  // Pin SDA (Chip Select)

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Crear instancia del lector MFRC522
Servo miServo;                     // Crear instancia para el servomotor

const int SERVO_PIN = 3;           // Pin digital donde está conectado el servo

// UID autorizado (tarjeta específica)
// UID: 91 EA A6 66
byte tarjetaAutorizada[] = {0x91, 0xEA, 0xA6, 0x66};

void setup() {
  Serial.begin(9600);   // Inicializar comunicación serial a 9600 baudios
  while (!Serial);      // Esperar a que se abra el puerto serial
  
  SPI.begin();          // Inicializar el bus SPI
  mfrc522.PCD_Init();   // Inicializar el módulo RC522
  
  miServo.attach(SERVO_PIN);  // Asociar el servo al pin 3
  miServo.write(0);           // Posicionar el servo en 0 grados al iniciar
  
  Serial.println("Sistema listo. Acerca una tarjeta...");
  Serial.println();
}

void loop() {
  // Detectar si hay una nueva tarjeta presente
  if (!mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  // Leer la tarjeta detectada
  if (!mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  // Mostrar el UID leído por el Monitor Serial
  Serial.print("UID leido:");
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
  }
  Serial.println();

  // Verificar si la tarjeta leída coincide con la autorizada
  if (compararUID(mfrc522.uid.uidByte, tarjetaAutorizada)) {
    Serial.println("¡Tarjeta autorizada! Abriendo mecanismo...");
    
    miServo.write(0);  // Gira el servo a 180 grados
    delay(1000);         // Espera X segundos en esa posición
    miServo.write(180);    // Regresa el servo a 0 grados
    
    Serial.println("Mecanismo cerrado.");
  } else {
    Serial.println("Acceso denegado.");
  }

  // Detener la lectura actual para permitir leer de nuevo
  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();
}

// Función auxiliar para comparar los bytes del UID
bool compararUID(byte lectura[], byte autorizada[]) {
  for (byte i = 0; i < 4; i++) {
    if (lectura[i] != autorizada[i]) {
      return (false);
    }
  }
  return (true);
}
