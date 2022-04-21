#include "spimcore.h"


/* ALU */
/* 10 Points */
void ALU(unsigned A,unsigned B,char ALUControl,unsigned *ALUresult,char *Zero)
{
  // using a pointer, so need a varialble for ALUresult to actually point too
  unsigned result; 
  // this whole switch case implments the operations
  switch (ALUControl) // will take in the char of the ALUControl
  {
    case 0: result = A + B; 
      break; 
    case 1: result = A - B; 
      break; 
    case 2: // could do a different function for this? 
      if((int)A< (int)B) // will wrk bc A & B are unsigned INTEGERS
        result = 1; 
      else 
         result = 0; 
      
      break; 
    case 3: 
      if(A < B)
        result = 1; 
      else
        result = 0;
      break; 
    case 4: 
      result = (A & B); 
      break; 
    case 5: result = (A | B);
      break; 
    case 6: // incorrect, needs to merge 16? 
      if((int)A < 0) 
        result = 1; 
      else
        result = 0;
      break; 
    case 7: 
      result = ~A;// if not case A
      break; 
  }
  *ALUresult = result; // now we can point the pointer to the variable result
  // ^^ outputs result(Z) to ALUtresult
  // assign zero to one if the reuslt is 0, or assign 0
  
  if(result ==0)
    *Zero = 1; // hope this is okay to point pointer to direct value, been a while
  else
    *Zero = 0; 

}

/* instruction fetch */
/* 10 Points */
int instruction_fetch(unsigned PC,unsigned *Mem,unsigned *instruction)
{
  // return 1 if halt condition occurs, hopefully PC conditions are correct
  if(PC > 65535 | PC & 0x3) 
    return 1; 
  // fetch instruction addressed by PC from Mem
  *instruction = *Mem[ PC >> 2]; // should Mem not have " * "? 
    return 0; // no halt

}


/* instruction partition */
/* 10 Points */
void instruction_partition(unsigned instruction, unsigned *op, unsigned *r1,unsigned *r2, unsigned *r3, unsigned *funct, unsigned *offset, unsigned *jsec)
{
  *op = (instruction >> 26) & 0x0000003f; 
  *r1 = (instruction >> 21) & 0x0000001F; 
  *r2 = (instruction >> 16) & 0x0000001F; 
  *r3 = (instruction >> 11) & 0x0000001F; 
  *funct = instruction & 0x0000003f; 
  *offset = instruction & 0x0000FFFF;
  *jsec = instruction & 0x03FFFFFF;

}



/* instruction decode */
/* 15 Points */
int instruction_decode(unsigned op,struct_controls *controls)
{
  switch(op)
  {
      case 0x00: 
        controls -> RegDst = 1; 
        controls -> Jump = 0; 
       `controls -> Branch = 0; 
        controls -> MemRead= 0; 
        controls -> MemtoReg = 0;
        controls -> ALUOp = 7; 
        controls -> MemWrite = 0; 
       controls -> ALUSrc = 0; 
       controls -> RegWrite = 1; 
        break; 
      case 0x0d:  // OR immediate field
        controls -> RegDst = 0; 
        controls -> Jump = 0; 
       `controls -> Branch = 0; 
        controls -> MemRead= 0; 
        controls -> MemtoReg = 0;
        controls -> ALUOp = 5; 
        controls -> MemWrite = 0; 
       controls -> ALUSrc = 1; 
       controls -> RegWrite = 1; 
        break; 
      case 0x23: 
        controls -> RegDst = 0; 
        controls -> Jump = 0; 
       `controls -> Branch = 0; 
        controls -> MemRead= 1; 
        controls -> MemtoReg = 1;
        controls -> ALUOp = 0; 
        controls -> MemWrite = 0;  
       controls -> ALUSrc = 1; 
       controls -> RegWrite = 1; 
        break; 
      case 0x2b: // store
        controls -> RegDst = 2; 
        controls -> Jump = 0; 
       `controls -> Branch = 0; 
        controls -> MemRead= 0; 
        controls -> MemtoReg = 2;
        controls -> ALUOp = 0; 
        controls -> MemWrite = 1; 
       controls -> ALUSrc = 1; 
       controls -> RegWrite = 1; 
        break; 
      case 0x0a: // set less than immdt 
        controls -> RegDst = 0; 
        controls -> Jump = 0; 
       `controls -> Branch = 0; 
        controls -> MemRead= 0; 
        controls -> MemtoReg = 0;
        controls -> ALUOp = 2; 
        controls -> MemWrite = 0; 
       controls -> ALUSrc = 1; 
       controls -> RegWrite = 1; 
        break; 
    case 0x04: // branch:  on = 1, equal comparator used, ALUrc will also be 1
      controls -> RegDst = 2; 
        controls -> Jump = 0; 
       `controls -> Branch = 1; 
        controls -> MemRead= 0; 
        controls -> MemtoReg = 2;
        controls -> ALUOp = 0; 
        controls -> MemWrite = 0; 
       controls -> ALUSrc = 1; 
       controls -> RegWrite = 0; 
        break; 
    case 0x01: // brach >=0, branch 1 again ALUrc will be 1 
      controls -> RegDst = 0; 
        controls -> Jump = 0; 
       `controls -> Branch = 1; 
        controls -> MemRead= 0; 
        controls -> MemtoReg = 0;
        controls -> ALUOp = 6; 
        controls -> MemWrite = 0; 
       controls -> ALUSrc = 1; 
       controls -> RegWrite = 0; 
        break; 
    case 0x02: // jump case, 
      controls -> RegDst = 2; 
        controls -> Jump = 1; 
       `controls -> Branch = 2; 
        controls -> MemRead= 2; 
        controls -> MemtoReg = 2;
        controls -> ALUOp = 0; 
        controls -> MemWrite = 0; 
       controls -> ALUSrc = 2; 
       controls -> RegWrite = 0; 
        break; 
      
    default: return 1; // 1 will halt
  }
  return 0; // no halt

}

