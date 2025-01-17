/* Compile com o G++: g++ trigger.cpp -o nebula.elf -lpqxx -lpq && ./nebula.elf */

#include "crow.h"
#include "crow/middlewares/cors.h"
#include "iostream"
#include "pqxx/pqxx"
#include "env.h"

#include "vector"

#include <ctime>

using namespace std;
using namespace crow;


int main(){

    crow::App<crow::CORSHandler> app;
    

    CROW_ROUTE(app, "/post/new").methods("POST"_method)([](const crow::request& req){
        pqxx::connection cx{PG_URL};
        pqxx::work tx{cx};
        auto body = crow::json::load(req.body);


        tx.exec("CALL new_post($1, $2, $3, NULL)", pqxx::params{string(body["titulo"]), string(body["texto"]), string(body["topico"])});
        tx.commit();
    
        return crow::response(200, "ok");
    });

    CROW_ROUTE(app, "/post/read").methods("GET"_method)([](const crow::request& req){
        pqxx::connection cx{PG_URL};
        pqxx::work tx{cx};

        int limit = req.url_params.get("limit") ? stoi(req.url_params.get("limit")) : 5;
        int offset = req.url_params.get("offset") ? stoi(req.url_params.get("offset")) : 0;
        bool desc  = stoi(req.url_params.get("desc")? req.url_params.get("desc") : "0") == 0 ? false : true;

        cout << "limite: " << limit << endl << "pagina: " << offset << endl;

        pqxx::result r = tx.exec("SELECT * FROM read_posts($1, $2, $3)", pqxx::params{offset, limit, desc});
        tx.commit();

        size_t const num_rows = size(r);
        vector<crow::json::wvalue> db_rows;
        for (size_t rownum=0u; rownum < num_rows; ++rownum)
        {
        pqxx::row const row = r[rownum];
        crow::json::wvalue sub_json;

        /* Montando JSON */
        string fields[] = { "titulo", "texto", "topico", "likes", "resposta", "data_criacao" };

        for(string field : fields){
            sub_json[field] = row[field].c_str();
        }

        db_rows.push_back(std::move(sub_json));


        cout << db_rows[rownum].dump() << '\n';
        }

        crow::json::wvalue last = std::move(db_rows);

        return crow::response(std::move(last));
    });

    CROW_ROUTE(app, "/")([](){
        return "hello";
    });

    app.port(7777).multithreaded().run();
}