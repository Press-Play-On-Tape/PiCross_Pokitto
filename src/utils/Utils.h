#pragma once

#include "Pokitto.h"
#include <stdint.h>
#include <stddef.h>


using PC = Pokitto::Core;
using PD = Pokitto::Display;


// ----------------------------------------------------------------------------
//  A better absolute as it uses less memory than the standard one .. 
//
template<typename T> T absT(const T & v) {
  
  return (v < 0) ? -v : v;

}

// This gets the length of an array at compile time
template< typename T, size_t N > constexpr size_t ArrayLength(T (&)[N]) {
	return N;
}


static inline uint16_t getFrameCount() {

    return Pokitto::Core::frameCount;

}

static inline uint16_t getFrameCount(uint16_t mod) {

    return (Pokitto::Core::frameCount % mod);

}

static inline bool getFrameCountHalf(uint16_t mod) {

    return ((Pokitto::Core::frameCount % mod) > (mod /2));

}

static inline bool isFrameCount(uint16_t mod) {

    return ((Pokitto::Core::frameCount % mod) == 0);

}

static inline bool isFrameCount(uint16_t mod, uint16_t val) {
    
    return ((Pokitto::Core::frameCount % mod) == val);

}


static inline void drawDottedColumn(uint8_t x, uint8_t sy, uint8_t ey) {
    
    for (uint8_t y = sy; y <= ey; y = y + 2) {
        
        PD::drawPixel(x, y);
    }

}

static inline void drawDottedRow(uint8_t sx, uint8_t ex, uint8_t y) {
    
    for (uint8_t x = sx; x <= ex; x = x + 2) {
        
        PD::drawPixel(x, y);
    }

}


static void renderPuzzleImage(uint8_t xPos, uint8_t yPos, const uint8_t *puzzleImg, uint8_t scale) {

    uint8_t idx = 0;

    uint8_t width = puzzleImg[idx++];
    uint8_t height = puzzleImg[idx++];
    uint8_t height8 = (height % 8 == 0 ? height / 8 : (height / 8) + 1);

    for (uint8_t y = 0; y < height8; y++){

        for (uint8_t x = 0; x < width; x++){

            uint8_t data = puzzleImg[idx++];

            for (uint8_t z = 0; z < 8; z++) {

                uint8_t val = (data & (1 << z));

                if (val > 0)
                    PD::fillRect(xPos + (x * scale), yPos + (((y * 8) + z) * scale), scale, scale - 1);

            }

        }

    }

}