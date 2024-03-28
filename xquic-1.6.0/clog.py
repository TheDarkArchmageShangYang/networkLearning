import time
from watchdog.observers import Observer
from watchdog.events import FileSystemEventHandler

def OutputPower1():
  with open("./build/clog", 'r') as file:
    logs = file.readlines()
    for log in logs:
        if log.find("xqc_calc_through_power1") != -1:
            with open('example.txt', 'w') as f:
                f.write(log)
                print(log)
        elif log.find("Congestion switching") != -1:
            with open('example.txt', 'w') as f:
                f.write(log)
                print(log)
        elif log.find("after update rtt") != -1:
            with open('example.txt', 'w') as f:
                f.write(log)
                print(log)


class MyHandler(FileSystemEventHandler):
    def on_modified(self, event):
        if not event.is_directory:
          OutputPower1()
          
            

if __name__ == "__main__":
  path = "./build/"  # 监视当前目录
  event_handler = MyHandler()
  observer = Observer()
  observer.schedule(event_handler, path, recursive=False)
  observer.start()
  try:
      while True:
          time.sleep(1)
  except KeyboardInterrupt:
      observer.stop()
      observer.join()
