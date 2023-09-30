use std::env;
mod simpletron;
use simpletron::Console;



fn main() {
    let args: Vec<String> = env::args().collect();

    let mut console = Console::new();
    if args.len() > 1{
        let command = args[1].clone();
        if command == "-h" || command == "--help"{
            simpletron::info();
        }else if command == "-v" || command == "--version"{
            simpletron::version();
        }else if args[1].starts_with('-'){
            println!("unrecognized command or flag: {}", command);
        }else{
            console.load(args[1].as_str());
        }
    }else{
        console.read();
    }
}
