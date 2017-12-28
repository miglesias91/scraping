#pragma once

// stl
#include <string>

// modelo
#include <twitter/include/Tweet.h>

// depuracion
#include <depuracion/include/IDepurable.h>

namespace scraping
{
namespace depuracion
{

class DepurableTweet : public IDepurable
{
public:
    DepurableTweet(scraping::twitter::modelo::Tweet tweet_a_depurar);
    virtual ~DepurableTweet();

    // GETTERS
    
    virtual std::string getTextoDepurable();

    // SETTERS

    // METODOS

    // CONSULTAS

private:

    scraping::twitter::modelo::Tweet tweet_a_depurar;
};

};
};


