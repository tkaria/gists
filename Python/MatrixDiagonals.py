# In[94]:

def read_matrix(file_name):
    m = []
    with open(file_name) as file:
        size = int(file.readline().strip())
        for x in range(0,size):
            m.append([])
            m[x] = file.readline().strip().split(' ')
    return (size, m)


# In[101]:

(size, m) = read_matrix('/Users/timir/projects/PythonGists/matrix_input.txt')


# In[96]:

def diag(matrix, size, reverse = False):
    sum = 0
    for x in range(0, size):
        if reverse is True:
            #print 'Elem: %s %s' % (x, m[x][size-x-1])
            sum += int(matrix[x][size-x-1])
        else:
            #print 'Elem: %s %s' % (x, m[x][x])
            sum += int(matrix[x][x])
        #print sum
    return sum


# In[103]:

diag(m, size)


# In[104]:

diag(m, size, reverse = True)


# In[108]:

diff = abs(diag(m, size) - diag(m, size, reverse=True))


# In[109]:

print diff


# In[ ]:



