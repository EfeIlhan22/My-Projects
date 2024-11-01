import requests
from bs4 import BeautifulSoup


# Making a GET request
r = requests.get('https://www.theshedend.com/topic/23522-our-new-stadium/')

# Parsing the HTML
soup = BeautifulSoup(r.content, 'html.parser')

s = soup.find('div', class_='cPost_contentWrap')
content = s.find_all('p')

print(content)