#include <M5Stack.h>

#include <MyPulseSensorPlayground.h>

const int PIN_INPUT = 36;
const int THRESHOLD = 550;   // Adjust this number to avoid noise when idle

const char* fname = "/pulse/out.csv";

PulseSensorPlayground pulseSensor;

void setup() {
    M5.begin();
    dacWrite(25, 0); // Speaker OFF(スピーカーノイズ対策)
    
    initPulseSensor();
}

const int LCD_WIDTH = 320;
const int LCD_HEIGHT = 240;
const int DOTS_DIV = 30;
#define GREY 0x7BEF

void DrawGrid() {
    for (int x = 0; x <= LCD_WIDTH; x += 2) { // Horizontal Line
        for (int y = 0; y <= LCD_HEIGHT; y += DOTS_DIV) {
            M5.Lcd.drawPixel(x, y, GREY);
        }
        if (LCD_HEIGHT == 240) {
            M5.Lcd.drawPixel(x, LCD_HEIGHT - 1, GREY);
        }
    }
    for (int x = 0; x <= LCD_WIDTH; x += DOTS_DIV) { // Vertical Line
        for (int y = 0; y <= LCD_HEIGHT; y += 2) {
            M5.Lcd.drawPixel(x, y, GREY);
        }
    }
}


#define REDRAW 20 // msec
#define PERIOD 60 // sec
short lastMin = 0, lastMax = 4096;
short minS = 4096, maxS = 0;
int lastY = 0;
int x = 0;

int loopcount = 0;

void loop() {
    delay(REDRAW);

    // 脈波の立ち上がり発見時  
    if (pulseSensor.sawStartOfBeat()) {
        int rri = pulseSensor.getInterBeatIntervalMs(); //心拍間隔の取得
        File file = SD.open(fname, FILE_APPEND);
        if(!file) {
          Serial.println("SD card naiyo~~~");
        } else {
          file.println(rri);
        }
        file.close();
    }

    //表示部はじめ-------------------------------------------------------------------
    int y = pulseSensor.getLatestSample();
    if (y < minS) minS = y;
    if (maxS < y) maxS = y;
    if (x > 0) {
        y = (int)(LCD_HEIGHT - (float)(y - lastMin) / (lastMax - lastMin) * LCD_HEIGHT);
        M5.Lcd.drawLine(x - 1, lastY, x, y, WHITE);
        lastY = y;
    }
    if (++x > LCD_WIDTH) {
        x = 0;
        M5.Lcd.fillScreen(BLACK);
        DrawGrid();
        lastMin = minS - 20;
        lastMax = maxS + 20;
        minS = 4096;
        maxS = 0;
        M5.Lcd.setCursor(0, 0);
        M5.Lcd.setTextSize(4);
        M5.Lcd.printf("BPM: %d", pulseSensor.getBeatsPerMinute());
    }
    //表示部おわり---------------------------------------------------------------------------

    // PERIOD秒ごとの処理
    if (++loopcount > PERIOD * 1000 / REDRAW) {
        loopcount = 0;
    }
}


void initPulseSensor() {
    pulseSensor.analogInput(PIN_INPUT);
    pulseSensor.setThreshold(THRESHOLD);

    while (!pulseSensor.begin()) {
        Serial.println("PulseSensor.begin: failed");
        delay(500);
    }
}
