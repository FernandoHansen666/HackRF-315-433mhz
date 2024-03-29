#include <ELECHOUSE_CC1101_SRC_DRV.h>
#include <RCSwitch.h>
#include <U8g2lib.h>

#define RX_PIN 4         // Pino de recepção
#define TX_PIN 2         // Pino de transmissão
#define BUTTON_PIN 14    // Pino do botão
#define BUTTON_PIN_DIR 27    // Pino do botão
#define BUTTON_PIN_ESQ 12    // Pino do botão
#define BUTTON_PIN_UP 26    // Pino do botão
#define FREQUENCY_SWITCH_PIN 13 // Pino do interruptor para mudar a frequência
#define SCREEN_WIDTH 128 // Largura da tela OLED
#define SCREEN_HEIGHT 64 // Altura da tela OLED

U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

#define scary_width 128
#define scary_height 64
unsigned const char scary_bits[] = {
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x3F, 0xFF, 0xFF, 0xFF, 0xFF, 
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x8F, 
  0xE0, 0xFF, 0xFF, 0xFF, 0xFF, 0x3F, 0xEF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
  0xFF, 0xFF, 0xFF, 0x03, 0xE0, 0xFF, 0xFF, 0xFF, 0xFF, 0x1F, 0xE0, 0xFF, 
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0xC0, 0x07, 0x00, 0xFE, 
  0xFF, 0x0F, 0xE0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x03, 
  0x00, 0x03, 0x00, 0xFF, 0xFF, 0x07, 0xE0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
  0xFF, 0xFF, 0xFF, 0x03, 0x00, 0x06, 0x00, 0xFF, 0xFF, 0x03, 0xE0, 0xFF, 
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x87, 0x00, 0x06, 0x00, 0xFF, 
  0xFF, 0x03, 0xE0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x87, 
  0x05, 0x06, 0x10, 0xFF, 0xFF, 0x01, 0xE1, 0xFF, 0xFB, 0xFF, 0xFF, 0xFF, 
  0xCF, 0x9F, 0xFF, 0x87, 0x0D, 0x06, 0xBE, 0xFF, 0xFF, 0x81, 0xE3, 0xDF, 
  0xF9, 0xFF, 0x80, 0xFB, 0xE3, 0xC7, 0xFF, 0x87, 0x0D, 0x06, 0xBE, 0xFF, 
  0xFF, 0xC1, 0xE7, 0x07, 0xE8, 0xF3, 0x80, 0xF1, 0xE0, 0xE1, 0xFF, 0x87, 
  0x0F, 0x06, 0xFF, 0xFF, 0xFF, 0xC0, 0xFF, 0x03, 0xC8, 0xE0, 0x03, 0x60, 
  0x60, 0xE0, 0xFF, 0x83, 0x0F, 0x06, 0xFF, 0xFF, 0xFF, 0xC1, 0xFF, 0x00, 
  0x0C, 0x80, 0x03, 0xC0, 0xE0, 0xE0, 0xFF, 0x83, 0x0F, 0x07, 0xFF, 0xFF, 
  0xFF, 0x01, 0xFE, 0x00, 0x0C, 0x00, 0x03, 0xC0, 0xE0, 0xE1, 0xFF, 0x87, 
  0x07, 0x07, 0xF7, 0xFF, 0xFF, 0x01, 0xFC, 0x20, 0x0C, 0x00, 0x83, 0xC0, 
  0xE0, 0xE1, 0xFF, 0x83, 0x03, 0x07, 0xF3, 0xFF, 0xFF, 0x03, 0xF8, 0x30, 
  0x0C, 0x06, 0x83, 0xC1, 0xE0, 0xC1, 0xFF, 0x83, 0x00, 0x07, 0xF3, 0xFF, 
  0xFF, 0x03, 0x70, 0xB0, 0x0C, 0x07, 0x83, 0xC1, 0xE0, 0xC1, 0xFF, 0x87, 
  0x80, 0x07, 0xF0, 0xFF, 0xFF, 0x03, 0x60, 0xF0, 0x8C, 0x03, 0x83, 0xC1, 
  0xE0, 0xE1, 0xFF, 0x07, 0xC0, 0x07, 0xF0, 0xFF, 0xFF, 0xEF, 0x60, 0xF8, 
  0xE6, 0x00, 0x83, 0xE1, 0xE0, 0xE1, 0xFF, 0x07, 0xC0, 0x07, 0xF0, 0xFF, 
  0xFF, 0xEF, 0x61, 0xF8, 0x3E, 0x00, 0x83, 0xE3, 0xE0, 0xE1, 0xFF, 0x03, 
  0x00, 0x07, 0xF0, 0xFF, 0xFF, 0xFF, 0x21, 0xF8, 0x1E, 0x00, 0x83, 0xE3, 
  0xE1, 0xE1, 0xFF, 0x03, 0x00, 0x07, 0xF3, 0xFF, 0xFF, 0xFF, 0x01, 0xF8, 
  0x0F, 0x0C, 0x83, 0xFB, 0xE0, 0xE1, 0xFF, 0x83, 0x03, 0x07, 0xF3, 0xFF, 
  0xFF, 0xFF, 0x01, 0xF8, 0x0F, 0x0E, 0x83, 0xFF, 0xF0, 0xE1, 0xFF, 0x83, 
  0x07, 0x0F, 0xF7, 0xFF, 0xFF, 0xF7, 0x01, 0xF8, 0x05, 0x0F, 0x83, 0xFB, 
  0xE0, 0xE1, 0xFF, 0x83, 0x07, 0x0F, 0xFF, 0xFF, 0xFF, 0x63, 0x00, 0xF8, 
  0x85, 0x0F, 0xC3, 0xFF, 0x60, 0xE0, 0xFF, 0x83, 0x07, 0x0F, 0xFF, 0xFF, 
  0xFF, 0x43, 0x60, 0xF0, 0x84, 0x0F, 0xC3, 0xFF, 0x00, 0xE0, 0xFF, 0x07, 
  0x07, 0x0F, 0xFF, 0xFF, 0xFF, 0x43, 0x60, 0xF0, 0x0C, 0x0B, 0xC3, 0xFF, 
  0x00, 0xE0, 0xFF, 0x03, 0x87, 0x0F, 0xFF, 0xFF, 0xFF, 0x03, 0xF0, 0x00, 
  0x0C, 0x03, 0xC3, 0xFF, 0x03, 0xE0, 0xFF, 0x03, 0x87, 0x0F, 0xFF, 0xFF, 
  0xFF, 0x03, 0xF0, 0x00, 0x0C, 0x00, 0xE3, 0xFF, 0x0F, 0xE0, 0xFF, 0x03, 
  0x87, 0x8F, 0xFF, 0xFF, 0xFF, 0x03, 0xF0, 0x01, 0x0C, 0x00, 0xE2, 0xFF, 
  0x0E, 0xE0, 0xFF, 0x03, 0x87, 0x8F, 0xFF, 0xFF, 0xFF, 0x03, 0xF4, 0x07, 
  0x1C, 0x00, 0xEA, 0xFF, 0xDE, 0xE0, 0xFF, 0x01, 0x87, 0x0F, 0xFF, 0xFF, 
  0xFF, 0x0F, 0xF6, 0x0F, 0x1C, 0x2E, 0xF8, 0xFF, 0xDC, 0xE0, 0xFF, 0x00, 
  0x86, 0x8F, 0xFF, 0xFF, 0xFF, 0x1F, 0xFF, 0x6F, 0xBC, 0xAF, 0xFB, 0xFF, 
  0xFC, 0xE0, 0xFF, 0xFF, 0xC7, 0x8F, 0xFF, 0xFF, 0xFF, 0x9F, 0xFF, 0x7F, 
  0xBC, 0xFF, 0xFB, 0xFF, 0x78, 0xF0, 0xFF, 0xFF, 0xC7, 0xDF, 0xFF, 0xFF, 
  0xFF, 0xDF, 0xFF, 0xFF, 0xFC, 0xFF, 0xFF, 0xFF, 0x30, 0xF8, 0xFF, 0xFF, 
  0xCF, 0xDF, 0xFF, 0xFF, 0xFF, 0xDF, 0xFF, 0xFF, 0xFE, 0xFF, 0xFF, 0xFF, 
  0x00, 0xFC, 0xFF, 0xFF, 0xEF, 0xDF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
  0xFE, 0xFF, 0xFF, 0xFF, 0x00, 0xFC, 0xFF, 0xFF, 0xEF, 0xFF, 0xFF, 0xFF, 
  0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xFF, 0xFF, 0xFF, 0x00, 0xFD, 0xFF, 0xFF, 
  0xEF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
  0x04, 0xFF, 0xFF, 0xFF, 0xEF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
  0xFF, 0xFF, 0xFF, 0xFF, 0x0E, 0xFF, 0xFF, 0xFF, 0xEF, 0xFF, 0xFF, 0xFF, 
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xBE, 0xFF, 0xFF, 0xFF, 
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
  0xBF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFE, 
  0x7F, 0xFE, 0xFF, 0xFF, 0xFD, 0xFF, 0xFF, 0xFD, 0xFF, 0xFF, 0xFF, 0xFF, 
  0xFF, 0xFF, 0xFF, 0xFC, 0x7F, 0xFF, 0xFF, 0xFF, 0xFC, 0xFF, 0xFF, 0xFD, 
  0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFD, 0x7F, 0xFF, 0xFF, 0x87, 
  0xFC, 0xFF, 0xFF, 0xFC, 0x7F, 0x3F, 0xF8, 0x87, 0xFF, 0xFF, 0xFF, 0xFD, 
  0x7F, 0xFF, 0xFF, 0xCF, 0x04, 0x04, 0x80, 0x0F, 0x60, 0xDF, 0xF1, 0x69, 
  0xFF, 0xFF, 0xFF, 0xFD, 0x7F, 0xFF, 0xFF, 0xCF, 0x64, 0x26, 0xF9, 0x65, 
  0x32, 0xFF, 0xF3, 0x59, 0xFE, 0xFF, 0xFF, 0xFD, 0x7F, 0xFE, 0xFF, 0xCF, 
  0x64, 0x26, 0x01, 0x64, 0x32, 0x1F, 0xF2, 0x53, 0xFE, 0xFF, 0xFF, 0xFD, 
  0x7F, 0xFF, 0xFF, 0xCF, 0x64, 0xA7, 0xBD, 0x64, 0x12, 0x9F, 0xF9, 0x53, 
  0xFE, 0xFF, 0xFF, 0xFD, 0x7F, 0xFF, 0xFF, 0xCF, 0xA4, 0xA7, 0x9F, 0x64, 
  0x12, 0x9F, 0xFF, 0x53, 0xFE, 0xFF, 0xFF, 0xFD, 0x7F, 0xFF, 0xFF, 0xCF, 
  0xC4, 0xE6, 0x9B, 0x64, 0x22, 0x9F, 0xF6, 0x53, 0xFE, 0xFF, 0xFF, 0xFD, 
  0x7F, 0xFE, 0xFF, 0xC7, 0x64, 0xE6, 0x99, 0x64, 0x22, 0x9F, 0xF2, 0x53, 
  0xFE, 0xFF, 0xFF, 0xFD, 0x7F, 0xFF, 0xFF, 0x8F, 0x66, 0xE6, 0xD9, 0x64, 
  0x32, 0x9F, 0xF2, 0x71, 0xFE, 0xFF, 0xFF, 0xFD, 0x7F, 0xFF, 0xFF, 0x1F, 
  0x02, 0xE3, 0x00, 0x00, 0x13, 0x9F, 0x32, 0x63, 0xFE, 0xFF, 0xFF, 0xFD, 
  0x7F, 0xFF, 0xFF, 0x1F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFB, 0x9F, 0x33, 0x87, 
  0xFF, 0xFF, 0xFF, 0xFD, 0x7F, 0xFF, 0xFF, 0xBF, 0xFF, 0xFF, 0xFF, 0xFF, 
  0xFB, 0x0F, 0xA0, 0xDF, 0xFF, 0xFF, 0xFF, 0xFD, 0x7F, 0xFC, 0xFF, 0xFB, 
  0xFF, 0xFF, 0xFF, 0xFF, 0xFB, 0xFF, 0xFF, 0xFB, 0x7F, 0xEF, 0xF7, 0xFC, 
  0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
  0xFF, 0xFF, 0xFF, 0xFF, };


