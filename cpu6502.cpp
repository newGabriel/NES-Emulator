#ifndef CPU6502_CPP
#define CPU6502_CPP

#include <stdint.h>
#include <string>
#include <map>

#include "cpu6502.hpp"

// Public

std::map<std::string,std::map<int8_t,int8_t>> objC =
{  // tabela de enderecamento
    {"aaa", {
        {0b000, 1},  // pre indexado indireto
        {0b001, 1},  // direto
        {0b010, 1},  // imediato
        {0b011, 2},  // direto extendido
        {0b100, 1},  // pos indexado indireto
        {0b101, 1},  // base page indexado
        {0b110, 2},  // indexado absoluto X
        {0b111, 2},  // indexado absoluto Y
        }
    },

    {"bb", {
        {0b000, 1},  // direto
        {0b001, 2},  // extendido direto
        {0b010, 1},  // base page indexado
        {0b011, 2},  // indexado absoluto
        },
    },

    {"bbb", {
        {0b001, 1},  // direto
        {0b010, 0},  // acumulador
        {0b011, 2},  // direto extendido
        {0b101, 1},  // base page indexado
        {0b111, 2},  // indexado absoluto
        }
    },

    {"cc", {
        {0b000, 1},  // imediato
        {0b001, 1},  // direto
        {0b011, 2},  // direto extendido
        }
    },

    {"ddd", {
        {0b000, 1},  // imediato
        {0b001, 1},  // direto
        {0b011, 2},  // direto extendido
        {0b101, 1},  // base page indexado
        {0b111, 2},  // indexado absoluto
        }
    },

    {"x", {
        {0b0, 1},  // direto
        {0b1, 2},  // direto extendido
        }
    },

    {"y", {
        {0b0, 2},  // direto extendido (label)
        {0b1, 2},  // indireto (label)
        }
    }
};

int8_t readRom(int16_t add){
    return 0;
}

Cpu6502::Cpu6502(/*RAM*/){
    pc = 0x00;
    sp = 0x00;
    A  = 0x0;
    X  = 0x0;
    Y  = 0x0;
    P  = 0x0;
    /*RAM*/
}

// Private

void Cpu6502::processInstruction(int8_t instruction){
    if     (!(instruction ^ 0b01100001)) ADC(instruction);
    else if(!(instruction ^ 0b00100001)) AND(instruction);
    else if(!(instruction ^ 0b00000110)) ASL(instruction);
    else if(!(instruction ^ 0b10010000)) BCC(instruction);
    else if(!(instruction ^ 0b10110000)) BCS(instruction);
    else if(!(instruction ^ 0b11110000)) BEQ(instruction);
    else if(!(instruction ^ 0b00100100)) BIT(instruction);
    else if(!(instruction ^ 0b00110000)) BMI(instruction);
    else if(!(instruction ^ 0b11010000)) BNE(instruction);
    else if(!(instruction ^ 0b00010000)) BPL(instruction);
    else if(!(instruction ^ 0b00000000)) BRK(instruction);
    else if(!(instruction ^ 0b01010000)) BVC(instruction);
    else if(!(instruction ^ 0b01110000)) BVS(instruction);
    else if(!(instruction ^ 0b00011000)) CLC(instruction);
    else if(!(instruction ^ 0b11011000)) CLD(instruction);
    else if(!(instruction ^ 0b01011000)) CLI(instruction);
    else if(!(instruction ^ 0b10111000)) CLV(instruction);
    else if(!(instruction ^ 0b11000001)) CMP(instruction);
    else if(!(instruction ^ 0b11100000)) CPX(instruction);
    else if(!(instruction ^ 0b11000000)) CPY(instruction);
    else if(!(instruction ^ 0b11000110)) DEC(instruction);
    else if(!(instruction ^ 0b11001010)) DEX(instruction);
    else if(!(instruction ^ 0b10001000)) DEY(instruction);
    else if(!(instruction ^ 0b01000001)) EOR(instruction);
    else if(!(instruction ^ 0b11100110)) INC(instruction);
    else if(!(instruction ^ 0b11101000)) INX(instruction);
    else if(!(instruction ^ 0b11001000)) INY(instruction);
    else if(!(instruction ^ 0b01001100)) JPM(instruction);
    else if(!(instruction ^ 0b00100000)) JSR(instruction);
    else if(!(instruction ^ 0b10100001)) LDA(instruction);
    else if(!(instruction ^ 0b10100010)) LDX(instruction);
    else if(!(instruction ^ 0b10100000)) LDY(instruction);
    else if(!(instruction ^ 0b01001010)) LSR(instruction);
    else if(!(instruction ^ 0b11101010)) NOP(instruction);
    else if(!(instruction ^ 0b00000001)) ORA(instruction);
    else if(!(instruction ^ 0b01001000)) PHA(instruction);
    else if(!(instruction ^ 0b00001000)) PHP(instruction);
    else if(!(instruction ^ 0b01101000)) PLA(instruction);
    else if(!(instruction ^ 0b00101000)) PLP(instruction);
    else if(!(instruction ^ 0b00101010)) ROL(instruction);
    else if(!(instruction ^ 0b01101010)) ROR(instruction);
    else if(!(instruction ^ 0b01000000)) RTI(instruction);
    else if(!(instruction ^ 0b01100000)) RTS(instruction);
    else if(!(instruction ^ 0b11100001)) SBC(instruction);
    else if(!(instruction ^ 0b00111000)) SEC(instruction);
    else if(!(instruction ^ 0b11111000)) SED(instruction);
    else if(!(instruction ^ 0b01111000)) SEI(instruction);
    else if(!(instruction ^ 0b10000001)) STA(instruction);
    else if(!(instruction ^ 0b10000110)) STX(instruction);
    else if(!(instruction ^ 0b10000100)) STY(instruction);
    else if(!(instruction ^ 0b10101010)) TAX(instruction);
    else if(!(instruction ^ 0b10101000)) TAY(instruction);
    else if(!(instruction ^ 0b10111010)) TSX(instruction);
    else if(!(instruction ^ 0b10001010)) TXA(instruction);
    else if(!(instruction ^ 0b10011010)) TXS(instruction);
    else if(!(instruction ^ 0b10011000)) TYA(instruction);
}

