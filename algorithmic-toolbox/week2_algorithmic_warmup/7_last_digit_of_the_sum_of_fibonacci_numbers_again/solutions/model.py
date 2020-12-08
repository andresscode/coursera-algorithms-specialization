def fibonacci_partial_sum_naive(from_, to):
    sum = 0

    current = 0
    next  = 1

    for i in range(to + 1):
        if i >= from_:
            sum += current

        current, next = next, current + next

    return sum % 10


from_, to = [int(i) for i in input().split()]
print(fibonacci_partial_sum_naive(from_, to))
