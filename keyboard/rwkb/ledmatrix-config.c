#include <avr/io.h>

//WIRING CONFIG
#define LED_MAT_ROWSIZE 4
#define LED_MAT_COLSIZE 12

//declar all ports and pins 
#define LED_MAT_ALLP    F,C,E
#define LED_MAT_ALLMASK 0b11111111, 0b10111011, 0b00000011

//split the above into row and col groups
#define LED_MAT_ROWMASK 0b00000000, 0b10110000, 0b00000001
#define LED_MAT_COLMASK 0b11111111, 0b00001011, 0b00000010

//finall declare the individual pins of the rows and cols
#define LED_MAT_ROW0    0b00000000, 0b00010000, 0b00000000
#define LED_MAT_ROW1    0b00000000, 0b00100000, 0b00000000
#define LED_MAT_ROW2    0b00000000, 0b00000000, 0b00000001
#define LED_MAT_ROW3    0b00000000, 0b10000000, 0b00000000

#define LED_MAT_COL0    0b00000000, 0b00001000, 0b00000000
#define LED_MAT_COL1    0b00000000, 0b00000000, 0b00000010
#define LED_MAT_COL2    0b00000000, 0b00000010, 0b00000000
#define LED_MAT_COL3    0b00000000, 0b00000001, 0b00000000
#define LED_MAT_COL4    0b10000000, 0b00000000, 0b00000000
#define LED_MAT_COL5    0b01000000, 0b00000000, 0b00000000
#define LED_MAT_COL6    0b00100000, 0b00000000, 0b00000000 
#define LED_MAT_COL7    0b00010000, 0b00000000, 0b00000000 
#define LED_MAT_COL8    0b00001000, 0b00000000, 0b00000000
#define LED_MAT_COL9    0b00000100, 0b00000000, 0b00000000
#define LED_MAT_COL10   0b00000010, 0b00000000, 0b00000000
#define LED_MAT_COL11   0b00000001, 0b00000000, 0b00000000

#define _IND 0xFF
#define _BLU 0xF0
#define _RED 0x0F

//remeber to update size  and change hook when adding layers
static uint8_t layerLED[5][LED_MAT_ROWSIZE * LED_MAT_COLSIZE] = {
    {//0 - default layer 
        _IND,_IND,_IND,_IND, _IND,_IND,_IND,_IND, _IND,_IND,_IND,_IND,
        _IND,_IND,_IND,_IND, _IND,_IND,_IND,_IND, _IND,_IND,_IND,_IND,
        _IND,_IND,_IND,_IND, _IND,_IND,_IND,_IND, _IND,_IND,_IND,_IND,
        _IND,_IND,_IND,_IND, _IND,_IND,_IND,_IND, _IND,_IND,_IND,_IND
    },
    {//1 - numbers 
        _IND,_IND,_IND,_IND, _IND,_IND,_IND,_RED, _RED,_RED,_IND,_IND,
        _IND,_IND,_IND,_IND, _IND,_IND,_IND,_RED, _RED,_RED,_IND,_IND,
        _IND,_IND,_IND,_IND, _IND,_IND,_IND,_RED, _RED,_RED,_IND,_IND,
        _IND,_IND,_IND,_IND, _IND,_IND,_IND,_RED, _IND,_IND,_IND,_IND
    },
    {//2 - special and nav
        _IND,_IND,_IND,_IND, _IND,_IND,_IND,_IND, _IND,_IND,_IND,_IND,
        _IND,_IND,_IND,_IND, _IND,_IND,_RED,_RED, _RED,_RED,_IND,_IND,
        _IND,_IND,_IND,_IND, _IND,_IND,_IND,_IND, _IND,_IND,_IND,_IND,
        _IND,_IND,_IND,_IND, _IND,_IND,_IND,_IND, _IND,_IND,_IND,_IND
    },
    {//3 - mouse and media layer 
        _IND,_IND,_RED,_IND, _IND,_IND,_IND,_IND, _IND,_IND,_IND,_RED,
        _IND,_RED,_RED,_RED, _IND,_RED,_IND,_IND, _IND,_IND,_IND,_IND,
        _IND,_IND,_IND,_IND, _IND,_IND,_IND,_IND, _IND,_IND,_IND,_IND,
        _IND,_RED,_IND,_IND, _IND,_IND,_IND,_IND, _RED,_RED,_RED,_RED
    },
    {//4 - game mode
        _IND,_IND,_RED,_IND, _IND,_IND,_IND,_RED, _RED,_RED,_RED,_RED,
        _IND,_RED,_RED,_RED, _IND,_IND,_IND,_RED, _RED,_RED,_RED,_IND,
        _IND,_IND,_IND,_IND, _IND,_IND,_IND,_IND, _IND,_IND,_IND,_IND,
        _IND,_IND,_IND,_IND, _IND,_IND,_IND,_IND, _IND,_IND,_IND,_IND
    }
};

//state is a 32bit int representing current active layers
void ledMatrixLayerChangeHook(uint32_t state){
    uint8_t layer = 0;
    if (1UL<<1 & state) layer = 1;
    if (1UL<<2 & state) layer = 2;
    if (1UL<<3 & state) layer = 3;
    if (1UL<<4 & state) layer = 4;

    ledMatrixSetState(layerLED[layer]);
}

