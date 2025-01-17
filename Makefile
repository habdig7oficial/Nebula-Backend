run: 
	g++ trigger.cpp -D BACKEND_PORT=7777 -D CROW_ENABLE_COMPRESSION -D NEBULA_COMPRESSION_GZIP -o nebula.elf -lpqxx -lpq -lz && ./nebula.elf
