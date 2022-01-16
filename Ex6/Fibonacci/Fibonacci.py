import threading
import queue

sequence = queue.Queue()
sequence.put(0)
sequence.put(1)


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
            sequence.put(c)

        return sequence


if __name__ == '__main__':
    n = int(input())
    f = threading.Thread(target=generate_sequence, args=[n])
    f.start()
    while not sequence.empty():
        print(sequence.get(timeout=1), end='  ')
