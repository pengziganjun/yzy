#include<Adafruit_GFX.h>
#include<Adafruit_SSD1306.h>
int choice = 10 ;

void star_t() {

  oled.drawBitmap(20, 10, kai , 16, 16, 1);
  oled.drawBitmap(40, 10, shi , 16, 16, 1);
  oled.drawBitmap(60, 10, you , 16, 16, 1);
  oled.drawBitmap(80, 10, xi , 16, 16, 1);

}
void jianto_u() {

  oled.drawBitmap(110, choice, jiantou , 16, 16, 1);

}
void xiongma_o() {

  oled.drawBitmap(6, 20, xiongmao1, 20, 20, 1);
  oled.drawBitmap(46, 20, xiongmao2 , 20, 20, 1);
  oled.drawBitmap(86, 20, xiongmao3 , 20, 20, 1);

}
void board() {

  oled.setTextSize(1);
  oled.setTextColor(1);
  oled.setCursor(0, 55);
  oled.print("2024.7.30");

}
void age() {

  oled.setTextSize(1);
  oled.setTextColor(1);
  oled.setCursor(80, 55);
  oled.print("brith 20");

}
void xiazhuazile() {

  oled.setTextSize(2);
  oled.setTextColor(1);
  oled.setCursor(20, 25);
  oled.print("Catch it");

}
