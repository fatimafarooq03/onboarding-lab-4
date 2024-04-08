#include <VExercise3.h>
#include <cstdint>


uint8_t m1(uint8_t a, uint8_t b, uint8_t c)
{
  if (a == 0)
  {
    return ((b<<3 & 0b00111000) + (c & 0b00000111)); 
  }

  else if (a == 1)
  {
    return ((0b01<<6) + (c<<3 & 0b00111000) + (b & 0b00000111));
  }

  else if (a==2)
  {
    return b;
  }

  else if (a==3)
  {
    return c; 
  }

  else
  {
    return 0; 
  }
}

uint16_t m2(uint8_t a, uint8_t b, bool reset)
{
  static uint8_t state; 
  static uint16_t out; 
  if (reset)
  {
    state = 0;
    out = ((b<<8)+a);
    return out;
  }

  else
  {

    if(state == 0)
    {
      state++;
      state = state % 5; 
      out = ((a<<8) + (out&0b11111111));
      return out; 
    }

    else if (state == 1)
    {
      state++;
      state = state % 5; 
      out = (out & (0b11111111<<8)) + b; 
      return out; 
    }

    else if (state == 2)
    {
      state++;
      state = state % 5; 
      out = (out << 8) + (out >> 8); 
      return out; 
    }

    else if (state == 3)
    {
      state++;
      state = state % 5; 
      out = (out << 12) + ((out << 4) & (0b11111111<<8)) + ((out>>4)&(0b11110000)) + (out>>12); 
      return out; 
    }

    else if (state == 4)
    {
      state++; 
      state = state % 5; 
       bool out_xor = out & 1;
        for (int i = 1; i < 16; i++) {
          out_xor ^= (out >> i) & 1;
        }
        out = out_xor;
        return out; 
    }

    return 0; 

  }
}



int main() {
  VExercise3 model;

  bool reset;
  bool clk;
  uint8_t a;
  uint16_t b;
  uint16_t c;
  uint16_t res;

  for (int i = 0; i < 400; i++)
  {

    // random numbers for input
    a = rand() % 15;
    b = rand() % 65535;
    c = rand() % 65535;

    // getting negative edge
    model.clk = 1;
    model.reset = 0;
    model.eval();
    model.clk = 0;

    // setting intial values 
    model.a = a;
    model.b = b;
    model.c = c;

    // starting with reset and evaluate
    model.reset = 1; 
    model.eval(); 

    // check for reset
     res = m2(m1((a & 3), (b & 255), (c & 255)), m1((((a >> 2)&3)), (b >> 8), (c >> 8)), 1);
     if (model.out != res)
     {
      return 1; 
     }

     // cheecking for all states in not reset
     for (int i = 0; i < 6; i++)
     {
      // getting negative edge 
      model.clk = 1;
      model.reset = 0;
      model.eval();
      model.clk = 0;
      // intializing module values 
      model.reset = 0;
      model.a = a;
      model.b = b;
      model.c = c;
      model.eval();

      res = m2(m1((a & 3), (b & 255), (c & 255)), m1(((a >> 2)&3), (b >> 8), (c >> 8)), 0);
      REQUIRE(model.out == res); 

     }

  }

  return 0; 


} 
