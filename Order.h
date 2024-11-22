#include "menu.h"

class Order : public Menu
{
private:
    Book **bookCode;
    int *bookCount;
    int types;

public:
    Order();
    ~Order();
    void Display_product();
    void ProcessOrder();
    void Add_Product();
    void confirm();
    void bill();
    long long Calculator();
    void reset();
};
