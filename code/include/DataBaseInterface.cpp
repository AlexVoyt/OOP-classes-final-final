class Config
{
    // stub class
    u32 some_settings;

    public:
    Config(u32 _some_settings = 0) // let 0 be default settings
    {
        some_settings = _some_settings;
    }
};

class DatabaseInterface
{
    public:
    virtual Info Get_Some_Info(u32 id) = 0;
    virtual void Set_Some_Info(u32 id, Info data) = 0;
    virtual void Configure_Database(Config _conf) = 0;
    virtual u32 Get_Size() = 0;
};

class Database : public DatabaseInterface
{
    std::vector<Info> table_with_info;
    Config conf;

    public:
    Info Get_Some_Info(u32 id)
    {
        std::cout << "Yeah, some very slow GET query is happening" << std::endl;
        return table_with_info[id];
    }

    void Set_Some_Info(u32 id, Info data)
    {
        std::cout << "Yeah, some very slow SET query is happening" << std::endl;
        table_with_info[id] = data;
    }

    void Configure_Database(Config _conf)
    {
        std::cout << "Some difficult logic is happening here, don't worry" << std::endl;
        conf = _conf;
    }

    u32 Get_Size()
    {
        return table_with_info.size();
    }

    Config Get_Conf()
    {
        return conf;
    }

    //just some random fill
    Database()
    {
        constexpr u32 stub_var = 100;
        table_with_info.reserve(stub_var);

        for(u32 i = 0; i < stub_var; i++)
        {
            // NOTE: lets assume we only have 10 different types of flyweights
            table_with_info.push_back(Info((rand() % 500), (rand() % 100), (rand() % 256)));
        }
    }

    // NOTE: dev function for checking if flyweights are working
#if 0
    u32 Calc_Space()
    {
        bool is_checked
    }
#endif

};

class ProxyDatabaseWithProtection : public DatabaseInterface
{
    bool is_cached = 0;
    Info cached_info;
    u32 cached_id;
    Database* db;

    public:
    ProxyDatabaseWithProtection(Database* _db = nullptr)
    {
        if(_db == nullptr)
        {
            db = new Database();
        }
        else
        {
            db = _db;
        }
    }


    Info Get_Some_Info(u32 id)
    {
        if(is_cached && cached_id == id)
        {
            std::cout << "Ha-ha, no query - here is your cached object" << std::endl;
        }
        else
        {
            std::cout << "Argh, not the right object - but, lets put that object into cache! Maybe we get lucky next time!" << std::endl;
            std::cout << "But first lets check that index!" << std::endl;
            if(id < Get_Size())
            {
                cached_info = db->Get_Some_Info(id);
                cached_id = id;
                is_cached = true;
            }
            else
            {
                //TODO: i dont know;
                std::cout << "Proxy database protection!" << std::endl;
                // throw "somethin";
            }
        }

        return cached_info;
    }


    void Set_Some_Info(u32 id, Info data)
    {
        std::cout << "Resetting cache!" << std::endl;
        is_cached = false;
        std::cout << "And check that id!" << std::endl;
        if(id < Get_Size())
        {
            db->Set_Some_Info(id, data);
        }
        else
        {
            //TODO: i dont know;
            std::cout << "Proxy database protection!" << std::endl;
            // throw "somethin";
        }
    }

    u32 Get_Size()
    {
        return db->Get_Size();
    }

    Config Get_Conf()
    {
        return db->Get_Conf();
    }

    void Configure_Database(Config conf)
    {
        std::cout << "Just delegating work to actual db!" << std::endl;
        db->Configure_Database(conf);

    }
};
