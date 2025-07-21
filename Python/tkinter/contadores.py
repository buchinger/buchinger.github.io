import tkinter as tk
from tkinter import ttk

contador1 = 0
contador2 = 0

def formatar_contador(contador, valor):
    return f"Contador #{contador} = {valor}"

def incrementa_contador_1():
    global contador1, label_contador1
    contador1 += 1
    label_contador1["text"] = formatar_contador(1, contador1)

def incrementa_contador_2():
    global contador2, label_contador2
    contador2 += 1
    label_contador2["text"] = formatar_contador(2, contador2)

raiz = tk.Tk()
raiz.title("Janela Principal")
raiz.geometry("250x150")
quadro = ttk.Frame(raiz)

label_contador1 = ttk.Label(quadro, text=formatar_contador(1, contador1))
label_contador1.pack()
botão = ttk.Button(quadro, text="Adicionar Contador 1", command=incrementa_contador_1)
botão.pack()

label_contador2 = ttk.Label(quadro, text=formatar_contador(2, contador2))
label_contador2.pack()
botão = ttk.Button(quadro, text="Adicionar Contador 2", command=incrementa_contador_2)
botão.pack()

quadro.pack(expand=True)
raiz.mainloop()
