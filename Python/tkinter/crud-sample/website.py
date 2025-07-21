from uuid import uuid4
import datetime

class Website:
    DATE_FORMAT_BR = "%d/%m/%Y"


    def __init__(
            self,
            /,
            url:str = None,
            category:str = None,
            date:str = None,
            id:str = None,
            notes:str = None
    ):
        if id is None:
            id = str(uuid4())
        self.id = id
        if date is None:
            date = datetime.date.today().strftime(Website.DATE_FORMAT_BR)
        else:
            try:
                datetime.datetime.strptime(date, Website.DATE_FORMAT_BR)
            except ValueError:
                date = ''
        self.date = date
        self.url = url
        self.category = category
        self.notes = notes
    

    def __str__(self):
        return f'Site {self.id}: {self.url} / {self.category} / {self.notes}'
    

