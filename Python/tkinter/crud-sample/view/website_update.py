import tkinter as tk
import tkinter.ttk as ttk
from website import Website
from view.data_widget import tkDate

class WebsiteUpdateView(tk.Toplevel):
    MIN_Y = 300
    MIN_X = 300
    PAD_XY = 10

    def __init__(self, parent, site, on_change=None):
        super().__init__(parent)
        self.geometry(f"{self.MIN_X}x{self.MIN_Y}")
        self.title("Website Record")
        self.padding = {"padx": self.PAD_XY, "pady": self.PAD_XY}
        self.on_change = on_change
        self.createControls()
        self.minsize(self.MIN_X, self.MIN_Y)
        self.websiteLoad(site)

    def websiteLoad(self, site):
        self.site = site or Website()
        self.url.set(self.site.url or "")
        self.date.set(self.site.date)
        self.category.set(self.site.category or "")
        # delete notes value from row 1 column 0 (1.0) to the end
        self.entry_notes.delete("1.0", tk.END)
        # insert value starting from row 1 column 0 (1.0)
        self.entry_notes.insert("1.0", self.site.notes or "")

    def __putURL__(self):
        self.frame_url = ttk.Frame(self)
        self.frame_url.grid(row=0, column=0, columnspan=3, sticky=tk.EW, **self.padding)
        self.label_url = ttk.Label(self.frame_url, text="URL")
        self.label_url.pack(anchor=tk.W)
        self.url = tk.StringVar()
        self.entry_url = ttk.Entry(self.frame_url, textvariable=self.url)
        self.entry_url.pack(fill=tk.X, expand=True)
    
    def __putCategory__(self):
        self.frame_category = ttk.Frame(self)
        self.frame_category.grid(row=1, column=0, sticky=tk.W, **self.padding)
        self.label_category = ttk.Label(self.frame_category, text="Category")
        self.label_category.pack(anchor=tk.W)
        self.category = tk.StringVar()
        self.entry_category = ttk.Entry(self.frame_category, textvariable=self.category)
        self.entry_category.pack()
    
    def __putDate__(self):
        self.frame_date = ttk.Frame(self)
        self.frame_date.grid(row=1, column=2, sticky=tk.E, **self.padding)
        self.label_date = ttk.Label(self.frame_date, text="Date")
        self.label_date.pack(anchor=tk.W)
        self.date = tkDate(self.frame_date)
        self.date.pack()

    def __putNotes__(self):
        self.frame_notes = ttk.Frame(self)
        self.frame_notes.grid(row=2, column=0, columnspan=3, sticky=tk.NSEW, **self.padding)
        self.label_notes = ttk.Label(self.frame_notes, text="Notes")
        self.label_notes.pack(anchor=tk.W)
        self.entry_notes = tk.Text(self.frame_notes, height=3)
        self.entry_notes.pack(fill=tk.BOTH, expand=True)

    def __putButtons__(self):
        self.frame_buttons = ttk.Frame(self)
        self.frame_buttons.grid(row=3, column=0, columnspan=3, **self.padding)
        self.button_ok = ttk.Button(self.frame_buttons, text="Ok", command=self.ok)
        self.button_ok.pack(side=tk.LEFT)
        self.button_cancel = ttk.Button(self.frame_buttons, text="Cancel", command=self.close)
        self.button_cancel.pack(side=tk.LEFT)

    def createControls(self):
        self.__putURL__()
        self.__putCategory__()
        self.__putDate__()
        self.__putNotes__()
        self.grid_columnconfigure(0, weight=2)
        self.grid_columnconfigure(2, weight=1)
        self.grid_rowconfigure(2, weight=1)
        self.__putButtons__()

    def close(self):
        self.destroy()

    def ok(self):
        self.site.url = self.url.get()
        self.site.category = self.category.get()
        self.site.date = self.date.get()
        self.site.notes = self.entry_notes.get('1.0', tk.END)
        if self.on_change:
            self.on_change(self.site)
        self.close()

