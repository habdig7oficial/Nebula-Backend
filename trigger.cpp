/* 
Compile com o G++: g++ trigger.cpp -o nebula.elf -lpqxx -lpq && ./nebula.elf
Com Compressão: g++ trigger.cpp -DCROW_ENABLE_COMPRESSION -o nebula.elf -lpqxx -lpq -lz && ./nebula.elf
*/

#include "crow.h"
#include "crow/middlewares/cors.h"
#include "iostream"
#include "pqxx/pqxx"
#include "env.h"
#include "vector"

#include "routes/routes.hpp"


#if defined(NEBULA_COMPRESSION_GZIP) || defined(NEBULA_COMPRESSION_DEFLATE)
    #include "crow/compression.h"
#endif

#if !defined(BACKEND_PORT)
    #define BACKEND_PORT 7777
#endif

using namespace std;
using namespace crow;


int main(){

    crow::App<crow::CORSHandler> app;
    
    CROW_ROUTE(app, "/posts/new").methods("POST"_method)(new_posts);
    CROW_ROUTE(app, "/posts/read").methods("GET"_method)(read_posts);
    CROW_ROUTE(app, "/").methods("GET"_method)(index_route);

    CROW_CATCHALL_ROUTE(app)([](const crow::request&, crow::response& res){

        switch(res.code){
            case 404:
                res.body = "Not found!!!";
        };

        res.end();
    });


    app.port(BACKEND_PORT)
        #if defined(NEBULA_COMPRESSION_GZIP)
            .use_compression(crow::compression::algorithm::GZIP)
        #endif
        #if defined(NEBULA_COMPRESSION_DEFLATE)
            .use_compression(crow::compression::algorithm::DEFLATE)
        #endif
        .multithreaded()
        .run();
}