RCSwitch mySwitch = RCSwitch();

unsigned long receivedValue = 0;
int receivedBitLength = 0;
int receivedProtocol = 0;
const int rssi_threshold = -75;

static const uint32_t subghz_frequency_list[] = {
    300000000, 303875000, 304250000, 310000000, 315000000, 318000000,
    390000000, 418000000, 433075000, 433420000, 433920000, 434420000, 434775000, 438900000,
    868350000, 915000000, 925000000
};

#define WAVEFORM_SAMPLES 128
int waveform[WAVEFORM_SAMPLES] = {0};
int waveformIndex = 0;

void setup() {
  Serial.begin(115200);

  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(FREQUENCY_SWITCH_PIN, INPUT_PULLUP);
  pinMode(BUTTON_PIN_UP, INPUT_PULLUP);
  pinMode(BUTTON_PIN_DIR, INPUT_PULLUP);
  pinMode(BUTTON_PIN_ESQ, INPUT_PULLUP);

  u8g2.begin();
  u8g2.enableUTF8Print();  // Permite imprimir caracteres UTF-8
  ELECHOUSE_cc1101.Init();


  u8g2.begin();
  u8g2.clearBuffer();
  u8g2.setFlipMode(3); //rotaciona tela
  u8g2.setFont(u8g2_font_6x10_tf);
    
    u8g2.firstPage();
    do {
        u8g2.drawXBMP(0, 0, scary_width, scary_height, scary_bits);
    } while (u8g2.nextPage()); 

  if (digitalRead(FREQUENCY_SWITCH_PIN) == LOW) {
    ELECHOUSE_cc1101.setMHZ(315);
  } else {
    ELECHOUSE_cc1101.setMHZ(433.92);
  }

  ELECHOUSE_cc1101.SetRx();

  mySwitch.enableReceive(RX_PIN);
  mySwitch.enableTransmit(TX_PIN);
}

