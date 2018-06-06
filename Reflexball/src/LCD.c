#include "LCD.h"
#include "charset.h"
#include "string.h"
#define SIZE_OF_ARRAY(_array) (sizeof(_array) / sizeof(_array[0]))
void initLCD(){
        // Initialiserer SPI komunikation.
        init_spi_lcd();


}

void LCDWrite(struct LCDDataLine *LineData, char* Text, int Line) {

    int i,j = 0;
    int Location = 0;

    for (j=0; j< strlen(Text); j++) {

        uint8_t t = Text[j];

        for (i=0; i<5; i++) {

            if ((Location+i) < 128) {
                LineData->Data[Line][Location + i] = character_data[t-0x20][i];
            }

        }
        Location += 5;

    }

}

void CollectGraph(char *Graph, struct LCDDataLine *LineData){

    for (int i=0; i<4; i++) {
        for (int j=0; j<128; j++) {
            Graph[(i*128) + j] = LineData->Data[i][j];
        }
    }

}

void ClearLineData(struct LCDDataLine *LineData) {

    for (int i=0; i<4; i++) {
        for (int j=0; j<128; j++) {
            LineData->Data[i][j] = 0;
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

void Shift(struct LCDDataLine *LineData, uint8_t Line) {
    int FirstElement = LineData->Data[Line][0];

    for (int i = 0; i < 127; i++){
        LineData->Data[Line][i] = LineData->Data[Line][i+1];
    }
    LineData->Data[Line][127] = FirstElement;
}

//void Shift2(char* Graph) {
//    int LastElement = Graph[511];
//
//    for (int i = 511; i > 0; i--){
//        Graph[i] = Graph[i-1];
//    }
//    Graph[0] = LastElement;
//}

void lcd_update(char *Graph, struct LCDDataLine *LineData) {
    Shift(LineData, 0);
    Shift(LineData, 1);
    Shift(LineData, 2);
    Shift(LineData, 3);
    CollectGraph(Graph, LineData);
    lcd_push_buffer(Graph);

}
