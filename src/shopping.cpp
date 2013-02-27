/*
ID: joao.c.1
PROG: shopping
LANG: C++
*/

#include <fstream>
#include <map>
#include <vector>

using namespace std;

#define MAX_PRODUCTS 5
#define MAX_CODE 1000

struct Offer {
    int nProducts;
    int products[MAX_PRODUCTS];
    int quantities[MAX_PRODUCTS];
    int price;
};

struct Quantities {
    int nProducts;
    int quantities[MAX_PRODUCTS];

    bool operator<(const Quantities & that) const {
        for (int i = 0; i < nProducts; i++) {
            if (quantities[i] < that.quantities[i])
                return true;
            else if (quantities[i] > that.quantities[i])
                return false;
        }

        return false;
    }
};

struct Basket {
    int nProducts;
    int codes[MAX_CODE];
    int quantities[MAX_PRODUCTS];
    int prices[MAX_PRODUCTS];

    Quantities toQuantities() const {
        Quantities q;
        q.nProducts = nProducts;
        for (int i = 0; i < nProducts; i++)
            q.quantities[i] = quantities[i];
        return q;
    }
};

inline bool validOffer(Offer & offer,
                       Basket & basket) {
    for (int i = 0; i < offer.nProducts; i++)
        if (basket.quantities[basket.codes[offer.products[i]]] < offer.quantities[i])
            return false;

    return true;
}

inline void reduceOffer(Offer & offer,
                        Basket & basket) {
    for (int i = 0; i < offer.nProducts; i++)
        basket.quantities[basket.codes[offer.products[i]]] -= offer.quantities[i];
}

inline void addOffer(Offer & offer,
                     Basket & basket) {
    for (int i = 0; i < offer.nProducts; i++)
        basket.quantities[basket.codes[offer.products[i]]] += offer.quantities[i];
}

int getLowestPossiblePrice(vector<Offer> & offers,
                           Basket & basket) {
    static map<Quantities, int> bestPrice;
    int O = offers.size();

    if (bestPrice[basket.toQuantities()] != 0)
        return bestPrice[basket.toQuantities()];

    for (int i = 0; i < O; i++) {
        if (validOffer(offers[i], basket)) {
            reduceOffer(offers[i], basket);
            int C = getLowestPossiblePrice(offers, basket) + offers[i].price;
            addOffer(offers[i], basket);
            if (bestPrice[basket.toQuantities()] == 0 || C < bestPrice[basket.toQuantities()])
                bestPrice[basket.toQuantities()] = C;
        }
    }

    for (int i = 0; i < basket.nProducts; i++) {
        if (basket.quantities[i] > 0) {
            basket.quantities[i]--;
            int C = getLowestPossiblePrice(offers, basket) + basket.prices[i];
            basket.quantities[i]++;
            if (bestPrice[basket.toQuantities()] == 0 || C < bestPrice[basket.toQuantities()])
                bestPrice[basket.toQuantities()] = C;
            break;
        }
    }

    return bestPrice[basket.toQuantities()];
}

int main() {
    ifstream fin("shopping.in");
    ofstream fout("shopping.out");

    int s;
    vector<Offer> offers;
    fin >> s;
    for (int i = 0; i < s; i++) {
        Offer offer;
        fin >> offer.nProducts;
        for (int j = 0; j < offer.nProducts; j++) {
            fin >> offer.products[j] >> offer.quantities[j];
        }
        fin >> offer.price;
        offers.push_back(offer);
    }

    Basket basket;
    fin >> basket.nProducts;
    for (int i = 0; i < basket.nProducts; i++) {
        int c;
        fin >> c;
        basket.codes[c] = i;
        fin >> basket.quantities[i] >> basket.prices[i];
    }

    fout << getLowestPossiblePrice(offers, basket) << endl;

    return 0;
}
