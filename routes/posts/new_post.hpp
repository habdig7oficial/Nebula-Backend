#include "crow.h"
#include "iostream"
#include "pqxx/pqxx"
#include "../../env.h"


using namespace std;
using namespace crow;

auto new_posts = [](const crow::request& req){
        pqxx::connection cx{PG_URL};
        pqxx::work tx{cx};
        auto body = crow::json::load(req.body);


        tx.exec("CALL new_post($1, $2, $3, NULL)", pqxx::params{string(body["titulo"]), string(body["texto"]), string(body["topico"])});
        tx.commit();
    
        return crow::response(200, "ok");
};