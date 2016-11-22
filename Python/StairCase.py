
# coding: utf-8

# In[33]:

def StairCase(n):
    for x in range(0, n):
        fill = n - (n-x)
        print ' ' * int(n-x-1) + '#' * int(fill + 1)
        


# In[34]:

foo(6)


# In[ ]:



