// gtest
#include <gtest/gtest.h>

// stl
#include <fstream>
#include <sstream>

// twitter
#include <twitter/include/Tweet.h>

// depuracion
#include <depuracion/include/Depurador.h>
#include <depuracion/include/ContenidoDepurable.h>

TEST(Depuracion, cargarMapeoCorrectamente)
{
    scraping::depuracion::mapeo::MapaUTF8 mapa_utf8("mapeo_utf8.json");
    
    ASSERT_STREQ("A", mapa_utf8.getTraduccion(192).c_str());
    ASSERT_STREQ("A", mapa_utf8.getTraduccion(193).c_str());
    ASSERT_STREQ("A", mapa_utf8.getTraduccion(194).c_str());

    ASSERT_STREQ("0", mapa_utf8.getTraduccion(168).c_str());
    ASSERT_STREQ("+-", mapa_utf8.getTraduccion(177).c_str());
    ASSERT_STREQ("^2", mapa_utf8.getTraduccion(178).c_str());

    ASSERT_STREQ(">>", mapa_utf8.getTraduccion(187).c_str());
    ASSERT_STREQ("1/4", mapa_utf8.getTraduccion(188).c_str());
    ASSERT_STREQ("1/2", mapa_utf8.getTraduccion(189).c_str());
    ASSERT_STREQ("3/4", mapa_utf8.getTraduccion(190).c_str());

    ASSERT_STREQ("A", mapa_utf8.getTraduccion("À").c_str());
    ASSERT_STREQ("A", mapa_utf8.getTraduccion("Á").c_str());
    ASSERT_STREQ("A", mapa_utf8.getTraduccion("Â").c_str());

    ASSERT_STREQ("0", mapa_utf8.getTraduccion("¨").c_str());
    ASSERT_STREQ("+-", mapa_utf8.getTraduccion("±").c_str());
    ASSERT_STREQ("^2", mapa_utf8.getTraduccion("²").c_str());

    ASSERT_STREQ(">>", mapa_utf8.getTraduccion("»").c_str());
    ASSERT_STREQ("1/4", mapa_utf8.getTraduccion("¼").c_str());
    ASSERT_STREQ("1/2", mapa_utf8.getTraduccion("½").c_str());
    ASSERT_STREQ("3/4", mapa_utf8.getTraduccion("¾").c_str());
}

TEST(Depuracion, depurarTexto)
{
    std::string texto = "Jerusalén: suenan sirenas de alarma en el sur de Israel tras el disparo de un cohete desde Gaza… https:\/\/t.co\/eqSJm9AkQB";

    scraping::depuracion::Depurador depurador;
    depurador.cargarMapeoUTF8("mapeo_utf8.json");

    scraping::twitter::modelo::Tweet tweet;
    tweet.setTexto(texto);

    scraping::depuracion::ContenidoDepurable contenido_depurable(&tweet);

    scraping::depuracion::ContenidoDepurado contenido_depurado = depurador.depurar(&contenido_depurable);

    std::vector<std::string> bolsa_de_palabras = contenido_depurado.getBolsaDePalabras();

    ASSERT_EQ(9, bolsa_de_palabras.size());
    ASSERT_STREQ("alarma", bolsa_de_palabras[0].c_str());
    ASSERT_STREQ("cohete", bolsa_de_palabras[1].c_str());
    ASSERT_STREQ("disparo", bolsa_de_palabras[2].c_str());
    ASSERT_STREQ("gaza", bolsa_de_palabras[3].c_str());
    ASSERT_STREQ("israel", bolsa_de_palabras[4].c_str());
    ASSERT_STREQ("jerusalen", bolsa_de_palabras[5].c_str());
    ASSERT_STREQ("sirenas", bolsa_de_palabras[6].c_str());
    ASSERT_STREQ("suenan", bolsa_de_palabras[7].c_str());
    ASSERT_STREQ("sur", bolsa_de_palabras[8].c_str());
}

