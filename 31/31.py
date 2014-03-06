#!/usr/bin/python -tt

from copy import deepcopy
import logging

LOGGER = logging.getLogger(__name__)


AVAILABLE_COINS = (200, 100, 50, 20, 10, 5, 2, 1)

def factorization(sum_, allow_self=False, threshold=None):
    """Given a number of pence, return a list
    containing its coin combination using the 
    least number of coins
    
    The parameter allow_self and threshold
    give control over which coins may be
    used to form the combination.  With
    allow_self True, factoring a sum of 5
    will return a factorization of 5,
    otherwise it will return 2 2 1.
    
    """
    LOGGER.debug("Factorization of %s...", sum_)
    initial_sum = sum_
    combination = []
    for coin in AVAILABLE_COINS:
        if threshold is not None:
            if coin > threshold:
                continue
        while float(sum_)/coin >= 1:
            if allow_self != True and coin == initial_sum and coin != 1:
                break
            else:
                combination.append(coin)
                sum_ -= coin
    LOGGER.debug(combination)
    return combination

def last_combination_reached(combination):
    """Check whether the last combination
    has been found.
    
    """
    LOGGER.debug("Checking last combination reached... ")
    if combination[0] == 1:
        LOGGER.info("Found!")
        return True
    LOGGER.debug("")
    return False

def regroup(combination, fact_num):
    """Regroups and refactors the combination's 
    coins smaller than given fact_num to their
    next largest form.
    Ex. Given a sum of 6 written as 5 1, next
    iteration would be (2 2 1) 1, but we know
    1 and 1 can be grouped into 2.  Thus, this
    function would return 2 2 2.
    
    """
    new_combination = []
    sum_to_regroup = 0
    for coin in combination:
        if coin < fact_num:
            sum_to_regroup += coin
        else:
            new_combination.append(coin)
    new_combination = new_combination + factorization(sum_to_regroup, allow_self=True, threshold=fact_num)
    return new_combination

def sublist_in_list(sublist, list_):
    """Tests whether every instance of every element
    of a list is contained within another list.
    
    """
    _list_ = deepcopy(list_)
    for item in sublist:
        if item in _list_:
            _list_.remove(item)
        else:
            return False
    return True

def find_combination(previous_combination, current_largest):
    """Finds the next combination given a
    previous combination and a parameter tracking
    which number was last used to expand or 
    regroup the combination.
    
    Two outcomes of this method can exist:
    - the next combination is trivial as we only
      need to expand the leftmost list entry which 
      isn't a value of 1
    - the next combination must be found by factoring
      and then regrouping the rightmost elements
      
    The current_largest attribute helps in determining
    which case we must consider to find the next
    combination.
    
    """
    next_largest = current_largest
    LOGGER.debug("")
    LOGGER.debug("Finding combination and next largest...")
    LOGGER.debug("-"*30)
    current_combination = []
    i = len(previous_combination) - 1
    previous_combination.sort(reverse=True)
    LOGGER.debug("Previous combination: %s", previous_combination)
    
    # Find right-most non-1 index
    while previous_combination[i] == 1 and i >= 0:
        i += -1
    factorization_num = previous_combination[i]
    
    LOGGER.debug("Factorization num: %s", factorization_num)
    factorization_list = factorization(factorization_num)
    LOGGER.debug("Factorization list: %s", factorization_list)
    current_combination = previous_combination[:i] + factorization_list + previous_combination[i+1:]
    LOGGER.debug("Current combination: %s", current_combination)
    next_largest = factorization_num
    LOGGER.debug("Current largest: %s", current_largest)
    
    if factorization_num > current_largest:
        # Case number two, we must regroup
        LOGGER.debug("Factorization num is greater than current largest")
        next_largest = factorization_num
        LOGGER.debug("Next largest: %s", next_largest)
        factorization_num = factorization_list[0]
        LOGGER.debug("New factorization num: %s", factorization_num)
        current_combination = regroup(current_combination, factorization_num)

    current_combination.sort(reverse=True)
    LOGGER.debug("Current combination: %s", current_combination)
    LOGGER.debug("Next largest: %s", next_largest)
    return (current_combination, next_largest)

def print_all_combinations(list_of_combinations):
    """Print function"""
    for combination in list_of_combinations:
        print_combination(combination)

def print_combination(combination):
    """Print helper function."""
    for coin in combination:
        LOGGER.info(coin)
    LOGGER.info("\n")

def main(sum_):
    """The main method of this computational program.
    Creates a list of combinations, runs a loop until the
    final combination is found, prints, then exits.
    
    """
    LOGGER.warn("Using coins from the set: %s", AVAILABLE_COINS)
    i = 0
    list_of_combinations = []
    current_largest = 1
    list_of_combinations.append(factorization(sum_, allow_self=True))
    while not last_combination_reached(list_of_combinations[-1]):
        (combination, current_largest) = find_combination(list_of_combinations[-1], current_largest)
        list_of_combinations.append(combination)
    print_all_combinations(list_of_combinations)
    LOGGER.warn("Number of combinations: %s", len(list_of_combinations))    
    return 0

if __name__ == "__main__":
    logging.basicConfig(level=logging.WARN)
    try:
        while True:
            sum_ = input("Enter an integer number of pence:")
            main(sum_)
    except KeyboardInterrupt:
        print "Goodbye!"
    except SyntaxError:
        print "Goodbye!"
    
