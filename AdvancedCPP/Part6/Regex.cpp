#include <regex>
#include <iostream>
#include <string>

int email() {

    std::cout << std::endl;

    std::string emailDescription = "Email addresses, such as rainer@grimm_jaud.de, have two parts.";

    // regular expression for the email address
    std::string regExprStr(R"((\w+(\.|_)?\w*)@(\w+(\.\w+)+))");

    // regular expression holder
    std::regex rgx(regExprStr);

    // search result holder
    std::smatch smatch;

    // looking for a partial match
    if (std::regex_search(emailDescription, smatch, rgx)) {

        std::cout << "Text: " << emailDescription << std::endl;

        std::cout << std::endl;

        std::cout << "Email address: " << smatch[0] << std::endl;
        std::cout << "Local part: " << smatch[1] << std::endl;
        std::cout << "Domain name: " << smatch[3] << std::endl;

        std::cout << std::endl;

        std::cout << "Text before the email address: " << smatch.prefix() << std::endl;
        std::cout << "Text after the email address: " << smatch.suffix() << std::endl;

    }

    std::cout << std::endl;
    return 0;
}


#include <regex>
#include <iomanip>
#include <iostream>
#include <string>

int replace() {

    std::cout << std::endl;

    std::string future{"Future"};
    int len = sizeof(future);

    std::string unofficialStandardName{"The unofficial name of the new C++ standard is C++0x."};
    std::cout << std::setw(len) << std::left << "Now: " << unofficialStandardName << std::endl;

    // replace C++0x with C++11
    std::regex rgxCpp(R"(C\+\+0x)");
    std::string newCppName{"C++11"};

    std::string newStandardName{std::regex_replace(unofficialStandardName, rgxCpp, newCppName)};
    std::cout << std::setw(len) << std::left << "Now: " << newStandardName << std::endl;

    // replace unofficial with official
    std::regex rgxOff{"unofficial"};
    std::string makeOfficial{"official"};

    std::string officialName{std::regex_replace(newStandardName, rgxOff, makeOfficial)};
    std::cout << std::setw(len) << std::left << "Future: " << officialName << std::endl;

    std::cout << std::endl;
    return 0;
}

// regex 3: TokenIterator

#include <regex>
#include <iostream>
#include <string>
#include <vector>

int regex() {

    std::cout << std::endl;

    // a few books
    std::string text{
            "Pete Becker,The C++ Standard Library Extensions,2006:Nicolai Josuttis,The C++ Standard Library,1999:Andrei Alexandrescu,Modern C++ Design,2001"};

    // regular expression for a book
    std::regex regBook(R"((\w+)\s(\w+),([\w\s\+]*),(\d{4}))");

    // get all books from text
    std::sregex_token_iterator bookItBegin(text.begin(), text.end(), regBook);
    const std::sregex_token_iterator bookItEnd;

    std::cout << "##### std::regex::match_results ######" << "\n\n";
    while (bookItBegin != bookItEnd) {
        std::cout << *bookItBegin++ << std::endl;
    }

    std::cout << "\n\n" << "##### last name, date of publication ######" << "\n\n";

    // get all last name and date of publication for the entries
    std::sregex_token_iterator bookItNameIssueBegin(text.begin(), text.end(), regBook, {{2, 4}});
    const std::sregex_token_iterator bookItNameIssueEnd;
    while (bookItNameIssueBegin != bookItNameIssueEnd) {
        std::cout << *bookItNameIssueBegin++ << ", ";
        std::cout << *bookItNameIssueBegin++ << std::endl;
    }

    // regular expression for a book, using negativ search
    std::regex regBookNeg(":");

    std::cout << "\n\n" << "##### get each entry, using negativ search  ######" << "\n\n";

    // get all entries, only using ":" as regular expression
    std::sregex_token_iterator bookItNegBegin(text.begin(), text.end(), regBookNeg, -1);
    const std::sregex_token_iterator bookItNegEnd;
    while (bookItNegBegin != bookItNegEnd) {
        std::cout << *bookItNegBegin++ << std::endl;
    }


    std::cout << std::endl;
    return 0;
}