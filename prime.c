#include <math.h>
#include "prime.h"

// method to see if a number is prime
int is_prime(const int x){
  // numbers less than 2 arent prime
  if (x < 2){
    return -1;
  }
  // numbers 2, and 3 are prime
  if (x < 4){
    return 1;
  }
  // filter for even numbers as they are not prime
  if (x % 2 == 0){
    return 0;
  }
  // check for divisibility of odd numbers
  for (int i = 3; i <= floor(sqrt((double) x)); i += 2){
    if (x % i == 0){
      return 0;
    }
  }
  // if the number passed all of the checks and got through it is prime and send off 1 signaling it is prime
  return 1;
}

// method to find next prime number greather than x
int next_prime(int x){
  // loop which will go on until a prime number is found
  while (is_prime(x) != 1){
    x++;
  }
  return x;
}