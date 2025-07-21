import tkinter as tk
import tkinter.ttk as ttk

class tkDate(ttk.Frame):

    def __init__(self, parent, min_year=1900, max_year=2040):
        super().__init__(parent)
        self.min_year = min_year
        self.max_year = max_year
        self.day = tk.StringVar()
        self.month = tk.StringVar()
        self.year = tk.StringVar()
        self.createControls()

    def set(self, date):
        day, month, year = date.split("/")
        self.day.set(day)
        self.month.set(month)
        self.year.set(year)
    
    def get(self):
        return f"{self.day.get()}/{self.month.get()}/{self.year.get()}"

    def createControls(self):
        self.cb_day = ttk.Combobox(
            master = self,
            textvariable = self.day,
            width = 3,
            values = [f"{d:02d}" for d in range(1, 32)],
            state = "readonly"
        )
        self.cb_day.pack(side=tk.LEFT)
        self.cb_month = ttk.Combobox(
            master = self,
            textvariable = self.month,
            width = 3,
            values = [f"{m:02d}" for m in range(1, 13)],
            state = "readonly"
        )
        self.cb_month.pack(side=tk.LEFT)
        self.cb_year = ttk.Combobox(
            master = self,
            textvariable = self.year,
            width = 6,
            values = [f"{y:04d}" for y in range(self.min_year, self.max_year + 1)],
            state = "readonly"
        )
        self.cb_year.pack(side=tk.LEFT)

