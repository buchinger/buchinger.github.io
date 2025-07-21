import tkinter as tk
from tkinter import ttk

class Contador(ttk.Frame):
    def __init__(self, number, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self.counter = 0
        self.number = number
        self.label = ttk.Label(self, text=self.formatCont())
        self.label.pack()
        self.button = ttk.Button(self, text=f"Somar contador #{self.number}", command=self.sumCont)
        self.button.pack()
        self.pack()

    def formatCont(self):
        return f"Valor do contador #{self.number}: {self.counter}"
    
    def sumCont(self):
        self.counter += 1
        self.label["text"] = self.formatCont()


class Aplicação(tk.Tk):
    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self.counters = []
        self.title("Janela Principal")
        # self.geometry("250x50")
        self.createFrame()

    def createFrame(self):
        self.frame = ttk.Frame(self)
        self.button = ttk.Button(self.frame, text="Adicionar novo contador", command=self.add_counter)
        self.button.pack()
        self.frame.pack(expand=True)
        
    def add_counter(self):
        new_counter = Contador(len(self.counters) + 1, master=self.frame)
        self.counters.append(new_counter)

raiz = Aplicação()
raiz.mainloop()
