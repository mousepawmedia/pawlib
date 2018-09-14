/*#include "pawlib/onestringbase.hpp"

namespace pawlib
{
    OneStringBase::OneStringBase():len(0)
    {
        MAX_SIZE = 4;
        master = new OneChar[MAX_SIZE];
        strType = QUICK_TYPE;
        double_size(strType);
    }

    OneStringBase::OneStringBase(bool type):len(0)
    {
        MAX_SIZE = 4;
        if(type == ONE_TYPE)
        {
            master = new OneChar[MAX_SIZE];
        }
        else
        {
            master = new OneChar[MAX_SIZE];
        }
        strType = type;
        double_size(strType);
    }

    OneStringBase::OneStringBase(char ch, bool type):len(0)
    {
        MAX_SIZE = 4;
        if(type == ONE_TYPE)
        {
            master = new OneChar[MAX_SIZE];
        }
        else
        {
            master = new OneChar[MAX_SIZE];
        }
        strType = type;
        double_size(strType);
        master[len].addDirectly(ch, 0);

        if(type == ONE_TYPE)
        {
            master[len].addDirectly('\0', 0);;
        }
        len = 1;
    }

    OneStringBase::OneStringBase(const OneChar& ch, bool type):len(0)
    {
        MAX_SIZE = 4;

        if(type == ONE_TYPE)
        {
            master = new OneChar[MAX_SIZE];
        }
        else
        {
            master = new OneChar[MAX_SIZE];
        }
        strType = type;
        double_size(strType);
        master[len] = ch;
        len = 1;
    }

    OneStringBase::OneStringBase(const OneStringBase& ostr, bool type):len(0)
    {
        MAX_SIZE = ostr.MAX_SIZE;

        if(type == ONE_TYPE)
        {
            master  = new OneChar[MAX_SIZE];
        }
        else
        {
            master = new OneChar[MAX_SIZE];
        }
        strType = type;
        double_size(strType);
        int i = 0;

        while((i < ostr.size()) && (i < MAX_SIZE))
        {
            //Where the issue is!!!!!!!!!
            master[i] = ostr[i];
            ++i;
        }
        len = i;
    }

    OneStringBase::OneStringBase(OneStringBase& ostr, bool type):len(0)
    {
        this->MAX_SIZE = ostr.max_size();
        if(type == ONE_TYPE)
        {
            this->master = new OneChar[MAX_SIZE];
        }
        else
        {
            this->master = new OneChar[MAX_SIZE];
        }
//        while(ostr.size() >= MAX_SIZE)
//        {
//            double_size(type);
//        }
        this->strType = type;
        for(int i = 0; i < ostr.size(); ++i)
        {
            //this->master[i] = ostr[i];
            this->append(ostr[i]);
        }
    }

    void OneStringBase::double_size(bool strType)
    {
        MAX_SIZE *= 2;
        OneChar* temp;

        if(strType == ONE_TYPE)
        {
            temp = new OneChar[MAX_SIZE];
        }
        else
        {
            temp = new OneChar[MAX_SIZE];
        }

        if(master != nullptr && temp != nullptr)
        {
            for(int i = 0; i < len; ++i)
            {
                //deleting object of abstract class type OneChar which has
                //non-virtual destructor which will cause undefined behavior
                temp[i] = master[i];
            }

            delete [] master;
        }

        master = temp;
    }

    bool OneStringBase::getType() const
    {
        return strType;
    }

    int OneStringBase::size() const
    {
        return len;
    }

    void OneStringBase::incLen()
    {
        ++len;
    }

    void OneStringBase::setLen(int newLen)
    {
        len = newLen;
    }

    OneChar& OneStringBase::at(int pos)
    {
        if((pos < len) && (pos >= 0))
            return (master[pos]);
        else
        {
            ioc << cat_error << ta_bold << fg_red <<
            "OneString Error: Index out of bound" << io_end;
            return (master[len - 1]);
        }
    }

    bool OneStringBase::equals(const OneStringBase& ostr) const
    {
        if(len == ostr.size())
        {
            for(int i = 0; i < len; ++i)
            {
                if(!(ostr[i] == master[i]))
                    return false;
            }
            return true;
        }
        return false;
    }

    bool OneStringBase::equals(std::string ostr) const
    {
        return equals(ostr.c_str());
    }

    //append functions

    void OneStringBase::append(const OneStringBase& ostr)
    {
        //if appending makes size go out of bound, double the size
        if(len + ostr.size() > MAX_SIZE)
            double_size(strType);

        else
        {
            for(int i = 0; i < ostr.size(); ++i)
            {
                master[len] = ostr[i];
                ++len;
            }
        }
    }

    void OneStringBase::append(std::string ostr)
    {
        append(ostr.c_str());
    }

    void OneStringBase::append(char ochar)
    {
        if(len >= MAX_SIZE)
            double_size(strType);
        master[len].addDirectly(ochar, 0);

        if(strType == ONE_TYPE)
        {
            master[len].addDirectly('\0', 1);
        }
        ++len;
    }

    void OneStringBase::append(const OneChar& ochar)
    {
        if(len >= MAX_SIZE)
        {
            double_size(strType);
        }
        master[len] = ochar;
        ++len;
    }

    //insert functions

    void OneStringBase::insert(int pos, const OneStringBase& ostr)
    {
        int insertSize = ostr.size();

        if(pos < 0 || pos > len)
        {
            ioc << cat_error << ta_bold << fg_red <<
            "OneStringBase Error: Index out of Bounds" << io_end;
            return;
        }

        if(pos >= MAX_SIZE || (len + insertSize > MAX_SIZE))
        {
            double_size(strType);
        }

        if(pos != len)
        {
            for(int i = len - 1; i >= pos; --i)
            {
                master[i + insertSize] = master[i];
            }
        }
        for(int off = 0; off < insertSize; ++off)
        {
            //invalid conversion from OneChar* to char
//            master[pos + off] = ostr[off];
        }
        len += ostr.size();
    }

    void OneStringBase::insert(int pos, std::string ostr)
    {
        insert(pos, ostr.c_str());
    }

    void OneStringBase::insert(int pos, char ochar)
    {
        if(len == MAX_SIZE)
        {
            double_size(strType);
        }
        for(int i = len - 1; i >= pos; --i)
        {
            master[i + 1] = master[i];
        }

        master[pos].addDirectly(ochar, 0);

        if(strType == ONE_TYPE)
        {
            master[pos].addDirectly('\0', 1);
        }
        len++;
    }

    void OneStringBase::insert(int pos, OneChar* ochar)
    {
        if(len == MAX_SIZE)
            double_size(strType);

        if(pos < 0 || pos > len)
        {
            ioc << cat_error << ta_bold << fg_red <<
            "OneStringBase Error: Index out of Bounds" << io_end;
            return;
        }

        for(int i = len - 1; i >= pos; --i)
        {
            master[i + 1] = master[i];
        }

        master[pos] = *ochar;
        ++len;
    }

    void OneStringBase::push_back(char ch)
    {
        append(ch);
    }

    void OneStringBase::push_back(const OneChar& ochar)
    {
        append(ochar);
    }

    void OneStringBase::pop_back()
    {
        if(len == 0)
        {
            ioc << cat_error << ta_bold << fg_red <<
            "OneString Error: Can't POP and empty OneString" << io_end;
        }
        else
        {
            master[len - 1] = '\0';
            --len;
        }
    }

    int OneStringBase::length()
    {
        if(strType == QUICK_TYPE)
            return MAX_SIZE;
        else
        {
            return (MAX_SIZE * 5);
        }
    }

    int OneStringBase::max_size()
    {
        return MAX_SIZE;
    }

    bool OneStringBase::empty() const
    {
        return (len == 0);
    }

    void OneStringBase::clear()
    {
        for(int i = 0; i < len; ++i)
            master[i] = '\0';
        len = 0;
    }

    OneChar OneStringBase::operator[](int pos) const
    {
        if((pos < len) && (pos >= 0))
        {
            //cannot convert OneChar to OneChar* in return
            return master[pos];
        }
        else
        {
            ioc << cat_error << ta_bold << fg_red <<
            "OneString Error : INDEX OUT OF BOUNDS" << io_end;
            //Same as above
            return master[len - 1];
        }
    }

    OneChar& OneStringBase::operator[](int pos)
    {
        if((pos < len) && (pos >= 0))
        {
            return master[pos];
        }
        else
        {
            ioc << cat_error << ta_bold << fg_red <<
            "OneString Error : IDEX OUT OF BOUNDS" << io_end;
            return master[len - 1];
        }
    }

    OneStringBase& OneStringBase::operator=(const OneStringBase& newostr)
    {
        strType = newostr.getType();
        int i = 0;

        while((i < newostr.size()) && (0 <= MAX_SIZE))
        {
            master[i] = newostr[i];
            ++i;
        }
        len = i;
        return *this;
    }

    OneStringBase& OneStringBase::operator=(const char* str)
    {
        *this = assignHelper(str);
        return *this;
    }

    OneStringBase& OneStringBase::operator=(std::string str)
    {
        *this = str.c_str();
        return *this;
    }

    OneStringBase& OneStringBase::operator=(char ch)
    {
        *this = assignChar(ch);
        return *this;
    }

    OneStringBase& OneStringBase::operator=(OneChar* ch)
    {
        this->master[0] = *ch;
        this->len = 1;
        return *this;
    }

    bool OneStringBase::operator==(const OneStringBase& ostr2)
    {
        return equals(ostr2);
    }

    bool OneStringBase::operator==(const char* ostr2)
    {
        return equals(ostr2);
    }

    bool OneStringBase::operator==(std::string ostr2)
    {
        return equals(ostr2);
    }

    bool OneStringBase::operator<(const OneStringBase& ostr2)
    {
        return lessThanStr(ostr2);
    }

    bool OneStringBase::operator<(const char* ostr2)
    {
        return lessThanCharP(ostr2);
    }

    bool OneStringBase::operator<(std::string ostr2)
    {
        return lessThanCharP(ostr2.c_str());
    }

    bool OneStringBase::operator<=(const OneStringBase& ostr2)
    {
        return (((*this) < ostr2) || ((*this) == ostr2));
    }

    bool OneStringBase::operator<=(const char* ostr2)
    {
        return (((*this) < ostr2)|| ((*this) == ostr2));
    }

    bool OneStringBase::operator<=(std::string ostr2)
    {
        return (((*this) < ostr2)|| ((*this) == ostr2));
    }

    bool OneStringBase::operator>(const OneStringBase& ostr2)
    {
        return(!((*this) <= ostr2));
    }

    bool OneStringBase::operator>(const char* ostr2)
    {
        return(!((*this) <= ostr2));
    }

    bool OneStringBase::operator>(std::string ostr2)
    {
        return(!((*this) <= ostr2));
    }

    bool OneStringBase::operator>=(const OneStringBase& ostr2)
    {
        return(!((*this) < ostr2));
    }

    bool OneStringBase::operator>=(const char* ostr2)
    {
        return(!((*this) < ostr2));
    }

    bool OneStringBase::operator>=(std::string ostr2)
    {
        return(!((*this) < ostr2));
    }

    void OneStringBase::operator+=(const OneStringBase& ostr2)
    {
        append(ostr2);
    }

    void OneStringBase::operator+=(const char* ostr2)
    {
        append(ostr2);
    }

    void OneStringBase::operator+=(std::string ostr2)
    {
        append(ostr2);
    }

    void OneStringBase::operator+=(char ochar)
    {
        append(ochar);
    }

    void OneStringBase::operator+=(const OneChar& ochar)
    {
        append(ochar);
    }
}
*/
