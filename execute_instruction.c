// Written by z5191493
// If you use C library functions add includes here.

#include "emu.h"
#include "ram.h"
#include "registers.h"
#include <limits.h>
#include <ctype.h>
// Definition of the instruction code
#define ADD 1
#define ADDU 2
#define SUB 3
#define MUL 4
#define AND 5
#define OR 6
#define XOR 7
#define SLLV 8
#define SRLV 9
#define SLT 10
#define ADDI 11
#define ANDI 12
#define ORI 13
#define XORI 14
#define SLL 15
#define SRL 16
#define SLTI 17
#define LUI 18
#define LB 19
#define LH 20
#define LW 21
#define SB 22
#define SH 23
#define SW 24
#define BEQ 25
#define BNE 26
#define BLEZ 27
#define BGTZ 28
#define BLTZ 29
#define BGEZ 30
#define J 31
#define JAL 32
#define JR 33
#define SYSTEMCALL 34


// Shifting bit size
#define SHIFT_26 26
#define SHIFT_21 21
#define SHIFT_16 16
#define SHIFT_11 11
#define SHIFT_6 6

// Mask definition
#define MASK_5 0x1F
#define MASK_7 0x3F
#define MASK_8 0xFF
#define MASK_11 0x7FF
#define MASK_16 0xFFFF
#define MASK_21 0x1FFFFF
#define MASK_26 0x3FFFFFF
#define MASK_32 0xF0000000
#define NEG_MASK_8 0xFFFFFF00
#define NEG_MASK_16 0xFFFF0000

// Constant definition
#define B_2 0b10
#define B_3 0b11
#define B_4 0b100
#define B_5 0b101
#define B_6 0b110
#define B_7 0b111
#define B_8 0b1000
#define B_10 0b1010
#define B_12 0b1100
#define B_13 0b1101
#define B_14 0b001110
#define B_32 0b100000
#define B_33 0b100001
#define B_34 0b100010
#define B_35 0b100011
#define B_36 0b100100
#define B_37 0b100101
#define B_38 0b100110
#define B_40 0b101000
#define B_41 0b101001
#define B_42 0b101010
#define B_43 0b101011
#define B_480 0b111100000



//Declaration of my own function
static int32_t extract_op(uint32_t instruction);
static int32_t extract_op_11(uint32_t instruction);
static int8_t extract_s(uint32_t instruction);
static int8_t extract_b(uint32_t instruction);
static int8_t extract_t(uint32_t instruction);
static int8_t extract_d(uint32_t instruction);
static int16_t extract_I_16(uint32_t instruction);
static int8_t extract_I_5(uint32_t instruction);
static int16_t extract_O(uint32_t instruction);
static int32_t extract_X(uint32_t instruction);
static int32_t extract_end_21(uint32_t instruction);
static int32_t extract_end_6(uint32_t instruction);
static int32_t extract_len_11(uint32_t instruction);
static int execute(uint32_t instruction);

/**
 * execute a MIPS instruction
 *
 * This function should:
 *
 * get register values by calling `get_register(register_type register_number)`
 * change registers by calling `set_register(register_type register_number, uint32_t value)`
 *
 * get memory values by `calling get_byte(uint32_t address)`
 * changes memory by `set_byte(uint32_t address, uint8_t value)`
 *
 * updates program_counter to address of next instruction
 *
 * returns 1 if an exit syscall is executed, 0 otherwise
 */
 
 
