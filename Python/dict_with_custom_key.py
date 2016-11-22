
class foo:
    def __init__(self, x): 
        self.num = x

    def __str__(self):
        return "foo=> %d" % self.num
    
    def __hash__(self):
        h = self.num.__hash__()
        print "__hash__: %d" % h
        return h

    def __eq__(self, other):
        print "__eq__: ", other
        return self.num == other.num

    def __ne__(self, other):
        print "__ne__:", other
        return self.num != other.num

    def __setitem__(self, y):
        self.num = y

    def __getitem__(self, z):
        self.num = z

# dict with native types
d = {}

d['a'] = 1
d['b'] = 2
d['c'] = 3
print "Original: ", d
d['c'] = 999
print "Modify element in place: ", d
x = d['c'];
x = 5
print "Modify assigned element: ", d
zip = d['k']

   
# dict with custom types
d1 = {}
f1 = foo(1)
f2 = foo(2)
f3 = foo(3)
d1[f1] = 'a'
d1[f2] = 'b'
for k,v in d1.items():
    print k,v 

bar = d1[f3]
print bar
print "Keys: %s" % d1.keys()
