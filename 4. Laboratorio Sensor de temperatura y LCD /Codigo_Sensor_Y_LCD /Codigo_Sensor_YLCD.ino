#include <LiquidCrystal.h>
#include <OneWire.h>
#include <DallasTemperature.h>

// Pantalla LCD
// RS, E, D4, D5, D6, D7
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

// Pin donde está conectado el DS18B20
#define ONE_WIRE_BUS A0

// Configura la comunicación con el sensor
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensor(&oneWire);

void setup() {

  // Inicia la pantalla
  lcd.begin(16, 2);

  // Inicia el sensor
  sensor.begin();

  // Limpia la pantalla
  lcd.clear();
}
 
void loop() {

  // Pide al sensor que mida la temperatura
  sensor.requestTemperatures();

  // Obtiene la temperatura en Celsius
  float temperatura = sensor.getTempCByIndex(0);

  // Limpia la pantalla
  lcd.clear();

  // Primera fila
  lcd.setCursor(0, 0);
  lcd.print("Temperatura:");

  // Segunda fila
  lcd.setCursor(0, 1);
  lcd.print(temperatura, 2);
  lcd.print(" C");

  // Espera 1 segundo
  delay(1000);
}
