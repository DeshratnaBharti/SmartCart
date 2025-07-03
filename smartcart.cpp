
#include <bits/stdc++.h>
using namespace std;

class Product {
public:
    int id;
    string name;
    double price;
    int stock;

    Product(int pid, string pname, double pprice, int pstock) {
        id = pid;
        name = pname;
        price = pprice;
        stock = pstock;
    }

    void show() {
        cout << left << setw(6) << id
             << setw(18) << name
             << "₹" << setw(8) << price
             << "Qty: " << stock << endl;
    }
};

class Inventory {
    vector<Product> list;

public:
    void load(string filename) {
        ifstream file(filename);
        int pid, stk;
        string pname;
        double p;
        while (file >> pid >> pname >> p >> stk) {
            list.push_back(Product(pid, pname, p, stk));
        }
        file.close();
    }

    void save(string filename) {
        ofstream file(filename);
        for (auto &item : list) {
            file << item.id << " " << item.name << " " << item.price << " " << item.stock << endl;
        }
        file.close();
    }

    void showAll() {
        cout << "\n--- Available Products ---\n";
        for (auto &p : list) {
            p.show();
        }
    }

    Product* find(int pid) {
        for (auto &p : list) {
            if (p.id == pid) return &p;
        }
        return nullptr;
    }
};

class CartItem {
public:
    Product* prod;
    int qty;

    CartItem(Product* p, int q) {
        prod = p;
        qty = q;
    }

    double amount() {
        return prod->price * qty;
    }
};

class Cart {
    vector<CartItem> cart;

public:
    void add(Product* p, int q) {
        cart.push_back(CartItem(p, q));
    }

    void bill() {
        double total = 0;
        cout << "\nYour Cart:\n";
        for (auto &item : cart) {
            cout << item.prod->name << " x" << item.qty << " = ₹" << item.amount() << endl;
            item.prod->stock -= item.qty;
            total += item.amount();
        }
        double gst = total * 0.18;
        cout << "\nSubtotal: ₹" << total;
        cout << "\nGST (18%): ₹" << gst;
        cout << "\nTotal Payable: ₹" << total + gst << endl;
    }
};

int main() {
    Inventory inv;
    inv.load("products.txt");

    Cart myCart;
    int ch;

    while (true) {
        cout << "\n\n1. Show Products\n2. Add Item\n3. Checkout\n0. Quit\nChoose: ";
        cin >> ch;

        if (ch == 1) {
            inv.showAll();
        } else if (ch == 2) {
            int pid, qty;
            cout << "Product ID: ";
            cin >> pid;
            Product* p = inv.find(pid);
            if (p) {
                cout << "Quantity: ";
                cin >> qty;
                if (qty <= p->stock) {
                    myCart.add(p, qty);
                    cout << "Added to cart.";
                } else {
                    cout << "Not enough stock.";
                }
            } else {
                cout << "Item not found.";
            }
        } else if (ch == 3) {
            myCart.bill();
            inv.save("products.txt");
        } else if (ch == 0) {
            break;
        } else {
            cout << "Invalid choice.";
        }
    }

    return 0;
}
