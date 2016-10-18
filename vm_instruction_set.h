#ifndef VM_INSTRUCTION_SET_H
#define VM_INSTRUCTION_SET_H
#include <tchar.h>
#include <string>
#include <vector>
#include <string>
#include <stdint.h>
#include <unordered_map>
#include "types.h"

type_handler POP32_REG{ "POP_32 R", "3 4", "MOV EDX, [EBP+0x0]", "ADD EBP, 0x4", "MOV [EAX+EDI], EDX" };
type_handler PUSH32_INT{ "PUSH_32 ", "2 1", "SUB EBP, 0x4", "MOV [EBP+0x0], EAX" };
type_handler ADD_N2_N1{ "ADD N2, N1", "", "MOV EAX, [EBP+0x0]", "ADD [EBP+0x4], EAX" };
type_handler PUSH32_REG{ "PUSH_32 R", "1 4", "MOV EDX, [EAX+EDI]", "SUB EBP, 0x4", "MOV [EBP+0x0], EDX" };
type_handler NOR32_N2_N1{ "NOR_32 N2, N1 ;CF", "", "MOV EAX, [EBP+0x0]", "MOV EDX, [EBP+0x4]", "NOT EAX", "NOT EDX", "AND EAX, EDX", "MOV [EBP+0x4], EAX" };
type_handler FETCH_32_N1{ "FETCH32 N1", "", "MOV EAX, [EBP+0x0]", "MOV EAX, [EAX]", "MOV [EBP+0x0], EAX" };
type_handler FETCH_32_N1_V2{ "FETCH32 N1", "", "MOV EAX, [EBP+0x0]", "MOV EAX, [SS:EAX]", "MOV [EBP+0x0], EAX" };
type_handler FETCH_N1_N2{ "MOV [N1], N2 //destroy both", "", "MOV EAX, [EBP+0x0]", "MOV EDX, [EBP+0x4]", "ADD EBP, 0x8", "MOV [SS:EAX], EDX" };
type_handler MOV_N1_WN2{ "MOV [N1], WORD N2", "", "MOV EAX, [EBP+0x0]", "MOV DX, [EBP+0x4]", "ADD EBP, 0x6", "MOV [SS:EAX], DX" };
type_handler NOR_16{ "NOR_16 ;CF", "", "MOV AX, [EBP+0x0]", "MOV DX, [EBP+0x2]", "NOT AL", "NOT DL", "SUB EBP, 0x2", "AND AL, DL", "MOV [EBP+0x4], AX" };
type_handler POP_16{ "POP_16 r", "3 4", "MOV DX, [EBP+0x0]", "ADD EBP, 0x2", "MOV [EAX+EDI], DX" };
type_handler PUSH_8{ "PUSH_8 r", "1 4", "MOV AL, [EAX+EDI]", "SUB EBP, 0x2", "MOV [EBP+0x0], AX" };
type_handler POP_8{ "POP_8 r", "3 4", "MOV DX, [EBP+0x0]", "ADD EBP, 0x2", "MOV [EAX+EDI], DL" };
type_handler PUSH_16{ "PUSH_16 r", "1 4", "MOV AX, [EAX+EDI]", "SUB EBP, 0x2", "MOV [EBP+0x0], AX" };
type_handler SHR_8{ "SHR BYTE N1, BYTE N2 ;CF", "", "MOV AL, [EBP+0x0]", "MOV CL, [EBP+0x2]", "SUB EBP, 0x2", "SHR AL, CL", "MOV [EBP+0x4], AX" };
type_handler SHL_8{ "SHL BYTE N1, BYTE N2 ;CF", "", "MOV AL, [EBP+0x0]", "MOV CL, [EBP+0x2]", "SUB EBP, 0x2", "SHL AL, CL", "MOV [EBP+0x4], AX" };
type_handler PUSH_INT_16{ "PUSH_16 ", "2 1", "SUB EBP, 0x2", "MOV [EBP+0x0], AX" };
type_handler FETCH_16{ "FETCH_16", "", "MOV EAX, [EBP+0x0]", "ADD EBP, 0x2", "MOV AX, [SS:EAX]", "MOV [EBP+0x0], AX" };
type_handler FETCH_16_2{ "FETCH_16", "", "MOV EAX, [EBP+0x0]", "ADD EBP, 0x2", "MOV AX, [EAX]", "MOV [EBP+0x0], AX" };
type_handler ADD_16{ "ADD WORD N2, WORD N1", "", "MOV AX, [EBP+0x0]", "SUB EBP, 0x2", "ADD [EBP+0x4], AX" };
type_handler NAND_N1{ "NAND WORD N1, WORD N2 ;CF", "", "NOT DWORD [EBP+0x0]", "MOV AX, [EBP+0x0]", "SUB EBP, 0x2", "AND [EBP+0x4], AX" };
type_handler SHR_N1_B_N2{ "SHR N1, BYTE N2", "", "MOV EAX, [EBP+0x0]", "MOV CL, [EBP+0x4]", "SUB EBP, 0x2", "SHR EAX, CL", "MOV [EBP+0x4], EAX" };
type_handler SHL_N1_B_N2{ "SHL N1, BYTE N2", "", "MOV EAX, [EBP+0x0]", "MOV CL, [EBP+0x4]", "SUB EBP, 0x2", "SHL EAX, CL", "MOV [EBP+0x4], EAX" };
type_handler JUMP{ "JUMP N1+N2 ", "", "MOV ESI, [EBP+0x0]", "ADD EBP, 0x4", "ADD ESI, [EBP+0x0]" };
type_handler ADD_8{ "ADD BYTE N1, BYTE N2 ;CF", "", "MOV AL, [EBP+0x0]", "SUB EBP, 0x2", "ADD [EBP+0x4], AL" };
type_handler ADD_STACK{ "ADD STACK, 4", "", "ADD EBP, 0x4" };
type_handler MOV_WN2_N1{ "MOV WORD N2, BYTE: [N1] ;stack +2", "", "MOV EDX, [EBP+0x0]", "ADD EBP, 0x2", "MOV AL, [SS:EDX]", "MOV [EBP+0x0], AX" };
type_handler SHR_WN1_BN2{ "SHR WORD N1, BYTE N2", "", "MOV AX, [EBP+0x0]", "MOV CL, [EBP+0x2]", "SUB EBP, 0x2", "SHR AX, CL", };
type_handler SHL_WN1_BN2{ "SHL WORD N1, BYTE N2", "", "MOV AX, [EBP+0x0]", "MOV CL, [EBP+0x2]", "SUB EBP, 0x2", "SHL AX, CL", };
type_handler FETCH_8_N1{ "FETCH_8 N1", "", "MOV EDX, [EBP+0x0]", "ADD EBP, 0x2", "MOV AL, [EDX]", "MOV [EBP+0x0], AX" };
type_handler TIME_STAMP{ "TIME_STAMP", "", "RDTSC ", "SUB EBP, 0x8", "MOV [EBP+0x0], EDX", "MOV [EBP+0x4], EAX" };
type_handler DIVIDE{ "DIVIDE WORD N3 ;CF", "", "MOV DX, [EBP+0x0]", "MOV AX, [EBP+0x2]", "MOV CX, [EBP+0x4]", "SUB EBP, 0x2", "DIV CX", "MOV [EBP+0x4], DX", "MOV [EBP+0x6], AX" };
type_handler SHL_64{ "SHL_64 <N1,N2>, BYTE N3", "", "MOV EAX, [EBP+0x0]", "MOV EDX, [EBP+0x4]", "MOV CL, [EBP+0x8]", "ADD EBP, 0x2", "SHLD EAX, EDX, CL", "MOV [EBP+0x4], EAX" };
type_handler SHR_64{ "SHR_64 <N1,N2>, BYTE N3", "", "MOV EAX, [EBP+0x0]", "MOV EDX, [EBP+0x4]", "MOV CL, [EBP+0x8]", "ADD EBP, 0x2", "SHRD EAX, EDX, CL", "MOV [EBP+0x4], EAX" };
type_handler MUL_16{ "MUL WORD N1, WORD N2 ;CF", "", "MOV DX, [EBP+0x0]", "MOV AX, [EBP+0x2]", "SUB EBP, 0x4", "MUL DX", "MOV [EBP+0x4], DX", "MOV [EBP+0x6], AX" };
type_handler MUL_32{ "MUL N1, N2","","MOV EDX, [EBP+0x0]", "MOV EAX, [EBP+0x4]", "SUB EBP, 0x4", "IMUL EDX", "MOV [EBP+0x4], EDX", "MOV [EBP+0x8], EAX" };
type_handler DIV_32{ "DIV N3", "", "MOV EDX, [EBP+0x0]", "MOV EAX, [EBP+0x4]", "DIV DWORD [EBP+0x8]", "MOV [EBP+0x4], EDX", "MOV [EBP+0x8], EAX" };
type_handler IDIV_32{ "IDIV N3", "", "MOV EDX, [EBP+0x0]", "MOV EAX, [EBP+0x4]", "IDIV DWORD [EBP+0x8]", "MOV [EBP+0x4], EDX", "MOV [EBP+0x8], EAX" };
type_handler MOV_STACK{ "MOV STACK, N1", "", "MOV EBP, [EBP+0x0]" };
type_handler MACHINE_ENTER{ "VM_OUTSIDE", "", "MOV ESP, EBP" };

std::vector<type_handler> good_handlers{ SHR_64, IDIV_32, MOV_STACK, MUL_32, DIV_32, SHL_8, MUL_16, SHL_64, SHL_WN1_BN2, DIVIDE, SHL_N1_B_N2, TIME_STAMP, FETCH_8_N1, SHR_WN1_BN2, MOV_WN2_N1, ADD_8, JUMP, SHR_N1_B_N2, NAND_N1, ADD_16, FETCH_16_2, FETCH_16, PUSH_INT_16, SHR_8, POP_8, PUSH_16, PUSH_8, POP_16, POP32_REG, PUSH32_INT, ADD_N2_N1, PUSH32_REG, NOR32_N2_N1, FETCH_32_N1, FETCH_32_N1_V2, FETCH_N1_N2, MOV_N1_WN2, NOR_16, MACHINE_ENTER, ADD_STACK };
std::unordered_map<uint32_t, hashmap> hashtable;


#endif // VM_INSTRUCTION_SET_H

