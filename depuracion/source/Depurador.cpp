#include <depuracion/include/Depurador.h>

// stl
#include <algorithm>
#include <regex>
#include <iostream>
#include <fstream>

// utiles
#include <utiles/include/FuncionesString.h>
#include <utiles/include/ImposibleAbrirArchivo.h>

// scraping
#include <scraping/include/Logger.h>

using namespace scraping::depuracion;

mapeo::MapaUTF8 * Depurador::mapa_utf8 = NULL;
std::vector<std::string> Depurador::stopwords_espaniol;

Depurador::Depurador()
{
}

Depurador::~Depurador()
{
    if (NULL != mapa_utf8)
    {
        delete mapa_utf8;
        mapa_utf8 = NULL;
    }
}

// GETTERS

// SETTERS

void Depurador::setMapaUTF8(mapeo::MapaUTF8 * mapa)
{
    if (NULL != mapa_utf8)
    {
        delete mapa_utf8;
        mapa_utf8 = NULL;
    }

    mapa_utf8 = mapa;
}

void Depurador::setStopwords(std::vector<std::string> stopwords)
{
    stopwords_espaniol = stopwords;
}

// METODOS

bool Depurador::cargarStopwords(std::string path_archivo_stopwords)
{
    std::ifstream archivo_stopwords(path_archivo_stopwords);

    if (false == archivo_stopwords.good())
    {
        throw herramientas::utiles::excepciones::ImposibleAbrirArchivo(path_archivo_stopwords);
    }

    std::string stopword;
    while (false == archivo_stopwords.eof())
    {
        std::getline(archivo_stopwords, stopword);
        stopwords_espaniol.push_back(stopword);
    }

    scraping::Logger::info("cargarStopwords: '" + path_archivo_stopwords + "' cargado. " + std::to_string(stopwords_espaniol.size()) + " stopwords cargados.");

    return true;
}

bool Depurador::cargarMapeoUTF8(std::string path_archivo_mapeo)
{
    if (NULL != mapa_utf8)
    {
        scraping::Logger::info("cargarMapeoUTF8: mapa_utf8 ya esta cargado.");
        return true;
    }

    try
    {
        scraping::Logger::info("cargarMapeoUTF8: cargando mapa '" + path_archivo_mapeo + "'.");
        mapa_utf8 = new mapeo::MapaUTF8(path_archivo_mapeo);
    }
    catch (herramientas::utiles::excepciones::Excepcion & e)
    {
        mapa_utf8 = NULL;
        scraping::Logger::error("cargarMapeoUTF8: " + e.getMensaje().str());
        throw;
    }

    scraping::Logger::info("cargarMapeoUTF8: mapa '" + path_archivo_mapeo + "' cargado OK.");

    return true;
}

ContenidoDepurado Depurador::depurar(IDepurable * depurable)
{
    std::string texto_a_depurar = depurable->getTextoDepurable();

    // 1ero: reemplazo los caracteres especiales: vocales con tildes, letras extrañas, 
    unsigned int caracteres_especiales_reemplazados = this->reemplazarTodosLosCaracteresEspeciales(texto_a_depurar);

    // 2do: reemplazo las mayusculas por minusculas.
    bool pasado_a_minuscula = this->todoMinuscula(texto_a_depurar);

    // 3ero: reemplazo las mayusculas por minusculas.
    unsigned int urls_eliminadas = this->eliminarURLs(texto_a_depurar);

    // 4to: elimino los simbolos que no forman palabras.
    unsigned int caracteres_signos_puntuacion_eliminados = this->eliminarSignosYPuntuacion(texto_a_depurar);

    // 5to: elimino los caracteres de control de texto.
    unsigned int caracteres_de_control_eliminados = this->eliminarCaracteresDeControl(texto_a_depurar);

    // 6to: paso de un texto con palabras a un vector con tokens.
    std::vector<std::string> bolsa_de_palabras = this->tokenizarTexto(texto_a_depurar);

    // 7mo: elimino las palabras con menos de 2 letras.
    unsigned int cantidad_palabras_muy_cortas_eliminadas = this->eliminarPalabrasMuyCortas(bolsa_de_palabras);

    // 8vo: elimino las palabras con mas de 15 letras.
    unsigned int cantidad_palabras_muy_largas_eliminadas = this->eliminarPalabrasMuyLargas(bolsa_de_palabras);

    unsigned int cantidad_stopwords_eliminadas = this->eliminarStopwords(bolsa_de_palabras);

    scraping::Logger::debug("depurar: {\n"
        "caracteres especiales reemplazadas: " + std::to_string(caracteres_especiales_reemplazados) + ",\n" +
        "pasado a minuscula: " + std::to_string(pasado_a_minuscula) + ",\n" +
        "urls eliminadas: " + std::to_string(urls_eliminadas) + ",\n" +
        "signos y puntuacion eliminados: " + std::to_string(caracteres_signos_puntuacion_eliminados) + ",\n" +
        "caracteres de control eliminados: " + std::to_string(caracteres_de_control_eliminados) + ",\n" +
        "palabras muy cortas eliminadas: " + std::to_string(cantidad_palabras_muy_cortas_eliminadas) + ",\n" +
        "palabras muy largas eliminadas: " + std::to_string(cantidad_palabras_muy_largas_eliminadas) + ",\n" +
        "stopwords eliminadas: " + std::to_string(cantidad_palabras_muy_largas_eliminadas) + ",\n}"
        //"preposiciones eliminadas: " + std::to_string(cantidad_preposiciones_eliminadas) + ",\n" +
        //"pronombres eliminados: " + std::to_string(cantidad_pronombres_eliminados) + "\n}"
    );

    ContenidoDepurado contenido_depurado(bolsa_de_palabras);
    return contenido_depurado;
}

ContenidoDepurado Depurador::depurarConTildes(IDepurable * depurable)
{
    std::string texto_a_depurar = depurable->getTextoDepurable();

    // 1ero: reemplazo los caracteres especiales: vocales con tildes, letras extrañas, 
    unsigned int caracteres_especiales_reemplazados = this->reemplazarTodosLosCaracteresEspecialesExceptoTildes(texto_a_depurar);

    // 2do: reemplazo las mayusculas por minusculas.
    bool pasado_a_minuscula = this->todoMinuscula(texto_a_depurar);

    // 3ero: reemplazo las mayusculas por minusculas.
    unsigned int urls_eliminadas = this->eliminarURLs(texto_a_depurar);

    // 4to: elimino los simbolos que no forman palabras.
    unsigned int caracteres_signos_puntuacion_eliminados = this->eliminarSignosYPuntuacion(texto_a_depurar);

    // 5to: elimino los caracteres de control de texto.
    unsigned int caracteres_de_control_eliminados = this->eliminarCaracteresDeControl(texto_a_depurar);

    // 6to: paso de un texto con palabras a un vector con tokens.
    std::vector<std::string> bolsa_de_palabras = this->tokenizarTexto(texto_a_depurar);

    // 7mo: elimino las palabras con menos de 2 letras.
    unsigned int cantidad_palabras_muy_cortas_eliminadas = this->eliminarPalabrasMuyCortas(bolsa_de_palabras);

    // 8vo: elimino las palabras con mas de 15 letras.
    unsigned int cantidad_palabras_muy_largas_eliminadas = this->eliminarPalabrasMuyLargas(bolsa_de_palabras);

    unsigned int cantidad_stopwords_eliminadas = this->eliminarStopwords(bolsa_de_palabras);

    scraping::Logger::debug("depurarConTildes: {\n"
        "caracteres especiales reemplazadas: " + std::to_string(caracteres_especiales_reemplazados) + ",\n" +
        "pasado a minuscula: " + std::to_string(pasado_a_minuscula) + ",\n" +
        "urls eliminadas: " + std::to_string(urls_eliminadas) + ",\n" +
        "signos y puntuacion eliminados: " + std::to_string(caracteres_signos_puntuacion_eliminados) + ",\n" +
        "caracteres de control eliminados: " + std::to_string(caracteres_de_control_eliminados) + ",\n" +
        "palabras muy cortas eliminadas: " + std::to_string(cantidad_palabras_muy_cortas_eliminadas) + ",\n" +
        "palabras muy largas eliminadas: " + std::to_string(cantidad_palabras_muy_largas_eliminadas) + ",\n" +
        "stopwords eliminadas: " + std::to_string(cantidad_palabras_muy_largas_eliminadas) + ",\n}"
    );

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

            std::string reemplazo = mapa_utf8->getTraduccion(valor_decimal_codepoint);

            it = texto_a_depurar.erase(it, it + 4);
            texto_a_depurar.insert(it, reemplazo.begin(), reemplazo.end());

            cantidad_de_reemplazos += 1;
        }
        else if (225 <= caracter_1)
        {// codepoint con 3 codeunits
            unsigned char caracter_2 = *(it + 1);
            unsigned char caracter_3 = *(it + 2);

            unsigned int valor_decimal_codepoint = (caracter_1 - 224) * 4096 + (caracter_2 - 128) * 64 + caracter_3 - 128;


            std::string reemplazo = mapa_utf8->getTraduccion(valor_decimal_codepoint);

            it = texto_a_depurar.erase(it, it + 3);
            texto_a_depurar.insert(it, reemplazo.begin(), reemplazo.end());

            cantidad_de_reemplazos += 1;
        }
        else if (193 <= caracter_1)
        {// codepoint con 2 codeunits
            unsigned char caracter_2 = *(it + 1);

            unsigned int valor_decimal_codepoint = (caracter_1 - 192) * 64 + caracter_2 - 128;

            std::string reemplazo = mapa_utf8->getTraduccion(valor_decimal_codepoint);

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

unsigned int Depurador::reemplazarTodosLosCaracteresEspecialesExceptoTildes(std::string & texto_a_depurar)
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

            std::string reemplazo = mapa_utf8->getTraduccion(valor_decimal_codepoint);

            it = texto_a_depurar.erase(it, it + 4);
            texto_a_depurar.insert(it, reemplazo.begin(), reemplazo.end());

            cantidad_de_reemplazos += 1;
        }
        else if (225 <= caracter_1)
        {// codepoint con 3 codeunits
            unsigned char caracter_2 = *(it + 1);
            unsigned char caracter_3 = *(it + 2);

            unsigned int valor_decimal_codepoint = (caracter_1 - 224) * 4096 + (caracter_2 - 128) * 64 + caracter_3 - 128;


            std::string reemplazo = mapa_utf8->getTraduccion(valor_decimal_codepoint);

            it = texto_a_depurar.erase(it, it + 3);
            texto_a_depurar.insert(it, reemplazo.begin(), reemplazo.end());

            cantidad_de_reemplazos += 1;
        }
        else if (193 <= caracter_1)
        {// codepoint con 2 codeunits
            unsigned char caracter_2 = *(it + 1);

            if (!(caracter_2 == 129 || caracter_2 == 137 || caracter_2 == 141 || caracter_2 == 147 || caracter_2 == 154 ||
                caracter_2 == 157 || caracter_2 == 161 || caracter_2 == 169 || caracter_2 == 173 || caracter_2 == 179 ||
                caracter_2 == 186 || caracter_2 == 189))
            {// los valores corresponden al segundo codepoint del vocales con tildes:
             // 129: Á - 137: É - 141: Í - 147: Ó - 154: Ú - 157:Ý - 161: á - 169: é - 173: í - 179: ó - 186: ú - 189: ý
                unsigned int valor_decimal_codepoint = (caracter_1 - 192) * 64 + caracter_2 - 128;

                std::string reemplazo = mapa_utf8->getTraduccion(valor_decimal_codepoint);

                it = texto_a_depurar.erase(it, it + 2);
                texto_a_depurar.insert(it, reemplazo.begin(), reemplazo.end());

                cantidad_de_reemplazos += 1;
            }
        }

        if (it == texto_a_depurar.end())
        {// el ultimo caracter es especial, entonces entra en este if.
         // esto evita que pinche cuando entra de nuevo el 'for' e intenta incrementar el iterator.
            break;
        }
    }

    return cantidad_de_reemplazos;

    return 0;
}

unsigned int Depurador::eliminarTildes(std::string & texto_a_depurar)
{
    std::vector<std::string> vocales_con_tilde = { u8"á", u8"é", u8"í", u8"ó", u8"ú" };

    unsigned int cantidad_de_tildes_reemplazadas = 0;
    for (std::vector<std::string>::iterator it_vocal = vocales_con_tilde.begin(); it_vocal != vocales_con_tilde.end(); it_vocal++)
    {
        cantidad_de_tildes_reemplazadas += herramientas::utiles::FuncionesString::reemplazarOcurrencias(texto_a_depurar, (*it_vocal), mapa_utf8->getTraduccion(*it_vocal));
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

unsigned int Depurador::eliminarStopwords(std::vector<std::string>& bolsa_de_palabras)
{
    unsigned int cantidad_de_stopwords_eliminadas = 0;
    for (std::vector<std::string>::iterator it_stopword = stopwords_espaniol.begin(); it_stopword != stopwords_espaniol.end(); it_stopword++)
    {
        for (std::vector<std::string>::iterator it_palabra = bolsa_de_palabras.begin(); it_palabra != bolsa_de_palabras.end(); )
        {
            std::string palabra_sin_tilde = std::string(*it_palabra);
            this->eliminarTildes(palabra_sin_tilde);
            if (0 == it_stopword->compare(palabra_sin_tilde))
            {
                it_palabra = bolsa_de_palabras.erase(it_palabra);
                cantidad_de_stopwords_eliminadas++;
            }
            else
            {
                it_palabra++;
            }
        }
    }

    return cantidad_de_stopwords_eliminadas;
}

// CONSULTAS

// METODOS PRIVADOS


unsigned int Depurador::hilo_eliminar_stopwords(std::vector<std::string>& bolsa_de_palabras, unsigned int desde, unsigned int hasta)
{
    std::unique_lock<std::mutex> lock(this->mutex);
    unsigned int cantidad_de_stopwords_eliminadas = 0;
    for (std::vector<std::string>::iterator it_stopword = stopwords_espaniol.begin() + desde; it_stopword != stopwords_espaniol.begin() + hasta; it_stopword++)
    {
        for (std::vector<std::string>::iterator it_palabra = bolsa_de_palabras.begin(); it_palabra != bolsa_de_palabras.end(); )
        {
            std::string palabra_sin_tilde = std::string(*it_palabra);
            this->eliminarTildes(palabra_sin_tilde);
            if (0 == it_stopword->compare(palabra_sin_tilde))
            {
                it_palabra = bolsa_de_palabras.erase(it_palabra);
                cantidad_de_stopwords_eliminadas++;
            }
            else
            {
                it_palabra++;
            }
        }
    }

    return cantidad_de_stopwords_eliminadas;
}