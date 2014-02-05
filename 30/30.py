#!/usr/bin/python -tt

def main():
    running_total = 0
    for i in range(4150, 999999):
        i_str = str(i)
        sum = 0
        for num in i_str:
            sum += int(num)**5
        if sum == i:
            print i
            running_total += i
    print "running_total: ", running_total
        


if __name__ == "__main__":
    main()
