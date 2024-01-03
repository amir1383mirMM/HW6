#include "Input.h"
#include "DataBase.h"
#include <typeinfo>

int main()
{
    Input input;
    Data_base data_base();


    while (input.set())
    {
        try
        {
            data_base.manage_command(input.command_(), input.value_());
        }
        catch (runtime_error& ex)
        {
            cout << ex.what() << '\n';
        }
        input.clear();
    }

}