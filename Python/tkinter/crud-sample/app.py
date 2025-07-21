import tkinter as tk
import tkinter.ttk as ttk
import tkinter.filedialog
import tkinter.messagebox
from website import Website
from websiteDAO import WebsiteDAO 
from view.website_update import WebsiteUpdateView

class App(tk.Tk):
    DATA_JSON = "web_data.json"
    MIN_Y = 200
    MIN_X = 800

    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self.title("Website Manager")
        self.geometry(f"{App.MIN_X}x{App.MIN_Y}")
        self.createControls()
        self.website_dao = WebsiteDAO(App.DATA_JSON)
        self.showData()
        self.minsize(App.MIN_X, App.MIN_Y)

    def createControls(self):
        self.frame = ttk.Frame(self)
        self.frame.grid(row=0, column=0, columnspan=2, padx=10, pady=10, sticky=tk.NSEW)
        self.grid_rowconfigure(0, weight=1)
        self.table = ttk.Treeview(
            self.frame, columns=['url', 'category', 'date', 'notes'], show='headings'
        )
        self.table.heading("url", text="URL")
        self.table.heading("category", text="Category")
        self.table.heading("date", text="Date")
        self.table.heading("notes", text="Notes")
        for key in ('category', 'date'):
            self.table.column(key, anchor=tk.CENTER)
        self.table.grid(row=0, column=0, sticky=tk.NSEW)
        self.table.config(selectmode='browse')
        scrollbar = ttk.Scrollbar(self.frame, orient=tk.VERTICAL, command=self.table.yview)
        self.table.configure(yscroll=scrollbar.set)
        scrollbar.grid(row=0, column=1, sticky=tk.NS)
        self.table.bind("<Double-Button-1>", self.editWebsite)
        self.frame.grid_columnconfigure(0, weight=1)
        self.frame.grid_rowconfigure(0, weight=1)
        self.frame.pack(expand=True, fill=tk.BOTH, padx=10, pady=10)
        self.__putMenu__()

    def __putMenu__(self):
        self.menu = tk.Menu(self)
        self.menu_file = tk.Menu(self.menu, tearoff=0)
        self.menu_file.add_command(label="Load", command=self.load)
        self.menu_file.add_command(label="Save", command=self.save)
        self.menu_sites = tk.Menu(self.menu, tearoff=0)
        self.menu_sites.add_command(label="Add", command=self.addWebsiteNew)
        self.menu_sites.add_command(label="Remove", command=self.removeWebsite)
        self.menu_sites.add_separator()
        self.menu_sites.add_command(label="Clear", command=self.clearWebsites)
        self.menu.add_cascade(label="File", menu=self.menu_file)
        self.menu.add_cascade(label="Websites", menu=self.menu_sites)
        self.menu.add_command(label="About", command=self.about)
        self.config(menu=self.menu)
    
    def removeWebsite(self):
        if selected := self.table.selection():
            id_site = selected[0]
            site = self.website_dao.deleteWebsite(id_site)
            self.table.delete(id_site)
    
    def clearWebsites(self):
        if tkinter.messagebox.askquestion(
            title="Clear all Websites",
            message="You really want to clear all Website records?"
        ) == "yes":
            self.__clear__()
    
    def __clear__(self):
        self.website_dao.clear()
        self.table.delete(*self.table.get_children())
    
    def about(self):
        tkinter.messagebox.showinfo(
            title="About",
            message="Learning about tkinter in Python"
        )
    
    def load(self):
        if filename := tkinter.filedialog.askopenfilename(filetypes=[('JSON', '*.json')]):
            self.__clear__()
            self.website_dao.load(filename)
            self.showData()

    def save(self):
        if filename := tkinter.filedialog.asksaveasfilename(
            filetypes=[('JOSN', '*.json')],
            defaultextension='.json'
        ):
            self.website_dao.save(filename)

    def showData(self):
        for site in self.website_dao.getWebsites():
            self.addWebsite(site)
            
    def addWebsite(self, site=None):
        if site is None:
            site = Website()
        self.table.insert(
            parent = "",
            index = tk.END,
            iid = site.id,
            values = (site.url, site.category, site.date, site.notes)
        )

    def addWebsiteNew(self):
        site = Website()
        self.website_dao.addWebsite(site)
        self.addWebsite(site)
    
    def editWebsite(self, event):
        site = None
        if selected := self.table.selection():
            # selection() allows for multiple record selection, then we grab the first element
            id_site = selected[0]
            site = self.website_dao.getWebsite(id_site)
        self.showWebsite(site)

    def showWebsite(self, site):
        self.window = WebsiteUpdateView(self, site=site, on_change=self.update)
        self.window.grab_set()

    def update(self, site:Website):
        if self.table.exists(site.id):
            self.table.item(site.id, text="",values=(site.url, site.category, site.date, site.notes))
            self.website_dao.updateWebsite(site)
        else:
            self.addWebsite(site)
        
    

App().mainloop()