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

    Byte operator[](u32 Address) const {
        return Data[Address];
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

    void Reset( Mem& memory ) {
        PC = 0xFFFC;
        SP = 0x0100;
        PS = 0;
        A = X = Y = 0;
        memory.Initialise();
    }

    Byte FetchByte(u32& Cycles, Mem& memory) {
        Byte Data = memory[PC];
        PC++;
        Cycles--;
        return Data;
    };

    void Execute( u32 Cycles, Mem& memory) {
        while (Cycles > 0) {
            Byte Instruction = FetchByte(Cycles, memory);
            (void)Instruction;
        }
    }
};

int main() {
    Mem mem;
    CPU cpu;
    cpu.Reset(mem);
    cpu.Execute(2, mem);
    return 0;
}