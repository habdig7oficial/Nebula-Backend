CREATE TABLE TOPICOS (
    id uuid PRIMARY KEY DEFAULT GEN_RANDOM_UUID(),
    nome VARCHAR(150) NOT NULL,
    descricao TEXT NOT NULL,
    data_criacao TIMESTAMP NOT NULL DEFAULT NOW()
)

CREATE TABLE POSTS (
    id uuid PRIMARY KEY DEFAULT GEN_RANDOM_UUID(),
    titulo VARCHAR(150) NOT NULL,
    texto TEXT NOT NULL,

    likes INTEGER NOT NULL DEFAULT 0 CHECK(likes >= 0),

    topico uuid NOT NULL REFERENCES topicos,
    resposta uuid REFERENCES posts,

    data_criacao TIMESTAMP NOT NULL DEFAULT NOW()
)

CREATE PROCEDURE new_post(varchar(150), text, uuid, uuid)
LANGUAGE SQL 
BEGIN ATOMIC 
    INSERT INTO POSTS(titulo, texto, topico, resposta)
    VALUES($1, $2, $3, $4);
END

CALL new_post(
    'Como compilar a sua versão do kernel linux', 
    'Lorem ipsum dolor sit amet, consectetur adipiscing elit. Donec pharetra egestas neque vel interdum. Nulla scelerisque a lorem eget pulvinar. Morbi laoreet vehicula arcu. Integer vel orci in arcu euismod dignissim. Quisque dignissim ligula at lacus tristique commodo. Sed a lectus vel quam commodo tristique. Nam pretium rhoncus dignissim. Praesent cursus ex quis venenatis rhoncus. Curabitur sodales eu lacus at lacinia.

Ut porta tellus sed turpis blandit, et elementum justo tempus. Sed a mi sollicitudin diam vehicula tincidunt. Integer ac gravida velit. Nam ultrices aliquet nisl. Ut condimentum, nunc venenatis facilisis accumsan, nunc est pharetra neque, nec molestie sem arcu eu lorem. Mauris sapien massa, bibendum eu tortor at, tristique laoreet massa. Sed eget aliquam nisl. Morbi eleifend maximus libero, sed sagittis magna malesuada eu. Interdum et malesuada fames ac ante ipsum primis in faucibus. Mauris at nisl mi. Vivamus ac sapien quam. Vestibulum non eros arcu. Aliquam non rhoncus tortor, lobortis cursus lorem. Aliquam facilisis, quam vel pharetra molestie, elit leo lobortis diam, a imperdiet turpis dui sit amet mi. Praesent a ex non dolor euismod pellentesque. Praesent ut diam malesuada, imperdiet erat eget, ullamcorper mi.

Nunc feugiat justo posuere odio laoreet gravida. Phasellus eget volutpat magna. Quisque sit amet malesuada dolor. Proin gravida elit et scelerisque vestibulum. Proin vitae sapien nec nunc venenatis porttitor ut sed nibh. Duis et lorem nec risus aliquam vestibulum. Suspendisse venenatis blandit maximus. Curabitur blandit nibh et sagittis egestas. Quisque ligula leo, placerat rhoncus consequat et, rhoncus ac ante. Fusce placerat ante eu risus sollicitudin ultricies.

Donec fermentum feugiat risus. Ut iaculis, risus in faucibus rhoncus, risus lectus volutpat libero, non eleifend nunc purus sed quam. Mauris bibendum libero vitae tortor tincidunt hendrerit. Integer luctus mollis pretium. Pellentesque dictum nibh a arcu porta, vitae varius massa faucibus. Nullam consectetur fermentum pulvinar. In massa libero, luctus vel nunc interdum, imperdiet mollis quam. Mauris in mollis ipsum. Quisque quis risus arcu. Ut tristique diam eros, eu blandit felis varius vitae.

Fusce pretium erat est, id efficitur risus consectetur eget. Vestibulum porttitor dui quis facilisis pellentesque. Nam iaculis lorem vel ante convallis porta. Praesent sapien sem, tempus quis eros sollicitudin, imperdiet consequat dolor. Nullam augue enim, varius vitae erat nec, rutrum commodo eros. Sed vulputate dolor eget nisl tincidunt commodo. Aliquam feugiat, felis eu posuere finibus, lorem tellus porta nibh, vitae hendrerit lorem dolor sed nulla. Aenean id justo eget nisi sagittis venenatis. Pellentesque eu dui molestie, volutpat nisi ac, consequat tellus. ',
    'a479adf9-74a0-48aa-82c2-57c0d7929695',
)
