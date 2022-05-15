#pragma once
#include <iostream>
#include <vector>
using namespace std;

bool is_Prime(int x)
{
  // invalid input
  if (x <= 1)
    return false;

  // process all potential divisors
  for(int i = 2; i <= x / 2; i++) {
      if(x % i == 0) {
         return false;
      }
   }

  // no divisor found, therfore it's a prime number
  return true;
}


int prime_factorial(int _number) {

   // vector to store all the prime factors of a number
   vector<int>Factors;
   // iterate from 2 to half of the number as there can be no factor
   // greater than half of the number. 
   for(int i = 2; i <= _number/2; i++)
   {
      //check if number is factor
      if(_number % i == 0)
      {
         // check if the factor is also a prime number
         if(is_Prime(i)==true)
         {
         // add the value in the vector
         Factors.push_back(i);
         }
      }
   }
   int max=1;
   // iterate the vector to find largest prime factor
   for(int i = 0; i < Factors.size(); i++)
   {
      if(Factors[i] > max)
      {
         max = Factors[i];
      }
   }
   
// output the largest prime factor
   cout<<"Largest prime factor = " << max<<endl;
   return max;
}


TEST_CASE("testing the factorial function") {
    CHECK(prime_factorial(1) == 1);
    CHECK(prime_factorial(2) == 1);
    CHECK(prime_factorial(4) == 2);   
    INFO("The prime factorial function");
}