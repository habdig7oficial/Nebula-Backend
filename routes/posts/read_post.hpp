#include "crow.h"
#include "iostream"
#include "pqxx/pqxx"
#include "../../env.h"
#include "vector"



auto read_posts = [](const crow::request& req){
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
        for (size_t rownum=0u; rownum < num_rows; ++rownum){
        pqxx::row const row = r[rownum];
        crow::json::wvalue sub_json;

        /* Montando JSON */
        string fields[] = {"id", "titulo", "texto", "topico", "likes", "resposta", "data_criacao" };

        for(string field : fields){
            sub_json[field] = row[field].c_str();
        }

        db_rows.push_back(std::move(sub_json));


        cout << db_rows[rownum].dump() << '\n';
        }

        crow::json::wvalue last = std::move(db_rows);

        return response(std::move(last));
};