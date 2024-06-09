
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <Arduino_GFX_Library.h>
#define TFT_SCK    18
#define TFT_MOSI   23
#define TFT_MISO   19
#define TFT_CS     22
#define TFT_DC     21
#define TFT_RESET  17

int count1 = 0;
int count2 = 0;

TaskHandle_t task1_handle = NULL;
Arduino_ESP32SPI bus = Arduino_ESP32SPI(TFT_DC, TFT_CS, TFT_SCK, TFT_MOSI, TFT_MISO);
Arduino_ILI9341 display = Arduino_ILI9341(&bus, TFT_RESET);

void task1(void * parameters){
  for(;;){
    display.fillScreen(WHITE);
    display.setCursor(20, 20);
    display.setTextSize(2);
    display.setTextColor(BLUE);
    display.println("STAN LOONA :");
    Serial.print("1");
    Serial.println(count1++);
    vTaskDelay(3000/portTICK_PERIOD_MS);

  }
   
}

void task2(void * parameters){
  for(;;){
    display.fillScreen(WHITE);
    display.setCursor(20, 20);
    display.setTextSize(2);
    display.setTextColor(BLUE);
    display.println("STAN ZB1 :");
    Serial.print("2");
    Serial.println(count2++);
    vTaskDelay(3000/portTICK_PERIOD_MS);
    
  }
  vTaskDelete(NULL);
}
void setup() {
  
  Serial.begin(115200);
 display.begin();
  xTaskCreate(
    task1,
    "Task 1",
    4096,
    NULL,
    1,
    &task1_handle
  );

  xTaskCreate(
    task2,
    "Task 2",
    4096,
    NULL,
    1,
    NULL
  );
 
 /* display.begin();
  display.fillScreen(WHITE);
  display.setCursor(20, 20);
  display.setTextSize(2);
  display.setTextColor(BLUE);
  display.println("STAN LOONA :");
  */
}
void importantTask(){
  vTaskSuspendAll();

  xTaskResumeAll();
}
void loop() {
  // put your main code here, to run repeatedly:
  if(count1%2==0 && task1_handle != NULL){
    vTaskSuspend(task1_handle);
  }
  if(count2%3==0 && task1_handle != NULL){
    vTaskResume(task1_handle);
  }
}
