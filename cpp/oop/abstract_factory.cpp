#include <iostream>
#include <vector>

using namespace std;

class ProductA
{
public:
    virtual void info() = 0;
    virtual ~ProductA() {}
};

class ProductB
{
public:
    virtual void info() = 0;
    virtual ~ProductB() {}
};

class ProductC
{
public:
    virtual void info() = 0;
    virtual ~ProductC() {}
};

class RedProductA : public ProductA
{
public:
    void info()
    {
        cout << "RedProductA" << endl;
    }
};

class RedProductB : public ProductB
{
public:
    void info()
    {
        cout << "RedProductB" << endl;
    }
};

class RedProductC : public ProductC
{
public:
    void info()
    {
        cout << "RedProductC" << endl;
    }
};

class GreenProductA : public ProductA
{
public:
    void info()
    {
        cout << "GreenProductA" << endl;
    }
};

class GreenProductB : public ProductB
{
public:
    void info()
    {
        cout << "GreenProductB" << endl;
    }
};

class GreenProductC : public ProductC
{
public:
    void info()
    {
        cout << "GreenProductC" << endl;
    }
};

class BlueProductA : public ProductA
{
public:
    void info()
    {
        cout << "BlueProductA" << endl;
    }
};

class BlueProductB : public ProductB
{
public:
    void info()
    {
        cout << "BlueProductB" << endl;
    }
};

class BlueProductC : public ProductC
{
public:
    void info()
    {
        cout << "BlueProductC" << endl;
    }
};

class ProductFactory
{
public:
    virtual ProductA *CreateProductA() = 0;
    virtual ProductB *CreateProductB() = 0;
    virtual ProductC *CreateProductC() = 0;
    virtual ~ProductFactory() {}
};

class RedProductFactory : public ProductFactory
{
public:
    ProductA *CreateProductA()
    {
        return new RedProductA;
    }
    ProductB *CreateProductB()
    {
        return new RedProductB;
    }
    ProductC *CreateProductC()
    {
        return new RedProductC;
    }
};

class GreenProductFactory : public ProductFactory
{
public:
    ProductA *CreateProductA()
    {
        return new GreenProductA;
    }
    ProductB *CreateProductB()
    {
        return new GreenProductB;
    }
    ProductC *CreateProductC()
    {
        return new GreenProductC;
    }
};

class BlueProductFactory : public ProductFactory
{
public:
    ProductA *CreateProductA()
    {
        return new BlueProductA;
    }
    ProductB *CreateProductB()
    {
        return new BlueProductB;
    }
    ProductC *CreateProductC()
    {
        return new BlueProductC;
    }
};

class Product
{
public:
    ~Product()
    {
        int i;
        for (i = 0; i < PA.size(); ++i)
            delete PA[i];
        for (i = 0; i < PB.size(); ++i)
            delete PB[i];
        for (i = 0; i < PC.size(); ++i)
            delete PC[i];
    }
    void info()
    {
        int i;
        for (i = 0; i < PA.size(); ++i)
            PA[i]->info();
        for (i = 0; i < PB.size(); ++i)
            PB[i]->info();
        for (i = 0; i < PC.size(); ++i)
            PC[i]->info();
    }
    vector<ProductA *> PA;
    vector<ProductB *> PB;
    vector<ProductC *> PC;
};

class DoShopping_TakeAll
{
public:
    Product *AddProduct(ProductFactory &factory)
    {
        Product *product = new Product;
        product->PA.push_back(factory.CreateProductA());
        product->PB.push_back(factory.CreateProductB());
        product->PC.push_back(factory.CreateProductC());
        return product;
    }
};

class DoShopping_TakeB
{
public:
    Product *AddProduct(ProductFactory &factory)
    {
        Product *product = new Product;
        product->PB.push_back(factory.CreateProductB());
        return product;
    }
};

class DoShopping_AddB
{
public:
    ProductB *AddProduct(ProductFactory &factory)
    {
        ProductB *productb;
        productb = factory.CreateProductB();
        return productb;
    }
};

/*
20. Abstract Factory
*/

int main()
{
    DoShopping_TakeAll cart_all;
    RedProductFactory r_factory;
    GreenProductFactory g_factory;
    BlueProductFactory b_factory;
    Product *product_red = cart_all.AddProduct(r_factory);
    Product *product_green = cart_all.AddProduct(g_factory);
    Product *product_blue = cart_all.AddProduct(b_factory);
    product_red->info();
    product_green->info();
    product_blue->info();
    cout << "\n==========================\n\n";
    DoShopping_TakeB cart_b;
    Product *product_red_b = cart_b.AddProduct(r_factory);
    Product *product_green_b = cart_b.AddProduct(g_factory);
    Product *product_blue_b = cart_b.AddProduct(b_factory);
    product_red_b->info();
    product_green_b->info();
    product_blue_b->info();
    cout << "\n==========================\n\n";
    DoShopping_AddB add_b;
    Product *product_multiple_b = cart_b.AddProduct(r_factory);
    product_multiple_b->PB.push_back(add_b.AddProduct(r_factory));
    product_multiple_b->PB.push_back(add_b.AddProduct(r_factory));
    product_multiple_b->PB.push_back(add_b.AddProduct(g_factory));
    product_multiple_b->PB.push_back(add_b.AddProduct(g_factory));
    product_multiple_b->PB.push_back(add_b.AddProduct(b_factory));
    product_multiple_b->PB.push_back(add_b.AddProduct(b_factory));
    product_multiple_b->info();
    system("pause>>void");
}