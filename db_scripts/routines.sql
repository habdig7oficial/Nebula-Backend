CREATE PROCEDURE new_post(titulo varchar(150), texto text, topico uuid, resposta uuid)
LANGUAGE SQL 
BEGIN ATOMIC 
    INSERT INTO POSTS(titulo, texto, topico, resposta)
    VALUES($1, $2, $3, $4);
END


CREATE FUNCTION read_posts(pagina integer, limite integer,ordenar boolean) RETURNS TABLE(titulo varchar(150), texto text, topico uuid, likes integer, resposta uuid, data_criacao timestamp)
LANGUAGE PLPGSQL 
AS $$
BEGIN
    IF pagina < 0 OR limite < 0 THEN
        RAISE EXCEPTION 'NÃO PODE EXISTIR PAGINA OU LIMITE NEGATIVA';
    ELSE 
        RETURN QUERY 
        SELECT posts.titulo, posts.texto, posts.topico, posts.likes, posts.resposta, posts.data_criacao FROM posts ORDER BY ordenar,
        CASE WHEN ordenar THEN data_criacao END ASC
        CASE WHEN ordenar THEN data_criacao END DESC,
        LIMIT limite OFFSET(pagina * limite);
    END IF;
END;
$$;