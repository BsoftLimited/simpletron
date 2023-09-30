mod lexer;
use self::lexer::{ Lexer, Token };

mod parser;
use self::parser::{ Expression, Parser };

use std::collections::HashMap;

pub struct Assemblier{ subroutines: Vec<(String,  Vec<Expression>)> }
impl Assemblier{
    pub fn new()->Self{
        Assemblier{ subroutines: Vec::new() }
    }

    pub fn init(&mut self, data: &str)->bool{
        let mut parser = Parser::new(data);

        let mut sub: Option<String> = None;
        let mut codes: Vec<Expression> = Vec::new();

        while parser.next_token(){
            match parser.get_next(){
                Err(error) =>{
                    println!("{}", error);
                    return false;
                },
                Ok(init) =>{
                    if (matches!(init, Expression::Branch{ nemode:_ , address:_ }) || matches!(init, Expression::Opcode(_))) && sub.is_some(){
                        codes.push(init);
                    }else if let Expression::Subroutine{name} = init{
                        self.insert(&mut sub, &mut codes);
                        sub = Some(name);
                    }
                }
            }
        }
        self.insert(&mut sub, &mut codes);
        return true;
    }

    fn insert(&mut self, sub: &mut Option<String>, codes: &mut Vec<Expression>){
        if sub.is_some() && !codes.is_empty(){
            self.subroutines.push((sub.as_ref().unwrap().clone(),  codes.to_vec()));
            codes.clear();
        }else if !codes.is_empty() && self.subroutines.is_empty(){
            self.subroutines.push(( String::from("_start") ,  codes.to_vec()));
            codes.clear();
        }
    }

    pub fn run(&mut self)->Vec<i32>{
        let mut codes:Vec<i32> = Vec::new();
        let mut addresses: HashMap<String, u16> = HashMap::new();

        let mut current: u16 = 0000;
        for subroutine in &self.subroutines{
            addresses.insert(subroutine.0.clone(), current);
            
            current += subroutine.1.len() as u16;
        }

        for subroutine in &self.subroutines{
            for exp in subroutine.1.clone(){
                if let Expression::Opcode(code) = exp{
                    codes.push(code.clone() as i32);
                }else if let Expression::Branch{nemode, address} = exp{
                    let init = nemode + addresses[&address];
                    codes.push(init as i32);
                }
            }
        }
        return codes;
    }
}