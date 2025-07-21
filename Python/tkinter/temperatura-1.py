import tkinter as tk
from tkinter import ttk

class Aplicação(tk.Tk):
    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self.title("Conversor de Temperatura")
        self.createFrame()

    def createFrame(self):
        self.frame = ttk.Frame(self, padding="100 20")
        self.label_temperature = ttk.Label(self.frame, text="Temperature")
        self.label_temperature.pack(pady=10)
        self.entry_temperature = ttk.Entry(self.frame, justify='center')
        self.entry_temperature.pack(ipady=5)
        self.button_celsius_fahrenheit = ttk.Button(
            self.frame,
            text = "Celsius to Fahrenheit",
            command = self.convertCelsiusFahrenheit
        )
        self.button_celsius_fahrenheit.pack(padx=10, pady=10, ipadx=7, ipady=3)
        self.button_fahrenheit_celsius = ttk.Button(
            self.frame,
            text = "Fahrenheit to Celsius",
            command = self.convertFahrenheitCelsius
        )
        self.button_fahrenheit_celsius.pack(ipadx=7, ipady=3)
        self.label_response = ttk.Label(self.frame, text="Result")
        self.label_response.pack(pady=10)
        self.frame.pack(expand=True)

    def convertFahrenheitCelsius(self):
        temperature = self.entry_temperature.get().replace(",", ".")
        temp = float(temperature)
        celsius = (temp - 32) * 5 / 9.0
        self.label_response["text"] = f"Result: {celsius:5.2f}°C"
    
    def convertCelsiusFahrenheit(self):
        temperature = self.entry_temperature.get().replace(",", ".")
        temp = float(temperature)
        fahrenheit = 9.0 * temp / 5 + 32 
        self.label_response["text"] = f"Result: {fahrenheit:5.2f}°F"

raiz = Aplicação()
raiz.mainloop()
