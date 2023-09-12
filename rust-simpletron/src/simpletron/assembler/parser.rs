use super::{Lexer, Token};

const NEMONICS:[&str; 12] = [ 
    "RD", "WR", "LD", "STR", "ADD", "SUB", "DIV", "MUL", "BR", "BRN", "BRZ", "HLT"
];

fn is_nemonic(name: &str)->bool{
    return NEMONICS.contains(&name);
}

fn v_value(code: &str)->u32{
    let mut init = code.to_uppercase();
    init.remove(0);
    return match init.as_ref(){
        "A" => 10, "B" => 11, "C" => 12,
        "D" => 13, "E" => 14, "F" => 15,
        _ => { init.parse().unwrap() }
    };
}

#[derive(Debug,Clone)]
pub enum Expression{
    Opcode(u16), Branch{ nemode: u16, address: String},  Subroutine{ name :String}, None
}

pub struct Parser{ lexer:Box<Lexer>, errors: Vec<String> , current: Token }
impl Parser{
    pub fn new(data:&str)->Self{
        return Parser{ lexer: Box::new(Lexer::new(data)), errors: Vec::new() , current: Token::None };
    }
    
    pub fn next_token(&mut self)->bool{
        while self.lexer.has_next(){
            match self.lexer.get_next_token(){
                Err(error) =>{ self.errors.push(String::from(error)); }
                Ok(token) =>{
                    self.current = token;
                    return true;
                }
            }
        }
        self.current = Token::None;
        return false;
    }

    fn pop_token(&mut self)->Token{
        let init = self.current.clone();
        self.next_token();
        return init;
    }

    pub fn get_next(&mut self)->Expression{
        while !matches!(self.current, Token::None){
            if let Token::Name(name) = &self.current{
                match name.to_uppercase().as_str(){
                    "RD"   => return self.init_opcode(0x1000),
                    "WR"   => return self.init_opcode(0x1100),

                    "LD"   => return self.init_opcode(0x2000),
                    "STR"  => return self.init_opcode(0x2100),

                    "ADD"  => return self.init_opcode(0x3000),
                    "SUB"  => return self.init_opcode(0x3100),
                    "DIV"  => return self.init_opcode(0x3200),
                    "MUL"  => return self.init_opcode(0x3300),

                    "BR"   => return self.init_branch(0x4000),
                    "BRN"  => return self.init_branch(0x4000),
                    "BRZ"  => return self.init_branch(0x4000),
                    "HLT"  => return Expression::Opcode(0x4300),

                    _ => return self.init_subroutine(),
                }
            }
            let token = self.pop_token();
            self.errors.push(format!("Unexpected token: {:?}", token));
        }
        return Expression::None;
    }

    fn init_opcode(&mut self, nemode: u16)->Expression{
        self.next_token();
        if let Token::Number(value) = &self.current {
            if !is_nemonic(value.as_ref()){
                match value.clone().parse::<u16>(){
                    Ok(init) => return Expression::Opcode(nemode + init),
                    Err(error) => self.errors.push(format!("Unexpected a number, instead {:?} was provided", value.clone())),
                }
                
            }else{
                self.errors.push(format!("Unexpected a number, instead {:?} was provided", value.clone()));
            }
        }
        return Expression::None;
    }

    fn init_branch(&mut self, nemode: u16)->Expression{
        self.next_token();
        if let Token::Name(value) = &self.current {
            if !is_nemonic(value.as_ref()){
                return Expression::Branch{ nemode, address: value.clone() };
            }
        }
        return Expression::None;
    }

    fn init_subroutine(&mut self)->Expression{
        let (mut step, mut name): (u16, Option<String>) = ( 0, None);
        loop{
            if let Token::Name(value) = &self.current{
                if step == 0 && !is_nemonic(&value){
                    name = Some(value.clone());
                    step = 1;
                }
            }else if let Token::Colon = &self.current{
                if step == 1{
                    return Expression::Subroutine{ name: name.unwrap() };
                }
            }else if let Token::None = self.current{
                break;
            }
            self.next_token();
        }
        return Expression::None;
    }
}