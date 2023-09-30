use super::{Lexer, Token};

const NEMONICS:[&str; 12] = [ 
    "RD", "WR", "LD", "STR", "ADD", "SUB", "DIV", "MUL", "BR", "BRN", "BRZ", "HLT"
];

fn is_nemonic(name: &str)->bool{
    return NEMONICS.contains(&name);
}



#[derive(Debug,Clone)]
pub enum Expression{
    Opcode(u16), Branch{ nemode: u16, address: String},  Subroutine{ name :String}
}

pub struct Parser{ lexer:Box<Lexer>, current: Token }
impl Parser{
    pub fn new(data:&str)->Self{
        return Parser{ lexer: Box::new(Lexer::new(data)), current: Token::None };
    }
    
    pub fn next_token(&mut self)->bool{
        while self.lexer.has_next(){
            match self.lexer.get_next_token(){
                Err(error) =>{ println!("{}", error); }
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

    pub fn get_next(&mut self)->Result<Expression, String>{
        while !matches!(self.current, Token::None){
            if let Token::Name(name) = &self.current{
                match name.to_uppercase().as_str(){
                    "RD"   => return self.init_opcode(1000),
                    "WR"   => return self.init_opcode(1100),

                    "LD"   => return self.init_opcode(2000),
                    "STR"  => return self.init_opcode(2100),

                    "ADD"  => return self.init_opcode(3000),
                    "SUB"  => return self.init_opcode(3100),
                    "DIV"  => return self.init_opcode(3200),
                    "MUL"  => return self.init_opcode(3300),

                    "BR"   => return self.init_branch(4000),
                    "BRN"  => return self.init_branch(4100),
                    "BRZ"  => return self.init_branch(4200),
                    "HLT"  => return Ok(Expression::Opcode(4300)),
                    "END"  => return Ok(Expression::Opcode(9999)),

                    _ => return self.init_subroutine(),
                }
            }
            let token = self.pop_token();
            return Err(format!("Unexpected token: {:?}", token));
        }
        return Err("unexpected end of token".to_owned());
    }

    fn init_opcode(&mut self, nemode: u16)->Result<Expression, String>{
        self.next_token();
        if let Token::Number(value) = &self.current {
            if !is_nemonic(value.as_ref()){
                match value.clone().parse::<u16>(){
                    Ok(init) => return Ok(Expression::Opcode(nemode + init)),
                    Err(_error) => return Err(format!("Unexpected a number, instead {:?} was provided", value.clone())),
                }
                
            }else{
                return Err(format!("Unexpected a number, instead {:?} was provided", value.clone()));
            }
        }
        return Err("unexpected end of token".to_owned());
    }

    fn init_branch(&mut self, nemode: u16)->Result<Expression, String>{
        self.next_token();
        if let Token::Name(value) = &self.current {
            if !is_nemonic(value.as_ref()){
                return Ok(Expression::Branch{ nemode, address: value.clone() });
            }
        }else if let Token::Number(value) = &self.current {
            match value.clone().parse::<u16>(){
                Ok(init) => return Ok(Expression::Opcode(nemode + init)),
                Err(_error) => return Err(format!("Unexpected a number, instead {:?} was provided", value.clone())),
            }
        }
        return Err("unexpected end of token".to_owned());
    }

    fn init_subroutine(&mut self)->Result<Expression, String>{
        let  mut name: Option<String> =  None;
        loop{
            if let Token::Name(value) = &self.current{
                if name.is_none() && !is_nemonic(&value){
                    name = Some(value.clone());
                }
            }else if let Token::Colon = &self.current{
                if name.is_some(){
                    return Ok(Expression::Subroutine{ name: name.unwrap() });
                }
            }else if let Token::None = self.current{
                break;
            }
            self.next_token();
        }
        return Err("unexpected end of token".to_owned());
    }
}