void Cpu6502::ADC(int8_t instruction){
    int8_t add;
    int8_t args = getValueFromAAAAdressing(instruction, &add);
    int8_t nx   = objC["aaa"][add]; // verificando na tabela de enderecamento quantos bytes sao recebidos por argumento

    this->A += args;

    ///TODO: carrier do overflow

    this->pc += nx ; // atualizando o PC para a posição depois dos argumentos
}

void Cpu6502::AND(int8_t instruction){
    int8_t add;
    int8_t args = getValueFromAAAAdressing(instruction, &add);
    int8_t nx   = objC["aaa"][add]; // verificando na tabela de enderecamento quantos bytes sao recebidos por argumento

    this->A &= args;

    ///TODO: carrier do overflow????

    this->pc += nx ; // atualizando o PC para a posição depois dos argumentos
}

void Cpu6502::ASL(int8_t instruction){
    ///TODO: revisar isso aq
    int8_t add;
    int8_t args = getValueFromBBAdressing(instruction, &add);
    int8_t nx   = objC["bb"][add]; // verificando na tabela de enderecamento quantos bytes sao recebidos por argumento
    
    this->A<<1;

    ///TODO: registrador de status
}

void Cpu6502::BCC(int8_t instruction){

}

void Cpu6502::BCS(int8_t instruction){

}

void Cpu6502::BEQ(int8_t instruction){

}

void Cpu6502::BIT(int8_t instruction){

}

void Cpu6502::BMI(int8_t instruction){

}

void Cpu6502::BNE(int8_t instruction){

}

void Cpu6502::BPL(int8_t instruction){

}

void Cpu6502::BRK(int8_t instruction){

}

void Cpu6502::BVC(int8_t instruction){

}

void Cpu6502::BVS(int8_t instruction){

}

void Cpu6502::CLC(int8_t instruction){
    this->P &= 0b11111110; 
    this->pc++;
}

void Cpu6502::CLD(int8_t instruction){
    this->P &= 0b11110111; 
    this->pc++;
}

void Cpu6502::CLI(int8_t instruction){
    this->P &= 0b11111011; vscode
    this->pc++;
}

void Cpu6502::CLV(int8_t instruction){
    this->P &= 0b11011111; 
    this->pc++;
}

void Cpu6502::CMP(int8_t instruction){
    int8_t add;
    int8_t args = getValueFromAAAAdressing(instruction, &add);
    int8_t nx   = objC["aaa"][add]; // verificando na tabela de enderecamento quantos bytes sao recebidos por argumento

    int8_t res = this->A - args;

    ///TODO: setar o registrador de Status

    this->pc += nx ; // atualizando o PC para a posição depois dos argumentos
}

