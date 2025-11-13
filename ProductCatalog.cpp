#include <iostream>
#include <string>
#include <iomanip>
#include <limits>

using namespace std;

struct Product {
    string name;
    double price;
    int quantity;
};

void input(Product* arr, int n) {
    if (arr == nullptr || n <= 0) {
        cout << "Error: Invalid array size or pointer." << endl;
        return;
    }
    cout << "--- ENTERING PRODUCT DATA ---\n";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int i = 0; i < n; ++i) {
        cout << "\nProduct #" << i + 1 << ":\n";

        cout << "  Name: ";
        getline(cin, arr[i].name);

        cout << "  Price (USD): ";
        while (!(cin >> arr[i].price) || arr[i].price <= 0) {
            cout << "  Error: Invalid price. Try again: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        cout << "  Quantity (pcs): ";
        while (!(cin >> arr[i].quantity) || arr[i].quantity < 0) {
            cout << "  Error: Invalid quantity. Try again: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cout << "\nData entry complete." << endl;
}

void show(const Product* arr, int n) {
    if (arr == nullptr || n <= 0) {
        cout << "\nCatalog is empty or uninitialized." << endl;
        return;
    }

    cout << "\n--- PRODUCT CATALOG ---\n";
    cout << left << setw(4) << "#"
         << setw(30) << "Name"
         << right << setw(10) << "Price"
         << setw(10) << "Qty"
         << endl;
    cout << string(54, '-') << endl;

    for (int i = 0; i < n; ++i) {
        cout << left << setw(4) << i + 1
             << setw(30) << arr[i].name
             << right << fixed << setprecision(2) << setw(10) << arr[i].price
             << setw(10) << arr[i].quantity
             << endl;
    }
    cout << string(54, '-') << endl;
}

Product* findMostExpensive(Product* arr, int n) {
    if (arr == nullptr || n <= 0) {
        return nullptr;
    }

    Product* mostExpensive = arr;

    for (int i = 1; i < n; ++i) {
        if (arr[i].price > mostExpensive->price) {
            mostExpensive = &arr[i];
        }
    }
    return mostExpensive;
}

double totalSum(const Product* arr, int n) {
    double sum = 0.0;
    if (arr == nullptr) {
        return sum;
    }

    for (int i = 0; i < n; ++i) {
        sum += arr[i].price * arr[i].quantity;
    }
    return sum;
}

int main() {
    int numProducts;

    cout << "Enter the number of products in the catalog: ";
    if (!(cin >> numProducts) || numProducts <= 0) {
        cout << "Invalid input. Defaulting to 3 products." << endl;
        numProducts = 3;
    }

    Product* catalog = new Product[numProducts];

    input(catalog, numProducts);

    show(catalog, numProducts);

    Product* mostExp = findMostExpensive(catalog, numProducts);

    if (mostExp != nullptr) {
        cout << "\nMOST EXPENSIVE PRODUCT:\n";
        cout << "  Name: **" << mostExp->name << "**\n";
        cout << "  Price: " << fixed << setprecision(2) << mostExp->price << " USD\n";
    }

    double total = totalSum(catalog, numProducts);

    cout << "\nTOTAL CATALOG VALUE (Price * Quantity):\n";
    cout << "  Total: **" << fixed << setprecision(2) << total << "** USD.\n";

    delete[] catalog;
    catalog = nullptr;
    cout << "\nMemory freed. Program finished." << endl;

    return 0;
}
