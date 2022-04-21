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

}

/* Read Register */
/* 5 Points */
void read_register(unsigned r1,unsigned r2,unsigned *Reg,unsigned *data1,unsigned *data2)
{

}


/* Sign Extend */
/* 10 Points */
void sign_extend(unsigned offset,unsigned *extended_value)
{

}

/* ALU operations */
/* 10 Points */
int ALU_operations(unsigned data1,unsigned data2,unsigned extended_value,unsigned funct,char ALUOp,char ALUSrc,unsigned *ALUresult,char *Zero)
{

}

/* Read / Write Memory */
/* 10 Points */
int rw_memory(unsigned ALUresult,unsigned data2,char MemWrite,char MemRead,unsigned *memdata,unsigned *Mem)
{

}


/* Write Register */
/* 10 Points */
void write_register(unsigned r2,unsigned r3,unsigned memdata,unsigned ALUresult,char RegWrite,char RegDst,char MemtoReg,unsigned *Reg)
{

}

/* PC update */
/* 10 Points */
void PC_update(unsigned jsec,unsigned extended_value,char Branch,char Jump,char Zero,unsigned *PC)
{

}

