/**
 *  @version 1.0
 *  @timestamp Jan 13 2020 07:05 PM CET
 *  @abreviaton BLE = Bluetooth Low Energy
 *  @UUID BLE = Universally Unique Identifier
 *  
 */
#ifndef _BALANCE_SHOE_PROJECT
#define _BALANCE_SHOE_PROJECT

// Used for C++ string operation
#include <string>
#include <iostream>

#include <Esp.h>
#include <EEPROM.h>

#include <BLE2902.h>
#include <BLEUtils.h>
#include <BLEDevice.h>
#include <BLEServer.h>

#include "HX711.h"
#include "soc/rtc.h"

#define DEVICE_NAME "BALANCE SHOE"

#define SERVICE_UUID          "3FA5B4BC-4F85-4905-A2AD-3713CF11E5F8"
#define USER_SETTINGS_UUID    "5A16B114-07C9-4FB4-8028-555DA52F0A3E"


#define KG (1000)

#define LED_GRUEN 17               //LED Pin D5
#define LED_ROT 16                //LED Pin D6
#define AKKU_PIN 12 /*A15*/    
#define DOUT_PIN 26
#define SCK_PIN 25
#define BAUD 115200

HX711 scale;

/*
 ********************************************************
 *                      STRUCTURES                      *
 ********************************************************
 */

/**
 * @brief Diese Struktur beinhaltet alle UUIDs für die BLE characteristics
 */
struct UUIDs_t{
    const char* user_weight =             "3845372F-32AC-443F-A397-17C24B97A4D3";
    const char* user_max_loaded_weight =  "A896D9F3-F8E8-4343-98BA-04C1F71F1FBD";
}UUIDs;

/**
 * @brief Diese Strukture beinhaltet alle BLE characteristics
 */
struct charateristics_t{
    BLECharacteristic* user_weight;
    BLECharacteristic* user_max_loaded_weight;
}characteristics;

/**
 * @brief Diese Strukture beinhaltet alle Geräteeinstellungen
 * @todo Richtige Werte einsetzen
 */
struct device_t{
    uint32_t scale_weight = 498;
    uint32_t max_weight = 0.5 * KG;
    uint32_t tolerance = 200 ;

    // Um die übertragung zu vereinfachen wird float und double in int umgewandelt
    uint32_t scale_calibrated = 1996;
    float scale_calibrated_float = 19.96;

    uint32_t lade_status = 100;
    uint32_t old_lade_status = 0;
}device;

/**
 * @brief Diese Strukture beinhaltet alle Nutzereinstellungen
 */
struct user_t{
    uint8_t weight = 0;
    uint8_t max_loaded_weight = 0;
}user;

/**
 * @brief Diese Klasse dient als Schnittstelle zum Client.
 * @details Diese Klasse beinhaltet alle nötigen Methoden damit ein Client mit dem ESP32 kommunizieren kann.
 */
class SettingsCharacteristicCallbacks : public BLECharacteristicCallbacks {
    /**
     * @brief Not used
     */
	void onRead(BLECharacteristic* pCharacteristic){
          if(pCharacteristic == characteristics.user_weight){
              characteristics.user_weight->setValue((uint8_t*)&user.weight, 1);
              characteristics.user_weight->notify();
          }else if(pCharacteristic == characteristics.user_max_loaded_weight){
              characteristics.user_max_loaded_weight->setValue((uint8_t*)&user.max_loaded_weight, 1);
              characteristics.user_max_loaded_weight->notify();
          }
	    }

    /**
     * @brief Diese Methode wird aufgerufen wenn der ESP32 Daten von einem Client empfängt
     * @details Wenn der ESP32 Daten empfängt werden sowohl Nutzer als auch Geräteeinstellungen
     *          aktualisiert. 
     */
	void onWrite(BLECharacteristic* pCharacteristic){
        if(pCharacteristic == characteristics.user_weight){
            user.weight = *(uint8_t*)(pCharacteristic->getData());
          }else if(pCharacteristic == characteristics.user_max_loaded_weight){
            user.max_loaded_weight = *(uint8_t*)(pCharacteristic->getData());
          }
    }
};


/*
 ********************************************************
 *               FUNCTION DECLARATION                   *
 ********************************************************
 */

/**
 * @brief Diese Funktion misst das Gewicht welches auf der Sohle liegt.
 */
float measure();

/**
 * @brief Diese Funktion berechnet den aktuellen Ladestatus des LiPos in Prozent
 */
void updateBatteryState();

/**
 * @brief Diese Funktion schaltet den ESP aus
 */
void powerOff();

/**
 *  @brief Diese Funktion erstellt die Nötigen BLE Characteristics für die Übertragung der Nutzereinstellungen
 */
void createUserCharacteristics(BLEServer* pServer);


void setup(){
    Serial.begin(BAUD);
    pinMode(LED_GRUEN, OUTPUT);
    pinMode(LED_ROT, OUTPUT);
    pinMode(14, INPUT);
    esp_sleep_enable_ext0_wakeup(GPIO_NUM_14, 1);

    // Wägezellen einstellen 
    rtc_clk_cpu_freq_set(RTC_CPU_FREQ_80M);
    
    scale.begin(DOUT_PIN, SCK_PIN);

    scale.set_scale(device.scale_calibrated_float);
    scale.tare();

    // BLE initialisieren
    BLEDevice::init(DEVICE_NAME);  
    BLEServer *pServer = BLEDevice::createServer(); 
    // Verschiedene Characeristics erstellen, das sind die angebotene Dienste vom ESP
    createUserCharacteristics(pServer);
    // Start advertising
    pServer->getAdvertising()->addServiceUUID(SERVICE_UUID);
    pServer->getAdvertising()->start();
}

