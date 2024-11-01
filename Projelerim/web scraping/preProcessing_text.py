import numpy as np
import pandas as pd
import re
import nltk
import spacy
import string
pd.options.mode.chained_assignment = None
nltk.download('vader_lexicon')

from nltk.corpus import stopwords
from nltk.stem.porter import PorterStemmer
from collections import Counter
from nltk.stem import WordNetLemmatizer 
from nltk.corpus import wordnet
from spellchecker import SpellChecker
from nltk.sentiment.vader import SentimentIntensityAnalyzer
# Veri yükleme
full_df = pd.read_csv("C:\\Users\\Efe İlhan\\Desktop\\Projelerim\\web scraping\\comments.csv")
df = full_df[["Comment"]]
df["Comment"] = df["Comment"].astype(str)

# Tüm metinleri küçük harflere çevirme
df["Comment"] = df["Comment"].str.lower()

# Noktalama işaretlerini kaldırma
PUNCT_TO_REMOVE = string.punctuation
def remove_punctuation(text):
    return text.translate(str.maketrans('', '', PUNCT_TO_REMOVE))

df["Comment"] = df["Comment"].apply(remove_punctuation)

# Stopwords kaldırma
STOPWORDS = set(stopwords.words('english'))
def remove_stopwords(text):
    return " ".join([word for word in str(text).split() if word not in STOPWORDS])

df["Comment"] = df["Comment"].apply(remove_stopwords)

# Sık kullanılan kelimeleri kaldırma
cnt = Counter()
for text in df["Comment"].values:
    for word in text.split():
        cnt[word] += 1

FREQWORDS = set([w for (w, wc) in cnt.most_common(10)])
def remove_freqwords(text):
    return " ".join([word for word in str(text).split() if word not in FREQWORDS])

df["Comment"] = df["Comment"].apply(remove_freqwords)

# Nadir kelimeleri kaldırma
n_rare_words = 10
RAREWORDS = set([w for (w, wc) in cnt.most_common()[:-n_rare_words-1:-1]])
def remove_rarewords(text):
    return " ".join([word for word in str(text).split() if word not in RAREWORDS])

df["Comment"] = df["Comment"].apply(remove_rarewords)

# Kök bulma (stemming)
stemmer = PorterStemmer()
def stem_words(text):
    return " ".join([stemmer.stem(word) for word in text.split()])

df["Comment"] = df["Comment"].apply(stem_words)

# Lemmatizasyon
lemmatizer = WordNetLemmatizer()
wordnet_map = {"N":wordnet.NOUN, "V":wordnet.VERB, "J":wordnet.ADJ, "R":wordnet.ADV}
def lemmatize_words(text):
    pos_tagged_text = nltk.pos_tag(text.split())
    return " ".join([lemmatizer.lemmatize(word, wordnet_map.get(pos[0], wordnet.NOUN)) for word, pos in pos_tagged_text])

df["Comment"] = df["Comment"].apply(lemmatize_words)
# Yazım hatalarını düzeltme
spell = SpellChecker()
def correct_spellings(text):
    corrected_text = []
    misspelled_words = spell.unknown(text.split())
    for word in text.split():
        if word in misspelled_words:
            correction = spell.correction(word)
            if correction:  # Check if there's a correction suggestion
                corrected_text.append(correction)
            else:
                corrected_text.append(word)  # If no suggestion, keep the original word
        else:
            corrected_text.append(word)
    return " ".join(corrected_text)

print("I am here")
# df["Comment"] = df["Comment"].apply(correct_spellings)
print("sonra")
# Emoji kaldırma
def remove_emoji(text):
    emoji_pattern = re.compile("["
                           u"\U0001F600-\U0001F64F"  # emoticons
                           u"\U0001F300-\U0001F5FF"  # symbols & pictographs
                           u"\U0001F680-\U0001F6FF"  # transport & map symbols
                           u"\U0001F1E0-\U0001F1FF"  # flags (iOS)
                           u"\U00002702-\U000027B0"
                           u"\U000024C2-\U0001F251"
                           "]+", flags=re.UNICODE)
    return emoji_pattern.sub(r'', text)

df["Comment"] = df["Comment"].apply(remove_emoji)

# Emoticon kaldırma
EMOTICONS = {':)': 'smile', ':(': 'sad', ':-)': 'smile', ':-(': 'sad'}  # Örnek olarak birkaç emoticon ekledim.
def remove_emoticons(text):
    emoticon_pattern = re.compile(u'(' + u'|'.join(k for k in EMOTICONS) + u')')
    return emoticon_pattern.sub(r'', text)

df["Comment"] = df["Comment"].apply(remove_emoticons)

# URL kaldırma
def remove_urls(text):
    url_pattern = re.compile(r'https?://\S+|www\.\S+')
    return url_pattern.sub(r'', text)

df["Comment"] = df["Comment"].apply(remove_urls)

# Kısaltma dönüşümü (chat words)
chat_words_str = "u=you\nr=are\nbrb=be right back"  # Örnek olarak birkaç kısaltma ekledim.
chat_words_map_dict = {}
chat_words_list = []
for line in chat_words_str.split("\n"):
    if line != "":
        cw = line.split("=")[0]
        cw_expanded = line.split("=")[1]
        chat_words_list.append(cw)
        chat_words_map_dict[cw] = cw_expanded
chat_words_list = set(chat_words_list)

def chat_words_conversion(text):
    new_text = []
    for w in text.split():
        if w.lower() in chat_words_list:
            new_text.append(chat_words_map_dict[w.lower()])
        else:
            new_text.append(w)
    return " ".join(new_text)

df["Comment"] = df["Comment"].apply(chat_words_conversion)

# Duygusal analiz
sid = SentimentIntensityAnalyzer()

# Duygusal analiz fonksiyonu
def analyze_sentiment(text):
    scores = sid.polarity_scores(text)
    compound_score = scores['compound']
    return compound_score

# DataFrame'e duygusal analiz sonucunu uygulama
df["Sentiment_Score"] = df["Comment"].apply(analyze_sentiment)

# İşlenmiş veriyi yeni bir CSV dosyasına kaydetme
df.to_csv("C:\\Users\\Efe İlhan\\Desktop\\Projelerim\\web scraping\\Pre_procecced_comment.csv", index=False)

# Son durumu gösterme
df.head()
