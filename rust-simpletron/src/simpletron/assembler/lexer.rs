use crate::simpletron::utils::Character;

#[derive(Clone, Debug)]
#[allow(dead_code)]
pub enum Token{
	Name(String), String(String), Number(String),
	Colon, Coma, None}

pub struct Lexer{ index:usize, current:Character, data: String, to_newline: bool }
impl Lexer{
    pub fn new(data:&str)->Self{
        let string = String::from(data);
        let init = Character::new(string.chars().nth(0).unwrap());
        Lexer{ index:0, current:init, data: string, to_newline: false }
    }
    
    pub fn has_next(&mut self)->bool{
        while self.index < self.data.len(){
            self.current = Character::new(self.data.chars().nth(self.index).unwrap());
			if self.to_newline && self.current.unwrap() == '\n'{
				self.to_newline = false;
			}else if !self.to_newline && !self.current.is_whitespace(){
				return true; 
			} 
            self.index += 1;
        }
        return false;
    }
    
    fn pop(&mut self)->char{
        let init = self.data.chars().nth(self.index).unwrap();
        self.index += 1;
        return init;
    }
    
    pub fn get_next_token(&mut self)->Result<Token, String>{
		if self.current.is_alphabetic(){
			return self.get_name_token();
		}
		
		if self.current.is_numeric(){
			return self.get_number_token();
		}
		match self.current.unwrap(){
			':' => { self.pop(); return Ok(Token::Colon); },
			',' => { self.pop(); return Ok(Token::Coma); },
			'"' => return self.get_string_token(),
			__  => return Result::Err(format!("unexpected token {} encountered", self.pop()))
		}
	}

	fn get_name_token(&mut self)->Result<Token, String>{
		let mut builder = String::new();
		while self.index < self.data.len(){
            self.current = Character::new(self.data.chars().nth(self.index).unwrap());
            let passable = !self.current.is_alphanumeric();
            if passable { break; }else { builder.push(self.current.unwrap()); }
            self.index += 1;
        }
		return Ok(Token::Name(builder));
	}

	fn get_number_token(&mut self)->Result<Token, String>{
		let mut builder = String::new();
		while self.index < self.data.len(){
            self.current = Character::new(self.data.chars().nth(self.index).unwrap());
            let important = !self.current.is_whitespace() && self.current.is_hexdigit();
            if important { builder.push(self.current.unwrap()); } else { break; };
            self.index += 1;
        }
		return Ok(Token::Number(builder));
	}
	
	fn get_string_token(&mut self)->Result<Token, String>{
		let open = self.pop();
		let mut builder = String::new();
		while self.index < self.data.len(){
		    let close = self.data.chars().nth(self.index).unwrap();
			if close == open{
                self.pop();
                return Ok(Token::String( builder));
			}else{
				builder.push(self.pop());
			}
		}
		return Err(format!("Expecting a closing {}", if open == '\''{ "'"} else {"\""}));
	}
}