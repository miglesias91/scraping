# ETAPAS
Las etapas NO SE EJECUTAN SECUENCIALMENTE (o en cascada, o una atras de otra, o como quieran llamarlo). Son independientes entre si. El diseño esta hecho para que las etapas puedan ejecutarse mas de 1 vez por dia. El resultado final de estas etapas es un registro NOSQL con valor en formato JSON, con la siguiente estructura:

clave: fecha(AAAAMMDD)

valor:
```json
{
"analisis_medios" : 
[
    {
        "id_medio" : 1234,
        "analisis" :
        {
            "fuerza_en_noticia" : 
            {
                "valores" : 
                [
                    "terminoABC_5.6786",
                    "terminoBCD_3.7862",
                    "...",
                    "terminoZZX_1.8921"
                ]
            }
        }
    },

    {"..." : "..."},

    {
        "id_medio" : 4321,
        "analisis" :
        {
            "fuerza_en_noticia" : 
            {
                "valores" : 
                [
                    "terminoABC_5.6786",
                    "terminoBCD_3.7862",
                    "...",
                    "terminoZZX_1.8921",
                    "terminoZZZ_1.0672"
                ]
            }
        }
    }
]
}
```

Este registro se almacena en la bd sobre la cual la aplicacion 'visualizador-de-contexto' realizara las consultas.

La idea es que haya UN REGISTRO POR DIA.

### 1 - Extraccion
Cada medio extrae el contenido y lo guarda en la base de datos diaria. Como resultado, se generan 2 registros:

    1.
    clave: <prefijo_medio><id_medio>
    valor[JSON]:
    {
        "mapa_ids_contenidos_no_analizados" : unordered_map<string_fecha_AAAAMMDD, ids_contenidos_no_analizados>,
        "mapa_ids_contenidos_analizados" : unordered_map<string_fecha_AAAAMMDD, ids_contenidos_analizados>
    }
    2. clave: <prefijo_contenido><id_contenido> | valor[JSON]: { "info_contenido" : "info del contenido" }

### 2 - Depuracion + Analisis
Se recuperan los contenidos de cada medio, se lo depura y se lo analiza. El analisis puede consistir en aplicar 1 o mas algoritmos al contenido (por ahora, el unico aplicado es 'Fuerza En Noticia').
Como resultado del analisis obtenemos un registro de la forma:

clave: <prefijo_resultado><id_contenido> | valor[JSON]: { resultados del analisis, agrupado por algoritmos aplicados }.

Este registro se guarda en la base de datos diaria.

### 3 - Preparacion
Se recuperan los resultados de los analisis de cada medio, se los integran y se genera un unico registro (el detallado en la seccion ETAPAS).
Primero se integran los resultados para cada medio, y luego se integran los resultados de cada medio en un unico registro agrupado por la fecha.

### CUESTIONES APARTE

Se saco el modulo de "json.hpp" de la libreria 'tiny-dnn' porque usaban una version de 'rapidjson' distinta a la utilizada en 'herramientas_desarrollo'. Es decir, elimino toda referencia a la version de 'rapidjson' ubicada en 'tiny-dnn/cereal/external/rapidjson' (se excluyo el archivo "cereal/json.hpp", y se modificaron "network.h" y "deserealiation_helper.h").
DEBIDO A ESTOS CAMBIOS, quedan DESHABILITADAS las funciones que incluyan operar con formato json, basicamente no se pueden usar 'network::from_json()' ni 'network::to_json()'.


