#include "crow.h"
#include "iostream"
#include "pqxx/pqxx"
using namespace std;

pqxx::connection cx{""};
pqxx::work tx{cx};

int main()
{
    crow::SimpleApp app;

    CROW_ROUTE(app, "/")([](){
        string v = tx.query_value<string>("SELECT 'lorem'");
        return v;
    });

    app.port(7777).multithreaded().run();
}