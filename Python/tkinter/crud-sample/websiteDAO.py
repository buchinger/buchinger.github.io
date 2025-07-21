import json
from website import Website

class WebsiteDAO:

    def __init__(self, filename:str = None):
        self.__website_dict__ = {}
        if filename is not None:
            self.load(filename)

    def __str__(self):
        return f'There is/are {len(self.__website_dict__)} website record(s)'

    def getWebsite(self, id:str) -> Website:
        """Retrieve a website by its ID."""
        if id in self.__website_dict__:
            return self.__website_dict__[id]
        raise ValueError(f"Website with id {id} does not exist.")
    
    def getWebsites(self):
        return list(self.__website_dict__.values())

    def addWebsite(self, site:Website):
        if site.id in self.__website_dict__:
            raise ValueError(f"Website with id {site.id} already exists.")
        self.__website_dict__[site.id] = site
    
    def updateWebsite(self, site:Website):
        if site.id not in self.__website_dict__:
            raise ValueError(f"Website with id {site.id} does not exist.")
        self.__website_dict__[site.id] = site

    def deleteWebsite(self, id:str) -> Website:
        """Delete a website by its ID and return the deleted website."""
        if id in self.__website_dict__:
            return self.__website_dict__.pop(id)
        raise ValueError(f"Website with id {id} does not exist.")

    def clear(self):
        self.__website_dict__.clear()
    
    def save(self, filename:str):
        with open(filename, 'w') as file:
            websites = []
            for site in self.__website_dict__.values():
                websites.append({
                    "id": site.id,
                    "url": site.url,
                    "category": site.category,
                    "date": site.date,
                    "notes": site.notes
                })
            json.dump(websites, file, indent=2, sort_keys=True)

    def load(self, filename:str):
        with open(filename) as file:
            websites = json.load(file)
        self.__website_dict__.clear()

        for record in websites:
            site = Website(
                id = record.get("id"),
                category = record.get("category"),
                date = record["date"],
                url = record["url"],
                notes = record.get("notes")
            )
            self.__website_dict__[site.id] = site
    

