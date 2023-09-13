mod lexer;
use self::lexer::{Lexer, Token};

mod parser;
use self::parser::{Expression, Parser};

use std::collections::HashMap;

struct Sub{ name: String }

pub struct Assemblier{ map: Vec<(String,  Vec<Expression>)> }
impl Assemblier{
    pub fn new()->Self{
        Assemblier{ map: Vec::new() }
    }

    pub fn init(&mut self, data: &str){
        let mut parser = Parser::new(data);

        let mut sub: Option<Sub> = None;
        let mut codes: Vec<Expression> = Vec::new();

        while parser.next_token(){
            let init = parser.get_next();
            if (matches!(init, Expression::Branch{ nemode:_ , address:_ }) || matches!(init, Expression::Opcode(_))) && sub.is_some(){
                codes.push(init);
            }else if let Expression::Subroutine{name} = init{
                self.insert(&mut sub, &mut codes);
                sub = Some(Sub{name});
            }
        }
        self.insert(&mut sub, &mut codes);
    }

    fn insert(&mut self, sub: &mut Option<Sub>, codes: &mut Vec<Expression>){
        if sub.is_some() && !codes.is_empty(){
            self.map.push((sub.as_ref().unwrap().name.clone(),  codes.to_vec()));
            codes.clear();
        }
    }

    pub fn run(&mut self)->Vec<u32>{
        let mut codes:Vec<u32> = Vec::new();
        let mut addresses: HashMap<String, u16> = HashMap::new();

        let mut current: u16 = 0000;
        for subroutine in &self.map{
            addresses.insert(subroutine.0.clone(), current);
            
            current += subroutine.1.len() as u16;
        }

        for subroutine in &self.map{
            for exp in subroutine.1.clone(){
                if let Expression::Opcode(code) = exp{
                    codes.push(code.clone() as u32);
                }else if let Expression::Branch{nemode, address} = exp{
                    let init = nemode + addresses[&address];
                    codes.push(init as u32);
                }
            }
        }
        return codes;
    }
}