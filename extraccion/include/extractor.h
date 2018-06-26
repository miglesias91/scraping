#pragma once

namespace scraping {
namespace extraccion {
class extractor {
public:
    extractor();
    virtual ~extractor();

    bool extraer_facebook();
    bool extraer_twitter();
    bool extraer_portales();

private:
};

};
};

