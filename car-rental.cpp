#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class User
{
public:
    string name;
    int id;
    string password;

public:
    User(string name, int id, string password) : name(name), id(id), password(password) {}

    void display_details() const
    {
        cout << "Name: " << name << endl;
        cout << "ID: " << id << endl;
    }

    void set_password(string password)
    {
        this->password = password;
    }

    string get_password() const
    {
        return password;
    }
};

class Customer : public User
{
private:
    vector<int> rented_cars;
    double fine_due;
    double customer_record;

public:
    Customer(string name, int id, string password) : User(name, id, password), customer_record(0) {}

    void rent_car(int car_id)
    {
        rented_cars.push_back(car_id);
    }

    int get_id() const
    {
        return id;
    }

    void return_car(int car_id)
    {
        rented_cars.erase(find(rented_cars.begin(), rented_cars.end(), car_id));
    }

    void calculate_fine(double due_date)
    {
        fine_due += (due_date - 1) * 10;
    }

    void update_customer_record(double new_record)
    {
        customer_record = new_record;
    }

    void clear_due()
    {
        fine_due = 0;
    }

    void writeToFile() const
    {
        ofstream outFile("customer_data.txt", ios::app);

        if (!outFile.is_open())
        {
            cerr << "Unable to open the file\n";
            return;
        }

        // Write customer details to file
        outFile << "Name: " << name << endl;
        outFile << "ID: " << id << endl;
        outFile << "Password: " << password << endl;

        // Write rented cars to file
        outFile << "Rented Cars: ";
        for (int car_id : rented_cars)
        {
            outFile << car_id << " ";
        }
        outFile << endl;

        outFile << "Fine Due: " << fine_due << endl;
        outFile << "Customer Record: " << customer_record << endl;

        outFile << "--------------------------------------" << endl;

        outFile.close();
    }

    static void readFromFile()
    {
        ifstream inFile("customer_data.txt");

        if (!inFile.is_open())
        {
            cerr << "Unable to open the file\n";
            return;
        }

        string line;
        while (getline(inFile, line))
        {
            cout << line << endl;
        }

        inFile.close();
    }
};

class Employee : public User
{
private:
    vector<int> rented_cars;
    double fine_due;
    double employee_record;

public:
    Employee(string name, int id, string password) : User(name, id, password), employee_record(0) {}

    int get_id() const
    {
        return id;
    }

    void rent_car(int car_id)
    {
        rented_cars.push_back(car_id);
    }

    void return_car(int car_id)
    {
        rented_cars.erase(find(rented_cars.begin(), rented_cars.end(), car_id));
    }

    void calculate_fine(double due_date)
    {
        fine_due += (due_date - 1) * 10;
    }

    void update_employee_record(double new_record)
    {
        employee_record = new_record;
    }

    void clear_due()
    {
        fine_due = 0;
    }

    void writeToFile() const
    {
        ofstream outFile("employee_data.txt", ios::app);

        if (!outFile.is_open())
        {
            cerr << "Unable to open the file\n";
            return;
        }

        // Write employee details to file
        outFile << "Name: " << name << endl;
        outFile << "ID: " << id << endl;
        outFile << "Password: " << password << endl;

        // Write rented cars to file
        outFile << "Rented Cars: ";
        for (int car_id : rented_cars)
        {
            outFile << car_id << " ";
        }
        outFile << endl;

        outFile << "Fine Due: " << fine_due << endl;
        outFile << "Employee Record: " << employee_record << endl;

        outFile << "--------------------------------------" << endl;

        outFile.close();
    }

    static void readFromFile()
    {
        ifstream inFile("employee_data.txt");

        if (!inFile.is_open())
        {
            cerr << "Unable to open the file\n";
            return;
        }

        string line;
        while (getline(inFile, line))
        {
            cout << line << endl;
        }

        inFile.close();
    }
};

class Car
{
private:
    int id;
    string model;
    string condition;
    double other_details;

public:
    Car(int id, string model, string condition, double other_details) : id(id), model(model), condition(condition), other_details(other_details) {}

    int get_id() const
    {
        return id;
    }

    void rent_car()
    {
        condition = "Rented";
    }

    void show_due_date() const
    {
        cout << "Due date: " << 1 << endl;
    }

    void update_condition(string new_condition)
    {
        condition = new_condition;
    }

    void writeToFile() const
    {
        ofstream outFile("car_data.txt", ios::app);

        if (!outFile.is_open())
        {
            cerr << "Unable to open the file\n";
            return;
        }

        // Write car details to file
        outFile << "Car ID: " << id << endl;
        outFile << "Model: " << model << endl;
        outFile << "Condition: " << condition << endl;
        outFile << "Other Details: " << other_details << endl;
        outFile << "--------------------------------------" << endl;

        outFile.close();
    }

    static void readFromFile()
    {
        ifstream inFile("car_data.txt");

        if (!inFile.is_open())
        {
            cerr << "Unable to open the file\n";
            return;
        }

        string line;
        while (getline(inFile, line))
        {
            cout << line << endl;
        }

        inFile.close();
    }
};

class Manager : public User
{
public:
    Manager(string name, int id, string password) : User(name, id, password) {}

