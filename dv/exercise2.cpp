[200~#include <VExercise2.h>
#include <cstdint>

uint16_t fib(uint16_t num) {
  return (num << 1) + (((num >> 10) & 1) ^ ((num >> 8) & 1) ^ ((num >> 3) & 1) ^ ((num >> 1) & 1));

}

bool test(uint16_t num)
{
    VExercise2 model; 

  // checking for reset 
    model.clk = 1;
    model.eval();
    model.clk = 0; // getting to negative edge
    model.reset = 1;
    model.init = num;
    model.eval(); // out now has ~ num

    uint16_t last = ~num; 

    for (int i=0; i <100; i++)
    {
    // getting negative edge of clock
    model.clk = 1;
    model.reset = 0;
    model.eval();
    model.clk = 0;
    model.reset = 0;
    model.eval();

    // check
    if (model.out != fib(last)) 
    {
      return false;
    }

    last = model.out; // update last 
    }
    
return true; 

}

int main() {

  REQUIRE(test(5)==true);
  REQUIRE(test(999)==true);
  REQUIRE(test(503)==true);
  REQUIRE(test(1001)==true);
  REQUIRE(test(5167)==true); 
  REQUIRE(test(21199)==true);
  REQUIRE(test(65535)== true);

return 0; 


}
