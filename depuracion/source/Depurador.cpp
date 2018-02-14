#include <depuracion/include/Depurador.h>

// stl
#include <algorithm>
#include <regex>
#include <iostream>

// utiles
#include <utiles/include/FuncionesString.h>

using namespace scraping::depuracion;

Depurador::Depurador() : mapa_utf8(NULL)
{
}

Depurador::~Depurador()
{
    if (NULL != this->mapa_utf8)
    {
        delete this->mapa_utf8;
        this->mapa_utf8 = NULL;
    }
}

bool Depurador::cargarMapeoUTF8(std::string path_archivo_mapeo)
{
    if (NULL != this->mapa_utf8)
    {
        delete this->mapa_utf8;
    }


    try
    {
        this->mapa_utf8 = new mapeo::MapaUTF8(path_archivo_mapeo);
    }
    catch (...)
    {
        this->mapa_utf8 = NULL;
        return false;
    }

    return true;
}

ContenidoDepurado Depurador::depurar(IDepurable * depurable)
{
    std::string texto_a_depurar = depurable->getTextoDepurable();

    // 1ero: reemplazo los caracteres especiales: vocales con tildes, letras extrañas, 
    this->reemplazarTodosLosCaracteresEspeciales(texto_a_depurar);

    // 2do: reemplazo las mayusculas por minusculas.
    this->todoMinuscula(texto_a_depurar);
    
    // 3ero: reemplazo las mayusculas por minusculas.
    this->eliminarURLs(texto_a_depurar);

    // 4to: elimino los simbolos que no forman palabras.
    this->eliminarSignosYPuntuacion(texto_a_depurar);

    // 5to: elimino los caracteres de control de texto.
    this->eliminarCaracteresDeControl(texto_a_depurar);

    // 6to: paso de un texto con palabras a un vector con tokens.
    std::vector<std::string> bolsa_de_palabras = this->tokenizarTexto(texto_a_depurar);

    // 7mo: elimino las palabras con menos de 2 letras.
    this->eliminarPalabrasMuyCortas(bolsa_de_palabras);

    // 8vo: elimino las palabras con mas de 15 letras.
    this->eliminarPalabrasMuyLargas(bolsa_de_palabras);

    // 9no: elimino las preposiciones.
    this->eliminarPreposiciones(bolsa_de_palabras);

    // 10mo: elimino pronombres.
    this->eliminarPronombres(bolsa_de_palabras);

    ContenidoDepurado contenido_depurado(bolsa_de_palabras);
    return contenido_depurado;
}

unsigned int Depurador::reemplazarTodosLosCaracteresEspeciales(std::string & texto_a_depurar)
{
    unsigned int cantidad_de_reemplazos = 0;
    for (std::string::iterator it = texto_a_depurar.begin(); it != texto_a_depurar.end(); it++)
    {
        unsigned char caracter_1 = *it;

        if (241 <= caracter_1)
        {// codepoint con 4 codeunits
            unsigned char caracter_2 = *(it + 1);
            unsigned char caracter_3 = *(it + 2);
            unsigned char caracter_4 = *(it + 3);

            unsigned int valor_decimal_codepoint = (caracter_1 - 240) * 262144 + (caracter_2 - 128) * 4096 + (caracter_3 - 128) * 64 + caracter_4 - 128;

            std::string reemplazo = this->mapa_utf8->getTraduccion(valor_decimal_codepoint);

            it = texto_a_depurar.erase(it, it + 4);
            texto_a_depurar.insert(it, reemplazo.begin(), reemplazo.end());

            cantidad_de_reemplazos += 1;
        }
        else if (225 <= caracter_1)
        {// codepoint con 3 codeunits
            unsigned char caracter_2 = *(it + 1);
            unsigned char caracter_3 = *(it + 2);

            unsigned int valor_decimal_codepoint = (caracter_1 - 224) * 4096 + (caracter_2 - 128) * 64 + caracter_3 - 128;
            

            std::string reemplazo = this->mapa_utf8->getTraduccion(valor_decimal_codepoint);

            it = texto_a_depurar.erase(it, it + 3);
            texto_a_depurar.insert(it, reemplazo.begin(), reemplazo.end());

            cantidad_de_reemplazos += 1;
        }
        else if (193 <= caracter_1)
        {// codepoint con 2 codeunits
            unsigned char caracter_2 = *(it + 1);

            unsigned int valor_decimal_codepoint = (caracter_1 - 192) * 64 + caracter_2 - 128;

            std::string reemplazo = this->mapa_utf8->getTraduccion(valor_decimal_codepoint);

            it = texto_a_depurar.erase(it, it + 2);
            texto_a_depurar.insert(it, reemplazo.begin(), reemplazo.end());

            cantidad_de_reemplazos += 1;
        }

        if (it == texto_a_depurar.end())
        {// el ultimo caracter es especial, entonces entra en este if.
         // esto evita que pinche cuando entra de nuevo el 'for' e intenta incrementar el iterator.
            break;
        }
    }

    return cantidad_de_reemplazos;
}

