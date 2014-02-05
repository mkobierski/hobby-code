#!/usr/bin/python -tt


def main():
    #compute number of ways to make change total from a set of coins
    pence_to_divide = 20
    coin_tuple = (1, 2, 5, 10, 25)
    i = 0
    while pence_to_divide / coin_tuple[i] > 0 and i < len(coin_tuple):
 #   for item in coin_tuple while pence_to_divide / item:
        
        print coin_tuple[i]
        i += 1
    #coin_tuple at i is greatest now
    coin_subset = list(coin_tuple[:i])
    coin_subset.sort(reverse=True)
    
    current_combination = []
    
    #loop until all combinations are found
    while current_combination.count(coin_tuple[0]) < pence_to_divide:
        current_combination.
        
    
    return 0
    


if __name__ == "__main__":
    main()
