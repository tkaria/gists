import zmq
from random import choice
context = zmq.Context()
socket = context.socket(zmq.PUB)
socket.bind("tcp://127.0.0.1:5000")

countries = ['NL', 'BR', 'GR', 'PO']
events = ['yellow', 'red', 'goal', 'corner', 'foul']

while True:
    msg = choice(countries) + " " + choice(events)
    print "->", msg
    socket.send(msg)