unsigned int Depurador::eliminarTildes(std::string & texto_a_depurar)
{
    std::vector<std::string> vocales_con_tilde = { u8"á", u8"é", u8"í", u8"ó", u8"ú" };

    unsigned int cantidad_de_tildes_reemplazadas = 0;
    for (std::vector<std::string>::iterator it_vocal = vocales_con_tilde.begin(); it_vocal != vocales_con_tilde.end(); it_vocal++)
    {
        cantidad_de_tildes_reemplazadas += herramientas::utiles::FuncionesString::reemplazarOcurrencias(texto_a_depurar, (*it_vocal), this->mapa_utf8->getTraduccion(*it_vocal));
    }

    return cantidad_de_tildes_reemplazadas;
}

bool Depurador::todoMinuscula(std::string & texto_a_depurar)
{
    return herramientas::utiles::FuncionesString::todoMinuscula(texto_a_depurar);
}

unsigned int Depurador::eliminarSignosYPuntuacion(std::string & texto_a_depurar)
{
    return herramientas::utiles::FuncionesString::eliminarSignosYPuntuacion(texto_a_depurar);
}

unsigned int Depurador::eliminarCaracteresDeControl(std::string & texto_a_depurar)
{
    return herramientas::utiles::FuncionesString::eliminarCaracteresDeControl(texto_a_depurar);
}

unsigned int Depurador::eliminarURLs(std::string & texto_a_depurar)
{
    std::vector<std::string> comienzo_de_urls = { "ftp", "http" };

    unsigned int cantidad_de_urls_reemplazadas = 0;
    for (std::vector<std::string>::iterator it_comienzo_url = comienzo_de_urls.begin(); it_comienzo_url != comienzo_de_urls.end(); it_comienzo_url++)
    {
        for (size_t posicion_ocurrencia = 0; ;)
        {
            posicion_ocurrencia = texto_a_depurar.find(*it_comienzo_url, posicion_ocurrencia);

            if (std::string::npos == posicion_ocurrencia)
            {
                break;
            }

            size_t posicion_primer_espacio_separador = texto_a_depurar.find(" ", posicion_ocurrencia);

            unsigned int tamanio_url = 0;
            if (std::string::npos == posicion_primer_espacio_separador)
            {
                tamanio_url = texto_a_depurar.size() - posicion_ocurrencia;
            }
            else
            {
                tamanio_url = posicion_primer_espacio_separador - posicion_ocurrencia;
            }

            texto_a_depurar.erase(posicion_ocurrencia, tamanio_url);

            cantidad_de_urls_reemplazadas++;
        }
    }

    herramientas::utiles::FuncionesString::eliminarEspaciosRedundantes(texto_a_depurar);

    return cantidad_de_urls_reemplazadas;
}

std::vector<std::string> Depurador::tokenizarTexto(std::string texto_a_tokenizar)
{
    return herramientas::utiles::FuncionesString::separar(texto_a_tokenizar);
}

unsigned int Depurador::eliminarPalabrasMuyCortas(std::vector<std::string> & bolsa_de_palabras)
{
    unsigned int cantidad_de_palabras_cortas_eliminadas = 0;
    for (std::vector<std::string>::iterator it_palabra = bolsa_de_palabras.begin(); it_palabra != bolsa_de_palabras.end(); )
    {
        if (3 > it_palabra->size())
        {
            it_palabra = bolsa_de_palabras.erase(it_palabra);
            cantidad_de_palabras_cortas_eliminadas++;
        }
        else
        {
            it_palabra++;
        }
    }

    return cantidad_de_palabras_cortas_eliminadas;
}

unsigned int Depurador::eliminarPalabrasMuyLargas(std::vector<std::string> & bolsa_de_palabras)
{
    unsigned int cantidad_de_palabras_largas_eliminadas = 0;
    for (std::vector<std::string>::iterator it_palabra = bolsa_de_palabras.begin(); it_palabra != bolsa_de_palabras.end(); )
    {
        if (15 < it_palabra->size())
        {
            it_palabra = bolsa_de_palabras.erase(it_palabra);
            cantidad_de_palabras_largas_eliminadas++;
        }
        else
        {
            it_palabra++;
        }
    }

    return cantidad_de_palabras_largas_eliminadas;
}

