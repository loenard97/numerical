#pragma once

#include <cstdint>
#include <ctime>

namespace numerical {
    namespace random {
        class XORShift32 {
        public:
            uint32_t state;
        
            XORShift32() {
                this->state = std::time(0);
            }
            XORShift32(uint32_t state) {
                this->state = state;
            }
        
            uint32_t rand() {
                this->state ^= this->state << 13;
                this->state ^= this->state >> 17;
                this->state ^= this->state << 5;
        
                return this->state;
            }
        
            float normalized() {
                return (float) this->rand() / (float) UINT32_MAX;
            }
        };

        class XORShift64 {
        public:
            uint64_t state;

            XORShift64() {
                this->state = std::time(0);
            }
            XORShift64(uint64_t state) {
                this->state = state;
            }

            uint64_t rand() {
                this->state ^= this->state << 13;
                this->state ^= this->state >> 7;
                this->state ^= this->state << 17;

                return this->state;
            }

            float normalized() {
                return (float) this->rand() / UINT64_MAX;
            }
        };
    }
}