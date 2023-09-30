use crate::simpletron::utils;

enum Operands{
    READ,        // Read a word from the terminal into a specific location in memory
    WRITE,         // Write a word from a specific location in memory to the terminal

    LOAD,          // Load a word from a specific location in memory into the self.accumulator
    STORE,         // Store a word from the self.accumulator into a specific location in memory

    ADD,           // Add a word from a specific location in memory to the word in the accumalator and then leaves the result in the self.accumulator
    SUBSTRACT,     // Substract a word from a specific location in memory to the word in the accumalator and then leaves the result in the self.accumulator
    DIVIDE,        // Divide a word from a specific location in memory into the word in the accumalator and then leaves the result in the self.accumulator
    MULTIPLY,      // Multiply a word from a specific location in memory to the word in the accumalator and then leaves it in the self.accumulator

    BRANCH,       // Branch to a specific location in memory
    BRANCHNEG,     // Branch to a specific location in memory if the self.accumulator is negative
    BRANCHZERO,    // Branch to a specific location in memory if the self.accumulator is zero
    HALT,          // Halt the program
}

impl Operands {
    fn from(value: i32)->Result<Self, String>{
        return match value {
            10 => Ok(Operands::READ),
            11 => Ok(Operands::WRITE),
            20 => Ok(Operands::LOAD),
            21 => Ok(Operands::STORE),
            30 => Ok(Operands::ADD),
            31 => Ok(Operands::SUBSTRACT),
            32 => Ok(Operands::DIVIDE),
            33 => Ok(Operands::MULTIPLY),
            40 => Ok(Operands::BRANCH),
            41 => Ok(Operands::BRANCHNEG),
            42 => Ok(Operands::BRANCHZERO),
            43 => Ok(Operands::HALT),
            _ => Err(format!("instruction not recognized {}", value))
        }
    }
}

const SIZE: usize = 100;

pub struct CPU{
    memory: [i32; SIZE], // memory
    accumulator: i32, // The self.accumulator
    instruction_counter: usize,  // The memory address of the current instruction
    instruction_register: i32, // The current instruction to be performed
    operation_code: i32, // The operation code currently being perfromed
    operand: i32 // The memory address the current variable operates 
}

impl CPU {
    pub fn new ()->Self{
        return CPU{
            memory: [0; SIZE], accumulator: 0,
            instruction_counter: 0, instruction_register: 0,
            operation_code: 0, operand: 0
        };
    }

    pub fn add(&mut self, data: Vec<i32>) {
        for i in 0..data.len(){
            self.memory[ i] = data[i];
        }
    }

    pub fn clear(&mut self){
        self.accumulator = 0;
        self.instruction_register = 0;
        self.operation_code = 0;
        self.operand = 0;
        self.memory = [0; SIZE];
    }

    pub fn run(&mut self){
        self.instruction_counter = 0;
        // Run infinte loop through the instructions
        while self.instruction_counter < self.memory.len() {   
            // get current instruction
            self.instruction_register = self.memory[self.instruction_counter];
            if self.instruction_register == 9999{
                break;
            }

            // get opcode and self.operand
            self.operation_code = self.instruction_register / 100;
            self.operand = self.instruction_register % 100;
            
            match Operands::from(self.operation_code){
                Ok(operand) =>{
                    match operand {
                        Operands::READ =>{
                            println!("? ");
                            let mut line: String = String::new();
                            if let Err(error) = std::io::stdin().read_line(&mut line){
                                print!("invalid input {}", error);
                                self.instruction_counter = 100;
                            }

                            self.memory[ self.operand as usize ] = line.trim().parse().unwrap();
                            println!("{} loaded into memory address: {}", self.memory[ self.operand as usize ], self.operand);
                            self.instruction_counter += 1;
                        }
                        Operands::WRITE =>{
                            println!("address {}: {} >> ? {} from memory address: {}", utils::format(self.instruction_counter as i32, 2), self.instruction_register, self.memory[ self.operand as usize ], self.operand);
                            self.instruction_counter += 1;
                        }
                        Operands::LOAD =>{
                            println!("address {}: {} >> Loaded {} into the accumulator.", utils::format(self.instruction_counter as i32, 2), self.instruction_register, self.memory[ self.operand as usize ]);
                            self.accumulator = self.memory[ self.operand as usize ];
                            self.instruction_counter += 1;
                        }
                        Operands::STORE =>{
                            println!("address {}: {} >> copied {} from the accumulator into memory address {}.",utils::format(self.instruction_counter as i32, 2), self.instruction_register, self.accumulator, self.operand);
                            self.memory[ self.operand as usize ] = self.accumulator;
                            self.instruction_counter += 1;
                        }
                        Operands::ADD =>{
                            println!("address {}: {} >> add {} to the acummulator's value: {}.", utils::format(self.instruction_counter as i32, 2), self.instruction_register, self.memory[ self.operand as usize ], self.accumulator);                
                            self.accumulator += self.memory[ self.operand as usize ];
                            self.instruction_counter += 1;
                        }
                        Operands::SUBSTRACT =>{
                            println!("address {}: {} >> substract {} from the acummulator's value: {}.", utils::format(self.instruction_counter as i32, 2), self.instruction_register, self.memory[ self.operand as usize ], self.accumulator);                            
                            self.accumulator -= self.memory[ self.operand as usize ];
                            self.instruction_counter += 1;
                        }
                        Operands::DIVIDE =>{
                            println!("address {}: {} >> divide the acummulator's value: {} with {}.", utils::format(self.instruction_counter as i32, 2), self.instruction_register, self.accumulator, self.memory[ self.operand as usize ]); 
                            self.accumulator /= self.memory[ self.operand as usize ];
                            self.instruction_counter += 1;
                        }
                        Operands::MULTIPLY =>{
                            println!("address {}: {} >> multiply the accumulator's value: {} with {}.", utils::format(self.instruction_counter as i32, 2), self.instruction_register, self.accumulator, self.memory[ self.operand as usize ]);
                            self.accumulator *= self.memory[ self.operand as usize ];
                            self.instruction_counter += 1;
                        }
                        Operands::BRANCH =>{
                            println!("address {}: {} >> performed Jump to: {}", utils::format(self.instruction_counter as i32, 2), self.instruction_register, self.operand);
                            self.instruction_counter = self.operand as usize;
                        }
                        Operands::BRANCHNEG =>{
                            if self.accumulator < 0{
                                self.instruction_counter = self.operand as usize;
                            }
                        }
                        Operands::BRANCHZERO =>{
                            if self.accumulator == 0{
                                self.instruction_counter = self.operand as usize;
                            }
                        }
                        Operands::HALT =>{
                            println!("address {}: {} >> program Halted", utils::format(self.instruction_counter as i32, 2), self.instruction_register);
                            self.instruction_counter = 100;
                        }
                    }
                },
                Err(error) =>{
                    println!("address {}: {} >> encounterd a strange instruction: {}", utils::format(self.instruction_counter as i32, 2), self.instruction_register, error);
                    self.instruction_counter += 1;
                }
            }
        }
    }
}