void Cpu6502::CPX(int8_t instruction){

}

void Cpu6502::CPY(int8_t instruction){

}

void Cpu6502::DEC(int8_t instruction){

}

void Cpu6502::DEX(int8_t instruction){
    this->X--;
    this->pc++;
}

void Cpu6502::DEY(int8_t instruction){
    this->Y--;
    this->pc++;
}

void Cpu6502::EOR(int8_t instruction){
    int8_t add;
    int8_t args = getValueFromAAAAdressing(instruction, &add);
    int8_t nx   = objC["aaa"][add]; // verificando na tabela de enderecamento quantos bytes sao recebidos por argumento

    this->A ^= args;

    ///TODO: reg de status

    this->pc += nx ; // atualizando o PC para a posição depois dos argumentos
}

void Cpu6502::INC(int8_t instruction){

}

void Cpu6502::INX(int8_t instruction){
    this->X++;
    this->pc++;
}

void Cpu6502::INY(int8_t instruction){
    this->Y++;
    this->pc++;
}

void Cpu6502::JPM(int8_t instruction){

}

void Cpu6502::JSR(int8_t instruction){

}

void Cpu6502::LDA(int8_t instruction){
    int8_t add;
    int8_t args = getValueFromAAAAdressing(instruction, &add);
    int8_t nx   = objC["aaa"][add]; // verificando na tabela de enderecamento quantos bytes sao recebidos por argumento

    this->A = args;

    ///TODO: registrado de status

    this->pc += nx ; // atualizando o PC para a posição depois dos argumentos
}

void Cpu6502::LDX(int8_t instruction){

}

void Cpu6502::LDY(int8_t instruction){

}

void Cpu6502::LSR(int8_t instruction){

}

void Cpu6502::NOP(int8_t instruction){
    this->pc++;
}

void Cpu6502::ORA(int8_t instruction){
    int8_t add;
    int8_t args = getValueFromAAAAdressing(instruction, &add);
    int8_t nx   = objC["aaa"][add]; // verificando na tabela de enderecamento quantos bytes sao recebidos por argumento

    this->A |= args;

    ///TODO: registrado de status

    this->pc += nx ; // atualizando o PC para a posição depois dos argumentos
}

void Cpu6502::PHA(int8_t instruction){

}

void Cpu6502::PHP(int8_t instruction){

}

void Cpu6502::PLA(int8_t instruction){

}

void Cpu6502::PLP(int8_t instruction){

}

void Cpu6502::ROL(int8_t instruction){
    ///TODO: Fazer para memoria
    
    int8_t bitToPut = this->A & 0b10000000;
    bitToPut >>= 7; // desloca para o bit menos relevante

    this->A = (this->A << 1) + (this->P & 0b00000001);

    this->P &= 0b11111110;
    this->P |= bitToPut;

    this->pc++;
}

void Cpu6502::ROR(int8_t instruction){
    ///TODO: Fazer para memoria
    
    int8_t bitToPut = this->P & 0b00000001;
    bitToPut <<= 7; // desloca para o bit mais relevante

    this->P &= 0b11111110;
    this->P |= this->A & 0b00000001;

    this->A = (this->A << 1) + bitToPut;

    this->pc++;
}

void Cpu6502::RTI(int8_t instruction){

}

void Cpu6502::RTS(int8_t instruction){

}

void Cpu6502::SBC(int8_t instruction){
    int8_t add;
    int8_t args = getValueFromAAAAdressing(instruction, &add);
    int8_t nx   = objC["aaa"][add]; // verificando na tabela de enderecamento quantos bytes sao recebidos por argumento

    this->A += args;

    ///TODO: registrado de status

    this->pc += nx ; // atualizando o PC para a posição depois dos argumentos
}

void Cpu6502::SEC(int8_t instruction){
    this->P |= 0b00000001;
    this->pc++;
}

void Cpu6502::SED(int8_t instruction){
    this->P |= 0b00001000;
    this->pc++;
}

void Cpu6502::SEI(int8_t instruction){
    this->P |= 0b00000100;
    this->pc++;
}

void Cpu6502::STA(int8_t instruction){

}

void Cpu6502::STX(int8_t instruction){

}

void Cpu6502::STY(int8_t instructvscodeion){

}

void Cpu6502::TAX(int8_t instruction){
    this->X = this->A;
    this->pc++;
}

