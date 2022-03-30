import os
import random


def show(word: str):
    os.system("clear")
    print()
    for letter in word:
        print("  \033[4m %s \033[0m" % letter, end="")
    print('\n')


with open('1-1000.txt') as words_file:
    data = words_file.read()
    words = data.split('\n')
    
word = random.choice(words)
word = word.upper()
show(word)