/* Read Register */
/* 5 Points */
void read_register(unsigned r1,unsigned r2,unsigned *Reg,unsigned *data1,unsigned *data2)
{
  // puts values of r2/r1 into the pointer data1/data2
  *data1 = Reg[r1];
  *data2 = Reg[r2];

}


/* Sign Extend */
/* 10 Points */
void sign_extend(unsigned offset,unsigned *extended_value)
{
  if(offset & 0x00008000)// checks 16th bit of offset
  {
    *extended_value = offset | 0xffff0000; // turns into negative value
  }
  else 
  {
    *extended_value = offset;
  }

}

/* ALU operations */
/* 10 Points */
int ALU_operations(unsigned data1,unsigned data2,unsigned extended_value,unsigned funct,char ALUOp,char ALUSrc,unsigned *ALUresult,char *Zero)
{
  if(ALUSrc == 0) // determined by ALUSrc, this is for r-type
  { // supposed to be based off funct &  ALUOp
    // more outcomes for ALUSrc, so will make case statement for that
    swtich(funct)
    {
      case 0x21: ALUOp = 0; // addition
        break; 
      case 0x23: ALUOp = 1;  // subtraction
        break; 
      case 0x24: ALUOp = 4; // AND 
        break; 
      case 0x2a: ALUOp = 2; // less than
        break;
      case 0x2b: ALUOp = 3; // unsigned less than
        break; 
      default: return 1; // idk whatever else it could be, unknown
    }
    ALU(data1, data2, ALUOp, ALUresult, Zero);
    
  }
  
  if(ALUSrc == 1) // I-type, operation will be immediate, witch data2
  {
    ALU(data1, extended_value, ALUOp, ALUresult, Zero); 
  }
  return 0; 
}

/* Read / Write Memory */
/* 10 Points */
int rw_memory(unsigned ALUresult,unsigned data2,char MemWrite,char MemRead,unsigned *memdata,unsigned *Mem)
{
  if((MemWrite == 1 || MemRead == 1) && ALUresult %4 != 0)
      return 1; // halt
  if(MemWrite == 1 && MemRead == 0)
    Mem[ALUresult >> 2] = data2; // set ALUresult memory to data2, stores wrd
  if(MemWrite == 0 && MemRead == 1)
    *memdata = Mem[ALUresult >> 2]; // set memory data AlUresult with shifted 2-bits, loads wrd
  
  return 0; 

}


/* Write Register */
/* 10 Points */
void write_register(unsigned r2,unsigned r3,unsigned memdata,unsigned ALUresult,char RegWrite,char RegDst,char MemtoReg,unsigned *Reg)
{
  if(RegWrite == 1)
  {
    if(MemtoReg == 1)
    {
     if( RegDst == 1)
       Reg[r3] = memdata; // r3 is rd
      else
        Reg[r2] = memdata; // r2 is rt
    }
    else
    {
      if(RegDst == 1)
        Reg [r3] = ALUresult; // r3 is rd
      else
        Reg[r2] = ALUresult; // r2 is rt
    }
      
  }
    
  

}

/* PC update */
/* 10 Points */
void PC_update(unsigned jsec,unsigned extended_value,char Branch,char Jump,char Zero,unsigned *PC)
{

}