TEST(Depuracion, depurarTextoConTildes)
{
    std::string texto = "Jerusalén: suenan sirenas de alarma en el sur de Israel tras el disparo de un cohete desde Gaza… https:\/\/t.co\/eqSJm9AkQB";

    scraping::depuracion::Depurador depurador;
    depurador.cargarMapeoUTF8("mapeo_utf8.json");

    scraping::twitter::modelo::Tweet tweet;
    tweet.setTexto(texto);

    scraping::depuracion::ContenidoDepurable contenido_depurable(&tweet);

    scraping::depuracion::ContenidoDepurado contenido_depurado = depurador.depurarConTildes(&contenido_depurable);

    std::vector<std::string> bolsa_de_palabras = contenido_depurado.getBolsaDePalabras();

    ASSERT_EQ(9, bolsa_de_palabras.size());
    ASSERT_STREQ("alarma", bolsa_de_palabras[0].c_str());
    ASSERT_STREQ("cohete", bolsa_de_palabras[1].c_str());
    ASSERT_STREQ("disparo", bolsa_de_palabras[2].c_str());
    ASSERT_STREQ("gaza", bolsa_de_palabras[3].c_str());
    ASSERT_STREQ("israel", bolsa_de_palabras[4].c_str());
    ASSERT_STREQ("jerusalén", bolsa_de_palabras[5].c_str());
    ASSERT_STREQ("sirenas", bolsa_de_palabras[6].c_str());
    ASSERT_STREQ("suenan", bolsa_de_palabras[7].c_str());
    ASSERT_STREQ("sur", bolsa_de_palabras[8].c_str());
}

TEST(Depuracion, reemplazarCaracteresEspeciales)
{
    std::string caracteres_normales_especiales_a_reemplazar = "µ a ¶ · ¸ ¹ º b » ¼ c ½ ¾ ¿ d À Á Â 1 Ã Ä Å Æ 2 Ç È É Ê Ë Ì Í Î Ï 3 Ð Ñ Ò Ó Ô Õ Ö × Ø Ù Ú Û Ü Ý Þ 4 ß à á â ã ä å æ";
    std::string caracteres_reemplazados = "u a p . . ^1 o b >> 1/4 c 1/2 3/4 ? d A A A 1 A A A AE 2 C E E E E I I I I 3 D N O O O O O x O U U U U Y P 4 B a a a a a a ae";

    scraping::depuracion::Depurador depurador;
    depurador.cargarMapeoUTF8("mapeo_utf8.json");

    depurador.reemplazarTodosLosCaracteresEspeciales(caracteres_normales_especiales_a_reemplazar);

    ASSERT_STREQ(caracteres_reemplazados.c_str(), caracteres_normales_especiales_a_reemplazar.c_str());
}

