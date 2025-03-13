#include <stdlib.h>
#include <stdio.h>

using Byte = unsigned char;
using Word = unsigned short;
using u32 = unsigned int;

struct Mem {
    static constexpr u32 MAX_MEM = 1024 * 64;
    Byte Data[MAX_MEM];

    void Initialise() {
        for (u32 i = 0; i < MAX_MEM; i++) {
            Data[i] = 0;
        }
    }
};

struct CPU {
    Word PC; // Program counter
    Word SP; // Stack pointer

    Byte A, Y, X; // Registers

    union {
        struct {
            Byte C : 1; // Carry
            Byte Z : 1; // Zero
            Byte I : 1; // Interrupt disable
            Byte D : 1; // Decimal mode
            Byte B : 1; // Break command
            Byte V : 1; // Overflow
            Byte N : 1; // Negative
            Byte : 1;  // Unused bit
        };
        Byte PS; // Combined status register
    };

    void Reset(Mem& memory) {
        PC = 0xFFFC;
        SP = 0x0100;
        PS = 0;
        A = X = Y = 0;
        memory.Initialise();
    }
};

int main() {
    Mem mem;
    CPU cpu;
    cpu.Reset(mem);
    return 0;
}