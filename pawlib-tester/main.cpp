#include <iostream>
#include <iochannel.hpp>
#include <pawstring.hpp>
#include <stdutils.hpp>
#include <goldilocks.hpp>
#include <stdutils.hpp>
#include <sigc++/signal.h>
#include <sigc++/trackable.h>

using pawlib::iochannel;

//Format enumerations.
using namespace pawlib::ioformat;
using namespace pawlib;
using namespace std;


void print(std::string msg, IOFormatVerbosity vrb, IOFormatCategory cat)
{
    //std::cout << msg;
}

int main()
{
    //This has to live here because evil.
    ioc.signal_all.connect(sigc::ptr_fun(print));
    ioc << ta_bold << fg_blue << "===== PawLIB Tester =====\n" << io_end;

    //Test code goes here.

    return 0;
}

//Temporary storage for Pawstring test.
int pawstringtest()
{
    const char* test = "走dðnde?¶";
    PawString<8> bat(test);
    cout<< bat <<endl;
    PawString<16> jokes = test;
    cout << jokes <<endl;
    if(bat == jokes)
        cout<<"The two are equal" <<endl;
    else
        cout<<"The two are not equal" <<endl;

    if(bat == "走dðnde?¶")
        cout<<"The two are equal" <<endl;
    else
        cout<<"The two are not equal" <<endl;
    bat.append('S');
    jokes.append('S');
    if(bat == jokes)
        cout<<"The two are equal" <<endl;
    else
        cout<<"The two are not equal" <<endl;
    cout << jokes <<endl;
    jokes.pop_back();
    jokes.append(bat);
    cout << jokes <<endl;

    PawString<2048> quote = "    \xF0\x9F\x90\xA6\n\
    Then methought the air grew denser, perfumed from an unseen censer\n\
    Swung by Seraphim whose footfalls tinkled on the tufted floor.\n\
    \"Wretch,\" I cried, \"thy God hath lent thee- by these angels he hath sent thee\n\
    Respite- respite and nepenthe, from thy memories of Lenore!\n\
    Quaff, oh quaff this kind nepenthe and forget this lost Lenore!\"\n\
    Quoth the Raven, \"Nevermore.\"\n\n\
    \"Prophet!\" said I, \"thing of evil! - prophet still, if bird or devil!\n\
    Whether Tempter sent, or whether tempest tossed thee here ashore,\n\
    Desolate yet all undaunted, on this desert land enchanted-\n\
    On this home by Horror haunted- tell me truly, I implore-\n\
    Is there- is there balm in Gilead?- tell me- tell me, I implore!\"\n\
    Quoth the Raven, \"Nevermore.\"\n\n\
    \"Prophet!\" said I, \"thing of evil! - prophet still, if bird or devil!\n\
    By that Heaven that bends above us- by that God we both adore-\n\
    Tell this soul with sorrow laden if, within the distant Aidenn,\n\
    It shall clasp a sainted maiden whom the angels name Lenore-\n\
    Clasp a rare and radiant maiden whom the angels name Lenore.\"\n\
    Quoth the Raven, \"Nevermore.\"\n\n\
    \"Be that word our sign in parting, bird or fiend\", I shrieked, upstarting-\n\
    \"Get thee back into the tempest and the Night's Plutonian shore!\"\n\
    Leave no black plume as a token of that lie thy soul hath spoken!\n\
    Leave my loneliness unbroken!- quit the bust above my door!\n\
    Take thy beak from out my heart, and take thy form from off my door!\"\n\
    Quoth the Raven, \"Nevermore.\"\n \n\
    And the Raven, never flitting, still is sitting, still is sitting\n\
    On the pallid bust of Pallas just above my chamber door;\n\
    And his eyes have all the seeming of a demon's that is dreaming,\n\
    And the lamp-light o'er him streaming throws his shadow on the floor;\n\
    And my soul from out that shadow that lies floating on the floor \n\
    Shall be lifted- nevermore!\n    \xF0\x9F\x90\xA6";

    cout << quote <<endl;
    cout << "That quote was: " << quote.size() << " characters long" << endl;


    // Test addition
    PawString<8> second = "co";
    PawString<16> third = "tt";
    PawString<8> fourth = "y";
    PawString<256> result = 'S' + second + third + 'T' + "a" + fourth;
    cout << result <<endl;
    cout << "Show that the values were not altered : " <<endl;
    cout << second << "\n" << third << "\n" << fourth << "\n" <<endl;

    // Interesting note. The "space" in the below character is actually part of the period.
    PawString<32> chinese = "我的名字是斯科特。我是蝙蝠侠";
    cout<< chinese.size() <<endl;
    cout<< chinese <<endl;
    for(int i =0; i < chinese.size(); i++)
        cout<<chinese[i] <<endl;;

    // < and <=
    bat = "走bð";
    cout<< "bat is: " << bat <<endl;
    cout<< bat.size() <<endl;
    jokes = "走dð";
    cout<< "jokes is: "<< jokes <<endl;
    if(bat < jokes)
        cout<< "bat is less than jokes." <<endl;
    else
        cout<< "bat is not less than jokes." <<endl;

    cout<<"Swap the 'b' for the 'd' and check again" <<endl;
    bat[1] = 'd';
    if(bat < jokes)
        cout<< "bat is less than jokes." <<endl;
    else
        cout<< "bat is not less than jokes." <<endl;

    if(bat <= jokes)
        cout<< "bat is less than or equal to jokes." <<endl;
    else
        cout<< "jokes is greater than bat." <<endl;

    // > and >=
    PawString<8> test1 = 'a';
    PawString<8> test2 = 'A';
    if(test1 > test2)
        cout<< "'a' is greater than 'A'" <<endl;
    else
        cout<< "'a' is not greater than 'A'"<<endl;
    test1 = 'A';
    if(test1 > test2)
        cout<< "'A' is greater than 'A'" <<endl;
    else
        cout<< "'A' is not greater than 'A'"<<endl;
    if(test1 >= test2)
        cout<< "'A' is greater than or equal to 'A'" <<endl;
    else
        cout<< "'A' is less than 'A'"<<endl;


    //Input
    PawString<64> input;
    cout<< "Enter your PawString<64>" <<endl;
    cin>> input;
    cout<< input <<endl;

    PawString<16> ostr = "ful";
    cout << ostr <<endl;
    cout<< "Original Size: " << ostr.size() <<endl;
    ostr.insert(0, "beti");
    cout << ostr <<endl;
    cout<< "New Size: " << ostr.size() <<endl;
    ostr.insert(2, "a");
    cout << ostr <<endl;
    cout<< "New Size: " << ostr.size() <<endl;
    ostr.insert(3, 'u');
    cout << ostr <<endl;
    cout<< "New Size: " << ostr.size() <<endl;

    PawString<8> full = "Nobody";
    PawString<16> sub1 = full.substr(0, 2);
    PawString<32> sub2 = full.substr(2, 3);
    PawString<64> sub3 = full.substr(2);

    cout<< "Original: " << full <<endl;
    cout<< "Sub1: " << sub1 <<endl;
    cout<< "Sub2: " << sub2 <<endl;
    cout<< "Sub3: " << sub3 <<endl;

    PawString<8> swap1 = "Mouse";
    PawString<8> swap2 = "Paw";
    swap1.swap(swap2);
    cout << swap1 <<endl;
    cout << swap2 <<endl;

    // max_size, clear, and empty
    PawString<128> clearStr = "IShallEnd";
    cout << "The string is : " << clearStr <<endl;
    if(! clearStr.empty())
        cout << "The String is not empty" <<endl;
    cout << "Max Size is: " << clearStr.max_size() <<endl;
    cout << "Clear the string" <<endl;
    clearStr.clear();
    cout << "The string is : " << endl;
    if(clearStr.empty())
        cout << "The String is empty" <<endl;


    PawString<16> emoji1 = "\xF0\x9F\x98\xB1";
    cout<< emoji1 <<endl;
    PawString<16> emoji2 = "\xF0\x9F\x98\xA2";
    cout<< emoji2 <<endl;
    cout<< (emoji2 < emoji1)<<endl;
}