TEST(Depuracion, reemplazarCaracteresEspecialesDeTexto)
{
    //std::string texto = "Hoy presentamos un proyecto de ley para que lxs jubiladxs y beneficiarixs de la AUH cobren un bono de emergencia.\nCon este bono, lxs ciudadanxs que padecen en carne propia el ajuste previsional consumado por el Gobierno de Cambiemos en diciembre de 2017, recibiran una compensacion.\nâ€ªEs sabido.El Gobierno de Cambiemos miente todo el tiempo.Esta vez lo hizo cuando prometiÃ³ que, con la nueva fÃ³rmula, las jubilaciones iban a aumentar mÃ¡s que la inflaciÃ³n.Falso.La inflaciÃ³n estÃ¡ descontrolada y las jubilaciones no paran de perder poder adquisitivo.â€¬\nPor eso, resulta necesario que el Congreso de la NaciÃ³n haga valer las facultades que le otorga la ConstituciÃ³n Nacional para reparar el daÃ±o que el Gobierno de Cambiemos ha causado a mÃ¡s de diez millones de argentinxs.\nConocÃ© el proyecto completoðŸ‘‡ðŸ¼\nhttp://telegra.ph/Bono-compensatorio-del-ajuste-ocasionado-por-la-Reforma-Previsional-03-19";
    //std::wstring texto_con_simbolos = L"Hoy presentamos un proyecto de ley para que lxs jubiladxs y beneficiarixs de la AUH cobren un bono de emergencia.\nCon este bono, lxs ciudadanxs que padecen en carne propia el ajuste previsional consumado por el Gobierno de Cambiemos en diciembre de 2017, recibirán una compensación.\n‪Es sabido.El Gobierno de Cambiemos miente todo el tiempo.Esta vez lo hizo cuando prometió que, con la nueva fórmula, las jubilaciones iban a aumentar más que la inflación.Falso.La inflación está descontrolada y las jubilaciones no paran de perder poder adquisitivo.‬\nPor eso, resulta necesario que el Congreso de la Nación haga valer las facultades que le otorga la Constitución Nacional para reparar el daño que el Gobierno de Cambiemos ha causado a más de diez millones de argentinxs.\nConocé el proyecto completo👇🏼\nhttp://telegra.ph/Bono-compensatorio-del-ajuste-ocasionado-por-la-Reforma-Previsional-03-19";
    std::string texto_con_caracteres_especiales = "Hoy presentamos un proyecto de ley para que lxs jubiladxs y beneficiarixs de la AUH cobren un bono de emergencia.\nCon este bono, lxs ciudadanxs que padecen en carne propia el ajuste previsional consumado por el Gobierno de Cambiemos en diciembre de 2017, recibirán una compensación.\n‪Es sabido.El Gobierno de Cambiemos miente todo el tiempo.Esta vez lo hizo cuando prometió que, con la nueva fórmula, las jubilaciones iban a aumentar más que la inflación.Falso.La inflación está descontrolada y las jubilaciones no paran de perder poder adquisitivo.‬\nPor eso, resulta necesario que el Congreso de la Nación haga valer las facultades que le otorga la Constitución Nacional para reparar el daño que el Gobierno de Cambiemos ha causado a más de diez millones de argentinxs.\nConocé el proyecto completo👇🏼\nhttp://telegra.ph/Bono-compensatorio-del-ajuste-ocasionado-por-la-Reforma-Previsional-03-19";

    std::string texto_sin_caracteres_especiales;
    texto_sin_caracteres_especiales += "Hoy presentamos un proyecto de ley para que lxs jubiladxs y beneficiarixs de la AUH cobren un bono de emergencia.\n";
    texto_sin_caracteres_especiales += "Con este bono, lxs ciudadanxs que padecen en carne propia el ajuste previsional consumado por el Gobierno de Cambiemos en diciembre de 2017, recibiran una compensacion.\n";
    texto_sin_caracteres_especiales += "Es sabido.El Gobierno de Cambiemos miente todo el tiempo.Esta vez lo hizo cuando prometio que, con la nueva formula, las jubilaciones iban a aumentar mas que la inflacion.Falso.La inflacion esta descontrolada y las jubilaciones no paran de perder poder adquisitivo.\n";
    texto_sin_caracteres_especiales += "Por eso, resulta necesario que el Congreso de la Nacion haga valer las facultades que le otorga la Constitucion Nacional para reparar el dano que el Gobierno de Cambiemos ha causado a mas de diez millones de argentinxs.\n";
    texto_sin_caracteres_especiales += "Conoce el proyecto completo\n";
    texto_sin_caracteres_especiales += "http ://telegra.ph/Bono-compensatorio-del-ajuste-ocasionado-por-la-Reforma-Previsional-03-19";

    scraping::depuracion::Depurador depurador;
    depurador.cargarMapeoUTF8("mapeo_utf8.json");

    depurador.reemplazarTodosLosCaracteresEspeciales(texto_con_caracteres_especiales);

    ASSERT_EQ(texto_sin_caracteres_especiales, texto_con_caracteres_especiales);
}

TEST(Depuracion, eliminarTildes)
{
    std::string oracion_con_tildes = "había una vez un café que usaba una cámara con mucha emoción.";
    std::string cafe_sin_tilde = "habia una vez un cafe que usaba una camara con mucha emocion.";

    std::string palabra_transformada = oracion_con_tildes;

    scraping::depuracion::Depurador depurador;
    depurador.cargarMapeoUTF8("mapeo_utf8.json");

    depurador.eliminarTildes(palabra_transformada);

    ASSERT_STREQ(cafe_sin_tilde.c_str(), palabra_transformada.c_str());
}

TEST(Depuracion, todoMinuscula)
{
    std::string oracion_con_mayusculas = "HabIa uNa veZ un CafE qUE uSaBa UnA cAmArA CoN MuChA EmOCiOn.";
    std::string oracion_sin_mayusculas = "habia una vez un cafe que usaba una camara con mucha emocion.";

    scraping::depuracion::Depurador depurador;

    depurador.todoMinuscula(oracion_con_mayusculas);

    ASSERT_STREQ(oracion_sin_mayusculas.c_str(), oracion_con_mayusculas.c_str());
}

TEST(Depuracion, eliminarSignosYPuntuacion)
{
    std::string oracion_con_simbolos_no_caracteres = "y matori dijo: \"me quedan $20,35.-\". habia (mal)gastado el premio -que no habia ganado- en un monton de m&m y demas basuras.";
    std::string oracion_sin_simbolos_no_caracteres = "y matori dijo me quedan 20 35 habia mal gastado el premio que no habia ganado en un monton de m m y demas basuras ";

    scraping::depuracion::Depurador depurador;

    depurador.eliminarSignosYPuntuacion(oracion_con_simbolos_no_caracteres);

    ASSERT_STREQ(oracion_con_simbolos_no_caracteres.c_str(), oracion_sin_simbolos_no_caracteres.c_str());
}

