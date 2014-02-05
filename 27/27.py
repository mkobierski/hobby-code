#!/usr/bin/python -tt

from math import sqrt
from pprint import pprint

def isPrime(num):
    if num < 0:
        return 0
    sieve = {}
    for n in range(1, int(sqrt(num)) + 1):
        sieve[n] = 1
    
    for (n, t) in sieve.items():
        if t and not n == 1:
            if not num % n:
                return 0
            i = 1
            while i*n < sqrt(num):
                sieve[i*n] = 0
                i += 1       
    return 1

def numberOfPrimes(a, b):
    n = 0
    while (isPrime(n**2 + a*n + b)):
        n += 1
    return n

def main():
    most_primes = (0, 0, 0)
    for a in range (-999, 1000):
        for b in range (-999, 1000):
            this_number_of_primes = (a, b, numberOfPrimes(a, b))
            if this_number_of_primes[2] > most_primes[2]:
                most_primes = this_number_of_primes
    print most_primes
    print most_primes[0]*most_primes[1]
    return 0

if __name__ == "__main__":
    main()
