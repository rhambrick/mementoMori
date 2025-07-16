# memento mori

import tkinter as tk
from datetime import datetime, timedelta
import time
import os

SAVE_FILE = "dob.txt"
LIFE_EXPECTANCY_YEARS = 72

def load_or_get_dob():
    if os.path.exists(SAVE_FILE):
        with open(SAVE_FILE, "r") as f:
            dob_str = f.read().strip()
    else:
        dob_str = input("Enter your birthdate (YYYYMMDD): ")
        with open(SAVE_FILE, "w") as f:
            f.write(dob_str)
    return datetime.strptime(dob_str, "%Y%m%d")

class MementoMoriApp:
    def __init__(self, root, death_date):
        self.root = root
        self.death_date = death_date

        root.configure(bg="black")
        root.title("Memento Mori")
        root.protocol("WM_DELETE_WINDOW", self.on_close)
        root.attributes("-topmost", True)

        # self.title_label = tk.Label(root, text="MEMENTO MORI", font=("Courier", 24, "bold"), fg="red", bg="black")
        # self.title_label.pack(pady=10)

        self.counter_label = tk.Label(root, text="", font=("Courier", 20), fg="red", bg="black")
        self.counter_label.pack(pady=10)

        self.update_clock()

    def update_clock(self):
        now = datetime.now()
        remaining = self.death_date - now
        total_secs = int(remaining.total_seconds())
        if total_secs < 0:
            total_secs = 0
        self.counter_label.config(text=f"    {total_secs:,}    ")
        self.root.after(1000, self.update_clock)

    def on_close(self):
        print("\nCarpe diem.\n")
        self.root.destroy()

def main():
    dob = load_or_get_dob()
    death_estimate = dob + timedelta(days=LIFE_EXPECTANCY_YEARS * 365.25)

    root = tk.Tk()
    app = MementoMoriApp(root, death_estimate)
    root.mainloop()

if __name__ == "__main__":
    main()

# python3 mm.py
