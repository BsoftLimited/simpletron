mod cpu;
pub use cpu::CPU;

mod utils;

mod console;
pub use console::Console;

mod assembler;
pub use assembler::Assemblier;

pub fn intro(){
    println!("*** Welcome to Simpletron! ***\n");
    println!("*** Please enter your program one instruction ***");
    println!("*** location number and a question mark (?).  ***");
    println!("*** You then type the word for that location. ***");
    println!("*** Type the sentinel END to stop entering ***");
    println!("*** your program. ***");
}
 
pub fn info(){
    println!("*** Welcome to Simpletron! ***");
    println!("To run:");
    println!("\tSingletron --help or -h: to display help options");
    println!("\tSingletron file: to run from a file");
    println!("\tSingletron --version or -v: to display version");
    println!("\tSingletron: to input singletron commands manually");
}
 
pub fn version(){
    println!("Simpletron version 0.1.0");
}