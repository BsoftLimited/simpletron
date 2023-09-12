mod character;

pub use character::Character;

pub fn hex(value: u32)->String{
    let mut init = value;
    let mut builder = String::new();
    while init > 0{
        let ch = format!("{}", init % 16);
        builder.insert_str(0, match ch.as_ref(){
            "10" => "A",
            "11" => "B",
            "12" => "C",
            "13" => "D",
            "14" => "E",
            "15" => "F",
            __ => ch.as_ref()
        });
        init /= 16;
    }
    return if builder.is_empty() { String::from("0") } else { builder };
}

pub fn from_hex(numb: &str)->u32{
    if numb.contains("0x") || numb.contains("0b"){
        let mut number: u32 = 0;
        for i in 2..numb.len(){
            let mut value = numb.chars().nth(i).unwrap() as u32;
            if value >= 65 && value <= 70{
                value -= 55;
            }else if value >= 97 && value <= 102{
                value -= 87;
            }else if value >= 48 && value <= 57{
                value -= 48;
            }
            number += value * u32::pow( if numb.contains("0x") { 16 } else { 2 }, (numb.len() - i - 1 ) as u32);
        }
        return number;   
    }
    return numb.parse().unwrap(); 
}