run: 
	g++ trigger.cpp -DCROW_ENABLE_COMPRESSION -o nebula.elf -lpqxx -lpq -lz && ./nebula.elf