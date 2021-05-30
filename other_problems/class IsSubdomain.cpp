class IsSubdomain
{
public:
    IsSubdomain(std::string_view domainToCheck)
    : m_checkingDomain {std::move(domainToCheck)}
    {}
    bool operator()(const domain_t& subdomain)
    {

    }

private:
    std::string_view m_checkingDomain;
};

