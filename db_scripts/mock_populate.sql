DO $$
DECLARE
    i integer;
BEGIN
    FOR i IN 1..22 LOOP
        
    CALL new_post(
        CONCAT(i::text, ' lorem'), 
        CONCAT(i::text, ' ipsum'),
        'a479adf9-74a0-48aa-82c2-57c0d7929695',
        NULL
    );
    END LOOP;
END $$;