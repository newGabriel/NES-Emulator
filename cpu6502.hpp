#ifndef CPU6502_HPP
#define CPU6502_HPP

#include <stdint.h>

class Cpu6502{

private:
    int16_t pc;
    int16_t sp; 
    int8_t A;
    int8_t X;
    int8_t Y;
    int8_t P;

    //RAM

    void processInstruction(int8_t instruction);

    void ADC(int8_t instruction);
    void AND(int8_t instruction);
    void ASL(int8_t instruction);
    void BCC(int8_t instruction);
    void BCS(int8_t instruction);
    void BEQ(int8_t instruction);
    void BIT(int8_t instruction);
    void BMI(int8_t instruction);
    void BNE(int8_t instruction);
    void BPL(int8_t instruction);
    void BRK(int8_t instruction);
    void BVC(int8_t instruction);
    void BVS(int8_t instruction);
    void CLC(int8_t instruction);
    void CLD(int8_t instruction);
    void CLI(int8_t instruction);
    void CLV(int8_t instruction);
    void CMP(int8_t instruction);
    void CPX(int8_t instruction);
    void CPY(int8_t instruction);
    void DEC(int8_t instruction);
    void DEX(int8_t instruction);
    void DEY(int8_t instruction);
    void EOR(int8_t instruction);
    void INC(int8_t instruction);
    void INX(int8_t instruction);
    void INY(int8_t instruction);
    void JPM(int8_t instruction);
    void JSR(int8_t instruction);
    void LDA(int8_t instruction);
    void LDX(int8_t instruction);
    void LDY(int8_t instruction);
    void LSR(int8_t instruction);
    void NOP(int8_t instruction);
    void ORA(int8_t instruction);
    void PHA(int8_t instruction);
    void PHP(int8_t instruction);
    void PLA(int8_t instruction);
    void PLP(int8_t instruction);
    void ROL(int8_t instruction);
    void ROR(int8_t instruction);
    void RTI(int8_t instruction);
    void RTS(int8_t instruction);
    void SBC(int8_t instruction);
    void SEC(int8_t instruction);
    void SED(int8_t instruction);
    void SEI(int8_t instruction);
    void STA(int8_t instruction);
    void STX(int8_t instruction);
    void STY(int8_t instruction);
    void TAX(int8_t instruction);
    void TAY(int8_t instruction);
    void TSX(int8_t instruction);
    void TXA(int8_t instruction);
    void TXS(int8_t instruction);
    void TYA(int8_t instruction);

    int8_t getValueFromAAAAdressing(int8_t instruction, int8_t* add);
    int8_t getValueFromBBAdressing (int8_t instruction, int8_t* add);
    int8_t getValueFromBBBAdressing(int8_t instruction, int8_t* add);
    int8_t getValueFromCCAdressing (int8_t instruction, int8_t* add);
    int8_t getValueFromDDDAdressing(int8_t instruction, int8_t* add);
    int8_t getValueFromPPAdressing (int8_t instruction, int8_t* add);
    int8_t getValueFromQQAdressing (int8_t instruction, int8_t* add);
    int8_t getValueFromXAdressing  (int8_t instruction, int8_t* add);
    int8_t getValueFromYAdressing  (int8_t instruction, int8_t* add);

    int16_t getPreIndexedIndirectAddress();
    int16_t getPosIndexedIndirectAddress();
    int16_t getZeroPageIndexedAddress();
    int16_t getAbsoluteXIndexedAddress();
    int16_t getAbsoluteYIndexedAddress();
    int16_t getZeroPageAddress();
    int16_t getImmediateAddress();
    int16_t getIndirectLabelAddress();
    int16_t getAbsoluteAddress();

    int8_t getIntFromBus(int16_t add);

public:
    Cpu6502(/*RAM*/);

    
};

#endif //CPU6502_HPP
