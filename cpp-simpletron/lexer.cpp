#include "lexer.h"

simpletron::assembler::Lexer::Lexer(std::string data){
    this->data = data;
}

char simpletron::assembler::Lexer::pop(){
    char init = this->data[self.index];
    this->index += 1;
    return init;
}

bool simpletron::assembler::Lexer::hasNext(){
    while(this->index < this->data.length()){
        this->current = new Character(this->data[this->index]);
        if(this->to_newline && this->current == '\n'){
            this->to_newline = false;
        }else if(!this->to_newline && !this->current.isWhitespace()){
            return true; 
        }
        this->index += 1;
    }
    return false;
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

simpletron::assembler::Token simpletron::assembler::Lexer::nextToken(){
    
}