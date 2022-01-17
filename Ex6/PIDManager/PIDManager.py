class PIDManager:
    def __init__(self, minimum=300, maximum=5000):
        self.Min_PID = minimum
        self.Max_PID = maximum
        self.bitmap = []

    def allocate_map(self):
        try:
            self.bitmap = [1 for _ in range(0, self.Min_PID)] + ([0 for _ in range(self.Max_PID - self.Min_PID)])
            return 1
        except:
            return -1

    def allocate_pid(self):
        try:
            available = self.bitmap.index(0)
            self.bitmap[available] = 1
            return available
        except:
            return -1

    def release_pid(self, pid):
        self.bitmap[pid] = 0


if __name__ == '__main__':
    P = PIDManager(3, 5)
    P.allocate_map()
    print(P.allocate_pid())
    print(P.allocate_pid())
    print(P.allocate_pid())
    print(P.allocate_pid())
