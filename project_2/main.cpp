#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>

using namespace std;

struct Order
{
    string client_ord;
    int side, amount, order_id , status, instrument;
    double unitPrice;

};

map<string, Order> order;


void readOrdersFromFile(const string &filename, map<string, Buyer> &buyers, map<string, Seller> &sellers, string ty)
{
    cout << "Opening files" << endl;
    ifstream inputFile(filename);
    if (!inputFile.is_open())
    {
        cerr << "Error: Could not open input file" << std::endl;
        return;
    }
    cout << " File successfully loaded " << std::endl;
    string line;
    while (getline(inputFile, line))
    {
        cout << "separating the row" << std::endl;
        istringstream iss(line);
        string client_od;
        int side, amount, order_id, instrument, status;
        double unitPrice;
        iss >> order_id >> client_od >> instrument >> side >> status >> amount >> unitPrice;

        order[name] = {name, unitPrice, amount};
        std::cout << "buyers " << name  << std::endl;

    }

    inputFile.close();
}

bool isBetterOption(const Seller &seller, const Buyer &newBuyer) {
    if (!seller.currentMatch.empty()) {
        const Buyer &currentBuyer = buyers[seller.currentMatch];
        return newBuyer.unitPrice > currentBuyer.unitPrice; // Compare based on your criteria
    }
    return true; // No current match
}

void match(Buyer &buyer, Seller &seller) {
    if (!seller.currentMatch.empty()) {
        buyers[seller.currentMatch].currentMatch.clear();
    }
    buyer.currentMatch = seller.name;
    seller.currentMatch = buyer.name;
}

void stableMatching() {
    std::vector<Buyer> unmatchedBuyers(buyers.size());
    std::transform(buyers.begin(), buyers.end(), unmatchedBuyers.begin(), [](const auto &pair) { return pair.second; });
    std::sort(unmatchedBuyers.begin(), unmatchedBuyers.end(), compareBuyers);

    while (!unmatchedBuyers.empty()) {
        Buyer &currentBuyer = unmatchedBuyers.back();
        for (const std::string &sellerName : currentBuyer.preferences) {
            Seller &currentSeller = sellers[sellerName];
            if (currentSeller.amount > 0 && currentBuyer.unitPrice >= currentSeller.unitPrice && isBetterOption(currentSeller, currentBuyer)) {
                match(currentBuyer, currentSeller);
                currentSeller.amount--;
                unmatchedBuyers.pop_back();
                break;
            }
        }
    }
}

int main() {
    std::cout << "Starting the process"<< std::endl;
    std::string ty = "buyer";
    readOrdersFromFile("buyers.csv", buyers, sellers, ty);
    std::cout<< "read the buyers file" << std::endl;
    ty = "seller";
    readOrdersFromFile("sellers.csv", buyers, sellers, ty);
    std::cout<< "read the sellers file" << std::endl;

    stableMatching();

    // Write matched results to output CSV file
    std::ofstream outputFile("output.csv");
    if (!outputFile.is_open()) {
        std::cerr << "Error: Could not open output file" << std::endl;
        return 1;
    }

    outputFile << "Buyer,Seller,Unit Price,Amount\n";
    for (const auto &buyerPair : buyers) {
        const Buyer &buyer = buyerPair.second;
        const Seller &seller = sellers[buyer.currentMatch];
        if (!buyer.currentMatch.empty()) {
            outputFile << buyer.name << "," << seller.name << "," << seller.unitPrice << "," << seller.amount << "\n";
        }
    }

    outputFile.close();

    std::cout << "Matching complete. Results saved in output.csv." << std::endl;

    return 0;
}