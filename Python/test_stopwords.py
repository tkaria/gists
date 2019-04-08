"""
AWS Lambda entry point for keyword generation given JSON file with text
"""

from __future__ import print_function
import logging
import os
import json
import settings
import requests
from stop_words import get_stop_words

STOPWORDS_EN = get_stop_words('en')
STOPWORDS_DE = get_stop_words('de')
STOPWORDS_NL = get_stop_words('nl')



if __name__ == '__main__':
    print(STOPWORDS_EN)
    print(STOPWORDS_DE)
    print(STOPWORDS_NL)