void loop() {
  if (mySwitch.available()) {
    receivedValue = mySwitch.getReceivedValue();
    receivedBitLength = mySwitch.getReceivedBitlength();
    unsigned int* rawSignal = mySwitch.getReceivedRawdata();
    receivedProtocol = mySwitch.getReceivedProtocol();

    if (receivedValue != 0) {
      u8g2.clearBuffer();
      u8g2.setCursor(0, 10);
      u8g2.print("Received Signal:");
      u8g2.setCursor(0, 20);
      u8g2.print(receivedValue);
      u8g2.setCursor(0, 30);
      u8g2.printf("Bit:%d  Ptc:%d", receivedBitLength, receivedProtocol);
      u8g2.sendBuffer();

      mySwitch.resetAvailable();
    }
  }

  if (digitalRead(BUTTON_PIN) == LOW && receivedValue != 0) {
    mySwitch.disableReceive();
    delay(100);
    mySwitch.enableTransmit(TX_PIN);
    ELECHOUSE_cc1101.SetTx();

    u8g2.clearBuffer();
    u8g2.setCursor(0, 10);
    u8g2.print("Received Signal:");
    u8g2.setCursor(0, 20);
    u8g2.print(receivedValue);
    u8g2.setCursor(0, 30);
    u8g2.print("Sending...");
    u8g2.sendBuffer();

    mySwitch.setProtocol(receivedProtocol);
    mySwitch.send(receivedValue, receivedBitLength);

    delay(500);

    u8g2.clearBuffer();
    u8g2.setCursor(0, 10);
    u8g2.print("Received Signal:");
    u8g2.setCursor(0, 20);
    u8g2.print(receivedValue);
    u8g2.setCursor(0, 30);
    u8g2.print("OK");
    u8g2.sendBuffer();

    ELECHOUSE_cc1101.SetRx();
    mySwitch.disableTransmit();
    delay(100);
    mySwitch.enableReceive(RX_PIN);
  }

  if (digitalRead(FREQUENCY_SWITCH_PIN) == LOW) {
    ELECHOUSE_cc1101.setMHZ(315);
  } else {
    ELECHOUSE_cc1101.setMHZ(433.92);
  }

  if (digitalRead(BUTTON_PIN_DIR) == LOW) {
    u8g2.clearBuffer();
    u8g2.setCursor(0, 10);
    u8g2.print("Sending Random:");
    u8g2.sendBuffer();
    delay(100);

    unsigned long randomValue = 100000000 + random(900000000);
    int randomBitLength = 28;
    int randomProtocol = 6;

    if (digitalRead(FREQUENCY_SWITCH_PIN) == LOW) {
      randomBitLength = 24;
      randomProtocol = 1;
    }

    mySwitch.disableReceive();
    delay(100);
    mySwitch.enableTransmit(TX_PIN);
    ELECHOUSE_cc1101.SetTx();

    u8g2.clearBuffer();
    u8g2.setCursor(0, 10);
    u8g2.print("Sending Random:");
    u8g2.setCursor(0, 20);
    u8g2.print(randomValue);
    u8g2.setCursor(0, 30);
    u8g2.print("Sending...");
    u8g2.sendBuffer();

    mySwitch.setProtocol(randomProtocol);
    mySwitch.send(randomValue, randomBitLength);

    delay(100);

    u8g2.clearBuffer();
    u8g2.setCursor(0, 10);
    u8g2.print("Sending Random:");
    u8g2.setCursor(0, 20);
    u8g2.print(randomValue);
    u8g2.setCursor(0, 30);
    u8g2.print("OK");
    u8g2.sendBuffer();

    ELECHOUSE_cc1101.SetRx();
    mySwitch.disableTransmit();
    delay(100);
    mySwitch.enableReceive(RX_PIN);
  }

  if (digitalRead(BUTTON_PIN_UP) == LOW) {
    u8g2.clearBuffer();
    u8g2.setCursor(0, 20);
    u8g2.print("Analyzing...");
    u8g2.sendBuffer();

    while (digitalRead(BUTTON_PIN_UP) == LOW) {
      int rssi;
      uint32_t detectedFrequency = 0;
      int detectedRssi = -100;

      for (size_t i = 0; i < sizeof(subghz_frequency_list) / sizeof(subghz_frequency_list[0]); i++) {
        uint32_t frequency = subghz_frequency_list[i];

        ELECHOUSE_cc1101.setMHZ((float)frequency / 1000000.0);
        ELECHOUSE_cc1101.SetRx();
        delayMicroseconds(3500);
        rssi = ELECHOUSE_cc1101.getRssi();

        if (rssi >= rssi_threshold && rssi > detectedRssi) {
          detectedRssi = rssi;
          detectedFrequency = frequency;
        }
      }

      if (detectedFrequency != 0) {
        u8g2.clearBuffer();
        u8g2.setCursor(0, 10);
        u8g2.printf("Signal detected:");
        u8g2.setCursor(0, 20);
        u8g2.printf("Frequency:%.2fMHz", (float)detectedFrequency / 1000000.0);
        u8g2.setCursor(0, 30);
        u8g2.printf("RSSI:%ddBm", detectedRssi);
        u8g2.sendBuffer();
      }

      delay(600);
    }
    ELECHOUSE_cc1101.SetRx();
    mySwitch.disableTransmit();
    delay(100);
    mySwitch.enableReceive(RX_PIN);
  }

  while (digitalRead(BUTTON_PIN_ESQ) == LOW) {
    u8g2.clearBuffer();
    float mhz = 0;

    for (int i = 1; i < SCREEN_WIDTH; i++) {
      int rssi = ELECHOUSE_cc1101.getRssi();
      waveform[i] = map(rssi, -100, -40, 0, 1023);

      if (rssi < -75) {
        if (i % 2 == 0) {
          ELECHOUSE_cc1101.setMHZ(433.92);
          ELECHOUSE_cc1101.SetRx();
          mhz = 433.92;
        } else {
          ELECHOUSE_cc1101.setMHZ(315);
          ELECHOUSE_cc1101.SetRx();
          mhz = 315.00;
        }
      } else {
        u8g2.setCursor(0, 7);
        u8g2.print(mhz);
      }

      int prevY = map(waveform[i - 1], 0, 1023, SCREEN_HEIGHT - 13, 8);
      int currY = map(waveform[i], 0, 1023, SCREEN_HEIGHT - 13, 8);
      u8g2.drawLine(i - 1, prevY, i, currY);

      u8g2.sendBuffer();
      delay(30);

      if (i == SCREEN_WIDTH && mhz != 0) {
        u8g2.clearBuffer();
        u8g2.setCursor(0, 7);
        u8g2.print(mhz);
        i = 1;
      }

      if (digitalRead(BUTTON_PIN_ESQ) != LOW) {
        break;
      }
    }

    delay(500);
  }
}
