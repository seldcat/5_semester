from typing import List


def hello(name: str = None) -> str:
    if name:
        return f'Hello, {name}!'
    else:
        return 'Hello!'


def int_to_roman(num: int) -> str:
    value = [
        1000, 900, 500, 400,
        100, 90, 50, 40,
        10, 9, 5, 4,
        1
    ]
    symbols = [
        "M", "CM", "D", "CD",
        "C", "XC", "L", "XL",
        "X", "IX", "V", "IV",
        "I"
    ]
    roman_numeral = ''
    i = 0
    while num > 0:
        for _ in range(num // value[i]):
            roman_numeral += symbols[i]
            num -= value[i]
        i += 1
    return roman_numeral


def longest_common_prefix(strs_input: List[str]) -> str:
    if strs_input:
        strs_input = list(map(lambda x: x.strip(), strs_input))
        last = ''
        i = 0
        example = strs_input[0]
        if not bool(example):
            return ''
        current = example[0]
        while len(list(filter(lambda x: x.startswith(current), strs_input))) == len(strs_input):
            last = current
            i += 1
            if i == len(example):
                return current
            current += example[i]
        return last
    else:
        return ''


def is_prime(n):
    if n <= 1:
        return False
    if n <= 3:
        return True
    if n % 2 == 0 or n % 3 == 0:
        return False
    i = 5
    while i * i <= n:
        if n % i == 0 or n % (i + 2) == 0:
            return False
        i += 6
    return True


def primes() -> int:
    i = 2
    while True:
        if is_prime(i):
            yield i
        i += 1


class BankCard:
    def __init__(self, total_sum: int, balance_limit: int = -1):
        self.total_sum = total_sum
        self.balance_limit = balance_limit

    def put(self, n: int):
        self.total_sum += n

    @property
    def balance(self):
        if self.balance_limit != 0:
            self.balance_limit -= 1
            return self.total_sum
        raise ValueError('Balance check limits exceeded.')

    def __str__(self):
        return 'To learn the balance call balance.'

    def __call__(self, n):
        if n > self.total_sum:
            raise ValueError('Not enough money to spend sum_spent dollars.')
        else:
            self.total_sum -= n
            print(f'You spent {n} dollars.')

    def __add__(self, other):
        res = BankCard(self.total_sum + other.total_sum, max(self.balance_limit, other.balance_limit))
        return res