/*
 ********************************************************
 *              FUNCTION IMPLEMENTATION                 *
 ********************************************************
 */

void loop(){
   
    float weight = measure();
    uint8_t intWeight = (uint8_t)(weight);
    uint8_t uintGramm = (uint8_t)((int)(weight * 100) % 100);
    uint8_t uintBat = (uint8_t)device.lade_status;
    uint8_t data[] = {intWeight, uintGramm, uintBat};
       
    characteristics.user_weight->setValue((uint8_t*)&data, 3);
    characteristics.user_weight->notify();
    
    if(weight > (device.tolerance + user.max_loaded_weight)){
        Serial.println("Weight is too big");
        characteristics.user_weight->setValue((uint8_t*)&data, 3);
        characteristics.user_weight->notify();
    }   

    powerOff();
    updateBatteryState();
    if(device.old_lade_status != device.lade_status){
        
        characteristics.user_weight->setValue((uint8_t*)&data, 3);
        characteristics.user_weight->notify();
        
        device.old_lade_status = device.lade_status;
    }

    Serial.println(weight);
}

float measure(){
    float x = scale.get_units(5);       // speichert das Mittel von 5 Messungen in x
    float y = x / KG;     

    if(y<0){return(0);};
    
    return(y);
}

void updateBatteryState(){
    float akkuValue = 0;                        //Variable um Akkuwert zu speichern
    akkuValue = analogRead(AKKU_PIN);
        
   // float volt = (akkuValue / (4096 / 4.2));// * 2;   // gemessenen Wert am Pin umrechnen in volt
    int volt_i = map(akkuValue, 0, 4096, 0, 210);
    float volt = ((float)volt_i / 100) * 2;
    
    int ladezustand = (volt / 4.2) * 100;       // volt in % umrechnen
    device.lade_status = ladezustand;  
  
    if(volt > 3.5){                             // Bis zu 3.5V bleibt die LED gruen
        digitalWrite(LED_GRUEN, HIGH);
        digitalWrite(LED_ROT, LOW);
    }
    if(volt <=3.5){                             // Ab einer Spannung von 3.5V geht die rote LED an 
        digitalWrite(LED_GRUEN, LOW);
        digitalWrite(LED_ROT, HIGH);
    }

    if(volt >= 4.2){
        while(volt >= 4.2){
            digitalWrite(LED_GRUEN, LOW);
            digitalWrite(LED_ROT, HIGH);  
            delay(300);
            digitalWrite(LED_GRUEN, HIGH);
            digitalWrite(LED_ROT, LOW); 
            delay(300);
            volt_i = map(akkuValue, 0, 4096, 0, 210);
            volt = (float)volt_i / 100 * 2;
        }
    }
    
    if(volt <= 3.3){                            // Bei einer Spannung von 3.3V blinkt die rote LED 50 mal, danach geht der ESP in den Deepsleep
        int i = 0;
        while(i < 25){
            digitalWrite(LED_GRUEN, LOW);
            digitalWrite(LED_ROT, HIGH);
            delay(300);
            digitalWrite(LED_GRUEN, LOW);
            digitalWrite(LED_ROT, LOW);
            delay(300);
            i++;
          
        }
        Serial.println("Going to sleep because of Low Energy");
        esp_deep_sleep_start();                      //ESP geht in Deepsleep
    }
    device.lade_status = ladezustand;   
}

void powerOff(){
    int zustand = digitalRead(14);      //Zustand vom Knopf
    
    if(zustand == 1){
        int i = 0;
        while(i < 3){
            digitalWrite(LED_GRUEN, LOW);
            digitalWrite(LED_ROT, LOW);
            delay(300);
            digitalWrite(LED_GRUEN, HIGH);
            digitalWrite(LED_ROT, HIGH);
            delay(300);
            i++;
        }
  
        delay(3000);
        zustand = 0;
        esp_deep_sleep_start();
    }
}


/*
 ********************************************************
 *                  BLUETOOTH PART                      *
 ********************************************************
 */

void createUserCharacteristics(BLEServer* pServer){
    BLEService *pService = pServer->createService(USER_SETTINGS_UUID);  

    characteristics.user_weight = pService->createCharacteristic(UUIDs.user_weight, BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE | BLECharacteristic::PROPERTY_NOTIFY);
    characteristics.user_weight->addDescriptor(new BLE2902);
    characteristics.user_weight->setValue((uint8_t*)&user.weight, 1);
    characteristics.user_weight->setCallbacks(new SettingsCharacteristicCallbacks());
    pService->addCharacteristic(characteristics.user_weight);
    
    characteristics.user_max_loaded_weight = pService->createCharacteristic(UUIDs.user_max_loaded_weight, BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE | BLECharacteristic::PROPERTY_NOTIFY);
    characteristics.user_max_loaded_weight->addDescriptor(new BLE2902);
    characteristics.user_max_loaded_weight->setValue((uint8_t*)&user.max_loaded_weight, 1);
    characteristics.user_max_loaded_weight->setCallbacks(new SettingsCharacteristicCallbacks());
    pService->addCharacteristic(characteristics.user_max_loaded_weight);
    pService->start(); 
}

#endif //_BALANCE_SHOE_PROJECT
