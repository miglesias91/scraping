// gtest
#include <gtest/gtest.h>

// stl
#include <fstream>
#include <sstream>

// twitter
#include <depuracion/include/Depurador.h>

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

TEST(Depuracion, reemplazarCaracteresEspeciales)
{
    std::string caracteres_normales_especiales_a_reemplazar = "µ a ¶ · ¸ ¹ º b » ¼ c ½ ¾ ¿ d À Á Â 1 Ã Ä Å Æ 2 Ç È É Ê Ë Ì Í Î Ï 3 Ð Ñ Ò Ó Ô Õ Ö × Ø Ù Ú Û Ü Ý Þ 4 ß à á â ã ä å æ";
    std::string caracteres_reemplazados = "u a p . . ^1 o b >> 1/4 c 1/2 3/4 ? d A A A 1 A A A AE 2 C E E E E I I I I 3 D N O O O O O x O U U U U Y P 4 B a a a a a a ae";

    scraping::depuracion::Depurador depurador;
    depurador.cargarMapeoUTF8("mapeo_utf8.json");

    depurador.reemplazarTodosLosCaracteresEspeciales(caracteres_normales_especiales_a_reemplazar);

    ASSERT_STREQ(caracteres_reemplazados.c_str(), caracteres_normales_especiales_a_reemplazar.c_str());
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