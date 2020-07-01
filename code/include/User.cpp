class User
{
    // pointer to database that user is working with
    protected:
    DatabaseInterface* db;

    public:
    //TODO: ask about handling input in oop style (it this even a thing?)
    virtual void Ask_Input() = 0;
    virtual void List_Options() = 0;
};

class Client : public User
{
    public:
    Client(DatabaseInterface* _db)
    {
        db = _db;
    }

    void List_Options()
    {
        std::cout << "Get some info operation" << std::endl;
    }

    void Ask_Input()
    {
        // NOTE: yeah, better to move this somewhere else
        std::cout << "You are only allowed to read some data" << std::endl;
    }

    Info Get_Some_Info(u32 id)
    {
        return db->Get_Some_Info(id);
    }
};

class Manager : public User
{
    public:
    Manager(DatabaseInterface* _db)
    {
        db = _db;
    }

    void List_Options()
    {
        std::cout << "Get some info operation" << std::endl;
        std::cout << "Set some info operation" << std::endl;
    }

    void Ask_Input()
    {
    }
};

class Administrator : public User
{
    Config conf;

    public:
    Administrator(DatabaseInterface* _db)
    {
        db = _db;
    }

    void List_Options()
    {
        std::cout << "Get some info operation" << std::endl;
        std::cout << "Set some info operation" << std::endl;
        std::cout << "Configure database operation" << std::endl;
    }

    void Ask_Input()
    {
    }

    void Configure_Database(Config conf)
    {
        db->Configure_Database(conf);
    }

};