int execute_instruction(uint32_t instruction, uint32_t *program_counter) {

    // Set Register Part: ADD
    if (execute(instruction) == ADD) {
        uint32_t s = get_register(extract_s(instruction));
        uint32_t t = get_register(extract_t(instruction));
        uint32_t d = extract_d(instruction);
        uint32_t sum = s + t;
        set_register(d, sum);
        
        // Set Register Part: ADDU
    } else if (execute(instruction) == ADDU) {
        uint32_t s = get_register(extract_s(instruction));
        uint32_t t = get_register(extract_t(instruction));
        uint32_t d = extract_d(instruction);
        uint32_t addu = s + t;
        set_register(d, addu);
        
        // Set Register Part: SUB
    } else if (execute(instruction) == SUB) { 
        uint32_t s = get_register(extract_s(instruction));
        uint32_t t = get_register(extract_t(instruction));
        uint32_t d = extract_d(instruction);
        uint32_t sub = s - t;
        set_register(d, sub);
        
        // Set Register Part: MUL
    } else if (execute(instruction) == MUL) { 
        uint32_t s = get_register(extract_s(instruction));
        uint32_t t = get_register(extract_t(instruction));
        uint32_t d = extract_d(instruction);
        uint32_t mul = s * t;
        set_register(d, mul);

        // Set Register Part: AND
    } else if (execute(instruction) == AND) { 
        uint32_t s = get_register(extract_s(instruction));
        uint32_t t = get_register(extract_t(instruction));
        uint32_t d = extract_d(instruction);
        int32_t and = (int32_t)s & (int32_t)t;
        set_register(d, and);

        // Set Register Part: OR
    } else if (execute(instruction) == OR) { 
        uint32_t s = get_register(extract_s(instruction));
        uint32_t t = get_register(extract_t(instruction));
        uint32_t d = extract_d(instruction);
        int32_t or = (int32_t)s | (int32_t)t;
        set_register(d, or);
        
        // Set Register Part: XOR
    } else if (execute(instruction) == XOR)  { 
        uint32_t s = get_register(extract_s(instruction));
        uint32_t t = get_register(extract_t(instruction));
        uint32_t d = extract_d(instruction);
        uint32_t xor = (int32_t)s ^ (int32_t)t;
        set_register(d, xor);
        
        // Set Register Part: SLLV
    } else if (execute(instruction) == SLLV) { 
        uint32_t s = get_register(extract_s(instruction));
        uint32_t t = get_register(extract_t(instruction));
        uint32_t d = extract_d(instruction);
        uint32_t sllv = s << t;
        set_register(d, sllv);
        
        // Set Register Part: SRLV
    } else if (execute(instruction) == SRLV) { 
        uint32_t s = get_register(extract_s(instruction));
        uint32_t t = get_register(extract_t(instruction));
        uint32_t d = extract_d(instruction);
        uint32_t srlv = s >> t;
        set_register(d, srlv);
        
        // Set Register Part: SLT
    } else if (execute(instruction) == SLT) {
        uint32_t s = get_register(extract_s(instruction));
        uint32_t t = get_register(extract_t(instruction));
        uint32_t d = extract_d(instruction);
        uint32_t slt = ((int32_t)s < (int32_t)t);
        set_register(d, slt);
        
        // Set Register Part: ADDI
    } else if (execute(instruction) == ADDI)  {
        uint32_t s = get_register(extract_s(instruction));
        int32_t I = extract_I_16(instruction);
        uint32_t t = extract_t(instruction);
        int32_t addi = (int32_t)s + (int32_t)I;
        set_register(t, addi);
        
        // Set Register Part: ANDI
    } else if (execute(instruction) == ANDI)   {
        uint32_t s = get_register(extract_s(instruction));
        uint32_t I = extract_I_16(instruction);
        int32_t t = extract_t(instruction);
        int32_t andi = (int32_t)s & (int32_t)I;
        set_register(t, andi);
        
        // Set Register Part: ORI
    } else if (execute(instruction) == ORI)  {
        uint32_t s = get_register(extract_s(instruction));
        uint32_t t = extract_t(instruction);
        uint32_t I = extract_I_16(instruction);
        int32_t ori = (s | I);
        set_register(t, ori);
        
        // Set Register Part: XORI
    } else if (execute(instruction) == XORI)  {
        uint32_t s = get_register(extract_s(instruction));
        uint32_t t = extract_t(instruction);
        int32_t I = extract_I_16(instruction);
        int32_t xori = ((int32_t)s ^ (int32_t)I);
        set_register(t, xori);
        
        // Set Register Part: SLL
    } else if (execute(instruction) == SLL)  {
        uint32_t t = get_register(extract_t(instruction));
        int32_t I = extract_I_5(instruction);
        uint32_t d = extract_d(instruction);
        uint32_t sll = t << I;
        set_register(d, sll);
        
        // Set Register Part: SRL
    } else if (execute(instruction) == SRL)  {
        uint32_t t = get_register(extract_t(instruction));
        int32_t I = extract_I_5(instruction);
        uint32_t d = extract_d(instruction);
        uint32_t srl = t >> I;
        set_register(d, srl);
        
        // Set Register Part: SLTI
    } else if (execute(instruction) == SLTI)  {
        uint32_t s = get_register(extract_s(instruction));
        uint32_t I = extract_I_16(instruction);
        uint32_t t = extract_t(instruction);
        uint32_t slti = ((int32_t)s < (int32_t)I);
        set_register(t, slti);
        
        // Set Register Part: LUI
    } else if (execute(instruction) == LUI)  {
        uint32_t I = extract_I_16(instruction);
        uint32_t t = extract_t(instruction);
        uint32_t lui = (I << 16);
        set_register(t, lui);
        
        // Set Register Part: LB
    } else if (execute(instruction) == LB)  {
        uint32_t b = get_register(extract_b(instruction));
        int32_t O = extract_O(instruction);
        uint32_t t = extract_t(instruction);
        int32_t tem = (uint32_t) get_byte(b + O);
        if ((tem >> 7) == 1) {
            tem = tem | NEG_MASK_8;
        }
        set_register(t, tem);
        
        // Set Register Part: LH
    } else if (execute(instruction) == LH)  {
        uint32_t b = get_register(extract_b(instruction));
        int32_t O = extract_O(instruction);
        uint32_t t = extract_t(instruction);
        int32_t tem = get_byte(b + O);
        tem = ((uint32_t) get_byte(b + O + 1) << 8) | tem;
        if ((tem >> 15) == 1) {
            tem = tem | NEG_MASK_16;
        }
        set_register(t, tem);
        
        // Set Register Part: LW
    } else if (execute(instruction) == LW)  {
        uint32_t b = get_register(extract_b(instruction));
        int32_t O = extract_O(instruction);
        uint32_t t = (extract_t(instruction));
        int32_t tem = get_byte(b + O);
        tem = ((uint32_t) get_byte(b + O + 1) << 8) | tem;
        tem = ((uint32_t) get_byte(b + O + 2) << 16) | tem;
        tem = ((uint32_t) get_byte(b + O + 3) << 24) | tem;
        set_register(t, tem);
        
        // Set Byte Part: SB
    } else if (execute(instruction) == SB)  {
        uint32_t b = get_register(extract_b(instruction));
        int32_t O = extract_O(instruction);
        uint32_t t = get_register(extract_t(instruction));
        set_byte(b+O, t & MASK_8);
      
        // Set Byte Part: SH
    } else if (execute(instruction) == SH)  {
        uint32_t b = get_register(extract_b(instruction));
        int32_t O = extract_O(instruction);
        uint32_t t = get_register(extract_t(instruction));
        set_byte(b + O, t & MASK_8);
        set_byte(b + O + 1, (t >> 8) & MASK_8);
        
        // Set Byte Part: SW
    } else if (execute(instruction) == SW) { 
        uint32_t b = get_register(extract_b(instruction));
        int32_t O = extract_O(instruction);
        uint32_t t = get_register(extract_t(instruction));
        
        set_byte(b + O, t);
        set_byte(b + O + 1, (t >> 8) & MASK_8);
        set_byte(b + O + 2, (t >> 16) & MASK_8);
        set_byte(b + O + 3, (t >> 24) & MASK_8);
    }
    
    // Branch Part: BEQ
    if (execute(instruction) == BEQ) {
        // Extract immediate, rs and rt
        int32_t I = extract_I_16(instruction);
        uint32_t s = get_register(extract_s(instruction));
        uint32_t t = get_register(extract_t(instruction));
        
        // Compare the value of s and t
        if (s == t) {
            (*program_counter) += (int32_t)((uint32_t)I << 2);
        } else {
            (*program_counter) += 4;
        }
        
        // Branch Part: BEQ
    } else if (execute(instruction) == BNE) {
        // Extract immediate, rs and rt
        uint32_t I = extract_I_16(instruction);
        int32_t s = get_register(extract_s(instruction));
        int32_t t = get_register(extract_t(instruction));

        // Compare the value of s and t
        if (s != t) {
            (*program_counter) += (int32_t)((uint32_t)I << 2);
        } else {
            (*program_counter) += 4;
        }
        // Branch Part: BLEZ
    } else if (execute(instruction) == BLEZ) {
        uint32_t I = extract_I_16(instruction);
        int32_t s = get_register(extract_s(instruction));

        if (s <= 0) {
            (*program_counter) += (int32_t)((uint32_t)I << 2);
        } else {
            (*program_counter) += 4;
        }
        // Branch Part: BGTZ
    } else if (execute(instruction) == BGTZ) {
        uint32_t I = extract_I_16(instruction);
        int32_t s = get_register(extract_s(instruction));

        if (s > 0) {
            (*program_counter) += (int32_t)((uint32_t)I << 2);
        } else {
            (*program_counter) += 4;
        }
        // Branch Part: BLTZ
    } else if (execute(instruction) == BLTZ) {

        int32_t I = extract_I_16(instruction);
        int32_t s = get_register(extract_s(instruction));
        if (s < 0) {
            (*program_counter) += (int32_t)((uint32_t)I << 2);
        } else {
            (*program_counter) += 4;
        }
        // Branch Part: BGEZ
    } else if (execute(instruction) == BGEZ) {
        int32_t I = extract_I_16(instruction);
        int32_t s = get_register(extract_s(instruction));
        if (s >= 0) {
            (*program_counter) += (int32_t)((uint32_t)I << 2);
        } else {
            (*program_counter) += 4;
        }
 
        // Jump Part: J
    } else if (execute(instruction) == J) {
        uint32_t X = extract_X(instruction);
        uint32_t res = ((*program_counter) & MASK_32);
        (*program_counter) = (res | ((int32_t)X << 2)); 
        
        // Jump Part: JAL
    } else if (execute(instruction) == JAL) {
        uint32_t X = extract_X(instruction);
        uint32_t b = (*program_counter) + 4;
        set_register(ra, b);
        uint32_t res = ((*program_counter) & MASK_32);
        (*program_counter) = (res | (X << 2)); 

        // Jump Part: JR
    } else if (execute(instruction) == JR) {
        uint32_t s = get_register(extract_s(instruction));
        (*program_counter) = s;
        
        // SYSTEM CALL Part
    } else if (execute(instruction) == SYSTEMCALL) {

        //print integer
        //$a0 = integer to print 
        if (get_register(v0) == 1) {
            printf("%d", get_register(a0));
            
            //print string
            //$a0 = address of NUL-terminated string to print 
        } else if (get_register(v0) == 4) {
            int i = 0;
            while (get_byte(get_register(a0) + i) != '\0') {
                fputc(get_byte(get_register(a0) + i), stdout);
                i++;
            }
            //read integer
        } else if (get_register(v0) == 5) {
            int32_t read;
            scanf("%d", &read);
            if (read > INT_MAX) {
                set_register(v0, INT_MAX);
            } else {
                set_register(v0, read);
            }
            //read string
        } else if (get_register(v0) == 8) {
            int max = get_register(a1) - 1;
            int read[max + 1];
            int i = 0;
            read[i] = fgetc(stdin);
            while (i < max) {
                set_byte(get_register(a0) + i, read[i]);
                if (read[i] == EOF || read[i] == '\n') break;
                i++;
                read[i] = fgetc(stdin);
            }
            if (i < max) {
                for(; i >= max; i++) {
                    set_byte(get_register(a0) + i, '\0');
                }
            }
            //exit
        } else if (get_register(v0) == 10) {
            return 1;
            //print character
        } else if (get_register(v0) == 11) {
            printf("%c", get_register(a0));
            //read character
        } else if (get_register(v0) == 12) {
            char read;
            scanf("%c", &read);
            set_register(v0, read);
        }
        //PC = PC + 4
        (*program_counter) += 4;
        
    } else {
        (*program_counter) += 4;
    }
    return 0;
}

