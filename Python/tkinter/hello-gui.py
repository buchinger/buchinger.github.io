import tkinter as tk
from tkinter import ttk

raiz = tk.Tk()
raiz.title("Janela Principal")
raiz.geometry("250x150")
quadro = ttk.Frame(raiz)
texto = ttk.Label(quadro, text="Olá GUI!")
texto.pack()

botão = ttk.Button(quadro, text="Fechar", command=raiz.destroy)
botão.pack()
quadro.pack(expand=True)
raiz.mainloop()
