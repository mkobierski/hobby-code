// constructing vectors
#include <iostream>
#include <vector>

int main ()
{
  unsigned int i;

  // constructors used in the same order as described above:
  std::vector<int> first;                                // empty vector of ints
  std::vector<int> second (4,100);                       // four ints with value 100
  std::vector<int> third (1,4);  // iterating through second
  std::vector<int> fourth (third);                       // a copy of third

  // the iterator constructor can also be used to construct from arrays:
  int myints[] = {16,2,77,29};
  std::vector<int> fifth (myints, myints + sizeof(myints) / sizeof(int) );

  std::cout << "The contents of first are:";
  for (std::vector<int>::iterator it = first.begin(); it != first.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';
  
  std::cout << "The contents of second are:";
  for (std::vector<int>::iterator it = second.begin(); it != second.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';
  
  std::cout << "The contents of third are:";
  for (std::vector<int>::iterator it = third.begin(); it != third.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';
  
  std::cout << "The contents of fourth are:";
  for (std::vector<int>::iterator it = fourth.begin(); it != fourth.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';
  
  std::cout << "The contents of fifth are:";
  for (std::vector<int>::iterator it = fifth.begin(); it != fifth.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';

  return 0;
}

