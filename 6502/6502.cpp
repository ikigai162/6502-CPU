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

    Byte& operator[](u32 Address) {  // Removed const qualifier
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
        Byte PS;
    };

    static constexpr Byte INS_LDA_IM = 0xA9;

    void Reset(Mem& memory) {
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
    }

    void Execute(u32& Cycles, Mem& memory) {
        while (Cycles > 0) {
            Byte Instruction = FetchByte(Cycles, memory);
            switch (Instruction) {
            case INS_LDA_IM: {
                Byte Value = FetchByte(Cycles, memory);
                A = Value;
                Z = (A == 0);
                N = (A & 0b10000000) > 0;
            } break;
            default: {
                printf("Instruction not handled %d\n", Instruction);
                break;
            }
            }
        }
    }
};

int main() {
    Mem mem;
    CPU cpu;
    cpu.Reset(mem);
    mem[0xFFFC] = CPU::INS_LDA_IM;
    mem[0xFFFD] = 0x42;

    u32 cycles = 2;
    cpu.Execute(cycles, mem);
    return 0;
}