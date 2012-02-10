#########################
#NOTE:
#The core lib is essential part
#We use fe.all front-end lib so we can log with all severity levels
#We use stock fprintf back-end so we link to be.fprintf and bec.fprintf lib
#Util lib may be needed so we link to it
#########################
p: p.o
	g++ -o p.exe p.o -L$(PANTHEIOS_ROOT)/lib \
-lpantheios.1.core.gcc44.file64bit \
-lpantheios.1.be.fprintf.gcc44.file64bit -lpantheios.1.bec.fprintf.gcc44.file64bit \
-lpantheios.1.fe.all.gcc44.file64bit -lpantheios.1.util.gcc44.file64bit -lpantheios.1.be.file.gcc44.file64bit

p.o: p.cpp
	g++ p.cpp -c -I$(PANTHEIOS_ROOT)/include -I$(STLSOFT)/include
clean:
	rm -f p.o p
