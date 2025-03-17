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
    // Read 1 byte
    Byte operator[](u32 Address) const {
        return Data[Address];
    }
    // Write 1 byte
    Byte& operator[](u32 Address) {
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
    static constexpr Byte INS_LDA_ZP = 0xA5; // Zero page
    static constexpr Byte INS_LDA_ZPX = 0xB5;

    void LDASetStatus(){
        Z = (A == 0);
        N = (A & 0b10000000) > 0;
    }

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

    Byte ReadByte(u32& Cycles, Byte Address, Mem& memory) {
        Byte Data = memory[Address];
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
                LDASetStatus();

                printf("[LDA] A=0x%02X, Z=%d, N=%d\n", A, Z, N);
            } break;
            case INS_LDA_ZP: {
                Byte ZeroPageAddress = FetchByte(Cycles, memory);
                A = ReadByte(Cycles, ZeroPageAddress, memory);
                LDASetStatus();
                printf("[LDA ZP] A=0x%02X, Z=%d, N=%d, ZP Address=0x%02X\n", A, Z, N, ZeroPageAddress);
            }break;
            case INS_LDA_ZPX: {
                Byte ZeroPageAddr = FetchByte(Cycles, memory);
                ZeroPageAddr += X;
                Cycles--;
                LDASetStatus();
            }break;
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
     
    mem[0xFFFC] = CPU::INS_LDA_ZP;
    mem[0xFFFD] = 0x42;
    mem[0x0042] = 0x84;

    u32 cycles = 3;
    cpu.Execute(cycles, mem);

    printf("Final registers:\n");
    printf("A=0x%02X, X=0x%02X, Y=0x%02X\n", cpu.A, cpu.X, cpu.Y);
    printf("Flags: Z=%d, N=%d\n", cpu.Z, cpu.N);

    getchar(); // Păstrează consola deschisă
    return 0;
}