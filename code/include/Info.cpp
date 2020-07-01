class InfoFlyweight
{
    u8 type; // we can determine what
    u32 huge_data[100000] = {0};

    public:
    InfoFlyweight(u8 _type)
    {
        type = _type;
        huge_data[0] = _type; // just for example
    }
};

class InfoFlyweightFactory
{
    static InfoFlyweight* collection[256];
    static bool states[256];

    public:
    static InfoFlyweight* Get_Flyweight(u8 type)
    {
        if(states[type] == false)
        {
            states[type] = true;
            collection[type] = new InfoFlyweight(type);
        }
        return collection[type];
    }

    //NOTE: dev function for checking if flyweight are working
    static void Flyweight_Count()
    {
        u32 counter = 0;
        for(u32 i = 0; i < 256; i++)
        {
            if(states[i] == true)
                counter++;
        }
        std::cout << counter << std::endl;
    }
};

InfoFlyweight* InfoFlyweightFactory::collection[256] = {0};
bool InfoFlyweightFactory::states[256] = {0};

class Info
{
    u32 some_data;
    u16 another_data;
    // pointer to data that is common across multiple info objets
    InfoFlyweight* flyweight;

    public:
    Info() = default;
    Info(u32 _data, u16 _another, u8 _f_type)
    {
        some_data = _data;
        another_data = _another;
        flyweight = InfoFlyweightFactory::Get_Flyweight(_f_type);
    }
};
