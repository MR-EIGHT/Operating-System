import random
import threading
import time


class PIDManager_Safe:
    def __init__(self, minimum=300, maximum=5000):
        self.Min_PID = minimum
        self.Max_PID = maximum
        self.bitmap = []
        self.lock = threading.Lock()

    def allocate_map(self):
        try:
            self.bitmap = [1 for _ in range(0, self.Min_PID)] + ([0 for _ in range(self.Max_PID - self.Min_PID)])
            return 1
        except:
            return -1

    def allocate_pid(self):
        with self.lock:
            try:
                available = self.bitmap.index(0)
                self.bitmap[available] = 1
                return available
            except:
                return -1

    def release_pid(self, pid):
        with self.lock:
            self.bitmap[pid] = 0


if __name__ == '__main__':
    P = PIDManager_Safe()
    P.allocate_map()


    def drive():
        pid = P.allocate_pid()
        print(f'pid: {pid} started!')
        time.sleep(random.uniform(0, 10))
        P.release_pid(pid)
        # print(f'pid: {pid} released!')


    for _ in range(101):
        threading.Thread(target=drive).start()
