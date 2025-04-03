#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 5     // ESP32 SS (SDA) pin for RFID
#define RST_PIN 2    // ESP32 RST pin for RFID

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance

MFRC522::MIFARE_Key key;
byte blockAddress = 2;             // Block to read from
byte blockDataRead[18];            // Buffer to store read data
byte bufferBlockSize = 18;         // Buffer size

void setup() {
  Serial.begin(115200);
  SPI.begin();         // Initialize SPI bus
  mfrc522.PCD_Init();  // Initialize RFID module

  Serial.println("Place RFID Card to read...");

  // Set default key (Factory default FFFFFFFFFFFF)
  for (byte i = 0; i < 6; i++) {
    key.keyByte[i] = 0xFF;
  }
}

void loop() {
  // Check if a new RFID card is present
  if (!mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial()) {
    delay(500);
    return;
  }

  // Authenticate the block using KEY_A
  if (mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, blockAddress, &key, &(mfrc522.uid)) != MFRC522::STATUS_OK) {
    Serial.println("Authentication failed.");
    mfrc522.PICC_HaltA();
    mfrc522.PCD_StopCrypto1();
    return;
  }

  // Read data from the block
  if (mfrc522.MIFARE_Read(blockAddress, blockDataRead, &bufferBlockSize) == MFRC522::STATUS_OK) {
    // Serial.print("Data: ");
    for (byte i = 0; i < 16; i++) {
      if (blockDataRead[i] == 0) break;  // Stop printing at null character
      Serial.print((char)blockDataRead[i]);  // Print stored data as characters
    }
    Serial.println();
  } else {
    Serial.println("Read failed.");
  }

  // Halt communication with the card
  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();

  delay(2000);  // Small delay before next read
}
