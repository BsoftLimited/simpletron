use std::fs;

use crate::simpletron::utils;

use super::{CPU, Assemblier, intro};

fn combine(inputs: &Vec<String>)->String{
    let mut init = String::new();

    for input in inputs{
        init.push_str(format!(" {}", input).as_str());
    }
    return init;
}

pub struct Console{ cpu: Box<CPU> }

impl Console {
    pub fn new()->Self{
        let console =  Console{ cpu: Box::new(CPU::new()) };
        return  console;
    }

    pub fn clear(&self){
        if cfg!(windows) {
            std::process::Command::new("clr").status().unwrap();
        } else if cfg!(unix) {
            std::process::Command::new("clear").status().unwrap();
        }
    }

    pub fn load(&mut self, path: &str) {
        self.clear();
        let contents = fs::read_to_string(path).expect(format!("Should have been able to read the file: {}", path).as_str());

        let mut assembler = Assemblier::new();
        assembler.init(contents.as_str());

        self.cpu.add(assembler.run());
        println!("*** Program loading completed ***"); 
        self.run();       
    }

    pub fn run(&mut self){
        println!("\n\n*** Program execution begins  ***");
        self.cpu.run();
    }

    pub fn read(&mut self){
        self.clear();
        intro();
        let mut assembler = Assemblier::new();
        let mut inputs: Vec<String> = Vec::new();

        let mut input = String::new();
        while input != "end"{
            print!("address {}: >> ", utils::format(inputs.len() as i32, 4));
            input.clear();
            std::io::stdin().read_line(&mut input).unwrap();
            if input != "end"{
                let temp_data = format!("{} {}", combine(&inputs), input);
                if assembler.init(&temp_data){
                    inputs.push(input.clone());
                }
            }
        }

        if input.len() > 0{
            self.cpu.add(assembler.run());
            println!("*** Program loading completed ***\n");
            self.run();
        }
    }
}