TEST(Depuracion, eliminarURLs)
{
    std::string texto_con_urls = "Jerusalén: ftp:\/\/t.co\/asdijv1m2_1234.html#matorito suenan sirenas de alarma en el sur de Israel http:\/\/userid:password@example.com:8080\/ tras el disparo de un cohete desde Gaza…https:\/\/t.co\/eqSJm9AkQB";
    std::string texto_sin_urls = "Jerusalén: suenan sirenas de alarma en el sur de Israel tras el disparo de un cohete desde Gaza…";

    scraping::depuracion::Depurador depurador;

    depurador.eliminarURLs(texto_con_urls);
 
    ASSERT_STREQ(texto_con_urls.c_str(), texto_sin_urls.c_str());

    std::string texto_con_urls_2 = "#YCRT Dirigentes sindicales y políticos santacruceños se reunieron con @cfkargentina para \nanalizar el estado de situación que atraviesa el yacimiento, tras los más de 400 despidos dispuestos por la intervención del Gobierno Nacional \nhttps://t.co/ptle5JWGte https://t.co/rM23gXjjqg";
    std::string texto_sin_urls_2 = "#YCRT Dirigentes sindicales y políticos santacruceños se reunieron con @cfkargentina para \nanalizar el estado de situación que atraviesa el yacimiento, tras los más de 400 despidos dispuestos por la intervención del Gobierno Nacional \n ";
    
    depurador.eliminarURLs(texto_con_urls_2);

    ASSERT_STREQ(texto_con_urls_2.c_str(), texto_sin_urls_2.c_str());
}

TEST(Depuracion, eliminarPalabrasMuyCortas)
{
    std::vector<std::string> palabras_a_depurar = { "hola", "si", "que", "tal", "como", "le", "va", "espero", "que", "bien" };

    scraping::depuracion::Depurador depurador;

    depurador.eliminarPalabrasMuyCortas(palabras_a_depurar);

    ASSERT_STREQ("hola", palabras_a_depurar[0].c_str());
    ASSERT_STREQ("que", palabras_a_depurar[1].c_str());
    ASSERT_STREQ("tal", palabras_a_depurar[2].c_str());
    ASSERT_STREQ("como", palabras_a_depurar[3].c_str());
    ASSERT_STREQ("espero", palabras_a_depurar[4].c_str());
    ASSERT_STREQ("que", palabras_a_depurar[5].c_str());
    ASSERT_STREQ("bien", palabras_a_depurar[6].c_str());
}

TEST(Depuracion, eliminarPalabrasMuyLargas)
{
    std::vector<std::string> palabras_a_depurar = { "otorrinolaringolo", "profesion", "nombre", "extramegadificil", "pronunciacion" };

    scraping::depuracion::Depurador depurador;

    depurador.eliminarPalabrasMuyLargas(palabras_a_depurar);

    ASSERT_STREQ("profesion", palabras_a_depurar[0].c_str());
    ASSERT_STREQ("nombre", palabras_a_depurar[1].c_str());
    ASSERT_STREQ("pronunciacion", palabras_a_depurar[2].c_str());
}

TEST(Depuracion, eliminarPreposiciones)
{
    std::vector<std::string> palabras_a_depurar = { "hola", "que", "tal", "con", "mucho", "gusto", "hacia", "usted", "durante" };

    scraping::depuracion::Depurador depurador;

    depurador.eliminarPreposiciones(palabras_a_depurar);

    ASSERT_STREQ("hola", palabras_a_depurar[0].c_str());
    ASSERT_STREQ("que", palabras_a_depurar[1].c_str());
    ASSERT_STREQ("tal", palabras_a_depurar[2].c_str());
    ASSERT_STREQ("mucho", palabras_a_depurar[3].c_str());
    ASSERT_STREQ("gusto", palabras_a_depurar[4].c_str());
    ASSERT_STREQ("usted", palabras_a_depurar[5].c_str());
}

TEST(Depuracion, eliminarStopwords)
{
    std::vector<std::string> palabras_a_depurar = { "hola", "que", "tal", "con", "mucho", "gusto", "hacia", "usted", "durante" };

    scraping::depuracion::Depurador depurador;
    //depurador.cargarStopwords("stopwords_espaniol.txt");

    depurador.eliminarStopwords(palabras_a_depurar);

    ASSERT_STREQ("gusto", palabras_a_depurar[0].c_str());
    ASSERT_STREQ("hola", palabras_a_depurar[1].c_str());
    ASSERT_STREQ("tal", palabras_a_depurar[2].c_str());
}