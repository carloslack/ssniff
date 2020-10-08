#
# Makefile
# 

CC= 		gcc
CFLAGS= 	-I -O0 -Wall -g -ggdb -static
SRC= 		./src
STRIP= 		$(SRC)/strip
ARP= 		$(SRC)/arp
IP=			$(SRC)/ip
HEX= 		$(SRC)/hex
IFACE= 		$(SRC)/interface
MISC= 		$(SRC)/misc
USE= 		$(SRC)/usage
OUT= 		./ssnif
OBJS= 		$(SRC)/main.o \
	  			$(MISC)/int.o \
	  			$(MISC)/str.o \
	  			$(MISC)/mem.o \
	  			$(MISC)/verifyData.o \
	  			$(IFACE)/setIface.o \
	  			$(HEX)/ip_hex.o \
	  			$(ARP)/arp.o \
	  			$(IP)/ipReg.o \
	  			$(IP)/ipShort.o \
	  			$(IP)/ipVerb.o \
	  			$(IP)/dataDump.o \
	  			$(STRIP)/stripInput.o \
	  			$(STRIP)/setUnit.o \
	  			$(USE)/usage.o


ssnif: 	$(OBJS)
		$(CC) -o $(OUT) $(OBJS) $(CFLAGS)

clean:
	rm -rf $(OUT) *.o
	rm -rf $(SRC)/*.o
	rm -rf $(STRIP)/*.o
	rm -rf $(ARP)/*.o
	rm -rf $(IP)/*.o
	rm -rf $(HEX)/*.o
	rm -rf $(IFACE)/*.o
	rm -rf $(MISC)/*.o
	rm -rf $(USE)/*.o
	@echo "Clean."
