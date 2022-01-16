import threading

sequence = [0, 1]


def generate_sequence(n):
    global sequence
    if n <= 0:
        print("Incorrect input!")
        return

    elif n == 0:
        return 0

    else:
        a = 0
        b = 1

        for i in range(1, n - 1):
            c = a + b
            a = b
            b = c
            sequence.append(c)

        return sequence


if __name__ == '__main__':
    n = int(input())
    f = threading.Thread(target=generate_sequence, args=[n])
    f.start()
    f.join()
    print(sequence)