    void add_customer(Customer customer)
    {
        customers.push_back(customer);
    }

    void update_customer(int id, Customer new_customer)
    {
        for (int i = 0; i < customers.size(); i++)
        {
            if (customers[i].get_id() == id)
            {
                customers[i] = new_customer;
                break;
            }
        }
    }

    void delete_customer(int id)
    {
        customers.erase(remove_if(customers.begin(), customers.end(), [id](Customer customer)
                                  { return customer.get_id() == id; }),
                        customers.end());
    }

    void add_employee(Employee employee)
    {
        employees.push_back(employee);
    }

    void update_employee(int id, Employee new_employee)
    {
        for (int i = 0; i < employees.size(); i++)
        {
            if (employees[i].get_id() == id)
            {
                employees[i] = new_employee;
                break;
            }
        }
    }

    void delete_employee(int id)
    {
        employees.erase(remove_if(employees.begin(), employees.end(), [id](Employee employee)
                                  { return employee.get_id() == id; }),
                        employees.end());
    }

    void add_car(Car car)
    {
        cars.push_back(car);
    }

    void update_car(int id, Car new_car)
    {
        for (int i = 0; i < cars.size(); i++)
        {
            if (cars[i].get_id() == id)
            {
                cars[i] = new_car;
                break;
            }
        }
    }

    void delete_car(int id)
    {
        cars.erase(remove_if(cars.begin(), cars.end(), [id](Car car)
                             { return car.get_id() == id; }),
                   cars.end());
    }

    void writeToFile() const
    {
        ofstream outFile("manager_data.txt", ios::app);

        if (!outFile.is_open())
        {
            cerr << "Unable to open the file\n";
            return;
        }

        // Write manager details to file
        outFile << "Name: " << name << endl;
        outFile << "ID: " << id << endl;
        outFile << "Password: " << password << endl;

        // Write customer details to file
        outFile << "Customers:\n";
        for (const auto &customer : customers)
        {
            outFile << "----------------\n";
            customer.writeToFile();
        }

        // Write employee details to file
        outFile << "Employees:\n";
        for (const auto &employee : employees)
        {
            outFile << "----------------\n";
            employee.writeToFile();
        }

        // Write car details to file
        outFile << "Cars:\n";
        for (const auto &car : cars)
        {
            outFile << "----------------\n";
            // You need to implement a writeToFile() function in the Car class
            // and call it here to write car details to the file.
        }

        outFile << "--------------------------------------" << endl;

        outFile.close();
    }

    static void readFromFile()
    {
        ifstream inFile("manager_data.txt");

        if (!inFile.is_open())
        {
            cerr << "Unable to open the file\n";
            return;
        }

        string line;
        while (getline(inFile, line))
        {
            cout << line << endl;
        }

        inFile.close();
    }

private:
    vector<Customer> customers;
    vector<Employee> employees;
    vector<Car> cars;
};

class CustomerDatabase
{
private:
    vector<Customer> customers;

public:
    void add_customer(const Customer &customer)
    {
        customers.push_back(customer);
    }

    void update_customer(int id, const Customer &new_customer)
    {
        auto it = find_if(customers.begin(), customers.end(), [id](const Customer &customer) {});
        if (it != customers.end())
        {
            *it = new_customer;
        }
    }

    void delete_customer(int id)
    {
        customers.erase(remove_if(customers.begin(), customers.end(), [id](const Customer &customer) {}), customers.end());
    }

    Customer get_customer(int id) const
    {
        auto it = find_if(customers.begin(), customers.end(), [id](const Customer &customer) {});
        if (it != customers.end())
        {
            return *it;
        }
        throw invalid_argument("Customer not found");
    }

    vector<Customer> get_all_customers() const
    {
        return customers;
    }

    void writeToFile() const
    {
        ofstream outFile("customer_database.txt", ios::trunc);

        if (!outFile.is_open())
        {
            cerr << "Unable to open the file\n";
            return;
        }

        for (const auto &customer : customers)
        {
            customer.writeToFile();
        }

        outFile.close();
    }

    void readFromFile()
    {
        ifstream inFile("customer_database.txt");

        if (!inFile.is_open())
        {
            cerr << "Unable to open the file\n";
            return;
        }

        customers.clear(); // Clear existing data

        int id;
        string name, password;
        while (inFile >> id >> name >> password)
        {
            Customer customer(name, id, password);
            customers.push_back(customer);
        }

        inFile.close();
    }
};

class EmployeeDatabase
{
private:
    vector<Employee> employees;

public:
    void add_employee(const Employee &employee)
    {
        employees.push_back(employee);
    }

    void update_employee(int id, const Employee &new_employee)
    {
        auto it = find_if(employees.begin(), employees.end(), [id](const Employee &employee)
                          { return employee.get_id() == id; });
        if (it != employees.end())
        {
            *it = new_employee;
        }
    }

    void delete_employee(int id)
    {
        employees.erase(remove_if(employees.begin(), employees.end(), [id](const Employee &employee)
                                  { return employee.get_id() == id; }),
                        employees.end());
    }