void Cpu6502::TAY(int8_t instruction){
    this->Y = this->A;
    this->pc++;
}

void Cpu6502::TSX(int8_t instruction){
    this->X = this->sp;
    this->pc++;
}

void Cpu6502::TXA(int8_t instruction){
    this->A = this->X;
    this->pc++;
}

void Cpu6502::TXS(int8_t instruction){
    this->sp = this->X;
    this->pc++;
}

void Cpu6502::TYA(int8_t instruction){
    this->A = this->Y;
    this->pc++;
}

int8_t Cpu6502::getValueFromAAAAdressing(int8_t instruction, int8_t* add){
    int8_t bk   = 0b00011100; // bitmask para extracao do formato de enderecamento
          *add  = (instruction & bk) >> 2; // extraindo os bits referentes ao formato de enderecamento
    int8_t args = 0b0;

    int16_t addressX; 

    switch(*add){
        case 0b000: 
            addressX = getPreIndexedIndirectAddress();
            args     = getIntFromBus(addressX);
            break;
        case 0b001: 
            addressX = getZeroPageAddress();
            args     = getIntFromBus(addressX);
            break;
        case 0b010: 
            addressX = getImmediateAddress();
            args     = getIntFromBus(addressX);
            break;
        case 0b011: 
            addressX = getAbsoluteAddress();
            args     = getIntFromBus(addressX);    
            break;
        case 0b100: 
            addressX = getPosIndexedIndirectAddress();
            args     = getIntFromBus(addressX);
            break;
        case 0b101: 
            addressX = getZeroPageIndexedAddress();
            args     = getIntFromBus(addressX);
            break;
        case 0b110: 
            addressX = getAbsoluteYIndexedAddress();
            args     = getIntFromBus(addressX);
            break;
        case 0b111: 
            addressX = getAbsoluteXIndexedAddress();
            args     = getIntFromBus(addressX);
            break;
    }
    return args;
}

int8_t Cpu6502::getValueFromBBBAdressing(int8_t instruction, int8_t* add){
    ///TODO: revisar isso aq
    int8_t bk   = 0b00011100; // bitmask para extracao do formato de enderecamento
          *add  = (instruction & bk) >> 2; // extraindo os bits referentes ao formato de enderecamento
    int8_t args = 0b0;

    int16_t addressX; 

    switch(*add){
        case 0b00: 
            addressX = getZeroPageAddress();
            args     = getIntFromBus(addressX);
            break;
        case 0b01: 
            addressX = getAbsoluteAddress();
            args     = getIntFromBus(addressX);
            break;
        case 0b10: 
            addressX = getZeroPageIndexedAddress();
            args     = getIntFromBus(addressX);
            break;
        case 0b11: 
            addressX = getAbsoluteXIndexedAddress();
            args     = getIntFromBus(addressX);    
            break;
    }
    return args;
}

int8_t Cpu6502::getValueFromBBAdressing(int8_t instruction, int8_t* add){
    int8_t bk   = 0b00011000; // bitmask para extracao do formato de enderecamento
          *add  = (instruction & bk) >> 3; // extraindo os bits referentes ao formato de enderecamento
    int8_t args = 0b0;

    int16_t addressX; 

    switch(*add){
        case 0b00: 
            addressX = getZeroPageAddress();
            args     = getIntFromBus(addressX);
            break;
        case 0b01: 
            addressX = getAbsoluteAddress();
            args     = getIntFromBus(addressX);
            break;
        case 0b10: 
            addressX = getZeroPageIndexedAddress();
            args     = getIntFromBus(addressX);
            break;
        case 0b11: 
            addressX = getAbsoluteXIndexedAddress();
            args     = getIntFromBus(addressX);    
            break;
    }
    return args;
}

int8_t Cpu6502::getValueFromCCAdressing(int8_t instruction, int8_t* add){
    int8_t bk   = 0b00001100; // bitmask para extracao do formato de enderecamento
          *add  = (instruction & bk) >> 2; // extraindo os bits referentes ao formato de enderecamento
    int8_t args = 0b0;

    int16_t addressX; 

    switch(*add){
        case 0b00: 
            addressX = getImmediateAddress();
            args     = getIntFromBus(addressX);
            break;
        case 0b01: 
            addressX = getZeroPageAddress();
            args     = getIntFromBus(addressX);
            break;
        case 0b11: 
            addressX = getAbsoluteAddress();
            args     = getIntFromBus(addressX);    
            break;
    }
    return args;
}

