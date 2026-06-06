def exp_by_squaring(x, n):
    if n < 0:
        return exp_by_squaring(1 / x, -n)
    elif n == 0:
        return 1
    elif n % 2 == 0:
        return exp_by_squaring(x * x, n // 2)
    elif n % 2 != 0:
        return x * exp_by_squaring(x * x, (n - 1) // 2)

def main():
    print(exp_by_squaring(2, 4))

if __name__ == "__main__":
    main()
