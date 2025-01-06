/* Compile com o G++: g++ trigger.cpp -o nebula.elf -lpqxx -lpq && ./nebula.elf */

#include "crow.h"
#include "iostream"
#include "pqxx/pqxx"
#include "env.h"

using namespace std;


int main(){
    crow::SimpleApp app;

    CROW_ROUTE(app, "/")([](){
        pqxx::connection cx{PG_URL};
        pqxx::work tx{cx};
        string v = tx.query_value<string>("SELECT 'lorem'");
        return v;
    });

    app.port(7777).multithreaded().run();
}