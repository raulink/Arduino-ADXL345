#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>

// Asigna un ide unio al sensor
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);

void displaySensorDetails(void){
  sensor_t sensor;
  accel.getSensor(&sensor);
  Serial.println(".........................");
  Serial.print("Sensor:            "); Serial.println(sensor.name);
  Serial.print("Driver Ver:        "); Serial.println(sensor.version);
  Serial.print("Unique ID:         "); Serial.println(sensor.sensor_id);
  Serial.print("Max Value:         "); Serial.println(sensor.max_value);
  Serial.print("Min Value:        "); Serial.println(sensor.min_value);
  Serial.print("Resolucion:       "); Serial.println(sensor.resolution);
  Serial.println(".........................");
  delay(500);
}
void displayDataRate(void){
  Serial.print("Data Rate:    ");
  switch (accel.getDataRate()) {
    case ADXL345_DATARATE_3200_HZ:
      Serial.print("3200");
      break;
    case ADXL345_DATARATE_1600_HZ:
      Serial.print("1600");
      break;
    case ADXL345_DATARATE_800_HZ:
      Serial.print("800");
      break;
    case ADXL345_DATARATE_400_HZ:
      Serial.print("400");
      break;
    case ADXL345_DATARATE_200_HZ:
      Serial.print("200");
      break;
    case ADXL345_DATARATE_100_HZ:
      Serial.print("100");
      break;
    case ADXL345_DATARATE_50_HZ:
      Serial.print("50");
      break;
    case ADXL345_DATARATE_25_HZ:
      Serial.print("25");
      break;
    case ADXL345_DATARATE_12_5_HZ:
      Serial.print("12.5");
      break;
    case ADXL345_DATARATE_3_13_HZ:
      Serial.print("3.13");
      break;
    case ADXL345_DATARATE_1_56_HZ:
      Serial.print("1.56");
      break;
    case ADXL345_DATARATE_0_78_HZ:
      Serial.print("0.78");
      break;
    case ADXL345_DATARATE_0_39_HZ:
      Serial.print("0.39");
      break;
    case ADXL345_DATARATE_0_20_HZ:
      Serial.print("0.20");
      break;
    case ADXL345_DATARATE_0_10_HZ:
      Serial.print("0.10");
      break;
    default:
      Serial.print("?????");
      break;
  }
  Serial.println(" Hz");
}

void displayRange(void){
  Serial.print("displayRange      +/-");
  switch (accel.getRange()) {
    case ADXL345_RANGE_16_G:
      Serial.print("16 ");
      break;
    case ADXL345_RANGE_8_G:
      Serial.print("8 ");
      break;
    case ADXL345_RANGE_4_G:
      Serial.print("4 ");
      break;
    case ADXL345_RANGE_2_G:
      Serial.print("2 ");
      break;
    default:
      Serial.println(" ???");
      break;
  }
  Serial.println(" g");
}


void setup() {
  // put your setup code here, to run once:
  #ifndef ESP8266
    while(!Serial);   //Leonardo / Micro / Zero
  #endif
    Serial.begin(115200);
    Serial.println("Test Acelerometro");
    if(!accel.begin())
    {
      Serial.println("No Detectado");
      while(1);
    }
    //Establecer el rango para el proyecto
    accel.setRange(ADXL345_RANGE_2_G);
    //accel.setRange(ADXL345_RANGE_8_G);
    //accel.setRange(ADXL345_RANGE_4_G);
    //accel.setRange(ADXL345_RANGE_2_G);
    displaySensorDetails();
    displayDataRate();
    displayRange();
    Serial.println("");
}
long cont=0;
void loop() {
  // put your main code here, to run repeatedly:
  sensors_event_t event;

  Serial.print("Ini: \t "); Serial.print(millis());
  accel.getEvent(&event);
  Serial.print("\t "); Serial.print(cont++ );
  //MOstrar los resultados de la aceleracion en m/s **2
  Serial.print("\t "); Serial.print(event.acceleration.x);
  Serial.print("\t "); Serial.print(event.acceleration.y);
  Serial.print("\t "); Serial.print(event.acceleration.z);
  //Serial.print(" Temp: "); Serial.print(event.temperature);
  Serial.print("\t End: \t");  Serial.print(millis()),
  Serial.println("\t  m/s**2");
  delay(76);
}