//give the code of the instruction 
int execute(uint32_t instruction){
    int32_t op = extract_op(instruction);
    int32_t op_11 = extract_op_11(instruction);
    int32_t t = extract_t(instruction);
    int32_t end_21 = extract_end_21(instruction);
    int32_t end_6 = extract_end_6(instruction);
    int32_t len_11 = extract_len_11(instruction);
    
    
    if (op == 0 && len_11 == B_32) return ADD;
    else if (op == 0 && len_11 == B_33) return ADDU;
    else if (op == 0 && len_11 == B_34) return SUB;
    else if (op == 0b011100 && len_11 == B_2) return MUL;
    else if (op == 0 && len_11 == B_36) return AND;
    else if (op == 0 && len_11 == B_37) return OR;
    else if (op == 0 && len_11 == B_38) return XOR;
    else if (op == 0 && len_11 == B_4) return SLLV;
    else if (op == 0 && len_11 == B_6) return SRLV;
    else if (op == 0 && len_11 == B_42) return SLT;
    else if (op == B_8) return ADDI;
    else if (op == B_12) return ANDI;
    else if (op == B_13) return ORI;
    else if (op == B_14) return XORI;
    else if (op_11 == 0 && end_6 == 0) return SLL;
    else if (op_11 == 0 && end_6 == B_2) return SRL;
    else if (op == B_10) return SLTI;
    else if (op_11 == B_480) return LUI;
    else if (op == B_32) return LB;
    else if (op == B_33) return LH;
    else if (op == B_35) return LW;
    else if (op == B_40) return SB;
    else if (op == B_41) return SH;
    else if (op == B_43) return SW;
    else if (op == B_4) return BEQ;
    else if (op == B_5) return BNE;
    else if (op == B_6) return BLEZ;
    else if (op == B_7) return BGTZ;
    else if (op == 1 && t == 0) return BLTZ;
    else if (op == 1 && t == 1) return BGEZ;
    else if (op == B_2) return J;
    else if (op == B_3) return JAL;
    else if (op == 0 && (end_21 == 8)) return JR;
    else return SYSTEMCALL;
}
//extract the first five from the left hand side of opcode
int32_t extract_op(uint32_t instruction) {
    int32_t op = (instruction >> SHIFT_26) & MASK_7;
    return op;
}
//extract the first eleven from the left hand side of opcode
int32_t extract_op_11(uint32_t instruction) {
    int32_t op_11 = (instruction >> SHIFT_21) & MASK_11;
    return op_11;
}
//extract rs part from the opcode
int8_t extract_s(uint32_t instruction) {
    int32_t s = (instruction >> SHIFT_21) & MASK_5;
    return s;
}
//extract rb part from the opcode
int8_t extract_b(uint32_t instruction) {
    int32_t b = (instruction >> SHIFT_21) & MASK_5;
    return b;
}
//extract rt part from the opcode
int8_t extract_t(uint32_t instruction) {
    int32_t t = (instruction >> SHIFT_16) & MASK_5;
    return t;
}
//extract base register field part from the opcode
int8_t extract_d(uint32_t instruction) {
    int32_t d = (instruction >> SHIFT_11) & MASK_5;
    return d;
}
//extract immediate (16bits) part from the opcode
int16_t extract_I_16(uint32_t instruction) {
    int16_t I_16 = instruction & MASK_16;
    return I_16;
}
//extract immediate (5bits) part from the opcode
int8_t extract_I_5(uint32_t instruction) {
    int32_t I_5 = (instruction >> SHIFT_6) & MASK_5;
    return I_5;
}
//extract Offset immediate part from the opcode
int16_t extract_O(uint32_t instruction) {
    int32_t O = instruction & MASK_16;
    return O;
}
//extract immediate in hex part from the opcode
int32_t extract_X(uint32_t instruction) {
    int32_t X = instruction & MASK_26;
    return X;
}
//extract first 21 bits from the right hand side of the opcode
int32_t extract_end_21(uint32_t instruction) {
    int32_t end_21 = instruction & MASK_21;
    return end_21;
}
//extract first 6 bits from the right hand side of the opcode;
int32_t extract_end_6(uint32_t instruction) {
    int32_t end_6 = instruction & MASK_7;
    return end_6;
}
//extract first 11 bits from the right hand side of the opcode;
int32_t extract_len_11(uint32_t instruction) {
    int32_t len_11 = instruction & MASK_11; 
    return len_11;
}
