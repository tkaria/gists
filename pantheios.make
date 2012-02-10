CC=g++
LIBS= -L $(PANTHEIOS_ROOT)/lib \
        -l pantheios.1.core.gcc44.file64bit \
        -l pantheios.1.fe.simple.gcc44.file64bit \
        -l pantheios.1.util.gcc44.file64bit \
        -l pantheios.1.be.N.gcc44.file64bit \
        -l pantheios.1.bec.file.gcc44.file64bit \
        -l pantheios.1.bec.fprintf.gcc44.file64bit \
        -l pantheios.1.util.gcc44.file64bit \
        -l pantheios.1.core.gcc44.file64bit 

INCLUDE= -I $(PANTHEIOS_ROOT)/include -I $(STLSOFT)/include


pantheios: pantheios.cpp
	echo $(PANTHEIOS_ROOT)
	$(CC) pantheios.cpp $(INCLUDE) $(LIBS) -o $@


p2: p2.cpp
	$(CC) p2.cpp $(INCLUDE) $(LIBS) -o $@
	
p3: p3.cpp
	$(CC) p3.cpp $(INCLUDE) $(LIBS) -o $@

# NOTE - this is the multiplex - to file and console that works!!!!
# that is, p4 works 
p4: p4.cpp
	$(CC) p4.cpp $(INCLUDE) $(LIBS) -o $@

# NOTE - this is the multiplex - to file and console that works!!!!
# that is, p4 works 
p5: p5.cpp
	$(CC) p5.cpp $(INCLUDE) $(LIBS) -o $@
