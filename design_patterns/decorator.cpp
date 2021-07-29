
enum class Indentifications
{
    FirstName,
    LastName,
    Passport
};

using Identificaiton_t = std::map<Identifications, std::string>;

class Identification
{
public:
    virtual ~Identification() = default;
    virtual Identification_t GetIdentification() const = 0;
};

class PeopleIndentification : public Identification
{
public:
    PeopleIndentification(std::pair<std::string, std::string> name)
    : m_name {std::move(name)}
    {}
    Identification_t GetIdentification() const override
    {
        return {
            {Identifications::FirstName, m_name.first}, 
            {Identifications::LastName, m_name.second}
        };
    }
};

class Passport
{
public:
    Passport(std::string series, std::string number)
    : m_series{std::move(series)}
    , m_number{std::move(number)}
    {
    }
    
    std::string GetSeries() const
    {
        return m_series;
    }
    
    std::string GetNumber() const
    {
        return m_number;
    }
private:
    std::string m_series;
    std::string m_number;
};

class PeopleIndentificationWithPassportData : public Identification
{
public:
    PeopleIndentificationWithPassportData(Indentification &id, Passport passport )
    : m_rId {id}
    , m_passport {std::move(passport)}
    {
    }
    
    Identification_t GetIdentification() const override
    {
        auto id = m_rId.GetIdentification();
        id.emplace({Identifications::Passport, m_passport.GetSeries() + m_passport.GetNumber()});
        return id;
    }
private:
    Indentification &m_rId;
    Passport m_passport;
};