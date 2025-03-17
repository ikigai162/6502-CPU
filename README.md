![Logo](https://www.geo.uaic.ro/images/logo_uaic_ro_2_300_color_white.png)

# 6502 emulator

This project is a simple implementation of an emulator for the 6502 processor, used in retro computers and consoles. The emulator currently includes a simulation of memory, CPU registers, and implementation of LDA (Load Accumulator) instructions out of the box.

## Installation

Clone the GitHub repository:

```bash
git clone https://github.com/ikigai162/6502-CPU/tree/master/6502
cd 6502
```
### Compile the code:
```bash
g++ 6502.cpp
```

## Usage/Examples
The code sets the memory so that the program counter (PC) starts execution at address 0xFFFC. The LDA_IM instruction is placed at this address along with the immediate value 0x42.

```cpp
mem[0xFFFC] = CPU::INS_LDA_IM; // Instrucțiunea LDA_IM
mem[0xFFFD] = 0x42;            // Valoarea imediată de încărcat în A
```

## Lessons Learned

#### 1. **Low-Level CPU Architecture**

#### 2. **Memory Management**

#### 3. **Cycle-Accurate Emulation**

#### 4. **Bit Manipulation and Unions**

#### 5. **Debugging and Logging**

#### 6. **Project Structure and Code Organization**

#### 7. **Testing and Validation**



## Documentation
[Documentation](http://6502.org/users/obelisk/)

## Contributing

Contributions are welcome!
If you would like to extend the emulator's functionality or fix bugs, please open a pull request.

## License

[MIT](https://choosealicense.com/licenses/mit/)