unsigned int Depurador::eliminarPreposiciones(std::vector<std::string> & bolsa_de_palabras)
{
    std::vector<std::string> preposiciones = { "a", "ante", "bajo", "cabe", "con", "contra", "cuando", "de", "desde", "donde", "durante", "en", "entre", "excepto", "hacia", "hasta", "mediante", "menos", "para", "por", "segun", "salvo", "sin", "so", "sobre", "tras", "versus", "via" };

    // agrego aca las conjunciones
    std::vector<std::string> conjunciones = { "pero", "aunque", "mas", "sino", "embargo", "obstante", "porque" };

    preposiciones.insert(preposiciones.end(), conjunciones.begin(), conjunciones.end());

    unsigned int cantidad_de_preposiciones_eliminadas = 0;
    for (std::vector<std::string>::iterator it_preposicion = preposiciones.begin(); it_preposicion != preposiciones.end(); it_preposicion++)
    {
        for (std::vector<std::string>::iterator it_palabra = bolsa_de_palabras.begin(); it_palabra != bolsa_de_palabras.end(); )
        {
            if (0 == it_preposicion->compare(*it_palabra))
            {
                it_palabra = bolsa_de_palabras.erase(it_palabra);
                cantidad_de_preposiciones_eliminadas++;
            }
            else
            {
                it_palabra++;
            }
        }
    }

    return cantidad_de_preposiciones_eliminadas;
}

unsigned int Depurador::eliminarPronombres(std::vector<std::string>& bolsa_de_palabras)
{
    // lista de pronombres obtenida de la fuente de toda sabiduria: https://es.wikipedia.org/wiki/Pronombres_en_espa%C3%B1ol
    // solo se incluyen lo que tienen mas de 2 letras. ("yo", "tu", "el", etc etc..., no se incluyen).

    std::vector<std::string> pronombres_personales_tonicos = { "conmigo", "contigo", "vos", "usted", "ella", "ello", "consigo", "nosotros", "nosotras", "vosotros", "vosotras",
        "ustedes", "ellos", "ellas" };

    // los ultimosde los "personales atonos" no son pronombres, sino que son "articulos".
    std::vector<std::string> pronombres_personales_atonos = { "nos", "los", "las", "les", "del" };

    // los ultimos de los "posesivos" no son pronombres, sino que son "adjetivos posesivos".
    std::vector<std::string> pronombres_posesivos = { "mio", "mia", "mios", "mias", "tuyo", "tuya", "tuyos", "tuyas", "suyo", "suya", "suyos", "suyas",
        "nuestro", "nuestra", "nuestros", "nuestras", "vuestro", "vuestra", "vuestros", "vuestras", "mis", "tus", "sus" };

    std::vector<std::string> pronombres_demostrativos = { "este", "esta", "esto", "estos", "estas", "ese", "esa", "eso", "esos", "esas", "aquel", "aquella",
        "aquello", "aquellos", "aquellas" };

    std::vector<std::string> pronombres_relativos = { "que", "como", "cual", "cuales", "cuanto", "cuantos", "donde", "quien", "quienes", "cuyo", "cuyos" };

    std::vector<std::string> pronombres_indefinidos = { "uno", "una", "unos", "unas", "algun", "alguno", "alguna", "algo", "algunos", "algunas", "ningun", "ninguno",
        "ninguna", "nada", "ningunos", "ningunas", "poco", "poca", "pocos", "pocas", "escaso", "escasa", "escasos", "escasas", "mucho", "mucha", "muchos", "muchas",
        "demasiado", "demasiada", "demasiados", "demasiadas", "todo", "toda", "todos", "todas", "escaso", "escasa", "escasos", "escasas", "mucho", "mucha", "muchos", "muchas" };

    std::vector<std::string> todos_los_pronombres = pronombres_personales_tonicos;

    // junto todos los pronombres en un solo vector.
    todos_los_pronombres.insert(todos_los_pronombres.end(), pronombres_personales_atonos.begin(), pronombres_personales_atonos.end());
    todos_los_pronombres.insert(todos_los_pronombres.end(), pronombres_posesivos.begin(), pronombres_posesivos.end());
    todos_los_pronombres.insert(todos_los_pronombres.end(), pronombres_demostrativos.begin(), pronombres_demostrativos.end());
    todos_los_pronombres.insert(todos_los_pronombres.end(), pronombres_relativos.begin(), pronombres_relativos.end());
    todos_los_pronombres.insert(todos_los_pronombres.end(), pronombres_indefinidos.begin(), pronombres_indefinidos.end());

    unsigned int cantidad_de_pronombres_eliminados = 0;
    for (std::vector<std::string>::iterator it_pronombre = todos_los_pronombres.begin(); it_pronombre != todos_los_pronombres.end(); it_pronombre++)
    {
        for (std::vector<std::string>::iterator it_palabra = bolsa_de_palabras.begin(); it_palabra != bolsa_de_palabras.end(); )
        {
            if (0 == it_pronombre->compare(*it_palabra))
            {
                it_palabra = bolsa_de_palabras.erase(it_palabra);
                cantidad_de_pronombres_eliminados++;
            }
            else
            {
                it_palabra++;
            }
        }
    }

    return cantidad_de_pronombres_eliminados;
}
// GETTERS

// SETTERS

// METODOS

// CONSULTAS