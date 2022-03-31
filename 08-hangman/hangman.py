import os
import random
from select import select
import sys
from time import sleep
from typing import Union

from pynput.keyboard import (
    Key, KeyCode, Listener
)


hidden_word: str

cur_word: bytearray

pos: int = 0


def draw():
    '''Something.'''
    underline = lambda s: '\033[4m%s\033[0m' % s
    
    sleep(0.001)
    os.system('clear')
    print(' [Hangman]\n')
    for byte in cur_word:
        letter = chr(byte)
        s = underline(' %s ' % letter)
        print('  %s ' % s, end='')
    
    i, j = 3, (4 + 6*pos)
    print('\x1b[%d;%dH' % (i, j), end='', flush=True)


def on_press(key: Union[Key, KeyCode]):
    # print('%s pressed' % key)    
    draw()


def on_release(key: Union[Key, KeyCode]):
    # print('%s released' % key)
    global pos
    if key == Key.left:
        pos = max(pos - 1, 0)
    elif key == Key.right:
        pos = min(pos + 1, len(hidden_word) - 1)
    elif isinstance(key, KeyCode) and key.char.isalpha():
        cur_word[pos] = ord(key.char.upper())
    draw()
    return key != Key.esc


with open('1-1000.txt') as words_file:
    data = words_file.read()
    words = data.split('\n')
    hidden_word = random.choice(words).upper()

cur_word = bytearray(' ' * len(hidden_word), 'ascii')
draw()

with Listener(on_press, on_release) as listener:
    listener.join()
