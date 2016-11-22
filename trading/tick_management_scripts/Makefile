SYSTEM_BASE=./system_kr
MARKET_DATA_FIX=$(SYSTEM_BASE)/market_data/collect-fix
ORDER_ENTRY_FIX=$(SYSTEM_BASE)/order_entry/order-fix
CONFIGURATION_SERVER=$(SYSTEM_BASE)/configuration_server
TRADE_SERIALIZER=$(SYSTEM_BASE)/trade_serializer
AGGREGATED_BOOK=$(SYSTEM_BASE)/aggregated_book
VALIDATE_SYMBOLS=$(SYSTEM_BASE)/validate_symbols


ifeq ($(dbg),1)
        CFLAGS = -Wall -std=c++0x -pthread -DDEBUG -ggdb  -DLOG -pg
		LDFLAGS= -pg
endif

all: none 


none: 
	@echo "Use make install to install to /usr/local/capk"

install :
	@echo "Building market data connector for FIX"
	cd $(MARKET_DATA_FIX) && make clean && make 	
	@echo "Building order entry for FIX"
	cd $(ORDER_ENTRY_FIX) && make clean && make 	
	@echo "Building configuration server"
	cd $(CONFIGURATION_SERVER) && make clean && make 	
	@echo "Building mysql databse schema"
	#cd $(TRADE_SERIALIZER) && run_sql_cmds.sh 	
	@echo "Building trade serializer"
	cd $(TRADE_SERIALIZER) && make clean && make 	
	@echo "Building aggregated book"
	cd $(AGGREGATED_BOOK) && make clean && make 	
	@echo "Building symbol validation"
	cd $(VALIDATE_SYMBOLS) && make clean && make 	


