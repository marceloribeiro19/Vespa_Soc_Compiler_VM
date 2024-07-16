#alu instructions opcodes and assembly name
instructions_alu = {
    "ADD": 1, "SUB": 2, "OR": 3,
    "AND": 4, "XOR": 6, "CMP": 7
}

#alu instructions with imediate operand opcodes and assembly name
instructions_alu_imm = {
    "ADDI": 1, "SUBI": 2, "ORI": 3,
    "ANDI": 4, "XORI": 6, "CMPI": 7
}

#instruction not opcode and assembly name
instruction_not = {"NOT": 5}  

#load and store indexed opcode and assembly name
instruction_loadstore_index = {"LDX": 12, "STX": 14}

#load and store opcodes and assembly name
instruction_loadstore = {"LD": 10, "LDI": 11, "ST": 13}

#push opcode and assembly name
instruction_push = {"PUSH": 15}

#pop opcode and assembly name
instruction_pop = {"POP": 16}

#branch instructions opcode and assembly name
instructions_branch = {
    "BRA": 0b010000000, "BNV": 0b010001000,
    "BCC": 0b010000001, "BCS": 0b010001001,
    "BVC": 0b010000010, "BVS": 0b010001010,
    "BEQ": 0b010000011, "BNE": 0b010001011,
    "BGE": 0b010000100, "BLT": 0b010001100,
    "BGT": 0b010000101, "BLE": 0b010001101,
    "BPL": 0b010000110, "BMI": 0b010001110
}

#jump opcode and assembly name
instruction_jmp = {"JMP": 9 }

#jump with link register opcode and assembly name
instruction_jmp_link = {"JMPL": 9 }

#instructions without operands opcode and assembly name
instruction_without_operands = {"NOP": 0, "RETI": 17, "HALT": 31 }



#function to make intructions binary code
def convert_instruction_to_binary(instruction, operands):
    
    if instruction in instructions_alu:
        opcode = instructions_alu[instruction]
        return format(opcode, '05b') + format(int(operands[0]), '05b') + format(int(operands[1]), '05b') + format(int(0), '01b') + format(int(operands[2]), '05b') + format(int(0), '011b')

    elif instruction in instructions_alu_imm:
        opcode = instructions_alu_imm[instruction]
        return format(opcode, '05b') + format(int(operands[0]), '05b') + format(int(operands[1]), '05b') + '1' + format(int(operands[2]), '016b')

    elif instruction in instruction_not:
        opcode = instruction_not[instruction]
        return format(opcode, '05b') + format(int(operands[0]), '05b') + format(int(operands[1]), '05b') + format(int(0), '01b') + format(int(0), '016b')

    elif instruction in instruction_loadstore:
        opcode = instruction_loadstore[instruction]
        return format(opcode, '05b') + format(int(operands[0]), '05b') + format(int(operands[1]), '022b')
    
    elif instruction in instruction_loadstore_index:
        opcode = instruction_loadstore_index[instruction]
        return format(opcode, '05b') + format(int(operands[0]), '05b') + format(int(operands[1]), '05b') + format(int(operands[2]), '017b') 

    elif instruction in instructions_branch:
        opcode = instructions_branch[instruction]
        return format(opcode, '09b') + format(int(operands[0]), '023b')

    elif instruction in instruction_jmp:
        opcode = instruction_jmp[instruction]
        return format(opcode, '05b') + format(int(0), '05b') + format(int(operands[0]), '05b') + format(int(0), '01b') + format(int(operands[1]), '016b') 

    elif instruction in instruction_jmp_link:
        opcode = instruction_jmp_link[instruction]
        return format(opcode, '05b') + format(int(operands[0]), '05b') + format(int(operands[1]), '05b') + format(int(1), '01b') + format(int(operands[2]), '016b') 
    
    elif instruction in instruction_push:
        opcode = instruction_push[instruction]
        return format(opcode, '05b') + format(int(0), '05b') + format(int(operands[0]), '05b') + format(int(0), '017b')
    
    elif instruction in instruction_pop:
        opcode = instruction_pop[instruction]
        return format(opcode, '05b') + format(int(operands[0]), '05b') + format(int(0), '022b')

    elif instruction in instruction_without_operands:
        opcode = instruction_without_operands[instruction]
        return format(opcode, '05b') + format(0, '027b')

    else:
        raise ValueError(f"Invalid instruction: {instruction}")


#function to divide the 32 bits instructions in 4
def divide_instruction(binary):
    divided_bytes = []

    for _ in range(4):
        byte = binary & 0xFF
        divided_bytes.append(byte)
        binary >>= 8

    return divided_bytes    


#function that makes the following steps:
#  - read code.txt file
#  - parsing the instruction
#  - convert to binary and and write in binarycode.txt
#  - divide the binary code and write in each .coe file
def parse_and_generate_coe(input_filename, output_filenames):
    files = []
    first = True

    with open(input_filename, 'r') as input_file:

        for file_name in output_filenames:
            id = open(file_name, 'w')
            id.write("memory_initialization_radix=2;\n")        #coe header -> data format 
            id.write("memory_initialization_vector= \n")
            files.append(id)


        for line in input_file:
            words = line.split()

            instruction = words[0]
            operands = words[1:]

            print(f"parse: {instruction}, {operands}")

            binary_representation = convert_instruction_to_binary(instruction, operands)


            binary = int(binary_representation, 2)

            print(f"Binary Representation: {binary_representation}")
            print(f"Binary : {binary}")   

            divided_bytes = divide_instruction(binary)

            print(f"Divided Bytes: {divided_bytes}")    

            if first:
                first = False

            else: 
                files[0].write(",\n") 
                files[1].write(",\n") 
                files[2].write(",\n") 
                files[3].write(",\n")
                files[4].write(",\n")    

            files[3].write(format(int(divided_bytes[0]), '08b')) 
            files[2].write(format(int(divided_bytes[1]), '08b'))    
            files[1].write(format(int(divided_bytes[2]), '08b'))    
            files[0].write(format(int(divided_bytes[3]), '08b'))
            files[4].write(binary_representation)        


        files[0].write(";") 
        files[1].write(";") 
        files[2].write(";") 
        files[3].write(";") 
        files[4].write(";") 

        files[0].close() 
        files[1].close()
        files[2].close()
        files[3].close()   



if __name__ == "__main__":
    print("START")

    input_filename = "code.txt"
    output_filenames = ["code00.coe", "code01.coe", "code10.coe", "code11.coe", "code.coe"]
    parse_and_generate_coe(input_filename, output_filenames)       