int8_t Cpu6502::getValueFromDDDAdressing(int8_t instruction, int8_t* add){
    int8_t bk   = 0b00011100; // bitmask para extracao do formato de enderecamento
          *add  = (instruction & bk) >> 2; // extraindo os bits referentes ao formato de enderecamento
    int8_t args = 0b0;

    int16_t addressX; 

    switch(*add){
        case 0b000: 
            addressX = getImmediateAddress();
            args     = getIntFromBus(addressX);
            break;
        case 0b001: 
            addressX = getZeroPageAddress();
            args     = getIntFromBus(addressX);
            break;
        case 0b011: 
            addressX = getAbsoluteAddress();
            args     = getIntFromBus(addressX);    
            break;
        case 0b101: 
            addressX = getZeroPageIndexedAddress(); //TODO: validar se eh LDX ou LDY
            args     = getIntFromBus(addressX);
            break;
        case 0b111: 
            addressX = getAbsoluteYIndexedAddress(); //TODO: validar se eh LDX ou LDY
            args     = getIntFromBus(addressX);
            break;
    }
    return args;
}

int8_t Cpu6502::getValueFromPPAdressing(int8_t instruction, int8_t* add){
    ///TODO.
    return 0;
}

int8_t Cpu6502::getValueFromQQAdressing(int8_t instruction, int8_t* add){
    ///TODO.
    return 0;
}

int8_t Cpu6502::getValueFromXAdressing(int8_t instruction, int8_t* add){
    int8_t bk   = 0b00001000; // bitmask para extracao do formato de enderecamento
          *add  = (instruction & bk) >> 3; // extraindo os bits referentes ao formato de enderecamento
    int8_t args = 0b0;

    int16_t addressX; 

    switch(*add){
        case 0b0: 
            addressX = getZeroPageAddress();
            args     = getIntFromBus(addressX);
            break;
        case 0b1: 
            addressX = getAbsoluteAddress();
            args     = getIntFromBus(addressX);
            break;
    }
    return args;
}

int8_t Cpu6502::getValueFromYAdressing(int8_t instruction, int8_t* add){
    int8_t bk   = 0b00100000; // bitmask para extracao do formato de enderecamento
          *add  = (instruction & bk) >> 5; // extraindo os bits referentes ao formato de enderecamento
    int8_t args = 0b0;

    int16_t addressX; 

    switch(*add){
        case 0b0: 
            addressX = getAbsoluteAddress();
            args     = getIntFromBus(addressX);
            break;
        case 0b1: 
            addressX = getIndirectLabelAddress();
            args     = getIntFromBus(addressX);
            break;
    }
    return args;
}

int16_t Cpu6502::getPreIndexedIndirectAddress(){
    int16_t add = this->X;
    add += readRom(this->pc+1);
    return add;
}

int16_t Cpu6502::getPosIndexedIndirectAddress(){
    int16_t add = readRom(this->pc+1);
    add = getIntFromBus(add);
    add += this->Y;
    return add; 
}

int16_t Cpu6502::getZeroPageAddress(){
    int16_t add = readRom(this->pc+1);
    return add;
}

int16_t Cpu6502::getImmediateAddress(){
    return this->pc+1;
}

int16_t Cpu6502::getAbsoluteAddress(){
   int8_t lowAdd = readRom(this->pc+1);
   int8_t HiAdd  = readRom(this->pc+2); 
   
   int16_t add = (HiAdd<<8) + lowAdd;
   return add;
}

int16_t Cpu6502::getZeroPageIndexedAddress(){
    int16_t add = readRom(this->pc+1);
    add += this->X;
    return add; 
}

int16_t Cpu6502::getAbsoluteYIndexedAddress(){
    int8_t lowAdd = readRom(this->pc+1);
   int8_t HiAdd  = readRom(this->pc+2); 
   
   int16_t add = (HiAdd<<8) + lowAdd;
   add += this->Y;
   return add; 
}

int16_t Cpu6502::getAbsoluteXIndexedAddress(){
    int8_t lowAdd = readRom(this->pc+1);
   int8_t HiAdd  = readRom(this->pc+2); 
   
   int16_t add = (HiAdd<<8) + lowAdd;
   add += this->X;
   return add; 
}

int16_t Cpu6502::getIndirectLabelAddress(){
    ///TODO.
    return 0;
}

int8_t Cpu6502::getIntFromBus(int16_t add){
    return 0;
}

#endif //CPU6502_CPP