#include <DHT.h>
#include <LiquidCrystal.h>

// Definir el pin donde conectaste el sensor (A0)
#define DHTPIN A0     
#define DHTTYPE DHT11   // Cambiado a DHT11

// Inicializamos el sensor DHT
DHT dht(DHTPIN, DHTTYPE);

// Inicializamos la pantalla LCD con los pines de tu circuito:
// RS = 7, Enable = 6, D4 = 5, D5 = 4, D6 = 3, D7 = 2
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

void setup() {
  // Inicializar la pantalla LCD (16 columnas, 2 filas)
  lcd.begin(16, 2);
  
  // Iniciar el sensor DHT
  dht.begin();
  
  // Mensaje de bienvenida
  lcd.print("Iniciando DHT11");
  delay(2000);
  lcd.clear();
}
 //J4c0b
void loop() {
  // Esperar 2 segundos entre mediciones
  delay(2000);

  // Leer la humedad
  float h = dht.readHumidity();
  // Leer la temperatura en grados Celsius
  float t = dht.readTemperature();

  // Comprobar si hubo un error en la lectura
  if (isnan(h) || isnan(t)) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Error leyendo");
    lcd.setCursor(0, 1);
    lcd.print("sensor DHT11");
    return;
  }

  // Mostrar los datos en la pantalla LCD
  lcd.clear();
  
  // Fila 0: Temperatura
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(t);
  lcd.print(" C");

  // Fila 1: Humedad
  lcd.setCursor(0, 1);
  lcd.print("Humedad: ");
  lcd.print(h);
  lcd.print(" %");
}
