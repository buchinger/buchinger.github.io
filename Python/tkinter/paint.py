import tkinter as tk
from tkinter import ttk
from tkinter.colorchooser import askcolor

class App(tk.Tk):
    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self.title("Conversor de Temperatura")
        self.createFrame()

    def createFrame(self):
        self.frame = ttk.Frame(self)
        self.title("Paint")
        self.geometry("800x600")
        self.createTools()
        self.createBar()
        self.createDrawArea()
        self.tool = self.canvas.create_line
        self.frame.pack(expand=True, fill="both")
    
    def createTools(self):
        self.forecolor = "#222222"
        self.backcolor = ""
        self.drawing = False
        self.xi = None
        self.yi = None
        self.curr_id = 0
        self.tool = None

    def createBar(self):
        self.toolkit = ttk.Frame(self.frame, width=100, height=600)
        self.toolkit.grid(column=0, row=0, sticky=tk.NS)
        self.b_line = ttk.Button(self.toolkit, text="Line", padding="10", command=self.setToolLine)
        self.b_rectangle = ttk.Button(self.toolkit, text="Rectangle", padding="10", command=self.setToolRectangle)
        self.b_oval = ttk.Button(self.toolkit, text="Ellipse", padding="10", command=self.setToolOval)
        self.b_undo = ttk.Button(self.toolkit, text="Undo", padding="10", command=self.undo)
        self.b_clear = ttk.Button(self.toolkit, text="Clear", padding="10", command=self.clear)
        for button in (self.b_line, self.b_rectangle, self.b_oval, self.b_undo, self.b_clear):
            button.pack()

        self.label_forecolor = ttk.Label(self.toolkit, text='Foreground')
        self.label_forecolor.pack()
        self.b_forecolor = tk.Button(self.toolkit, text="Color", command=self.choseForecolor, bg=self.forecolor)
        self.b_forecolor.pack(fill='x')
        self.label_backcolor = ttk.Label(self.toolkit, text='Backgound')
        self.label_backcolor.pack()
        self.b_backcolor = tk.Button(self.toolkit, text="Transparente", command=self.choseBackcolor, bg=None)
        self.b_backcolor.pack(fill='x')    

    def choseForecolor(self):
        color = askcolor(title="Foreground Color")
        if color[1]:
            self.forecolor = color[1]
            self.b_forecolor.config(background=self.forecolor)

    def choseBackcolor(self):
        color = askcolor(title="Background Color")
        self.backcolor = color[1] or ""
        self.b_backcolor.config(
            text="Transparent" if self.backcolor == "" else "",
            background=self.backcolor or "SystemButtonFace"
        )

    def setToolLine(self):
        self.tool = self.canvas.create_line

    def setToolRectangle(self):
        self.tool = self.canvas.create_rectangle

    def setToolOval(self):
        self.tool = self.canvas.create_oval
    
    def undo(self):
        if itens := self.canvas.find_withtag("draw"):
            self.canvas.delete(itens[-1])

    def clear(self):
        self.canvas.delete("draw")
    
    def createDrawArea(self):
        self.workspace = ttk.Frame(self.frame, height=600)
        self.workspace.grid(column=1, row=0, sticky=tk.NSEW)
        self.frame.grid_columnconfigure(1, weight=1)
        self.frame.grid_rowconfigure(0, weight=1)
        self.canvas = tk.Canvas(self.workspace, background="#FFFFFF")
        self.canvas.pack(fill=tk.BOTH, expand=True)
        self.createCanvasElements()
        self.coordinates = tk.Label(self.workspace, text="Move your mouse")
        self.coordinates.pack(ipadx=10, ipady=10)

    def createCanvasElements(self):
        self.canvas.bind("<Motion>", self.mouseMove)
        self.canvas.bind("<Button-1>", self.mouseClick)
        self.canvas.bind("<ButtonRelease-1>", self.mouseRelease)
        self.mouse_cross = []
        for i in range(2):
            self.mouse_cross.append(self.canvas.create_line((0, 0, 0, 0), dash=[2,4]))

    def mouseMove(self, event):
        self.coordinates["text"] = f"Mouse x={event.x} y={event.y}"
        self.canvas.coords(self.mouse_cross[0], event.x, 0, event.x, self.canvas.winfo_height())
        self.canvas.coords(self.mouse_cross[1], 0, event.y, self.canvas.winfo_width(), event.y)
        # if is currently drawing - draw the shape
        if self.drawing:
            if self.canvas.type(self.curr_id) in ['rectangle', 'oval']:
                self.canvas.itemconfig(self.curr_id, {"outline": self.forecolor, "fill": self.backcolor})
            self.canvas.coords(self.curr_id, self.xi, self.yi, event.x, event.y) 
    
    def mouseClick(self, event):
        if not self.drawing:
            self.xi = event.x
            self.yi = event.y
            self.curr_id = self.tool((self.xi, self.yi, event.x, event.y), fill=self.forecolor, tags=["draw"])
            self.drawing = True

    def mouseRelease(self, event):
        if self.drawing:
            self.drawing = False

App().mainloop()
