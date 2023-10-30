mod basic_maths;

pub struct Result {
    pub add: f64,
    pub substract: f64,
    pub multiply: f64,
    pub divide: f64,
}

pub fn run(n1: f64, n2: f64) -> Result {
    return Result {
        add: basic_maths::add(n1, n2),
        substract: basic_maths::substract(n1, n2),
        multiply: basic_maths::multiply(n1, n2),
        divide: basic_maths::divide(n1, n2),
    };
}
