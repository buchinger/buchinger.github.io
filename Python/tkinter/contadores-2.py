import tkinter as tk
from tkinter import ttk

class Aplicação(tk.Tk):
    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self.cont = 0
        self.title("Janela Principal")
        self.geometry("250x125")
        self.createFrame()

    def formatCont(self):
        return f"Valor do contador: {self.cont}"

    def createFrame(self):
        self.frame = ttk.Frame(self)
        self.label_cont = ttk.Label(self.frame, text=self.formatCont())
        self.label_cont.pack()
        self.button_1 = ttk.Button(self.frame, text="Somar 1 ao contador", command=self.sumCont)
        self.button_1.pack()
        self.button_2 = ttk.Button(self.frame, text="Multiplicar contador por 2", command=self.multiplyCont)
        self.button_2.pack()
        self.frame.pack(expand=True)

    def sumCont(self):
        self.cont += 1
        self.label_cont["text"] = self.formatCont()
    
    def multiplyCont(self):
        self.cont *= 2
        self.label_cont["text"] = self.formatCont()

raiz = Aplicação()
raiz.mainloop()
