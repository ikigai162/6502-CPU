#include <stdlib.h>
#include <stdio.h>

struct CPU {
	using Byte = unsigned char;
	using Word = unsigned short;

//Program counter
	Word PC;
	//Stack pointer
	Word SP;

	Byte A, Y, X; //Registers

	//Status flags
	Byte C : 1;
	Byte Z : 1;
	Byte I : 1;
	Byte D : 1;
	Byte B : 1;
	Byte V : 1;
	Byte N : 1;

	void Reset() {
		PC = 0xFFFC; //Initialization
		SP = 0x0100;
		C = Z = I = D = B = V = N = 0;
		A = X = Y = 0;
	}
};

int main() {
	CPU cpu;
	cpu.Reset();

}