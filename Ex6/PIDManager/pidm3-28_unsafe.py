import random
import threading
import time
from PIDManager import PIDManager

manager = PIDManager()
manager.allocate_map()


def drive():
    global manager
    pid = manager.allocate_pid()
    print(f'pid: {pid} started!')
    time.sleep(random.uniform(0, 10))
    manager.release_pid(pid)


if __name__ == '__main__':
    for _ in range(100):
        threading.Thread(target=drive).start()
