import random
import threading
import time
from PIDManager import PIDManager

lock = threading.Lock()
manager = PIDManager()
manager.allocate_map()


def drive():
    global manager
    with lock:
        pid = manager.allocate_pid()
        print(f'pid: {pid} started!')
    time.sleep(random.uniform(0, 10))
    with lock:
        manager.release_pid(pid)


if __name__ == '__main__':
    for _ in range(100):
        threading.Thread(target=drive).start()
