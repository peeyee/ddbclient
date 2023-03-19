#include  <boost/program_options.hpp>

class ParseOptions
{
    private:
        variables_map vm_;
    public:
        variables_map parse(int argc, char* argv[]);
        ParseOptions();
        ~ParsOptions() override;
}
    
    