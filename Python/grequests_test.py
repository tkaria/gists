from __future__ import print_function
import grequests
import requests

urls = [
    'http://www.heroku.com',
    'http://python-tablib.org',
    'http://httpbin.org',
    'http://python-requests.org',
    'http://fakedomain/',
    'http://kennethreitz.com'
]


def exception_handler(request, exception):
    print("Request failed", request, exception)

def print_response(response, *args, **kwargs):
    # print(args)
    # print(kwargs)
    # print(response)
    # print(response.content)
    print(response.request.url)
    print(response.request.headers)

header = {
    'User-Agent': 'Mozilla/5.0 AppleWebKit/537.36 (KHTML, like Gecko; compatible; Googlebot/2.1; +http://www.google.com/bot.html) Safari/537.36',
    'X-entity-id': '123'
}
headers = requests.utils.default_headers()
headers.update(header)

timeout = None

# https://stackoverflow.com/questions/41947557/imap-vs-map-in-grequests-library
# Using map
rs = (grequests.get(u, headers=headers, hooks=dict(response=print_response)) for u in urls)
results = grequests.map(rs, exception_handler=exception_handler)

# Using imap generator
# results = grequests.map(rs, exception_handler=exception_handler)
# for x in results:
#     print_response(x)

# print(results)

# for url in urls:
#     response = requests.get(url, headers=headers, timeout=timeout)
#     print(response)