    Employee get_employee(int id) const
    {
        auto it = find_if(employees.begin(), employees.end(), [id](const Employee &employee)
                          { return employee.get_id() == id; });
        if (it != employees.end())
        {
            return *it;
        }
        throw invalid_argument("Employee not found");
    }

    vector<Employee> get_all_employees() const
    {
        return employees;
    }

    void writeToFile() const
    {
        ofstream outFile("employee_database.txt", ios::trunc);

        if (!outFile.is_open())
        {
            cerr << "Unable to open the file\n";
            return;
        }

        for (const auto &employee : employees)
        {
            employee.writeToFile();
        }

        outFile.close();
    }

    void readFromFile()
    {
        ifstream inFile("employee_database.txt");

        if (!inFile.is_open())
        {
            cerr << "Unable to open the file\n";
            return;
        }

        employees.clear(); // Clear existing data

        int id;
        string name, password;
        while (inFile >> id >> name >> password)
        {
            Employee employee(name, id, password);
            employees.push_back(employee);
        }

        inFile.close();
    }
};

class Car
{
private:
    int id;
    string model;
    string condition;
    string other_details;

public:
    Car(int id, const string &model, const string &condition, const string &other_details)
        : id(id), model(model), condition(condition), other_details(other_details) {}

    int get_id() const
    {
        return id;
    }

    void display_details() const
    {
        cout << "Car ID: " << id << endl;
        cout << "Model: " << model << endl;
        cout << "Condition: " << condition << endl;
        cout << "Other Details: " << other_details << endl;
    }

    void writeToFile(ofstream &outFile) const
    {
        outFile << id << " " << model << " " << condition << " " << other_details << endl;
    }
};

class CarDatabase
{
private:
    vector<Car> cars;

public:
    void add_car(const Car &car)
    {
        cars.push_back(car);
    }

    void update_car(int id, const Car &new_car)
    {
        auto it = find_if(cars.begin(), cars.end(), [id](const Car &car)
                          { return car.get_id() == id; });
        if (it != cars.end())
        {
            *it = new_car;
        }
    }

    void delete_car(int id)
    {
        cars.erase(remove_if(cars.begin(), cars.end(), [id](const Car &car)
                             { return car.get_id() == id; }),
                   cars.end());
    }

    Car get_car(int id) const
    {
        auto it = find_if(cars.begin(), cars.end(), [id](const Car &car)
                          { return car.get_id() == id; });
        if (it != cars.end())
        {
            return *it;
        }
        throw invalid_argument("Car not found");
    }

    vector<Car> get_all_cars() const
    {
        return cars;
    }

    void writeToFile() const
    {
        ofstream outFile("car_database.txt", ios::trunc);

        if (!outFile.is_open())
        {
            cerr << "Unable to open the file\n";
            return;
        }

        for (const auto &car : cars)
        {
            car.writeToFile(outFile);
        }

        outFile.close();
    }

    void readFromFile()
    {
        ifstream inFile("car_database.txt");

        if (!inFile.is_open())
        {
            cerr << "Unable to open the file\n";
            return;
        }

        cars.clear(); // Clear existing data

        int id;
        string model, condition;
        string other_details;
        while (inFile >> id >> model >> condition >> other_details)
        {
            Car car(id, model, condition, other_details);
            cars.push_back(car);
        }

        inFile.close();
    }
};
class CarRentalSystem
{
public:
    CustomerDatabase customer_database;
    EmployeeDatabase employee_database;
    CarDatabase car_database;

    void writeToFile()
    {
        customer_database.writeToFile();
        employee_database.writeToFile();
        car_database.writeToFile();
    }

    void readFromFile()
    {
        customer_database.readFromFile();
        employee_database.readFromFile();
        car_database.readFromFile();
    }
};

int main()
{
    CarRentalSystem system;

    // Add customers
    for (int i = 1; i <= 5; i++)
    {
        system.customer_database.add_customer(Customer("Customer" + to_string(i), i, "555-" + to_string(i)));
    }

    // Add employees
    for (int i = 1; i <= 5; i++)
    {
        if (i == 1)
        {
            system.employee_database.add_employee(Employee("Manager" + to_string(i), i, "Manager"));
        }
        else
        {
            system.employee_database.add_employee(Employee("Employee" + to_string(i), i, "Role" + to_string(i)));
        }
    }

    // Add cars
    for (int i = 1; i <= 5; i++)
    {
        system.car_database.add_car(Car(i, "Make" + to_string(i), "Model" + to_string(i), "Color" + to_string(i)));
    }

    // Search for a car
    for (int i = 1; i <= 5; i++)
    {
        try
        {
            Car car = system.car_database.get_car(i);
            cout << "Car Found: " << &car << endl;
        }
        catch (invalid_argument &e)
        {
            cout << e.what() << endl;
        }
    }

    // Search for a customer
    for (int i = 1; i <= 5; i++)
    {
        try
        {
            Customer customer = system.customer_database.get_customer(i);
            cout << "Customer Found: " << &customer << endl;
        }
        catch (invalid_argument &e)
        {
            cout << e.what() << endl;
        }
    }

    // Write data to file before program termination
    system.writeToFile();

    return 0;
}
