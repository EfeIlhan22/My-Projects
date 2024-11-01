import requests
from bs4 import BeautifulSoup
import pandas as pd

comments = []

for i in range(1, 158):  # İlk iki sayfayı almak için range(1, 3) kullanıyoruz
    url = f"https://www.theshedend.com/topic/23522-our-new-stadium/page/{i}/#comments"
    response = requests.get(url, verify=False)
    response = response.content
    soup = BeautifulSoup(response, 'html.parser')
    div = soup.find_all('div', class_='cPost_contentWrap')
    for p in div:
        # <p> etiketini içeren içerikleri alıyoruz
        paragraph = p.find('p')
        if paragraph:  # Eğer <p> etiketi bulunduysa
            comment = paragraph.get_text()  # <p> etiketinin içeriğini al
            comments.append(comment)


df = pd.DataFrame(comments, columns=['Comment'])
df.to_csv('comments.csv', index=False)  # index'i CSV'ye yazmamak için index=False kullanıyoruz
