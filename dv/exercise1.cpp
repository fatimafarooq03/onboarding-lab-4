#include <VExercise1.h>
#include <cstdint>

 // VExercise1 model;
 

bool test(uint8_t op)
{
  VExercise1 model;
  model.op = op;
  model.a = 0;
  model.b = 0;
  while(++model.b)
  {
    while(++model.a)
    {
       model.eval();
       uint8_t result; 
       if (op == 0)
       {
        result = model.a^model.b; 
       }

       else if (op==1)
       {
        result = model.a << model.b; 
       }

       else if (op==2)
       {
        result = model.a % model.b; 
       }

       else if (op==3)
       {
        result = ~(model.a & model.b); 
       }

       else
       {
        return false;
       }
      
      if (model.out != result)
      {
        return false;
      }
    }
  }


  return true; 

}

int main()
{

  REQUIRE(test(0) == true);
  REQUIRE(test(1) == true);
  REQUIRE(test(2) == true);
  REQUIRE(test(3) == true);


return 0; 

};
