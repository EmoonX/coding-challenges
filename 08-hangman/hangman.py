import os
import random
from select import select
import sys
from time import sleep

from pynput.keyboard import Key, Listener


word: str

pos: int = 0


def draw():
    '''Something.'''
    underline = lambda s: '\033[4m%s\033[0m' % s
    
    sleep(0.001)
    os.system('clear')
    print(' [Hangman]\n')
    for letter in word:
        print('  %s ' % underline(' %s ' % ' '), end='')
    
    i, j = 3, (4 + 6*pos)
    print('\x1b[%d;%df' % (i, j), end='')
    print(underline('A'), end='')
    print('\x1b[%d;%df' % (i, j), end='', flush=True)


def on_press(key: Key):
    # print('%s pressed' % key)    
    draw()


def on_release(key: Key):
    # print('%s released' % key)
    global pos
    if key == Key.left:
        pos = max(pos - 1, 0)
        draw()
    elif key == Key.right:
        pos = min(pos + 1, len(word) - 1)
        draw()
    return key != Key.esc


with open('1-1000.txt') as words_file:
    data = words_file.read()
    words = data.split('\n')
    word = random.choice(words)
    word = word.upper()

draw()

with Listener(on_press, on_release) as listener:
    listener.join()
