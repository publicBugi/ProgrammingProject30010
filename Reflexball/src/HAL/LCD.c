#include "LCD.h"
#include "charset.h"
#include "string.h"
#define SIZE_OF_ARRAY(_array) (sizeof(_array) / sizeof(_array[0]))
void initLCD(){
        // Initialiserer SPI komunikation.
        init_spi_lcd();


}
/**
  * Descripton:T his function inserts Text argument in the LCDData array.
  * Argument: char LCDData[4][128], char* Text, int Line
  * Return value: None.
  */
void LCDWrite(char LCDData[4][128], char* Text, int Line) {

    int Location = 0;

    for (int j=0; j < strlen(Text); j++) {

        uint8_t t = Text[j];

        for (int i=0; i<5; i++) {
            if ((Location+i) < 128) {
                LCDData[Line][Location + i] = character_data[t-0x20][i];
            }
        }
        Location += 5;
    }
}

/**
  * Descripton: This function replace the Graph array with LCDData array. .
  * Argument: char *Graph, char LCDData[4][128]
  * Return value: None.
  */
void CollectGraph(char *Graph, char LCDData[4][128]){

    for (int i=0; i<4; i++) {
        for (int j=0; j<128; j++) {
            Graph[(i*128) + j] = LCDData[i][j];
        }
    }

}

void ClearLineData(char LCDData[4][128]) {

    for (int i=0; i<4; i++) {
        for (int j=0; j<128; j++) {
            LCDData[i][j] = 0;
        }
    }
}

//void LCDWrite2(char *Graph, char* Text, int Line) {
//    int j = 0;
//    int i = 0;
//    int Location = 0;
//
//    for (j=0; j< strlen(Text); j++) {
//
//        uint8_t t = Text[j];
//
//        for (i=0; i<5; i++) {
//            if ((((Line-1)*128) + i + Location) < 512) {
//                Graph[((Line-1)*128) + i + Location] = character_data[t-0x20][i];
//
//            }
//        }
//        Location += 5;
//
//    }
//  lcd_push_buffer(Graph);
//
//}

void Shift(char LCDData[4][128], uint8_t Line) {
    int FirstElement = LCDData[Line][0];
    for (int i = 0; i < 127; i++){
        LCDData[Line][i] = LCDData[Line][i+1];
    }
    LCDData[Line][127] = FirstElement;
}

//void Shift2(char* Graph) {
//    int LastElement = Graph[511];
//
//    for (int i = 511; i > 0; i--){
//        Graph[i] = Graph[i-1];
//    }
//    Graph[0] = LastElement;
//}

/**
  * Descripton: This function push the Graph data to LCD buffer.
  * Argument: char *Graph, char LCDData[4][128].
  * Return value: None.
  */
void lcd_update(char *Graph, char LCDData[4][128]) {
    //Shift(LineData, 0);
    //Shift(LineData, 1);
    //Shift(LineData, 2);
    //Shift(LineData, 3);
    CollectGraph(Graph, LCDData);
    lcd_push_buffer(Graph);

}
